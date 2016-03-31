ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)



target=test_msg msg_send msg_receive


all:$(target)


test_msg : test_msg.o 
	$(CC) $^ -o $@ $(LDFLAGS) 
	@echo -e "简单测试共享内存的使用...\n"

msg_send : msg_send.o 
	$(CC) $^ -o $@ $(LDFLAGS) 
	@echo -e "简单测试共享内存的使用...\n"

msg_receive : msg_receive.o 
	$(CC) $^ -o $@ $(LDFLAGS) 
	@echo -e "读端进程从共享内存中读数据...\n"


%.o : %.c
	$(CC) -c $^  -o $@  $(CFLAGS) $(DEFINES)
	@echo -e ""

clean :
	rm -rf *.o
	rm -rf $(target)
