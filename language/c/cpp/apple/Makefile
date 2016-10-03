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


target=main_wrapper



all:$(target)



main_wrapper : main.o libapplewrapper.a
	$(CC) $^ -o $@ -lstdc++


main_handle : main.o libapplehandle.a 
	$(CC) $^ -o $@ -lstdc++

main_wrapper_sdk : main.o libapplewrapper.so
	$(CC) $^ -o $@ -lstdc++ -L./ -lapplewrapper

main_handle_sdk : main.o libapplehandle.so
	$(CC) $^ -o $@ -lstdc++ -L./ -lapplehandle


libapplewrapper.a:apple.o applewrapper.o
	ar crv $@ $^

libapplehandle.a:apple.o applehandle.o
	ar crv $@ $^

libapplewrapper.ao : apple.o applewrapper.o
	$(CXX) $(SHAREDLIB_LINK_OPTIONS) $(FPIC) $(LDFLAGS) $^ -o $@

libapplehandle.ao : apple.o applehandle.o
	$(CXX) $(SHAREDLIB_LINK_OPTIONS) $(FPIC) $(LDFLAGS) $^ -o $@


%.o:%.cpp
	$(CXX) $(FPIC) $(CXXFLAGS) -c $^ -o $@ $(INC)


%.o:%.c
	$(CC) $(FPIC) $(CFLAGS) -c $^ -o $@ $(INC)


clean :
	rm -rf *.o
	rm -rf libapple.so libapple.a
	rm -rf $(target)
