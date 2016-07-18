ROOT=../../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=partition


all:$(target)


partition : partition.o
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "简单的快速排序算法..."
	@echo ""


%.o : %.c
	$(CXX) -c $^ -o $@  $(CXXFLAGS) $(DEFINES)


%.o : %.cpp
	$(CXX) -c $^ -o $@  $(CXXFLAGS) $(DEFINES)

clean :
	rm -rf *.o
	rm $(target)
