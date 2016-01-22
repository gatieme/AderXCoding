#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include <sys/time.h>
#define MAX_SIZE 200
#define INF 1000000000

int N, M;
int graph[MAX_SIZE][MAX_SIZE];
int hami[MAX_SIZE];            //记录回路中的第i个点
bool flag[MAX_SIZE];



//  哈密顿环求解
void Hamilton();
//  打印哈密顿回路
void PrintHamilton();
//  打印图的信息
void PrintGraph();
//  输入图的信息
void ScanGraph();



int main()
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif

#ifdef RELEASE
    freopen("input.txt", "r", stdin);
    freopen("hamiltonoutput.txt", "w", stdout);
#endif

    while(scanf("%d", &N) != EOF)
    {
        memset(graph, 0, sizeof(graph));
        memset(flag, 0, sizeof(flag));
        memset(hami, 0, sizeof(hami));

        ScanGraph();

#ifdef DEBUG
        printf("=================START=================\n");
	    PrintGraph();
#endif

       //  计算运行时间
//ifdef TIME
        struct timeval start, end;
        gettimeofday( &start, NULL );
//#endif // TIME
        //  图graph的哈密顿环
        Hamilton();


	    gettimeofday( &end, NULL );
        int timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec -start.tv_usec;

#ifdef DEBUG
        PrintHamilton();
        printf("\nN = %5d, usetime = %10dus\n\n", N, timeuse);
        printf("==================END==================\n\n\n");
#endif
#ifdef RELEASE
        printf("%5d%10d\n", N, timeuse);
#endif
    }

    return EXIT_SUCCESS;
}



void PrintHamilton()
{
#ifdef DEBUG
    printf("\nThe all hamilton of the garph\n");
#endif
    bool f = false;
    for(int i = 0; i < N; i++)
    {
        flag[hami[i]] = 1;
    }
    for(int i = 0; i < N; i++)
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
        for(int i = 0; i <= N; i++)
        {
            if(i == N)
            {
                printf("%2d\n", hami[0] + 1);
            }
            else
            {
                printf("%2d -=>", hami[i] + 1);
            }
        }
    }
}


void Hamilton()
{
    int k;
    bool visited[MAX_SIZE];

    //  初始化设置图中没有哈密顿环
    for(int i = 0; i < N; i++)
    {
        hami[i] = -1;
        visited[i] = false;
    }

    // 从第一个点出发开始寻找
    k = 1;
    visited[0] = true;
    hami[0] = 0;

    while(k >= 0)
    {
        hami[k]++;              //

        while(hami[k] < N)                      //  走到最后一个定点为止
        {
            if(visited[hami[k]] != true
            && graph[hami[k - 1]][hami[k]])     //  从k-1到当前顶点有路可达
            {
                break;
            }
            else                //  否则此路不可达, 继续寻找下一个顶点
            {
                hami[k]++;
            }
        }

        if((hami[k] < N)
        && (k != N - 1))
        {
            visited[hami[k++]] = true;
        }
        else if((hami[k] < N)
             && (k == N - 1)
             && graph[hami[k]][hami[0]])
        {
            break;
        }
        else
        {
            hami[k] = -1;
            k--;
            visited[hami[k]] = false;
        }
    }
}



// 输出图的信息
void PrintGraph(/*int (*graph)[MAX_SIZE], int n*/)
{
	printf("There are %d points and %d vertexs\n", N, M);
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
#if 0                               //  也可以使用输入矩阵的方式输入图的信息
                scanf("%d", &a);
                graph[i][j] = a;
#endif
			printf("%3d", graph[i][j]);
		}
		printf("\n");
	}
}



//  输入图的信息
void ScanGraph()
{
#ifdef SCAN_VERTEX  //  输入边的信息
    scanf("%d", &M);
    for(int i = 0; i < M; i++)
    {
       int a, b;
        scanf("%d%d",&a,&b);
        a--;
        b--;
        graph[a][b] = graph[b][a] = true;
    }
#endif // SCAN_VERTEX

    for(int i = 0 ; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
}
