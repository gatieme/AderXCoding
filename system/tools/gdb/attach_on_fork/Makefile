ROOT=../../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

LDFLAGS+=-lpthread

target= test


all:$(target)


test : test.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "gdb调试多进程..." 

%.o : %.c
	$(CC) -g -c $^ -o $@  $(CFLAGS) $(DEFINES)

.PHONY : clean
clean :
	rm *.o
	rm $(target)
