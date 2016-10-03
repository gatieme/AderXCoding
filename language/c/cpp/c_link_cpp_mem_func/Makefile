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


target=main libmyclass.a



all:$(target)



main:main.o libmyclass.a
	$(CC) $^ -o $@ -lstdc++



libmyclass.so:libmyclass.o myclass.o
	$(CXX) $(SHAREDLIB_LINK_OPTIONS) $(FPIC) $(LDFLAGS) $^ -o $@


libmyclass.a:libmyclass.o myclass.o
	ar crv $@ $^


%.o:%.cpp
	$(CXX) $(FPIC) $(CXXFLAGS) -c $^ -o $@ $(INC)


%.o:%.c
	$(CC) $(FPIC) $(CFLAGS) -c $^ -o $@ $(INC)


clean :
	rm -rf *.o
	rm -rf $(target)
