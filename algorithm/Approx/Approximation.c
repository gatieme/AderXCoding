/// 动态规划求解0-1背包问题

/// 根据递归式填写相应的最优解矩阵


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MaxNode 10000
#define MAXINT 147483647



#define DEBUG
//代价矩阵计算
void ApproxBoolPacking(int Weight[],int Value[],int cost[][MaxNode+1],int C,int n);

//最优解输出
void ApproxBoolPackSolution(int cost[][MaxNode+1],int Weight[],int Value[],int capcity,int totalValue,int n);

//寻找价值量最大值
int FindMax(int Value[],int n);

int C;
int Weight[MaxNode+1] = {0};
int Value[MaxNode+1] = {0};
int B[MaxNode+1][MaxNode+1] = {0};

int main()
{
    int i;
    int num;

    double epsilon;
    //printf("input ε：");
    scanf("%lf", &epsilon);
    printf("\n");

#ifdef DEBUG
    freopen("input.txt", "r", stdin);
    //freopen("ApproxOutput.txt", "w", stdout);
#endif

#ifdef RELEASE
    freopen("input.txt", "r", stdin);
    freopen("ApproxOutput.txt", "w", stdout);
#endif

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

        printf("\nN = %d, timeuse = %dus\n", num, runtime);
    }

    return EXIT_SUCCESS;
}

//近似解代价矩阵计算
//ApproxBoolPacking(Weight,valueApprox,B,C,num);
void ApproxBoolPacking(int Weight[],int Value[],int cost[][MaxNode+1],int totalValue,int n)
{
    int i,j;
    for(i = 1; i <= totalValue; i++)
    {
        if(i <= Value[n])
        {
            cost[n][i] = Weight[n];
        }
        else
        {
            cost[n][i] = MAXINT;
        }

    }

    for (i = n - 1; i > 0; --i )
    {
        for ( j = 1; j <= totalValue; ++j )
        {
            if(j < Value[i])
            {
                cost[i][j] = cost[i + 1][j];
            }
            else
            {
                if(cost[i + 1][j] < (cost[i + 1][j - Value[i]] + Weight[i]))
                {

                    cost[i][j] = cost[i + 1][j];
                }
                else
                {

                    cost[i][j] = cost[i + 1][j - Value[i]] + Weight[i];;
                }
            }
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

    printf("Package Weight %d %d\n", C, capcity);
    printf("\nPackget List : \n");

    printf("%d", cost[1][j]);
    while ( cost[1][j] > capcity )
    {
        --j;
    }
    printf("j = %d, %d %d\n", j, cost[1][j], capcity);

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
    printf("\nTotalWeight = %d\nTotalValue = %d\n",totalW,totalV);
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


