/*************************************************************************
    > File Name: test_abort.c
    > Author: gatieme
    > Created Time: 2016年03月27日 星期日 13时01分51秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    printf("Calling abort()\n");
    abort();

    /* The next code will never reach... */
    printf("after abort...\n");

    return 0;
}
