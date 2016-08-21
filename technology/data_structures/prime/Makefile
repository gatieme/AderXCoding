ROOT=../../../
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target= get_nth_prime1 get_nth_prime2 get_nth_prime3	\
		get_nth_prime4 get_prime	  get_prime_count


all:$(target)


get_prime : get_prime.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "筛素数法详解..."
	@echo ""

get_nth_prime1 : get_nth_prime1.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "暴力法第N个素数..."
	@echo ""

get_nth_prime2 : get_nth_prime2.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "筛素数法求第N个素数..."
	@echo ""

get_nth_prime3 : get_nth_prime3.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "优化的筛素数法求第N个素数__1..."
	@echo ""


get_nth_prime4 : get_nth_prime4.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "优化的筛素数法求第N个素数__2..."
	@echo ""

get_prime_count : get_prime_count.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "获取[min, max]之间素数的个数..."
	@echo ""



%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm -rf *.o
	rm $(target)
