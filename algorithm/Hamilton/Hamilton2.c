//
//http://blog.csdn.net/Wiking__acm/article/details/12709023void Hamilton()
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


#define maxn 200
#define INF 1000000000

int N, M;
int graph[maxn][maxn];
int hami[maxn];            //记录回路中的第i个点
bool flag[maxn];



//  哈密顿环求解
void Hamilton();
//  打印哈密顿回路
void PrintHamilton();

int main()
{
    freopen("in.txt", "r", stdin);

    while(scanf("%d", &N) != EOF)
    {
        memset(graph, 0, sizeof(graph));
        memset(flag, 0, sizeof(flag));
        memset(hami, 0, sizeof(hami));

    	for(int i = 1 ; i <= N; i++)
    	{
        	for(int j = 1; j <= N; j++)
        	{
            	scanf("%d", &graph[i][j]);
        	}
    	}

        Hamilton();
        PrintHamilton();
    }

    return EXIT_SUCCESS;
}



void PrintHamilton()
{
    bool f = false;
    for(int i = 1; i <= N; i++)
    {
        flag[hami[i]] = 1;
    }
    for(int i = 1; i <= N; i++)
    {
        if(flag[i] != true)
        {
            f = true;
        }
    }
    if(f == true)
    {
        printf("no solution\n");
    }
    else
    {
        for(int i = 1; i <= N; i++)
        {
            if(i == N)
            {
                printf("%d\n", hami[i]);
            }
            else
            {
                printf("%d ", hami[i]);
            }
        }
    }
}


void Hamilton()
{
    int k;
    bool s[maxn];
    for(int i = 1; i <= N; i++)
    {
        hami[i] = -1;
        s[i] = false;
    }

    k = 1;
    s[1] = true;
    hami[1] = 0;

    while(k > 0)
    {
        hami[k]++;
        while(hami[k] <= N)
        {
            if(!s[hami[k]] && graph[hami[k - 1]][hami[k]])
            {
                break;
            }
            else
            {
                hami[k]++;
            }
        }
        if((hami[k] <= N) && (k != N))
        {
            s[hami[k++]] = true;
        }
        else if((hami[k] <= N) && k == N && graph[hami[k]][hami[1]])
        {
            break;
        }
        else
        {
            hami[k] = -1;
            k--;
            s[hami[k]] = false;
        }
    }
}

