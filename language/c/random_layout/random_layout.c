#include <stdio.h>
#include <stdlib.h>

#define __randomize_layout __attribute__((randomize_layout))

struct A
{
	int a;
	char b;
	long c;
	void *d;
} __randomize_layout;

int main(void)
{
	printf("%ld\n", sizeof(struct A));
	printf("%ld\n", (size_t)&((struct A *)0)->a);
	printf("%ld\n", (size_t)&((struct A *)0)->b);
	printf("%ld\n", (size_t)&((struct A *)0)->c);
	printf("%ld\n", (size_t)&((struct A *)0)->d);

	return EXIT_SUCCESS;
}
