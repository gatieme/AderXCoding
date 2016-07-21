#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <mcheck.h>


void get_memory(char *p, int num)
{
    p = (char*)malloc(sizeof(char) * num);//C++中使用new也能够检测出来
}

int main(void)
{
    char *str = NULL;

    setenv("MALLOC_TRACE", "mtrace.out", 1);
    mtrace( );
    printf("Memory leak test!\n");


    for(int i = 0; i < 10; i++)
    {
        get_memory(str, 100);   /*  每次分配100个字节而不释放  */
    }
    //如果main中存在while循环调用get_memory
    //那么问题将变得很严重
    //while(1){GetMemory(...);}
    return 0;
}
