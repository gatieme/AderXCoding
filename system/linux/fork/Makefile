ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target= testfork testvfork testvfork2 testclone


all:$(target)


testfork : testfork.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "编译fork的测试程序..."

testvfork : testvfork.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "编译循环产生僵死进程的测试程序..."

testvfork2 : testvfork2.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "编译循环产生僵死进程的测试程序..."

testclone : testclone.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "编译循环产生僵死进程的测试程序..."

%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm *.o
	rm $(target)
