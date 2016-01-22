ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target= orphan zombie badparent goodparent sigzombie zombietoorphan
 


all:$(target)


orphan : orphan.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "编译孤儿进程测试程序..."

zombie : zombie.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "编译僵死进程测试程序..."

badparent : badparent.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "编译循环产生僵死进程的测试程序..."

goodparent : goodparent.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "编译处理僵死进程的测试程序..."

sigzombie : sigzombie.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "编译信号量处理僵死进程的程序..."

zombietoorphan : zombietoorphan.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "通过两次fork将僵死进程转换为孤儿进程..."

%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm *.o
	rm $(target)
