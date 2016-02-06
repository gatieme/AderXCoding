ROOT=../../
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)
LDFLAGS +=-lpthread
target= pthread mutex multiargs
 


all:$(target)


pthread : pthread.o
	$(CC) $^ -o $@ $(LDFLAGS) 
	echo "最简单的pthread测试程序..."

mutex : mutex.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "进程互斥锁测试程序..."

multiargs : multiargs.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "编译循环产生僵死进程的测试程序..."

%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm *.o
	rm $(target)
