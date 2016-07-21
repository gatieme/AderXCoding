ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

LDFLAGS +=-lpthread

target=memcheck leak_mtrace


all:$(target)

memcheck:memcheck.o
	$(CC)  $^ -o $@ $(LDFLAGS)

leak_mtrace : leak_mtrace.o
	$(CC)  $^ -o $@ $(LDFLAGS)

%.o : %.c
	$(CC) -g -c $^ -o $@  $(CFLAGS) $(DEFINES)

.PHONY : clean
clean :
	rm *.o
	rm $(target)
	rm mtrace.out
