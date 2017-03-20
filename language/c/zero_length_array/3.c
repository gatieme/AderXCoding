#include <stdio.h>
#include <stdlib.h>


struct f1 {
    int x;
    int y[];
} f1 = { 1, { 2, 3, 4 } };

struct f2 {
    struct f1 f1;
    int data[3];
} f2 = { { 1 }, { 5, 6, 7 } };


struct f3
{
    int x;
    int *y;
};

int main(void)
{
    printf("sizeof(f1) = %d\n", sizeof(struct f1));
    printf("sizeof(f2) = %d\n", sizeof(struct f2));
    printf("szieof(f3) = %d\n\n", sizeof(struct f3));

    printf("f1.x = %d\n", f1.x);
    printf("f1.y[0] = %d\n", f1.y[0]);
    printf("f1.y[1] = %d\n", f1.y[1]);
    printf("f1.y[2] = %d\n", f1.y[2]);


    printf("f2.f1.x = %d\n", f1.x);
    printf("f2.f1.y[0] = %d\n", f2.f1.y[0]);
    printf("f2.f1.y[1] = %d\n", f2.f1.y[1]);
    printf("f2.f1.y[2] = %d\n", f2.f1.y[2]);

    return EXIT_SUCCESS;
}
