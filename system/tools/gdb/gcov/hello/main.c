/*************************************************************************
    > File Name: main.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: Sun 22 Oct 2017 09:35:02 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void test(int vount);

int main(int argc, char *argv[])
{
	int i = 0;
	if(argc == 2)
		i = atoi(argv[1]);
	else
		i = 10;

	printf("arg is %d\n", i);

	test(i);

	return EXIT_SUCCESS;
}


