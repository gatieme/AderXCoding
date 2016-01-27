ROOT=../../../
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=add sub



all:$(target)

add : add.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "内敛汇编实现 a + b..."

sub : sub.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "内敛汇编实现 a - b..."

%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm *.o
	rm $(target)
