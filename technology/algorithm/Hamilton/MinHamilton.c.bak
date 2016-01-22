#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#ifdef LINUX
    #include <sys/time.h>
#endif
#ifdef WINDOWS
    #include <windows.h>
#endif

//#define RELEASE
//#define DEBUG           //  调试输出信息

#define MAX_SIZE 10001

int N, M;
int visited[MAX_SIZE];

int graph[MAX_SIZE][MAX_SIZE],hami[MAX_SIZE];

//int s;                    //

int counter = 1;


//  判断路径是否可行
int IsPathOk(int graph[][MAX_SIZE], int depth, int hami[]);

//  递归的进行哈密顿搜索
bool HamiltonProcess(int graph[][N + 1], int depth, int hami[]);

//  搜索所有可能的哈密顿环路
void Hamilton(int graph[][MAX_SIZE], int hami[]);


// 输入图的信息
void ScanGraph(int (*graph)[MAX_SIZE]);
// 输出图的信息
void PrintGraph(int (*graph)[MAX_SIZE]);

int main()
{
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
#endif

#ifdef RELEASE
	freopen("input.txt", "r", stdin);
    freopen("allhamiltonoutput.txt", "w", stdout);
#endif

    while(scanf("%d", &N) != EOF) //  顶点数目N, 边数目M
    {
#ifdef DEBUG
    printf("=================START=================\n");
#endif
        memset(graph, 0, MAX_SIZE);
        counter = 1;

        ScanGraph(graph);
#ifdef DEBUG
        PrintGraph(graph);
#endif

        //  计算运行时间
//ifdef TIME
        struct timeval start, end;
        gettimeofday( &start, NULL );
        //double cl = (double)start.tv_sec + (double)start.tv_usec / 1000000;
//#endif // TIME


        //  所有图graph的所有哈密顿环
	    Hamilton(graph, hami);

	    gettimeofday(&end, NULL);
        int timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec -start.tv_usec;

#ifdef DEBUG
        printf("\nN = %5d, usetime = %10dus\n\n", N, timeuse);
        printf("==================END==================\n\n\n");
#endif

#ifdef RELEASE
        printf("%5d%10d\n", N, timeuse);
#endif
    }


    return EXIT_SUCCESS;
}



//  判断路径是否可行
int IsPathOk(int graph[][MAX_SIZE], int depth, int hami[])
{
    if(visited[hami[depth]] == 1)       //  如果当前顶点已经被访问
    {
        //printf("point:%d has been visited\n", hami[k]);
        return 0;
    }

    if(depth < N)   //  内部顶点判断是否有路径即可
    {
        //printf("graph[%d][%d] == %d\n", hami[k - 1], hami[k], graph[hami[k-1]][hami[k]]);
		return graph[hami[depth - 1]][hami[depth]];
    }
	else        //  最后一个顶点处理要判断是否有路径, 还需要判断是否可以形成环路
	{
        //printf("graph[%d][%d] == %d\n", hami[k - 1], hami[k], graph[hami[k-1]][hami[k]]);
   		return graph[hami[N - 1]][hami[N]] && graph[hami[1]][hami[N]];
	}
}

bool HamiltonProcess(int (*graph)[MAX_SIZE],int depth, int hami[])
{
    for(hami[depth] = 1; hami[depth] <= N; hami[depth]++)    // 下一个顶点可能是1~N中的任何一个顶点
    {
    	if(IsPathOk(graph, depth, hami) != 0)   //  判断当前是否有边可达
   		{
            ////////////////////////////////////////////////////////////////////
			visited[hami[depth]] = true;        // 访问顶点K
            ////////////////////////////////////////////////////////////////////

            ///if(k == N || HamiltonProcess(graph, k+1, hami))
            //  递归的进行下一个顶点, 其实本质上也是一层相当于K++
            //  外层循环遍历所有可能的第k的顶点的可能位置
            //  没发现一个可能的顶点K,存入hami[k]中,
            //  然后接着递归查找下一个顶点K+1,
            HamiltonProcess(graph, depth + 1, hami);        //  递归的进行下一个顶点
#ifdef DEBUG
            if(depth == N)
            {
				printf("Case %2d:  ", counter++);

     	        for(int i = 1; i <= N + 1; i++)
     		    {
                    if(i == N + 1)
                    {
                        printf("=> %d\n", hami[1]);
                    }
      				else
                    {
                        printf("=> %d", hami[i]);
     			    }
                }
     			//printf("=> %d\n", hami[1]);
     		}
#endif
            ////////////////////////////////////////////////////////////////////
            ///  BUG -=> importmant
            ///  递归跳出后, 应该清除标志信息 否则的话, 下次查找无法正常进行
    		visited[hami[depth]] = false;           //  递归结束后清除标志
            ////////////////////////////////////////////////////////////////////
		}
    }
	return false;
}

void Hamilton(int graph[][MAX_SIZE],int hami[])
{
    for(int start = 1; start <= N; start++)         //  循环每个顶点为起始
    {
        for(int i = 1; i <= N; i++) //  初始化visited位false
        {
            visited[i] = false;
        }

        hami[1] = start;                   //  起始的位置为S

        visited[hami[1]] = true;              //  先访问起始的顶点

#ifdef DEBUG
        printf("\nStart from point %d\n", hami[1]);
#endif
        //  进行深度优先搜索
        HamiltonProcess(graph, 2, hami);
    }
}

void ScanGraph(int (*graph)[MAX_SIZE])
{
    /*
    for(int i = 1; i <= M; i++)     //  循环输入M条边
    {
       scanf("%d%d", &a, &b);
			graph[a][b] = 1;
            graph[b][a] = 1;
    }
    */

    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
}

// 输出图的信息
void PrintGraph(int (*graph)[MAX_SIZE])
{

	printf("\nThere are %d points and %d vertexs\n", N, M);
	for(int row = 1; row <= N; row++)
	{
		for(int col = 1; col <= N; col++)
		{
#if 0                               //  也可以使用输入矩阵的方式输入图的信息
            scanf("%d", &a);
            graph[i][j] = a;
#endif
			printf("%3d", graph[row][col]);
		}
		printf("\n");
	}
    printf("\nThe all hamilton of the garph\n");
}

//  对图的邻接矩阵进行预处理
//  首先 每行减去一个最小值
//  要保证每行（已经保证）每列都有一个零元素
//  否则的话如果某一列存在一个非零元素
//  那么让这一列再减去一个这一列的最小值
void PreTreatGraph(int (*graph)[MAX_SIZE])
{
    int minRowPos[MAX_SIZE] = {1};  //  存储每一行的最小值的位置, 初始为第一行

    int minColPos[MAX_SIZE] = {1};  //  存储每一列的最小值的位置，初始化为第一列

    for(int row = 1; row <= N; row++)
    {
        for(int col = 1; col <= N; col++)
        {
            // 寻找每一行的最小值
            if(graph[row][col] < graph[minRowPos[row]])
            {
                    minColPos[row] = col;
            }
            if(graph[row][col] < graph)
        }
    }
}
