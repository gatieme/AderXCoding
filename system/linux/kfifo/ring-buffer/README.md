ringbuffer
==========

a ring buffer like kfifo, work in linux kernel space and user space, and test on kernel 3.16 
on x86, ARM platform.

Please note that the data in the buffer will keep there until they be read out. If the buffer
is full, the data could not be put into any more, until a read action free some space.


git@github.com:dennis-musk/ringbuffer.git
https://github.com/dennis-musk/ringbuffer
