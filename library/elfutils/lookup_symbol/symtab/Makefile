ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

target=lookup


all:$(target)

lookup : lookup.o
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "获取系统中的cpu核心数目..."


%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES)

clean :
	rm -rf *.o
	rm -rf $(target)

run :
	./$(target)
