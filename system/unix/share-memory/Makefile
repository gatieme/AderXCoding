ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)



target=test_shm test_shm_count reader writer


all:$(target)


test_shm : test_shm.o 
	$(CC) $^ -o $@ $(LDFLAGS) 
	@echo -e "简单测试共享内存的使用...\n"

test_shm_count : test_shm_count.o 
	$(CC) $^ -o $@ $(LDFLAGS) 
	@echo -e "简单测试共享内存的使用...\n"


reader : reader.o 
	$(CC) $^ -o $@ $(LDFLAGS) 
	@echo -e "读端进程从共享内存中读数据...\n"

writer : writer.o 
	$(CC) $^ -o $@ $(LDFLAGS) 
	@echo -e "写端进程向共享内存写数据...\n"

%.o : %.c
	$(CC) -c $^  -o $@  $(CFLAGS) $(DEFINES)
	@echo -e ""

clean :
	rm -rf *.o
	rm -rf $(target)
