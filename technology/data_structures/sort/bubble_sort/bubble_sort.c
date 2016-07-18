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


void PrintDown(int *array, int length, int index)
{
    int k;
    for(k = 0; k < length - index; k++)
    {
        printf("%4d", array[k]);
    }

    if(k < length)
    {
        printf(" [ ");
        for(k = length - index; k < length; k++)
        {
            printf("%4d", array[k]);
        }
        printf(" ]");
    }
    printf("\n");
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

/*  冒泡排序下沉法
 *  从前往后两两比较相邻记录的关键字, 如果反序则交换, 直到没有反序的位置
 *  这相当于一个下沉的过程, 每次下沉, 当前最大的哪个节点就会下沉的末尾的位置  */
void BubbleSortDown(int *array, int length, int (*comp)(int, int))
{
    int     i = 0, j = 0;
    bool    isswap = true;

    /*  冒牌排序每次下沉, 都会当前最大(小)沉到末尾  */
    for(j = 0; j < length - 1 && isswap; j++)     /*  共计需要length - 1次下沉  */
    {
        isswap = false;     /*  假设当前不会发生交换, 即数组已经有序  */
        for(i = 0; i < length - 1 - j; i++)
        {
            if(comp(array[i], array[i + 1]))
            {
                isswap = true;
                swap(array[i], array[i + 1]);
            }
        }
#ifdef DEBUG
        PrintDown(array, length, j + 1);        /*  打印当前排序的结果*/
#endif
    }
}


/*  冒泡排序上升法
 *  从后往前两两比较相邻记录的关键字, 如果反序则交换, 直到没有反序的位置
 *  这相当于一个上升(冒泡)的过程, 每次冒泡
 *  当前最大(小)的那个节点就会上升至起始的位置  */
void BubbleSortUp(int *array, int length, int (*comp)(int, int ))
{
    int     i = 0, j = 0;
    bool    isswap = true;

    /*  冒牌排序每次上升, 都会当前最大(小)冒泡到起始  */
    for(j = 0; j < length - 1 && isswap; j++)   /*  共计需要length - 1次冒泡  */
    {
        isswap = false;     /*  假设当前不会发生交换, 即数组已经有序  */
        for(i = length - 1; i > j; i--)
        {
            if(comp(array[i - 1], array[i]))
            {
                isswap = true;
                swap(array[i - 1], array[i]);
            }
        }
#ifdef DEBUG
        PrintUp(array, length, j + 1);        /*  打印当前排序的结果*/
#endif
    }
}

int __tmain(void)
{
    int array[] = {36, 48, 48, 90, 88, 80, 76, 99};
    int length = sizeof(array) / sizeof(array[0]);

    /*  =======Bubble Sort Down=======  */
    printf("begin : ");
    PrintDown(array, length, 0);        /*  打印当前排序的结果*/

    BubbleSortDown(array, length, Large);

    printf("after : ");
    PrintDown(array, length, length);        /*  打印当前排序的结果*/

    printf("again : ");
    BubbleSortDown(array, length, Large);

    printf("\n");


    /*  =======Bubble Sort Up=======  */
    printf("begin : ");
    PrintUp(array, length, 0);        /*  打印当前排序的结果*/

    BubbleSortUp(array, length, Less);

    printf("after : ");
    PrintUp(array, length, length);        /*  打印当前排序的结果*/

    printf("again : ");
    BubbleSortUp(array, length, Less);

    printf("\n");


    return EXIT_SUCCESS;
}
