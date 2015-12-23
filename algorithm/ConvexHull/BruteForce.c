/// 暴力方式求解凸包问题
///
/// 提示：
/// 考虑Q中的任意四个点A、B、C、D，如果A处于BCD构成的三角形内部，
/// 那么A一定不属于凸包P的顶点集合。

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef LINUX
#include <sys/time.h>
#endif

#define MaxNode 100015


//#define TIME

//  点集
typedef struct Point
{
    int x;
    int y;
}Point;




// 交换
//void Swap(Point *point, int i, int j);
void Swap(Point *left, Point *right);
//叉乘,用于求凸包的面积
double Multiply(Point p1, Point p2, Point p0);

/// 计算两点p1和p2的距离
double Distance(Point p1,Point p2); //p1,p2的距离

// GrahamScan求凸包
void BruteForce(int n);

// 比较两个点的坐标
int Cmp(const void *left, const void *right);

//求凸包的面积
double PolygonArea(Point *point, int length);

// 逆时针方式打印凸包
void PrintPloygon(Point *p, int length);
double PolygonCircumference(Point *point, int n);
//4
//0 0
//0 101
//75 0
//75 101
// 7575
Point point[MaxNode];           //  点集合
int stack[MaxNode];             //  存储凸包中的点集合的位置
int top = 0;                    //  [0~top)存储了位置节点信息
//

int main()
{
    int i;
    int N/*, length*/;

#ifdef RELEASE
    /*FILE *ifp = */freopen("input.txt", "r", stdin);
    /*FILE *ofp = */freopen("bruteforceoutput.txt", "w", stdout);
#endif // RELEASE

#ifdef DEBUG
    /*FILE *ifp = */freopen("in.txt", "r", stdin);
    ///*FILE *ofp = */freopen("bruteforceoutput.txt", "w", stdout);
#endif // DEBUG

    ///
    while(scanf("%d", &N) != EOF)           ///  输入顶点个数
    {
#ifdef DEBUG
        printf("=================START=================\n");
        printf("There are %d input points\n", N);
#endif // DEBUG
        for(i = 0; i < N; i++)
        {
            scanf("%d%d", &(point[i].x), &(point[i].y));
#ifdef DEBUG
            printf("x = %d, y = %d\n", point[i].x, point[i].y);
#endif // DEBUG
        }
//ifdef TIME
        struct timeval start, end;
        gettimeofday( &start, NULL );
        //double cl = (double)start.tv_sec + (double)start.tv_usec / 1000000;

//#endif // TIME

        BruteForce(N);

//#ifdef TIME
        gettimeofday( &end, NULL );
        int timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec -start.tv_usec;
#ifdef DEBUG
        printf("\nN = %5d, usetime = %20dus\n\n", N, timeuse);
#endif
#ifdef RELEASE
        printf("%5d%10d\n", N, timeuse);
#endif


//#endif // TIME

#ifdef DEBUG
        printf("There are %d points in ConvexHull\n", top);
        PrintPloygon(point, top);

        printf("Area = %lf\n", PolygonArea(point, top));
        printf("Ference = %lf\n", PolygonCircumference(point, top));
        printf("==================END==================\n\n\n");
#endif
    }

    return EXIT_SUCCESS;
}


/// 计算两点p1和p2的距离
double Distance(Point p1,Point p2) //p1,p2的距离
{
    return sqrt((double)(p1.x-p2.x) * (double)(p1.x-p2.x) + (double)(p1.y-p2.y)*(double)(p1.y-p2.y));
}

bool EqualPoint(Point *left, Point *right)
{
    return (left->x == right->x
         && left->y == right->y);
}


void InsertPoint(int pos)
{
    int i;
    for(i = 0; i < top; i++)
    {
        if(stack[i] == pos
        && EqualPoint(&point[stack[i]], &point[pos]) == true)
        {
            break;
        }
    }
    if(i == top)
    {
        stack[top++] = pos;
        //printf("%d -=> [%d, %d] insert\n", pos, point[stack[top - 1]].x, point[stack[top - 1]].y);
    }
}
//  算法思想
//  对于N个点构成的机集合中任意选择两个点Pi和Pj，
//  当且仅当该集合的其他点都位于穿过这两点的直线的同一边时
//  他们的连线是该集合凸包边界的一部分
void BruteForce(int n)
{
    int i, j, k;                            //  枚举变量
    int a, b, c;                            //  直线方程
    int result, left, right;                    //  线性规划

    top = 0;
    for(i = 0; i < n; i++)                  //  循环第1个点
    {
        for(j = i + 1; j < n; j++)          //  循环第2个点
        {
            ///  前两个点组成的直线为ax + by = c 即 ax + by - c = 0;
            a = point[j].y - point[i].y;
            b = point[i].x - point[j].x;
            c = point[i].x * point[j].y - point[i].y * point[j].x;

            left = right = 0;
            for(k = 0; k < n; k++)          //  循环第三个点
            {
                //  将第三个点的坐标带入前两个点连线构成的方程ax + by中
                result = a * point[k].x + b * point[k].y - c;

                if(result < 0)      // ax + by - c < 0点在直线的左侧
                {
                    left++;
                }
                else if(result > 0) //  ax + by -c > 0 点在直线的右侧
                {
                    right++;
                }

                if(left * right != 0)
                {
                    break;
                }
            }
            ///  如果循环结束时k == n, 则说明点pi和pj两点是凸包内的点
            if(k == n)
            {
                //  添加的时候
                //  在C++中可以STL的set
                InsertPoint(i);
                InsertPoint(j);
                //printf("")
            }
        }
    }
}



//求凸包的面积
double PolygonArea(Point p[], int n)
{
    double area;
    int i;
    area = 0;
    for(i = 1; i < n; i++)
    {
        area += ((double)p[stack[i - 1]].x * (double)p[stack[i % n]].y - (double)p[stack[i % n]].x * (double)p[stack[i - 1]].y);
        //printf("%lf\n", (double)p[stack[i - 1]].x * (double)p[stack[i % n]].y - (double)p[stack[i % n]].x * (double)p[stack[i - 1]].y);
    }

    return fabs(area) / 2;
}

double PolygonCircumference(Point *point, int n)
{
    double sum = 0.0;
    for(int i = 0; i < n - 1; i++)
    {
        sum += Distance(point[stack[i]], point[stack[i+1]]);
    }
    sum += Distance(point[stack[top]], point[stack[0]] );

    return sum;
}

void PrintPloygon(Point p[], int n)
{
    for(int i = 0;i < n;i++)
    {
        printf("%d %d\n", p[stack[i]].x, p[stack[i]].y);
    }
}




