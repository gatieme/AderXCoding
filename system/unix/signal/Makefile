ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=	test_kill1 test_kill2 				\
	   	test_raise test_alarm				\
	   	test_setitimer	test_pause			\
	   	test_abort							\
		test_sigaction						\
		sigaction_signal					\
		sigaction_mask						\
		send_int							\
		send_data	recv_data				\
		test_sigprocmask test_sigpending	\
		test_sigset

all:$(target)


test_kill1 : test_kill1.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "用户输入信号num，然后父进程通过kill向子进程发送num信号...\n"

test_kill2 : test_kill2.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "父进程向子进程发送信号，终止子进程...\n"

test_raise : test_raise.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "进程通过raise向自身发送信号...\n"


test_alarm : test_alarm.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "进程通过alarm发送定时器信号...\n"

test_setitimer : test_setitimer.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "进程通过setitimer设置更精确的定时器信号...\n"

test_pause : test_pause.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "子进程挂起直至接收到父进程的信号...\n"

test_abort : test_abort.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "通过abort终止进程...\n"

test_sigaction:test_sigaction.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "利用sigaction安装SIGINT信号...\n"

sigaction_signal:sigaction_signal.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "利用sigaction实现signal...\n"

sigaction_mask:sigaction_mask.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "验证sigaction.sa_mask效果...\n"

send_int:send_int.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "给自身发送int型数据...\n"

send_data:send_data.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "发送数据的客户端...\n"

recv_data:recv_data.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "接收数据的服务器...\n"

test_sigprocmask:test_sigprocmask.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "测试sigprocmask屏蔽和取消屏蔽信号量...\n"

test_sigpending:test_sigpending.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "测试sigpengding检测未决的信号量...\n"

test_sigset:test_sigset.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "测试sigset信号集...\n"

%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm *.o
	rm $(target)
