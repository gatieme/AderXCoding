ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target= pipe fifo_write fifo_read
FIFO_FILE=./myfifo


all:$(target)


pipe : pipe.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "父子进程间的管道通信程序..."


fifo_write : fifo_write.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "FIFO写程序..."

fifo_read : fifo_read.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "FIFO读程序..."

%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm *.o
	rm $(target)
	rm $(FIFO_FILE)
