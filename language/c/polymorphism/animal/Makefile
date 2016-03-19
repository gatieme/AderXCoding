
all:main

main:main.o dog.o cat.o animal-base.o
	gcc -o $@ $^

main.o:main.c

cat.o:cat.c

dog.o:dog.c

animal-base.o:animal-base.c

.PHONY:clean

clean:
	rm main main.o dog.o cat.o animal-base.o