ROOT=../../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=shell_sort


all:$(target)


shell_sort : shell_sort.o
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "希尔插入排序..."
	@echo ""


%.o : %.c
	$(CXX) -c $^ -o $@  $(CXXFLAGS) $(DEFINES)


%.o : %.cpp
	$(CXX) -c $^ -o $@  $(CXXFLAGS) $(DEFINES)

clean :
	rm -rf *.o
	rm $(target)
