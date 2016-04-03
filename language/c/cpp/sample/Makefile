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


target=libsample.so libmylib.so main



all:$(target)



main:main.o libmylib.so
	$(CC) $^ -o $@ -ldl



libsample.so:sample.o
	gcc $(SHAREDLIB_LINK_OPTIONS) $(FPIC) $(LDFLAGS) $^ -o $@


libmylib.so:mylib.o
	gcc $(SHAREDLIB_LINK_OPTIONS) $(FPIC) $(LDFLAGS) $^ -o $@


%.o:%.cpp
	$(CXX) $(FPIC) $(CXXFLAGS) -c $^ -o $@ $(INC)


%.o:%.c
	$(CC) $(FPIC) $(CFLAGS) -c $^ -o $@ $(INC)


clean :
	rm -rf *.o
	rm -rf $(target)
