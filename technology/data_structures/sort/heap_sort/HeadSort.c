#include <stdio.h>
#include <stdlib.h>

#define DEBUG

#define swap(a, b) (a) ^= (b) ^= (a) ^= (b)

//  调整的过程
void ShiftAdjust(int *array, int low, int high)
{
    // array[low]是不满足堆的元素,也是调整的根节点
    for(int f = low, i = 2 * low + 1;  //  i 是左孩子
        i <= high;
        i = 2 * i + 1)                  //  递归其左孩子
    {
        if(i < high
        && array[i] < array[i + 1])   //  比较左孩子和由孩子
        {
            i++;        //  找到较大的那个
        }

        if(array[f] >= array[i])
        {
            break;
        }

        swap(array[f], array[i]);
        f = i;          //  保存其下标
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
    for(i = (length - 1) / 2; i >= 0; i--)
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
    int array[] = {36, 48, 48, 90, 88, 80, 76, 99};
    HeadSort(array, 8);


    return EXIT_SUCCESS;
}
