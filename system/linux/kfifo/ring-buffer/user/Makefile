ROOT=../../../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)



target=buffer_test

all:$(target)



buffer_test: ring_buffer.o
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread
	@echo -e "测试自己实现的kfifo--ring_buffer...\n"

%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm *.o
	rm $(target)
