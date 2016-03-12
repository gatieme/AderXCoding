ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=constructor copyconstructor-onrvo  copyconstructor-rvo



all:$(target)

constructor :   constructor
	$(CXX) $^ -o $@ 
	#echo "单参数构造函数..."

copyconstructor-nonrvo: copyconstructor.o
	$(CXX) $^ -o $@ 
	echo "拷贝构造函数的调用时机-非优化版..."

copyconstructor-rvo: copyconstructor.o
	$(CXX) $^ -o $@ 
	echo "拷贝构造函数的调用时机-RVO优化版..."

      
copyconstructexplicit : copyconstructexplicit.o
	$(CXX) -c $^ -o $@  
       	echo "explicit限制下的拷贝构造函数..."

clean :
	rm $(target)
