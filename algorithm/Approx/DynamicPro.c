/// 动态规划求解0-1背包问题

/// 根据递归式填写相应的最优解矩阵


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MaxNode 10000

//代价矩阵计算
void BoolPackCost(int Weight[],int Value[],int C,int num);

//最优解输出
void BoolPackSolution(int B[][MaxNode+1],int Weight[],int Value[],int num,int C);

int C,Weight[MaxNode+1] = {0},Value[MaxNode+1] = {0},B[MaxNode+1][MaxNode+1] = {0};

int main()
{
    int i;
    int num;
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
#endif
#ifdef RELEASE
    freopen("input.txt", "r", stdin);
    freopen("DynamicProOutput.txt", "w", stdout);
#endif

    if(scanf("%d", &num) != EOF)
    {
        scanf("%d", &C);
        for(i = 1; i <= num; i++)
        {
            scanf("%d%d", &(Weight[i]), &(Value[i]));
            //printf("%d:\t%10d%10d\n", i,Weight[i], Value[i]);
        }

        struct timeval start, end;

        gettimeofday( &start, NULL );

        BoolPackCost(Weight,Value,C,num);

        BoolPackSolution(B,Weight,Value,num,C);

        gettimeofday( &end, NULL );

        int runtime = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec -start.tv_usec;
#ifdef DEBUG
        printf("\nN = %d, timeuse = %dus\n", num, runtime);
#endif

#ifdef RELEASE
        printf("%5d%10d\n", num, runtime);
#endif

    }

    return EXIT_SUCCESS;
}

//代价矩阵计算
void BoolPackCost(int Weight[],int Value[],int C,int num)
{
    int i,j;
    for(j = 1; (j < Weight[num])&& (j < C); j++)
        B[num][j] = 0;
    for(j = Weight[num]; j <= C; j++)
        B[num][j] = Value[num];
    for(i = num - 1; i > 1; i--)
    {
        for(j = 1; (j < Weight[i]) && (j <= C); j++)
            B[i][j] = B[i+1][j];
        for(j = Weight[i]; j <= C; j++)
        {
            B[i][j] = B[i + 1][j - Weight[i]] + Value[i];
            if(B[i][j] < B[i + 1][j])
                B[i][j] = B[i + 1][j];
        }
    }
    B[1][C] = B[2][C - Weight[1]] + Value[1];
    if(B[1][C] < B[2][C])
       B[1][C] = B[2][C];
    /*for(i = 1;i <= num;i++)
    {
        for(j=1;j <= C;j++)
            printf("%10d",B[i][j]);
        printf("\n");
    }*/
}

//最优解输出
void BoolPackSolution(int B[][MaxNode+1],int Weight[],int Value[],int num,int C)
{
    int j = C,totalWeight = 0,totalValue = 0;
    int i,X[MaxNode+1] = {0};
#ifdef DEBUG
    printf("Packeage Weoght : %d\n",C);
    printf("\nPackage List : \n");
#endif
    for(i = 1;i < num; i++)
    {
        if(B[i][j] == B[i + 1][j])
            X[i] = 0;
        else{
            X[i] = 1;
            //printf("%10d%10d\n",Weight[i],Value[i]);
            j = j - Weight[i];
        }
    }
    if(B[num][j] == 0)
        X[num] = 0;
    else{
        X[num] = 1;
        //printf("%10d%10d\n",Weight[num],Value[num]);
    }
    for(i = 1;i <= num; i++)
    {
        if(X[i])
        {
            totalWeight += Weight[i];
            totalValue += Value[i];
            //printf("%4d:",i);
#ifdef DEBUG
            printf("%10d%10d\n",Weight[i],Value[i]);
#endif
        }
    }

#ifdef DEBUG
    printf("\nTotal Weight = %d\nTotal Value = %d\n",totalWeight,totalValue);
#endif
}
