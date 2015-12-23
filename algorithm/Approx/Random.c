#include <stdio.h>
#include <time.h>



int main(void)
{
    int num,flag,base;
    printf("请选择需要生成的数据量：\n");
    printf("1：数据量100，取范围（1~1000）\n");
    printf("2：数据量1000，取范围（1~10000）\n");
    printf("3：数据量10000，取范围（1~100000）\n");
    printf("请选择：");
    scanf("%d", &flag);

    switch(flag)
    {
    case 1:
        num = 100;
        base = 1000;
        break;
    case 2:
        num = 1000;
        base = 10000;
        break;
    case 3:
        num = 10000;
        base = 100000;
        break;
    default:
        printf("输入错误！\n");
        exit(0);
    }


    FILE *fp = freopen("input.txt", "w", stdout);

    printf("%d\n", num);

    srand(time(NULL));

    printf("%d\n", rand() % base + 1);

    for(int j = 0; j < num ; j++)
    {
        printf("%10d%10d\n", rand() % base + 1,rand() % base + 1);
    }

    return 0;
}

