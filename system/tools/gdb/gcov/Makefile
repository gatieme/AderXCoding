ROOT=../../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

CFLAGS+=-fprofile-arcs -ftest-coverage
LDFLAGS+=-lpthread

target=tmp


all:$(target)


tmp : tmp.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "gdb-gcov测试程序覆盖率..."

%.o : %.c
	$(CC) -g -c $^ -o $@  $(CFLAGS) $(DEFINES)

.PHONY : clean
clean :
	rm -rf *.o
	rm -rf $(target)
	rm -rf  *.gcov *.gcda *.gcno

