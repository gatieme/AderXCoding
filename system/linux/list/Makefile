ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=list_entry_test mylist_test mylist_macro_test

all:$(target)


list_entry_test:list_entry_test.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "测试自己实现的list_entry...\n"


mylist_test:mylist_test.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "测试自己实现的list...\n"

mylist_macro_test:mylist_macro_test.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo -e "测试自己实现的list中的list_entry宏...\n"

%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm *.o
	rm $(target)
