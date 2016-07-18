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



int Index(char *str, char *sub)
{
    if(strlen(str) < strlen(sub))
    {
        return -1;
    }

    int i = 0;  /*  i用于主串中当前位置下标索引  */
    int j = 0;  /*  j用于子串中当前位置下标索引  */

    while(i < strlen(str) && j < strlen(sub))   /*  控制循环在字符串的范围内  */
    {
        if(str[i] == sub[j])        /*  子串与主串相同则继续  */
        {
            debug("[%d]%c [%d]%c\n", i, str[i], j, sub[j]);
            i++;
            j++;
        }
        else                        /*  指针后退重新开始匹配  */
        {
            /*  此时两个指针正好走了j个长度
             *  i - j为子串的起始下标  */
            i = i - j + 1;          /*  主串退回到上次匹配首位的下一位  */
            j = 0;                  /*  子串回到起点  */
        }
    }

    if(j == strlen(sub))
    {
        return i - strlen(sub);
    }
    else
    {
        return -1;
    }
}

int main(int argc, char *argv[])
{
    printf("%d\n", Index("aaaaacefghij", "aaac"));

    return EXIT_SUCCESS;
}


