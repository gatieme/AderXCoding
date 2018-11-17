target=example prog handler

all:$(target)

example : example.o
prog : prog.o
handler : handler.o

$(target) :
	$(CC) $^ -o $@ $(LDFLAGS) -rdynamic -g
%.o : %.c
	$(CC) -c $^ -o $@  $(CFLAGS) $(DEFINES) -rdynamic -g

clean :
	rm -rf *.o
	rm -rf $(target)
