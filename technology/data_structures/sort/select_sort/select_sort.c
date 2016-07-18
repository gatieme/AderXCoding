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


void SelectSort(int *array, int length, int (*comp)(int, int))
{
    for(int i = 0; i < length - 1; i++)
    {
        int selectIndex = i;

        for(int j = i + 1; j < length; j++)
        {
            if(array[j] < array[selectIndex])
            {
                selectIndex = j;
            }
        }

        if(selectIndex != i)
        {
            swap(array[i], array[selectIndex]);
        }
#ifdef  DEBUG
        PrintUp(array, length, i + 1);
#endif
    }
}

int __tmain(void)
{
    int array[] = {48, 36, 32, 99, 88, 80, 76, 90};
    int length = sizeof(array) / sizeof(array[0]);

    printf("begin : ");
    PrintUp(array, length, 0);        /*  打印当前排序的结果*/

    SelectSort(array, length, Less);

    printf("after : ");
    PrintUp(array, length, length);        /*  打印当前排序的结果*/

    printf("\n");



    return EXIT_SUCCESS;
}
