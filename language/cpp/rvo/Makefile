ROOT=../../../
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=enrvo dervo  



all:$(target)


enrvo : rvo.cpp
	$(CXX) $^ -o $@ $(LDFLAGS)
	echo "使用返回值优化..."

dervo: rvo.cpp
	$(CXX) $^ -o $@ $(LDFLAGS) -fno-elide-constructors
	echo "不使用返回值优化..."


clean :
	rm -rf *.o
	rm -rf $(target)
