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


target=	main_wrapper main_wrapper_sdk			\
		main_handle	main_handle_sdk


all:$(target)



main_wrapper : mainwrapper.o libapplewrapper.a
	$(CC) $^ -o $@ -lstdc++


main_handle : mainhandle.o libapplehandle.a
	$(CC) $^ -o $@ -lstdc++

main_wrapper_sdk : mainwrapper.o libapplewrapper.so
	$(CC $^ -o $@ -lstdc++ -L./ -lapplewrapper  $(CXXFLAGS)

main_handle_sdk : mainhandle.o libapplehandle.so
	$(CC) $^ -o $@ -lstdc++ -L./ -lapplehandle	$(CXXFLAGS)


libapplewrapper.a : apple.o applewrapper.o
	ar crv $@ $^

libapplehandle.a : apple.o applehandle.o
	ar crv $@ $^

libapplewrapper.so : apple.o applewrapper.o
	$(CXX) $(SHAREDLIB_LINK_OPTIONS) $(FPIC) $(LDFLAGS) $^ -o $@

libapplehandle.so : apple.o applehandle.o
	$(CXX) $(SHAREDLIB_LINK_OPTIONS) $(FPIC) $(LDFLAGS) $^ -o $@


%.o : %.cpp
	$(CXX) $(FPIC) $(CXXFLAGS) -c $^ -o $@ $(INC)


%.o : %.c
	$(CC) $(FPIC) $(CFLAGS) -c $^ -o $@ $(INC)


clean :
	rm -rf *.o
	rm -rf libapple.so libapple.a
	rm -rf $(target)
