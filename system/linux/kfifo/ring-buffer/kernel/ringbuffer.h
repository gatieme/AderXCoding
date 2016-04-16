#ifndef __RINGBUFFER_H
#define	__RINGBUFFER_H

#include <linux/types.h>

struct ringbuffer {
	void *data;
	unsigned int size;
	unsigned int read_pos;
	unsigned int write_pos;
};

struct ringbuffer *ringbuffer_create(unsigned int byte, gfp_t gfp_mask);
void ringbuffer_destroy(struct ringbuffer *ring_buf);

void ringbuffer_reset(struct ringbuffer *ring_buf);

unsigned int ringbuffer_put(struct ringbuffer *ring_buf, 
 	const unsigned char *buf, unsigned int len);

unsigned int ringbuffer_get(struct ringbuffer *ring_buf,
 		unsigned char *buf, unsigned int len);

void ringbuffer_print(struct ringbuffer *ring_buf, unsigned int cnt);

unsigned int ringbuffer_fromio(struct ringbuffer *ring_buf, void *source, unsigned int len);

int ringbuffer_from_user(struct ringbuffer *ring_buf, const void __user *from, unsigned long len);
int ringbuffer_to_user(struct ringbuffer *ring_buf, void __user *dest, unsigned long len);

unsigned int ringbuffer_is_empty(struct ringbuffer *ring_buf);
unsigned int ringbuffer_is_full(struct ringbuffer *ring_buf);

unsigned int ringbuffer_len(struct ringbuffer *ring_buf);

#endif
