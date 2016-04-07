/**
 * Title 	: ringbuffer.c
 * Author	: zengxianbo 
 * Date		: 2014.11 @Beijing
 * Description 	: implement an ring buffer just like kfifo. Please note that
 * the data in the buffer will keep there until them be read out. If the buffer
 * is full, the data could not be put into any more, until the read action free
 * some space.  
 */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/log2.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/string.h>
#include <linux/uaccess.h>

#include "ringbuffer.h"

struct ringbuffer *ringbuffer_create(unsigned int size, gfp_t gfp_mask)
{
	unsigned int order;
	struct ringbuffer *ring_buf;
/* round up to the next power of 2, so that we can use 
 * "buf->write_pos & (buf->size – 1) instead of "buf->write_pos % buf->size"
 */
	if (!is_power_of_2(size)) {
		BUG_ON(size > 0x80000000);   
		size = roundup_pow_of_two(size);   
	}
	
	order = order_base_2(size / PAGE_SIZE);

	if (order > MAX_ORDER) {
		pr_err("[%s:] The memory size request too big!\n", __func__);
		return ERR_PTR(-EINVAL); 
	}

	ring_buf = kmalloc(sizeof(*ring_buf), gfp_mask);
	if (!ring_buf) {
		return ERR_PTR(-ENOMEM);
	}

	ring_buf->data = (void *)__get_free_pages(gfp_mask, order);
	if (!ring_buf->data) {
		kfree(ring_buf);
		return ERR_PTR(-ENOMEM);
	}

	ring_buf->size = size;
	ring_buf->read_pos = 0;
	ring_buf->write_pos = 0;

	return ring_buf;
}

void ringbuffer_destroy(struct ringbuffer *ring_buf)
{
	free_pages((unsigned long)ring_buf->data, 
			order_base_2(ring_buf->size / PAGE_SIZE));
	ring_buf->data = NULL;
	kfree(ring_buf);
	ring_buf = NULL;
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
		const unsigned char *buffer, unsigned int len)   
{   
	unsigned int l;   

	len = min(len, ring_buf->size - ring_buf->write_pos + ring_buf->read_pos);   

	/*  
	 * Ensure that we sample the read_pos  before we  
	 * start putting bytes into the ring_buf.  
	 */   

	smp_mb();   

	/* first put the data starting from write_pos to buffer end */   
	l = min(len, ring_buf->size - (ring_buf->write_pos & (ring_buf->size - 1)));   
	memcpy(ring_buf->data + (ring_buf->write_pos & (ring_buf->size - 1)), buffer, l);   
	/* then put the rest (if any) at the beginning of the buffer */   
	memcpy(ring_buf->data, buffer + l, len - l);
	/*  
	 * Ensure that we add the bytes to the ring_buf -before-  
	 * we update the ring_buf->write_pos index.  
	 */   
	smp_wmb();   

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
	print_hex_dump(KERN_DEBUG, "", 
			DUMP_PREFIX_ADDRESS,
			32, 4, 
			ring_buf->data + ring_buf->read_pos, 
			cnt, 
			true);
	pr_debug("\n");	
}

/**
 *  ringbuffer_fromio - get the data from io memory, and put them into ringbuffer
 *  @ring_buf: the ringbuffer to be used.
 *  @source: the io memory addr.
 *  @len: the length of the data to be read and write.
 */
