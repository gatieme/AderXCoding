/// POJ 2007(计算几何初步——极角排序)
/// http://acm.hust.edu.cn/vjudge/contest/view.action?cid=59391
///POJ 凸包题目 1113 1228 2007 2079 2187
///poj 3348 : Cows  题意：一片草地上有n课树，现在你想用绳子圈出一个尽可能大的面积出来养牛。已知每只牛需要50单位的面积，问最多能养几只牛。

/// HDU 1392 Surround the Trees
/// HDU 3662 求凸包表面多边形个数


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef LINUX
#include <sys/time.h>
#endif

#define MaxNode 100015
//#define TIME
//#define DEBUG


//  DIA
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
int GrahamScan(int n);

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
Point point[MaxNode];
int stack[MaxNode];
int top;
//

int main()
{
    int i;
    int N/*, length*/;
#ifdef DEBUG
    /*FILE *ifp = */freopen("in.txt", "r", stdin);
    ///*FILE *ofp = */freopen("GrahamScanOutput.txt", "w", stdout);
#endif // DEBUG

#ifdef RELEASE
    /*FILE *ifp = */freopen("input.txt", "r", stdin);
    /*FILE *ofp = */freopen("GrahamScanOutput.txt", "w", stdout);
#endif // RELEASE

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
            printf("x = %d, y= %d\n", point[i].x, point[i].y);
#endif // DEBUG
        }

//#ifdef TIME
        struct timeval start, end;
        gettimeofday( &start, NULL );

//#endif // TIME
/////////////////////////////////////////////////////////////////////
        GrahamScan(N);
///////////////////////////////////////////////////////////////////////

//#ifdef TIME
        gettimeofday( &end, NULL );
        int timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec -start.tv_usec;
        //printf("N : %5d, time: %dus\n", N, timeuse);

#ifdef DEBUG
        printf("N= %5d, timeuse = %10dus\n", N, timeuse);
#endif

#ifdef RELEASE
        printf("%5d%20d\n", N, timeuse);
#endif

//#endif // TIME

#ifdef DEBUG

        PrintPloygon(point, top + 1);

        printf("%lf\n", PolygonArea(point, top + 1));
        printf("%lf\n", PolygonCircumference(point, top + 1));  // zoj 1453
        printf("==================END==================\n\n\n");

#endif // DEBUG
    }

    return EXIT_SUCCESS;
}



// 交换第数组中第i个节点和第j个节点
//void Swap(Point point[],int i,int j)
//{
//    Point tmp;
//    tmp=point[i];
//    point[i]=point[j];
//    point[j]=tmp;
//}

void Swap(Point *left, Point *right)
{
    Point temp;
    temp = *left;
    *left = *right;
    *right = temp;

}

//  关于叉乘请使用如下信息
//  http://www.cnblogs.com/devtang/archive/2012/02/01/2334977.html
//  http://blog.csdn.net/tmljs1988/article/details/7259331
//  返回(p1 - p0) * (p2 -p0)的叉乘
//  若结果为正，则<p0, p1>在<p0,p2>的顺时针方向
//  若为0, 则<p0, p1>与<p0,p2>共线
//  若为负, 则<p0, p1>在<p0,p2>的逆时针方向
//  可以根据这个函数确定两条线段在交叉点处的转向
//  <0则左转, 大于0则右转, 等于0则共线
double Multiply(Point p1,Point p2,Point p0) //叉乘
{
    return ((p1.x - p0.x) * (p2.y-p0.y) - (p1.y-p0.y) * (p2.x-p0.x));
}

/// 计算两点p1和p2的距离
double Distance(Point p1,Point p2) //p1,p2的距离
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
//  比较两个点的大小
int Cmp(const void *left, const void *right)
{
    Point *leftPoint = (Point *)left;
    Point *rightPoint = (Point *)right;
    double k = Multiply(*leftPoint, *rightPoint, point[0]);
    if(k < 0)
    {
        return 1;
    }
    else if(k == 0 && Distance(*leftPoint, point[0]) >= Distance(*rightPoint, point[0])) return 1; //极角相同，比距离
    else return -1;
}

//
int GrahamScan(int n)
{
    int pos, leftDownPos;

    leftDownPos = 0;                //  初始位置是第0个位置
    for(pos = 1; pos < n; pos++)    //  找到最左下的点p0
    {
        if((point[pos].y < point[leftDownPos].y)                                //  如果当前点的纵坐标要小与最小点
        || ((point[pos].y == point[leftDownPos].y) && (point[pos].x < point[leftDownPos].x)))     //  或者总左边相同但是横坐标要小
        {
            leftDownPos = pos;
        }
    }
    Swap(&point[0], &point[leftDownPos]);                   // 找到的leftDownPos位置的点

    ///  现在Point中Y坐标最小的点，作为极点，位于Point[0]中
    ///  对顶点按照对极点Point[0]的极角按照从小到大的顺序排序
    ///  对于其中极角相同的点按照离Point[0]的距离从远到近进行排序
    qsort(point + 1, n - 1, sizeof(point[0]), Cmp); //按极角排序


    ///  依次将Point0, Point1, Point2入栈
    for(pos = 0; pos <= 2; pos++)
    {
        stack[pos] = pos; //p0,p1,p2入栈
    }
//    for(top  = 0; top < 3; top++)
//    {
//        stack[top] = top;
//    }
    top = 2;

    for(pos = 3; pos < n; pos++) //最终凸包的各顶点的编号依次存在stack[]中。
    {
        ///  Muliti > 0  -=>  表示<Point[strack[top -1]], Point[pos]> 在 <Point[strack[top -1]],point[stack[top]]>的顺时针方向
        ///  也就是说Point[pos]
        while(Multiply(point[pos], point[stack[top]], point[stack[top-1]]) >= 0) //弹出非左转的点
        {
            if(top == 0)
            {
                break;
            }
            top--;
        }

        //++top;
        stack[++top] = pos;
    }
    return top;
}
//求凸包的面积
double PolygonArea(Point p[], int n)
{
    double area;
    int i;
    area = 0;
    for(i = 1; i < n; i++)
    {
        area += (p[stack[i - 1]].x * p[stack[i % n]].y - p[stack[i % n]].x * p[stack[i - 1]].y);
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
