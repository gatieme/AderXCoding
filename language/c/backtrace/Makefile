target = example prog handler builtin0 builtin_c
target_cpp = builtin_cpp

all:$(target) $(target_cpp)

example : example.o
prog : prog.o
handler : handler.o
builtin0 : builtin0.o
builtin_c : builtin.o
builtin_cpp : builtin.c

$(target_cpp) :
	g++ $^ -o $@ $(LDFLAGS) -rdynamic -g -ldl

$(target) :
	$(CC) $^ -o $@ $(LDFLAGS) -rdynamic -g
%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES) -rdynamic -g

clean :
	rm -rf *.o
	rm -rf $(target)
	rm -rf $(target_cpp)
