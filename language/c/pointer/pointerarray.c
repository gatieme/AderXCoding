//  本程序摘自C/C++程序员生存手册 6.3面试例题21
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    //  array_of_pointers  指针数组
    /*const*/char *pointer_array[] = {"Welcome", "to", "AderStep", "gatieme", "END"};
    //  double_pointer  二重指针, 一个指向char *指针的指针
    char **double_pointer  = pointer_array;         //  此时p指向了str[1]这个指针的地址
    printf("sizeof(pointer_array) = %d\n", sizeof(pointer_array));  //  5个char *的大小


    char rectangular_array[][10] = {"Welcome\0", "to\0", "AderStep\0", "gatieme\0", "END\0"};
    char (*pointer_to_array)[10] = rectangular_array;           //  5个char[10]的大小
    printf("sizeof(rectangular_array) = %d\n", sizeof(rectangular_array));

    //  使用方式相同, 但是寻址方式不同


    //  循环指针数组  -=>  二维指针
    for(int row = 0; row < 4; row++)
    {
        //char *point = *(double_pointer + row) = pointer_array[row];
        for(int col = 0; pointer_array[row][col] != '\0'; col++)
        {
            //*(*(double_pointer + row) + col) == pointer_array[row][col];
            //printf("%c", pointer_array[row][col]);
            printf("%c", *(*(double_pointer + row) + col));

        }
        printf("\n");
    }
    pointer_array[row][col] *(*(double_pointer + row) + col)
    //double_pointer[0] = pointer_array[1];       //  可以修改指针数组中每个指针的指向
    //pointer_array[0][0] = 'a';                  //  但是字符串本身在常量区，无法修改


    //  循环二维数组
    for(int row = 0; row < 5; row++)
    {
        for(int col = 0; rectangular_array[row][col] != '\0'; col++)
        {
            printf("%c", *(*(rectangular_array + row) + col));
        }
        printf("\n");
    }
    //rectangular_array[0] = pointer_array[1];       //
    //rectangular_array[0][0] = 'a';                  //

    return EXIT_SUCCESS;
}
