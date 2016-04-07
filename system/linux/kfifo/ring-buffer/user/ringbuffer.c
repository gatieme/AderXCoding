/**
 * Title 	: ringbuffer.c
 * Author	: zengxianbo 
 * Date		: 2014.11 @Beijing
 * Description 	: implement an ring buffer just like kfifo. Please note that
 * the data in the buffer will keep there until them be read out. If the buffer
 * is full, the data could not be put into any more, until the read action free
 * some space. 
 *
 * NOTE: This version used for user space.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "ringbuffer.h"

static inline __attribute__((const))
int is_power_of_2(unsigned long n)
{
	return (n != 0 && ((n & (n - 1)) == 0));
}

struct ringbuffer *ringbuffer_create(unsigned int size)
{
	struct ringbuffer *ring_buf;

	if (!is_power_of_2(size)) {
		printf("The buffer size is must be power of 2!\n");
		errno = EINVAL;
		return NULL;
	}

	ring_buf = malloc(sizeof(*ring_buf));
	if (!ring_buf) {
		perror("malloc()");
		return NULL;
	}

	ring_buf->data = malloc(size);
	if (!ring_buf->data) {
		perror("malloc()");
		free(ring_buf);
		return NULL;
	}

	ring_buf->size = size;
	ring_buf->read_pos = 0;
	ring_buf->write_pos = 0;

	return ring_buf;
}

void ringbuffer_destroy(struct ringbuffer *ring_buf)
{
	if (ring_buf) {
		if (ring_buf->data) {
			free(ring_buf->data);
			ring_buf->data = NULL;
		}
		free(ring_buf);
		ring_buf = NULL;
	}
}

/**
 * ringbuffer_put - puts some data into the ringbuffer, no locking version
 * @ring_buf: the ringbuffer to be used.
 * @buffer: the data to be added.
 * @len: the length of the data to be added.
 *
 * This function copies at most @len bytes from the @buffer into
 * the ringbuffer depending on the free space, and returns the number of
 * bytes copied.
 *
 * Note that with only one concurrent reader and one concurrent
 * writer, you don't need extra locking to use these functions.
 */

unsigned int ringbuffer_put(struct ringbuffer *ring_buf,   
		const char *buffer, unsigned int len)   
{   
	unsigned int l;   

	len = min(len, ring_buf->size - ring_buf->write_pos + ring_buf->read_pos);   

	/* first put the data starting from write_pos to buffer end */   
	l = min(len, ring_buf->size - (ring_buf->write_pos & (ring_buf->size - 1)));   
	memcpy(ring_buf->data + (ring_buf->write_pos & (ring_buf->size - 1)), buffer, l);   

	/* then put the rest (if any) at the beginning of the buffer */   
	memcpy(ring_buf->data, buffer + l, len - l);

	ring_buf->write_pos += len;   

	return len;   
}  

/**
 *  ringbuffer_print - print ringbuf data
 *  @ring_buf: the ringbuffer to be used.
 *  @cnt : the number byte to be print.
 */
void ringbuffer_print(struct ringbuffer *ring_buf, unsigned int cnt)
{
	return;
}

/**
 *  ringbuffer_from_dev - read data from device, and put them into ringbuffer
 *  @fd: file descriptor of device
 *  @ring_buf: the ringbuffer to be used.
 *  @len: the length of the data to be read.
 */
ssize_t ringbuffer_from_dev(int fd, struct ringbuffer *ring_buf, unsigned int len)
{
	unsigned int l;   
	ssize_t ret, total;

	total = 0;

	len = min(len, ring_buf->size - ring_buf->write_pos + ring_buf->read_pos); 

	/* first put the data starting from write_pos to buffer end */   
	l = min(len, ring_buf->size - (ring_buf->write_pos & (ring_buf->size - 1)));   
	
	ret = read(fd, ring_buf->data + (ring_buf->write_pos & (ring_buf->size - 1)), l);
	if (ret < 0) {
		return ret;
	}

	total = ret;

	if (total < l) {
		ring_buf->write_pos += total;   

		return total;
	}

	if (len -l) {
		ret = read(fd, ring_buf->data, len - l);
		if (ret < 0) {
			return ret;
		}
		
		total += ret;
	}

	ring_buf->write_pos += total;   

	return total;   
}


/**
 *  ringbuffer_get - gets some data from the ringbuffer, no locking version
 *  @ring_buf: the ringbuffer to be used.
 *  @buffer: where the data must be copied.
 *  @len: the size of the destination buffer.
 * 
 *  This function copies at most @len bytes from the ringbuffer into the
 *  @buffer and returns the number of copied bytes.
 * 
 *  Note that with only one concurrent reader and one concurrent
 *  writer, you don't need extra locking to use these functions.
 */
unsigned int ringbuffer_get(struct ringbuffer *ring_buf,
		char *buffer, unsigned int len)
{
	unsigned int l;

	len = min(len, ring_buf->write_pos - ring_buf->read_pos);

	/* first get the data from ring_buf->read_pos until the end of the buffer */
	l = min(len, ring_buf->size - (ring_buf->read_pos & (ring_buf->size - 1)));
	memcpy(buffer, ring_buf->data + (ring_buf->read_pos & (ring_buf->size - 1)), l);

	/* then get the rest (if any) from the beginning of the buffer */
	memcpy(buffer + l, ring_buf->data, len - l);

	ring_buf->read_pos += len;

	return len;
}

/* FIXME: just for connection, as use "send()", for details, man 2 send */
unsigned int ringbuffer_to_socket(int socket_fd, struct ringbuffer *ring_buf, unsigned int len)
{
	unsigned int l;
	unsigned int send_num;

	len = min(len, ring_buf->write_pos - ring_buf->read_pos);

	l = min(len, ring_buf->size - (ring_buf->read_pos & (ring_buf->size - 1)));

	send_num = send(socket_fd, ring_buf->data + (ring_buf->read_pos & (ring_buf->size - 1)), l, 0); 
	if (send_num < 0){ 
		perror("send()");
		exit(1);
	}

	if (len - l) {
		send_num = send(socket_fd, ring_buf->data, len - l, 0); 
		if (send_num < 0){ 
			perror("send()");
			exit(1);
		}
	}
	ring_buf->read_pos += len;

	return len;
}


/**
 * ringbuffer_reset - removes the entire ringbuffer content
 * @ring_buf: address of the ringbuffer to be used
 *
 * Note: usage of ringbuffer_reset() is dangerous. It should be only called when the
 * ringbuffer is exclusived locked or when it is secured that no other thread is
 * accessing the fifo.
 */
void ringbuffer_reset(struct ringbuffer *ring_buf)
{
	ring_buf->write_pos = ring_buf->read_pos = 0;
}

unsigned int ringbuffer_is_empty(struct ringbuffer *ring_buf)
{
	return ring_buf->read_pos == ring_buf->write_pos;
}

unsigned int ringbuffer_is_full(struct ringbuffer *ring_buf)
{
	return ring_buf->size == ring_buf->write_pos -  ring_buf->read_pos;
}

unsigned int ringbuffer_len(struct ringbuffer *ring_buf)
{
	return ring_buf->write_pos -  ring_buf->read_pos;
}

unsigned int ringbuffer_space_left(struct ringbuffer *ring_buf)
{
	return ring_buf->size - ring_buf->write_pos + ring_buf->read_pos;
}


