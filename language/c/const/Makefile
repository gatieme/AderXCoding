ROOT=../../../
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=1 2 3  



all:$(target)


1 : 1.o
	$(CC) $^ -o $@ $(LDFLAGS)
	#echo "编译指针常量和常量指针"

2: 2.o
	$(CC) $^ -o $@ $(LDFLAGS)
	#echo "char * const pstr = "abcd";"

3: 3.o
	$(CC) $^ -o $@ $(LDFLAGS)
	#echo "segmentation fault (core dumped)"

%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm *.o
	rm $(target)
