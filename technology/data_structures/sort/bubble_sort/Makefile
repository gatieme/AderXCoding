ROOT=../../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=bubble_sort



all:$(target)


bubble_sort : bubble_sort.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "冒泡排序算法..."
	@echo ""


%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm -rf *.o
	rm $(target)
