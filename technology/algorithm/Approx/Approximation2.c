/// 动态规划求解0-1背包问题

/// 根据递归式填写相应的最优解矩阵


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MaxNode 10000
#define MAXINT 147483647

 //int valueApprox[MaxNode + 1] = {0};
//代价矩阵计算
void ApproxBoolPacking(int Weight[],int Value[],int cost[][MaxNode+1],int C,int n);

//最优解输出
void ApproxBoolPackSolution(int cost[][MaxNode+1],int Weight[],int Value[],int capcity,int totalValue,int n);

//寻找价值量最大值
int FindMax(int Value[],int n);

int C,Weight[MaxNode+1] = {0},Value[MaxNode+1] = {0},B[MaxNode+1][MaxNode+1] = {0};

int main()
{
    int i;
    int num;

    double epsilon;
    //printf("input ε：");
    scanf("%lf", &epsilon);
    printf("\n");

    freopen("input.txt", "r", stdin);
    freopen("ApproxOutput.txt", "w", stdout);


    int valueApprox[MaxNode + 1] = {0};

    while(scanf("%d", &num) != EOF)
    {
        int totalValue = 0;

        scanf("%d", &C);

        for(i = 1; i <= num; i++)
        {
            scanf("%d%d", &(Weight[i]), &(Value[i]));
            //totalValue += Value[i];
            //printf("%d:\t%10d%10d\n", i,Weight[i], Value[i]);
        }

        //  查找最大的权值
        int maxValue = FindMax(Value,num);
        //printf("%d\n", maxValue);

        double k = (double)num / epsilon;
        //printf("k = num / epsilon = %f\n", k);

        for (i = 1; i <= num; ++i)
        {
            valueApprox[i] = (int)(Value[i] * k / maxValue);

            //printf("valueApprox[i] = (int)(Value[i] * k / maxValue) = %d\n", valueApprox[i]);
            totalValue += valueApprox[i];
        }

        //printf("totalValue = %d\n", totalValue);

        struct timeval start, end;

        gettimeofday( &start, NULL );

        //  开始
        ApproxBoolPacking(Weight,valueApprox,B,totalValue,num);

        //
        ApproxBoolPackSolution(B,Weight,valueApprox,C,totalValue,num);

        gettimeofday( &end, NULL );

        int runtime = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec -start.tv_usec;

        printf("\n点数N为 : %d, 运行时间为: %d微秒\n", num, runtime);
    }

    return EXIT_SUCCESS;
}

//近似解代价矩阵计算
//ApproxBoolPacking(Weight,valueApprox,B,C,num);
void ApproxBoolPacking(int Weight[],int Value[],int cost[][MaxNode+1],int totalValue,int n)
{
    int i,j;
    //for(i = 1; i <= n; i++) printf("Value[%3d] = %d\n",i,Value[i]);
    //for(i = 1; i <= n; i++) printf("Weight[%3d] = %d\n",i,Weight[i]);
    //printf("Value[%3d] = %d\n",n,Value[n]);
    for(i = 1; i <= totalValue; i++)
    {
        //int currentWeight = Weight[n],currentValue = Value[n];
        if(i <= Value[n])
        {
            cost[n][i] = Weight[n];
        }
        else
        {
            cost[n][i] = MAXINT;
        }

        //cost[n][i] = i <= currentValue ? currentWeight : MAXINT;
        //printf("cost[%2d][%3d] = %d\n",n,i,cost[n][i]);
    }

    //for(i = 1; i <= totalValue; i++) printf("cost[%2d][%3d] = %d\n",n,i,cost[n][i]);
    for (i = n - 1; i > 0; -- i )
    {
        //int currentWeight = Weight[i],currentValue = Value[i];
        for ( j = 1; j <= totalValue; ++j )
        {
            if(j < Value[i])
            {
                cost[i][j] = cost[i + 1][j];
            }
            else
            {
                //printf("Enter else!!");
                if(cost[i + 1][j] < (cost[i + 1][j - Value[i]] + Weight[i]))
                {
                    //printf("%d<%d\n",cost[i + 1][j], cost[i + 1][j - Value[i]] + Weight[i]);

                    cost[i][j] = cost[i + 1][j];
                }
                else
                {
                    //printf("%d<%d\n",cost[i + 1][j], cost[i + 1][j - Value[i]] + Weight[i]);

                    cost[i][j] = cost[i + 1][j - Value[i]] + Weight[i];;
                }
                //cost[i][j] = cost[i + 1][j] < cost[i + 1][j - currentValue] + currentWeight ? cost[i + 1][j] : cost[i + 1][j - currentValue] + currentWeight;
            }
            //printf("cost[%2d][%3d] = %d\n",i,j,cost[i][j]);
        }
    }
}

//最优解输出
void ApproxBoolPackSolution(int cost[][MaxNode+1],int Weight[],int value[],int capcity,int totalValue,int n)
{
    int j = totalValue;
    int i;
    int X[MaxNode+1] = {0};
    int totalW = 0,totalV = 0;
    //memset(X, 0, MaxNode + 1);

    printf("包的容量为：%d %d\n",C, capcity);
    printf("\n包内各物品的重量与价值分别为：\n");

    printf("%d", cost[1][j]);
    while ( cost[1][j] > capcity )
    {
        --j;
    }
    printf("j = %d, %d %d\n", j, cost[1][j], capcity);

    //
    for ( i = 1; i < n ; ++ i )
    {
        if(j < 0)
        {
            break;
        }
        if ( cost[i][j] != cost[i + 1][j] )
        {
            X[i] = 1;
            j -= value[i];

            printf("i = %d is in packeage, j = %d, value = %d, weight = %d\n", i, j, value[i], Weight[i]);
        }
    }

    if(cost[n][j] == Weight[n])
    {
        X[n] = 1;
    }

    for(i = 1; i < n; i++)
    {
        if(X[i])
        {
            //printf("%4d:",i);
            totalW += Weight[i];
            totalV += Value[i];
            printf("%10d%10d\n",Weight[i],value[i]);
        }
    }
    printf("\n总重量为：%d\n总价值为：%d\n",totalW,totalV);
}

//寻找价值量最大值
int FindMax(int Value[],int n)
{
    int Vmax = -1;
    for(int i = 1; i < n; i++)
        if(Value[i] > Vmax)
            Vmax = Value[i];
    return Vmax;
}


