ROOT=../../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=select_sort


all:$(target)


select_sort : select_sort.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "简单的选择排序算法..."
	@echo ""


%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)


%.o : %.cpp
	$(CXX) -c $^ -o $@  $(CXXFLAGS) $(DEFINES)

clean :
	rm -rf *.o
	rm -rf $(target)
