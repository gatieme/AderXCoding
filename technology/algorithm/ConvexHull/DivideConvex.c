#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef LINUX
#include <sys/time.h>
#endif
#define MAX_SIZE  10000
//#define DEBUG
#define RELEASE
#define TIME


typedef struct {
	int x,y;
}Point;

//  输入数据
void RandInput(Point *point, int length);

//  交换位置
void Swap(Point *left, Point *right);
//  打印信息
int Print(Point *convex, int length);
// 按照x的从小到大进行排序，X相同按照Y从小到大排序
int CmpByX(const void *left, const void *right);

//向convex数组里面添加point数组首尾项
void AddHeadTail(Point *point, Point *convex);

//向convex数组里面添加 point[i]
void AddPosition(Point *point,Point *convex,int i);


//处理point[first]->point[final]射线左侧的点
void DealWithLeft(int first,int final,Point *point,Point *convex);
void DivideConvexHull(Point *point,Point *convex);

void PrintPoints(Point *convex, int length);

int N;
Point point[MAX_SIZE];
Point convex[MAX_SIZE];
int position[MAX_SIZE];
int convexCount=0;	//convex里面插入值的个数


int main(void)
{
#ifdef RELEASE
    /*FILE *ifp = */freopen("input.txt", "r", stdin);
    /*FILE *ofp = */freopen("bruteforceoutput.txt", "w", stdout);
#endif // RELEASE

#ifdef DEBUG
    /*FILE *ifp = */freopen("in.txt", "r", stdin);
    ///*FILE *ofp = */freopen("bruteforceoutput.txt", "w", stdout);
#endif // DEBUG


	while(scanf("%d", &N) != EOF)
    {
    	convexCount = 0;
        for(int i = 0; i < N; i++)
        {
            scanf("%d%d",&point[i].x,&point[i].y);
            //printf("%d\t%d\n",point[i].x,point[i].y);
        }
#ifdef DEBUG
        printf("=================START=================\n");
        printf("There are %d inpu points\n", N);
        PrintPoints(point, N);
#endif // DEBUG

//#ifdef TIME
        struct timeval start, end;
        gettimeofday( &start, NULL );
        //double cl = (double)start.tv_sec + (double)start.tv_usec / 1000000;

//#endif // TIME
        //给数组排序，按x从小到大
        qsort(point, N, sizeof(point[0]), CmpByX);

#ifdef DEBUG
        printf("The input data after sort\n");
        PrintPoints(point,N);
#endif // DEBUG

        //获取convex数组，存放所有结果顶点
        DivideConvexHull(point,convex);

        gettimeofday( &end, NULL );
        int timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec -start.tv_usec;
#ifdef DEBUG
        printf("N : %5d, time: %10dus\n", N, timeuse);
#endif
#ifdef RELEASE
        printf("%5d%20d\n", N, timeuse);
#endif
        //cl = ((double)end.tv_sec + (double)end.tv_usec / 1000000) - cl;
        //printf("execution time : %0.3fs\n", cl);

//#endif // debug


#ifdef DEBUG
        printf("There are %d points in ConvexHull\n", convexCount);
        PrintPoints(convex, convexCount);
        printf("==================END==================\n\n\n");
#endif // DEBUG
    }
	return EXIT_SUCCESS;
}



//  输入数据
void RandInput(Point *point, int length)
{
    srand(time(NULL));
    for(int i = 0; i < length; i++)
    {
        point[i].x = rand() % 100 + 1;
        point[i].y = rand() % 100 + 1;
    }
}




//交换位置
void Swap(Point *left, Point *right)
{
    Point temp;
    temp = *left;
    *left = *right;
    *right = temp;
}



// 按照x的从小到大进行排序，X相同按照Y从小到大排序
int CmpByX(const void *left, const void *right)
{
    Point *leftPoint = (Point *)left;
    Point *rightPoint = (Point *)right;
    if(leftPoint->x != rightPoint->x)
    {
        return (leftPoint->x - rightPoint->x);
    }
    else
    {
        return (leftPoint->y - rightPoint->y);
    }
}



//向convex数组里面添加point数组首尾项
void AddHeadTail(Point *point, Point *convex)
{
	convex[convexCount].x=point[0].x;
	convex[convexCount++].y=point[0].y;

	convex[convexCount].x=point[N - 1].x;
	convex[convexCount++].y=point[N - 1].y;
}

//向convex数组里面添加 point[i]
void AddPosition(Point *point,Point *convex,int i)
{
	convex[convexCount].x=point[i].x;
	convex[convexCount++].y=point[i].y;
}

//处理point[first]->point[final]射线左侧的点
void DealWithLeft(int first, int final, Point *point, Point *convex)
{
	int max = 0, index = -1;
	int i = first;
	if(first < final)                   //   point[first]->point[final]射线左侧
	{
		for(; i < final; i++)
		{
			int x1 = point[first].x,y1 = point[first].y;
			int x2 = point[final].x,y2 = point[final].y;
			int x3 = point[i].x;
			int y3 = point[i].y;


			int compute = x1 * y2 + x3 * y1 + x2 * y3 - x3 * y2 - x2 * y1 - x1 * y3;
			if(compute > max)
			{
				max = compute;
				index = i;
			}
		}
	}
	else
	{
		for(; i >= 0; i--)//point[final]->point[first]射线左侧
		{
			int x1 = point[first].x,y1 = point[first].y;
			int x2 = point[final].x,y2 = point[final].y;
			int x3 = point[i].x,y3 = point[i].y;


			int compute = x1 * y2 + x3 * y1 + x2 * y3 - x3 * y2 - x2 * y1 - x1 * y3;
			if(compute > max)
			{
				max = compute;
				index = i;
			}
		}
	}


	if(index!=-1)	//取到point[index]（即最高点） ，这个点与point[final]、point[first]构成的三角形面积最大
	{
		AddPosition(point,convex,index);
		DealWithLeft(first,index,point,convex);
		DealWithLeft(index,final,point,convex);
	}
}
void DivideConvexHull(Point *point,Point *convex)
{
	AddHeadTail(point,convex);	//将首尾两个点并入convex[15]

	DealWithLeft(0,N - 1,point,convex);	//处理point[0]->point[N - 1]射线左边的点
	DealWithLeft(N - 1,0,point,convex);	//处理point[N - 1]->point[0]射线右边的点
}


void PrintPoints(Point *convex, int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%d\t%d\n", convex[i].x, convex[i].y);
    }
}
