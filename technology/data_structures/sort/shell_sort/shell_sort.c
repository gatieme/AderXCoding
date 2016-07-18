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


// 函数功能：希尔插入排序
// array待排序的数组, length待排序数组的长度, comp( )数据比较函数,
void ShellSort(int *array, int length, int (*comp)(int, int))
{
    // 排序函数部分
    int incr/*Shell步长*/, i/*控制每趟步长的插入过程*/, j/*循环移动元素*/;
    int temp;          // 一个单位的辅助空间

    for(incr = length / 2; incr >= 1; incr /= 2)          // 控制每个步长的排序
    {   // 第coun趟排序-=>步长为incr
        for(i = incr; i < length; i++)      // 控制每趟步长的插入过程
        {   // 每趟排序的插入过程
            temp = array[i];
            for(j = i - incr; j >= 0 && comp(temp, array[j]); j -= incr)     // 寻找插入位置
            {   // 将不满足插入位置要求的元素依次后移
                array[j + incr] = array[j];
            }
            array[j + incr] = temp;      // 将元素插入
        }
#ifdef  DEBUG
        for(int pos = 0; pos < length; pos++)
        {
            printf("%4d", array[pos]);             // 打印每个记录信息
        }
        printf("\n");
#endif
    }
}



int __tmain(void)
{
    int array[] = {36, 48, 48, 99, 88, 80, 76, 90};
    int length = sizeof(array) / sizeof(array[0]);

    printf("begin : ");
    PrintUp(array, length, 0);        /*  打印当前排序的结果*/

    ShellSort(array, length, Less);

    printf("after : ");
    PrintUp(array, length, length);        /*  打印当前排序的结果*/

    printf("again : ");
    ShellSort(array, length, Large);

    printf("\n");



    return EXIT_SUCCESS;
}
