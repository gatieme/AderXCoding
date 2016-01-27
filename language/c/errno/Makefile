ROOT=../../../
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=showerrno



all:$(target)

showerrno : showerrno.o
	$(CC) $^ -o $@ $(LDFLAGS)
	echo "输出errno的值..."

%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm *.o
	rm $(target)
