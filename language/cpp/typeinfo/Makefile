ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=test_bad_typeid test_typeid



all:$(target)

test_bad_typeid : test_bad_typeid.o
	$(CXX) $^ -o $@ 
	@echo "测试typeid的异常处理..."

test_typeid : test_typeid.o
	$(CXX) $^ -o $@ 
	@echo "测试typeid进行类别判断..."


%.o : %.c
	$(CXX) -c $^ -o $@ 

clean :
	rm $(target)
	rm *.o
