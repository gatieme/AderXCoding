#include <stdio.h>

void test(int count)
{
	int i;
	for (i = 1; i < count; i++)
	{
		if (i % 3 == 0)
			printf ("%d is divisible by 3\n", i);
		if (i % 11 == 0)
			printf ("%d is divisible by 11\n", i);
		if (i % 13 == 0)
			printf ("%d is divisible by 13\n", i);
	}
}
