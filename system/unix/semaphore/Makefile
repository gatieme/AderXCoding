ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

DEFINES+= -DSEMAPHORE

DLL=libsempv.so
target=forksem pthread_sem1 pthread_sem2 fork_sync server client		\
	   semget semop semgetvalue semsetvalue	producer_consumer 

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

server : server.o
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread
	@echo -e "有名信号量在无相关进程间的同步[服务器]...\n"

client : client.o
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread
	@echo -e "有名信号量在无相关进程间的同步[客户端]...\n"

semget : semget.o
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread
	@echo -e "System V的信号量, 测试semget函数...\n"

semop : semop.o
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread
	@echo -e "System V的信号量, 测试semop函数...\n"

semgetvalua : semgetvalue.o
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread
	@echo -e "System v信号量, 通过semctl函数获取信号量的值...\n"

semsetvalua : semsetvalue.o
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread
	@echo -e "System v信号量, 通过semctl函数设置信号量的值...\n"

producer_consumer : producer_consumer.o
	$(CC) $^ -o $@ $(LDFLAGS) -lpthread
	@echo -e "生产者消费者问题...\n"

$(DLL):sempv.o
	$(CC) -shared $^ -o $@

%.o : %.c
	$(CC) -fpic -c $^  -o $@  $(CFLAGS) $(DEFINES)
	@echo -e ""

clean :
	rm -rf *.o
	rm -rf $(DLL)
	rm -rf $(target)
