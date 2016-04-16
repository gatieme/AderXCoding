#ifndef __RINGBUFFER_H
#define	__RINGBUFFER_H

#define min(x,y) ({ 			\
		typeof(x) _x = (x);	\
		typeof(y) _y = (y);	\
		(void) (&_x == &_y);	\
		_x < _y ? _x : _y; })

struct ringbuffer {
	void *data;
	unsigned int size;
	unsigned int read_pos;
	unsigned int write_pos;
};

struct ringbuffer *ringbuffer_create(unsigned int bytes);
void ringbuffer_destroy(struct ringbuffer *ring_buf);

void ringbuffer_reset(struct ringbuffer *ring_buf);

unsigned int ringbuffer_put(struct ringbuffer *ring_buf, 
 	const char *buf, unsigned int len);

unsigned int ringbuffer_get(struct ringbuffer *ring_buf,
 		char *buf, unsigned int len);

void ringbuffer_print(struct ringbuffer *ring_buf, unsigned int cnt);

ssize_t ringbuffer_from_dev(int fd, struct ringbuffer *ring_buf, unsigned int len);

unsigned int ringbuffer_is_empty(struct ringbuffer *ring_buf);
unsigned int ringbuffer_is_full(struct ringbuffer *ring_buf);

unsigned int ringbuffer_len(struct ringbuffer *ring_buf);
unsigned int ringbuffer_space_left(struct ringbuffer *ring_buf);

unsigned int ringbuffer_to_socket(int socket_fd, struct ringbuffer *ring_buf, unsigned int len);

#endif
