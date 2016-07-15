#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

#ifdef DEBUG
    #define     debug       printf
    #define     __tmain     main
#else
    #define     debug       0 && printf
#endif



int FrontRearIndex(char *str, char *sub, int pos)
{
    if(strlen(str) < strlen(sub))
    {
        return -1;
    }

    int i = pos;
    while(i < strlen(str) - strlen(sub) + 1)
    {
        int front = 0, rear = strlen(sub) - 1;

        while(front <= rear)
        {
            debug("front : [%d]%c [%d]%c, ",
                  i + front, str[i + front], front, sub[front]);
            debug("rear  : [%d]%c [%d]%c\n",
                  i + rear, str[i + rear], rear, sub[rear]);
            if(str[i + front] != sub[front]
            || str[i + rear] != sub[rear])
            {
                break;
            }
            else
            {
                front++;
                rear--;
            }
        }

        if(front > rear)
        {
            return i;
        }
        else
        {
            ++i;
        }
    }

    return -1;
}

int __tmain(int argc, char *argv[])
{
    printf("%d\n", FrontRearIndex("aaaaacefghij", "aaac", 0));

    return EXIT_SUCCESS;
}


