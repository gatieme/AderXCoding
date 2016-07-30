ROOT=../../../
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

LDFLAGS +=-lpthread

target= core_dump_test args_test



all:$(target)


core_dump_test : core_dump_test.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "因为修改const char *导致的段错误..."


args_test : args_test.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "设置参数信息..."

%.o : %.c
	$(CC) -g -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm *.o
	rm $(target)
