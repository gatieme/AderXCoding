#include <stdio.h>
#include <stdlib.h>

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


//  调整的过程
void ShiftAdjust(int *array, int low, int high)
{
    printf("%d\n", array[low]);
    // array[low]是不满足堆的元素,也是调整的根节点
    for(int father = low, child = 2 * low + 1;  //  i 是左孩子
        child <= high;
        child = 2 * child + 1)                  //  递归其左孩子
    {
        if(child < high
        && array[child] < array[child + 1])   //  比较左孩子和由孩子
        {
            child++;        //  找到较大的那个
        }

        if(array[father] >= array[child])
        {
            break;
        }
        printf("swap %d %d\n", array[father], array[child]);
        swap(array[father], array[child]);
        father = child;                     //  递归的对子结点进行调整
    }
}

void Print(int *array, int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%4d", array[i]);
    }
    printf("\n");

}

void HeadSort(int *array, int length)
{
    int i;
    for(i = (length - 2) / 2; i >= 0; i--)
    {
        ShiftAdjust(array, i, length - 1);
    }

#ifdef DEBUG
    printf("\ninit the heap...\n");
    Print(array, length);
#endif // DEBUG

    for(int i = length - 1; i > 0; i--)
    {
#ifdef DEBUG
        printf("\nafter swap (%d, %d)...\n", array[0], array[i]);
        Print(array, length);
#endif // DEBUG

        swap(array[0], array[i]);

        ShiftAdjust(array, 0, i - 1);

#ifdef DEBUG
        //printf("\nafter shift ...\n", array[0], array[i]);
        Print(array, length);
#endif // DEBUG
    }

}



int main(void)
{
    int array[] = { 36, 48, 48, 90, 88, 80, 76, 99 };
    HeadSort(array, 8);


    return EXIT_SUCCESS;
}
