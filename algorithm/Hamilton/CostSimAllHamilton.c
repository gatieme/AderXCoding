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
#define START        1    //  哈密顿环的起始顶点

int N, M;
int visited[MAX_SIZE];

int graph[MAX_SIZE][MAX_SIZE],hami[MAX_SIZE];

//  哈密顿环的权重
//int cost[MAX_SIZE];             // 哈密顿环的权值信息
int cost = 0;
//  哈密顿环的数目计数器
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
    freopen("costsimallhamiltonoutput.txt", "w", stdout);
#endif

    while(scanf("%d", &N) != EOF) //  顶点数目N, 边数目M
    {

#ifdef DEBUG
        printf("=================START=================\n");
#endif
        memset(graph, 0, MAX_SIZE);
        //memset(cost, 0, MAX_SIZE);
        counter = 1;

        ScanGraph(graph);

#ifdef DEBUG
        PrintGraph(graph);
#endif

        //  计算运行时间
        struct timeval start, end;
        gettimeofday(&start, NULL);


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


    return 0;
}



//  判断路径是否可行
int IsPathOk(int graph[][MAX_SIZE], int depth, int hami[])
{
    if(visited[hami[depth]] == 1)       //  如果当前顶点已经被访问
    {
        //printf("point:%d has been visited\n", hami[depth]);
        return 0;
    }

    if(depth < N)   //  内部顶点判断是否有路径即可
    {
        //printf("graph[%d][%d] == %d\n", hami[depth - 1], hami[depth], graph[hami[depth - 1]][hami[depth]]);
		return graph[hami[depth - 1]][hami[depth]];
    }
	else        //  最后一个顶点处理要判断是否有路径, 还需要判断是否可以形成环路
	{
        //printf("graph[%d][%d] == %d\n", hami[depth - 1], hami[depth], graph[hami[depth - 1]][hami[depth]]);
   		return graph[hami[N - 1]][hami[N]] && graph[hami[N]][hami[1]];
	}
}

bool HamiltonProcess(int (*graph)[MAX_SIZE],int depth, int hami[])
{

    for(hami[depth] = 1; hami[depth] <= N; hami[depth]++)    // 下一个顶点可能是1~N中的任何一个顶点
    {
        //  此时hami[depth] == K进入栈hami[depth]中,
        //  成为栈顶元素, 判断其是否可成为一条哈密顿的节点IsPathOk()
        //
        //  基于深度有限搜索策略, 如果期望使用爬山法,可在此处进行一个权值判断
        //  每次选择权值最小的哪个进行扩展
        if(IsPathOk(graph, depth, hami) != 0)   //  判断当前是否有边可达, 即该节点hami[depth]可行
   		{
            ////////////////////////////////////////////////////////////////////
			visited[hami[depth]] = true;        // 访问顶点K = hami[depth]
            ////////////////////////////////////////////////////////////////////

            //  哈密顿图的花费加上当前访问的边信息
            //cost[counter] += graph[hami[depth - 1]][hami[depth]];
            cost += graph[hami[depth - 1]][hami[depth]];

#ifdef DEBUG
            //printf("depth= %d, add line %d -=> %d, cost = %d, total = %d\n", depth, hami[depth -1], hami[depth], graph[hami[depth - 1]][hami[depth]], cost[counter]);
            printf("depth= %d, add line %d -=> %d, cost = %d, total = %d\n", depth, hami[depth -1], hami[depth], graph[hami[depth - 1]][hami[depth]], cost);
#endif

            ///if(k == N || HamiltonProcess(graph, k+1, hami))
            //  递归的进行下一个顶点, 其实本质上也是一层相当于K++
            //  外层循环遍历所有可能的第k的顶点的可能位置
            //  没发现一个可能的顶点K,存入hami[k]中,
            //  然后接着递归查找下一个顶点K+1,
            HamiltonProcess(graph, depth + 1, hami);        //  递归的进行下一个顶点
#ifdef DEBUG
            if(depth == N)
            {
                //  哈密顿环是条回路, 花费加上回边的权值
                //cost[counter] += graph[hami[N]][hami[1]];
                cost += graph[hami[N]][hami[1]];
                printf("     add back line %d -=> %d, cost = %d, total = %d\n", hami[N], hami[1], graph[hami[N]][hami[1]], cost);
                //  此处输出时应注意, 对于大多数编译器来说, 函数参数的入栈顺序
				//printf("Case %2d, Cost  %3d:", counter, cost[counter]);
				printf("Case %2d, Cost  %3d:", counter, cost);
                counter++;

                ////////////////////////////////////////////////////////////////
                ///  BUG No.2 201512.01 14:58 -=> importmant
                ///  一个哈密顿环查找结束后, 计数器counter++
                ///  因此在退栈的时候,cost减去的其实是当前新的哈密顿环的权值信息
                ///  因此新的哈密顿环是从当前栈中, 也就是前一个哈密顿环的退出开始的
                ///
                //cost[counter] = cost[counter - 1];
                ///
                ///   注意: 原来保存的是每个哈密顿路的权值信息,现在只保存当前的
                ///         无需保存每条哈密顿环的cost的原因是,
                ///         只有一个栈hami保存了当前哈密顿环的信息
                ///         因此对应的也只需要一个cost保存当前哈密顿环的信息
                ////////////////////////////////////////////////////////////////


                for(int i = 1; i <= N + 1; i++)
     		    {
                    if(i == N + 1)
                    {
                        printf("%3d\n", hami[1]);
                    }
      				else
                    {
                        printf("%3d -=> ", hami[i]);
     			    }
                }
                //continue;

     			//printf("=> %d\n", hami[1]);
     		}
#endif
            ////////////////////////////////////////////////////////////////////
            ///  BUG No.1 2015.11.29 10:34 -=> importmant
            ///  递归跳出后, 应该清除标志信息 否则的话, 下次查找无法正常进行
    		visited[hami[depth]] = false;           //  递归结束后清除标志
            ////////////////////////////////////////////////////////////////////

            //cost[counter] -= graph[hami[depth - 1]][hami[depth]];
            cost -= graph[hami[depth - 1]][hami[depth]];
#ifdef DEBUG
            //printf("depth= %d, add line %d -=> %d, cost = %d, total = %d\n", depth, hami[depth -1], hami[depth], graph[hami[depth - 1]][hami[depth]], cost[counter]);
            printf("depth= %d, add line %d -=> %d, cost = %d, total = %d\n", depth, hami[depth -1], hami[depth], graph[hami[depth - 1]][hami[depth]], cost);
#endif
        }
    }
	return false;
}

void Hamilton(int graph[][MAX_SIZE],int hami[])
{
    /*for(int start = 1; start <= N; start++)         //  循环每个顶点为起始
    {
        for(int i = 1; i <= N; i++) //  初始化visited位false
        {
            visited[i] = false;
        }
    */
    int depth = 1;
    hami[depth] = START;                   //  起始的位置为S

    visited[hami[depth]] = true;              //  先访问起始的顶点

#ifdef DEBUG
    printf("\nStart from point %d\n", hami[depth]);
#endif
        //  进行深度优先搜索
    HamiltonProcess(graph, depth + 1, hami);
    //}
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
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= N; j++)
		{
			printf("%3d", graph[i][j]);
		}
		printf("\n");
	}
    printf("\nThe all hamilton of the garph\n");
}
