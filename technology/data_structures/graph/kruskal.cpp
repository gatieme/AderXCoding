#include<iostream>
#include<fstream>
#include <cstring>
using  namespace std;

#define VertexNum 100
#define EdgeNum   100


typedef struct
{
    char    vertex[VertexNum];                                  //  顶点表
    int     edges[VertexNum][VertexNum];                        //  邻接矩阵,可看做边表
    int     n, e;                                               //  图中当前的顶点数和边数
}MGraph;

typedef struct node
{
    int     u;                                                  //  边的起始顶点
    int     v;                                                  //  边的终止顶点
    int     w;                                                  //  边的权值
}Edge;

void kruskal(MGraph G)
{
    int i, j, u1, v1, sn1, sn2, k;
    int vset[VertexNum];                                    //辅助数组，判定两个顶点是否连通
    int E[EdgeNum];                                         //存放所有的边
    k=0;                                                    //E数组的下标从0开始
    for (i=0;i<G.n;i++)
    {
        for (j=0;j<G.n;j++)
        {
            if (G.edges[i][j] != 0 && G.edges[i][j] != INT_MAX)
            {
                E[k].u=i;
                E[k].v=j;
                E[k].w=G.edges[i][j];
                k++;
            }
        }
    }
    heapsort(E,k,sizeof(E[0]));                            //堆排序，按权值从小到大排列
    for (i=0;i<G.n;i++)                                    //初始化辅助数组
    {
        vset[i]=i;
    }
    k=1;                                                   //生成的边数，最后要刚好为总边数
    j=0;                                                   //E中的下标
    while (k<G.n)
    {
        sn1=vset[E[j].u];
        sn2=vset[E[j].v];                                  //得到两顶点属于的集合编号
        if (sn1!=sn2)                                      //不在同一集合编号内的话，把边加入最小生成树
        {
            printf("%d ---> %d, %d",E[j].u,E[j].v,E[j].w);
            k++;
            for (i=0;i<G.n;i++)
            {
                if (vset[i]==sn2)
                {
                    vset[i]=sn1;
                }
            }
        }
        j++;
    }
}