unsigned int ringbuffer_fromio(struct ringbuffer *ring_buf, void *source, unsigned int len)
{
	unsigned int l, i;   

	len = min(len, ring_buf->size - ring_buf->write_pos + ring_buf->read_pos); 

	/*  
	 * Ensure that we sample the read_pos  before we  
	 * start putting bytes into the ring_buf.  
	 */   

	smp_mb(); 

	l = min(len, ring_buf->size - (ring_buf->write_pos & (ring_buf->size - 1)));   

	/* first put the data starting from write_pos to buffer end */   
	//memcpy_fromio(ring_buf->data + (ring_buf->write_pos & (ring_buf->size - 1)), source, l);   
	/* FIXME: it seems that ioread32_rep source address do not increaced automaticly */
	for (i = 0; i < l % 4; ++i) {
		ioread8_rep(source + i, ring_buf->data + (ring_buf->write_pos & (ring_buf->size - 1)) + i, 1);
	}

	for (; i < l; i += 4) {
		ioread32_rep(source + i, ring_buf->data + (ring_buf->write_pos & (ring_buf->size - 1)) + i, 1);
	}
	/* then put the rest (if any) at the beginning of the buffer */   
	//memcpy_fromio(ring_buf->data, source + l, len - l);
	for (i = 0; i < (len -l) % 4; ++i) {
		ioread8_rep(source + l + i, ring_buf->data + i, 1);
	}
	for (; i < len -l; i += 4) {
		ioread32_rep(source + l + i, ring_buf->data + i, 1);
	}
	/*  
	 * Ensure that we add the bytes to the ring_buf -before-  
	 * we update the ring_buf->write_pos index.  
	 */   
	smp_wmb();   

	ring_buf->write_pos += len;   

	return len;   
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
		unsigned char *buffer, unsigned int len)
{
	unsigned int l;

	len = min(len, ringbuffer_len(ring_buf));

	/*
	 * Ensure that we sample the ring_buf->write_pos index -before- we
	 * start removing bytes from the kring_buf.
	 */

	smp_rmb();

	/* first get the data from ring_buf->read_pos until the end of the buffer */
	l = min(len, ring_buf->size - (ring_buf->read_pos & (ring_buf->size - 1)));
	memcpy(buffer, ring_buf->data + (ring_buf->read_pos & (ring_buf->size - 1)), l);

	/* then get the rest (if any) from the beginning of the buffer */
	memcpy(buffer + l, ring_buf->data, len - l);

	/*
	 * Ensure that we remove the bytes from the kring_buf -before-
	 * we update the ring_buf->read_pos index.
	 */

	smp_mb();

	ring_buf->read_pos += len;

	return len;
}

/**
 *  ringbuffer_from_user - write user space data into ringbuffer
 *  @ring_buf: the ringbuffer to be used.
 *  @from: user buffer pointer.
 *  @len: the length of the data to be written.
 *
 *  This fucntion return the length have been written or -EFAULT if error.
 *
 */
int ringbuffer_from_user(struct ringbuffer *ring_buf, const void __user *from, unsigned long len)
{
	unsigned long l;   

	len = min(len, (unsigned long)(ring_buf->size - ring_buf->write_pos + ring_buf->read_pos));   

	/*  
	 * Ensure that we sample the read_pos  before we  
	 * start putting bytes into the ring_buf.  
	 */   
	smp_mb();   

	/* first put the data starting from write_pos to buffer end */   
	l = min(len, (unsigned long)(ring_buf->size - (ring_buf->write_pos & (ring_buf->size - 1))));   
	if (copy_from_user(ring_buf->data + (ring_buf->write_pos & (ring_buf->size - 1)), from, l)) {
		return -EFAULT;
	}

	/* then put the rest (if any) at the beginning of the buffer */   
	if (copy_from_user(ring_buf->data, from + l, len - l)) {
		return -EFAULT;
	}
	/*  
	 * Ensure that we add the bytes to the ring_buf -before-  
	 * we update the ring_buf->write_pos index.  
	 */   
	smp_wmb();   

	ring_buf->write_pos += len;

	return len;   
}


/**
 *  ringbuffer_to_user - copy ringbuffer data to user space buffer
 *  @ring_buf: the ringbuffer to be used.
 *  @dest: user space address where to store the data.
 *  @len: the length of the data to be copied.
 *
 *  This function return the length have copied or or -EFAULT if error.
 *
 */
int ringbuffer_to_user(struct ringbuffer *ring_buf, void __user *dest,
		unsigned long len)
{
	unsigned long l;

	len = min(len, (unsigned long)ringbuffer_len(ring_buf));

	/*
	 * Ensure that we sample the ring_buf->write_pos index -before- we
	 * start removing bytes from the kring_buf.
	 */

	smp_rmb();

	/* first get the data from ring_buf->read_pos until the end of the buffer */
	l = min(len, (unsigned long)(ring_buf->size - (ring_buf->read_pos & (ring_buf->size - 1))));
	if (copy_to_user(dest, ring_buf->data + (ring_buf->read_pos & (ring_buf->size - 1)), l)) {
		return -EFAULT;
	}

	if (l != len) {

		/* then get the rest (if any) from the beginning of the buffer */
		if (copy_to_user(dest + l, ring_buf->data, len - l)) {
			return -EFAULT;
		}
	}
	/*
	 * Ensure that we remove the bytes from the kring_buf -before-
	 * we update the ring_buf->read_pos index.
	 */

	smp_mb();

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

