ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

DEFINES+= -DSEMAPHORE

DLL=libsempv.so
target=forksem pthread_sem1 pthread_sem2 fork_sync

DEFINES= -DDEFINE_SEMAPHORE

all:$(target)


forksem : forksem.o $(DLL)
	$(CC) $^ -o $@ $(LDFLAGS) -L./ -lsempv
	@echo -e "父子间进程信号量通信的程序...\n"

pthread_sem1 : pthread_sem1.o
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread
	@echo -e "两个线程互斥读写number变量[执行顺序随机]...\n"

pthread_sem2 : pthread_sem2.o
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread
	@echo -e "两个线程互斥读写number变量[通过两个信号量保证执行顺序]...\n"

fork_sync : fork_sync.o
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread
	@echo -e "两个线程互斥读写number变量[通过两个信号量保证执行顺序]...\n"

$(DLL):sempv.o
	$(CC) -shared $^ -o $@

%.o : %.c
	$(CC) -fpic -c $^  -o $@  $(CFLAGS) $(DEFINES)
	@echo -e ""

clean :
	rm -rf *.o
	rm -rf $(DLL)
	rm -rf $(target)
