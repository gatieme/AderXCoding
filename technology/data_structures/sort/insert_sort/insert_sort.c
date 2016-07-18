#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG

#ifdef DEBUG
    #define     debug       printf
    #define     __tmain     main
#else
    #define     debug       0 && printf
#endif


//#define swap(a, b) (a) ^= (b) ^= (a) ^= (b)

/*
 * swap - swap value of @a and @b
 */
#define swap(a, b) \
        do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)


int Large(int left, int right)
{
    return (left > right);
}

int Less(int left, int right)
{
    return (left < right);
}



void PrintUp(int *array, int length, int index)
{
    int k;
    if(index > 0)
    {
        printf(" [ ");
        for(k = 0; k < index; k++)
        {
            printf("%4d", array[k]);
        }
        printf(" ]");
    }
    for(k = index; k < length; k++)
    {
        printf("%4d", array[k]);
    }
    printf("\n");
}


void InsertSort(int *array, int length, int (*comp)(int, int))
{
    int     i, j;
    int     temp;

    for(i = 1; i < length; i++)      // 循环第1个数据以后的每个数据
    {
        temp = array[i];         // 保存第i个数据,

        for(j = i - 1;
            j >= 0 && comp(temp, array[j]);
            j--)      // 将比保存的数据都往后移
        {
            array[j + 1] = array[j];
        }
        // 循环结束后就在有序的0-i的位置中找到了temp应该插入的位置(j + 1)
        array[j + 1] = temp;         // 将保存的数据插进来

        PrintUp(array, length, i);
        }
    }

int __tmain(void)
{
    int array[] = {36, 48, 48, 99, 88, 80, 76, 90};
    int length = sizeof(array) / sizeof(array[0]);

    printf("begin : ");
    PrintUp(array, length, 0);        /*  打印当前排序的结果*/

    InsertSort(array, length, Less);

    printf("after : ");
    PrintUp(array, length, length);        /*  打印当前排序的结果*/

    printf("again : ");
    InsertSort(array, length, Large);

    printf("\n");



    return EXIT_SUCCESS;
}
