#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define DEBUG

#ifdef DEBUG
    #define debug printf
#else
    #define debug 0 && printf
#endif



/*  通过计算返回子串T的next数组  */
void GetNext(char *str, int *next)
{
    int i = 0, j = -1;          /*  i, j分别为前缀和后缀的下标  */

    next[i] = -1;               /*  由next[0] == -1开始进行递推  */
    printf("next[%d] = %2d\n", i, next[i]);

    while(i < strlen(str) - 1)  /*  数组next的下标范围为0~strlen(str) - 1*/
    {
        printf("i = %d, j = %d\n", i, j);
        if(j == -1 || str[i] == str[j])
        {
            /*  IF str[i] == str[j]
             *  就定位next[i + 1] = 回溯位置j的下一个位置j + 1
             *
             *  此时如果未发生回溯 next[i] = j,
             *  而i,j完成自增后next[i-1]=j-1
             *  则next[i + 1] = next[i - 1] + 1 = j + 1;
             *  如果发生回溯, 则j则是其回溯的位置,
             *  那么next[i + 1] = 回溯位置的下一个位置 = j + 1
             *
             *  否则如果j == -1说明匹配刚开始或者回溯到最初始位置
             *  直接next[i + 1] = j + 1 = 0;
             *  */
#ifdef DEBUG
            if(str[i] == str[j])
            {
                if(next[i] == j)
                {
                    printf("un back : str[%d] == str[%d], ", i, j);
                }
                else
                {
                    printf("back to : str[%d] == str[%d], ", i, j);
                }
            }
            else /*if(j == -1)*/
            {
                printf("back to begin : j == -1, ");
            }
            printf("next[%d] = j + 1 = %d\n", i, j + 1);
#endif
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            printf("start back : str[%d] != str[%d], j = next[j] = %d\n", i, j, j);
            j = next[j];        /*  若字符不相等, 则j回溯  */
        }
        printf("next[%d] = %2d\n", i, next[i]);
    }

#ifdef DEBUG
    printf("\n");
    for(int i = 0; i < strlen(str); i++)
    {
        printf("%d  ", next[i]);
    }
    printf("\n");
#endif
}


int KMPIndex(char *str, char *sub, int pos)
{
    int i = pos, j = 0;
    int next[255];

    GetNext(sub, next);     /*  分析子串sub的next数组  */
    while(i < strlen(str) && j < strlen(sub))
    {
        if(j == -1 || str[i] == sub[j])  /*  两字符相等, 则继续匹配  */
        {
            debug("[%d]%c, [%d]%c\n", i, str[i], j, sub[j]);
            i++;
            j++;
        }
        else                            /*  否则的话, 返回合适位置重新匹配  */
        {
            j = next[j];                /*  子串退回到合适位置, 主串不变  */
        }
    }

    debug("%d %d\n", i, j);
    if(j >= strlen(sub))
    {
        return i - j; // j = strlen(sub);
    }
    else
    {
        return -1;
    }
}

int main(int argc, char *argv[])
{
    char    str[81];
    int     next[81];
    strcpy(str, "abaabcac");
    GetNext(str, next);

    strcpy(str, "aaac");
    GetNext(str, next);

    strcpy(str, "abab");
    GetNext(str, next);

    printf("%d\n", KMPIndex("aaaaacefghij", "aaac", 0));
    return EXIT_SUCCESS;
}


