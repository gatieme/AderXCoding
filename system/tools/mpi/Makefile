ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

LDFLAGS +=-lpthread

target=mpi_hello

MPICC=mpicc

all:$(target)

mpi_hello	:	mpi_hello.c
	$(MPICC)  $^ -o $@

leak_mtrace : 	leak_mtrace.c
	$(MPICC)  $^ -o $@

.PHONY : clean
clean :
	rm -rf *.o
	rm -rf $(target)
