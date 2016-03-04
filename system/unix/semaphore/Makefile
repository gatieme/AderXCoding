ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

DEFINES+= -DSEMAPHORE

DLL=libsempv.so
target=forksem


all:$(target)


forksem : forksem.o $(DLL)
	$(CC) $^ -o $@ $(LDFLAGS) -L./ -lsempv
	echo "父子间进程信号量通信的程序..."

$(DLL):sempv.o
	$(CC) -shared $^ -o $@ 

%.o : %.c
	$(CC) -fpic -c $^  -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm *.o
	rm $(DLL)
	rm $(target)
