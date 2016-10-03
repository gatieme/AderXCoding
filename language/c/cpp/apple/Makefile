ROOT=../../../../
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)




#  the compile options
CFLAGS = -Wall -std=gnu99 -O2 -pedantic -Wextra -g
CXXFLAGS = -Wall -std=c++11 -O2 -pedantic -Wextra -g

SHAREDLIB_LINK_OPTIONS = -shared

ifeq ($(PLATFORM), windows)
FPIC =
else
FPIC = -fPIC
endif
#-Wl,-soname,
#  the include directory
INC = -I./


target=main main_sdk



all:$(target)



main:main.o libapple.a
	$(CC) $^ -o $@ -lstdc++


main_sdk : main.o libapple.so
	$(CC) $^ -o $@ -lstdc++ -L./ -lapple


libapple.a:apple.o applewrapper.o
	ar crv $@ $^

libapple.so : apple.o applewrapper.o
	$(CXX) $(SHAREDLIB_LINK_OPTIONS) $(FPIC) $(LDFLAGS) $^ -o $@


%.o:%.cpp
	$(CXX) $(FPIC) $(CXXFLAGS) -c $^ -o $@ $(INC)


%.o:%.c
	$(CC) $(FPIC) $(CFLAGS) -c $^ -o $@ $(INC)


clean :
	rm -rf *.o
	rm -rf libapple.so libapple.a
	rm -rf $(target)
