ROOT=../../../
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=simple front_rear kmp_next kmp_nextvalue



all:$(target)


simple : simple.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "简单字符串模式匹配算法"
	@echo ""

front_rear: front_rear.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "首尾字符串模式匹配算法"
	@echo ""

kmp_next: kmp_next.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "KMP字符串模式匹配算法"
	@echo ""

kmp_nextvalue: kmp_nextvalue.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "优化的KMP字符串模式匹配算法"
	@echo ""

%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm -rf *.o
	rm $(target)
