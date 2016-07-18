ROOT=../../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=insert_sort


all:$(target)


insert_sort : insert_sort.o
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "简单的插入排序算法..."
	@echo ""


%.o : %.c
	$(CXX) -c $^ -o $@  $(CXXFLAGS) $(DEFINES)


%.o : %.cpp
	$(CXX) -c $^ -o $@  $(CXXFLAGS) $(DEFINES)

clean :
	rm -rf *.o
	rm $(target)
