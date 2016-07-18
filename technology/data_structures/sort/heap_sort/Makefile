ROOT=../../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=heap_sort


all:$(target)


heap_sort : heap_sort.o
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
	@echo "堆排序算法..."
	@echo ""


%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)


%.o : %.cpp
	$(CXX) -c $^ -o $@  $(CXXFLAGS) $(DEFINES)

clean :
	rm -rf *.o
	rm $(target)
