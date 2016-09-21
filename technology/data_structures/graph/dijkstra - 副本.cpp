#include <iostream>  
#include <string>  
#include <iomanip>  
using namespace std;  
  
#define INFINITY 65535  
#define MAX_VERTEX_NUM 10  
  
typedef struct MGraph
{  
    string  vexs[10];//顶点信息  
    int     arcs[10][10];//邻接矩阵  
    int     vexnum, arcnum;//顶点数和边数  
}MGraph;  
  
int LocateVex(MGraph G, string u)//返回顶点u在图中的位置  
{  
    for(int i = 0; i < G.vexnum; i++)  
        if(G.vexs[i] == u)  
            return i;
    return -1;  
}  
  
void CreateDN(MGraph &G)//构造有向图  
{  
    string v1, v2;  
    int w;  
    int i, j, k;  
    cout<<"请输入顶点数和边数：";  
    cin>>G.vexnum>>G.arcnum;  
  
    cout<<"请输入顶点：";  
    for(i=0; i<G.vexnum; i++)  
        cin>>G.vexs[i];  
  
    for(i=0; i<G.vexnum; i++)  
        for(j=0; j<G.vexnum; j++)  
            G.arcs[i][j]=INFINITY;  
  
    cout<<"请输入边和权值："<<endl;  
    for(k=0; k<G.arcnum; k++)  
    {  
        cin>>v1>>v2>>w;  
        i=LocateVex(G, v1);  
        j=LocateVex(G, v2);  
        G.arcs[i][j]=w;  
    }  
}  
  
//弗洛伊德算法求每一对顶点间的最短路径  
//p[v][w][i]表示当前求得的顶点v到顶点w的最短路径中的第i+1个顶点，这是打印最短路径的关键  
//D[v][w]表示当前求得的顶点v到顶点w的最短路径的长度  
void ShortestPath_FLOYD(MGraph G, int p[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM], int D[][MAX_VERTEX_NUM])  
{  
    int u, v, w, i, j;  
      
    for(v=0; v<G.vexnum; v++)  
        for(w=0; w<G.vexnum; w++)  
        {  
            D[v][w]=G.arcs[v][w];  
            for(u=0; u<G.vexnum; u++)  
                p[v][w][u]=-1;  
            if(D[v][w] < INFINITY)  
            {  
                p[v][w][0]=v;  
                p[v][w][1]=w;  
            }  
        }  
          
        for(u=0; u<G.vexnum; u++)  
            for(v=0; v<G.vexnum; v++)  
                for(w=0; w<G.vexnum; w++)  
                    if(D[v][u] < INFINITY && D[u][w] < INFINITY && D[v][u]+D[u][w] < D[v][w])  
                    {  
                        //更新D  
                        D[v][w]=D[v][u]+D[u][w];  
                        //更新p，从v到w的路径是从v到u，再从u到w的所有路径  
                        for(i=0; i<G.vexnum; i++)  
                        {  
                            if(p[v][u][i]!=-1)  
                                p[v][w][i]=p[v][u][i];  
                            else  
                                break;  
                        }  
                        for(j=1; j<G.vexnum; j++)//注意：这里j从1开始而不是从0开始，因为从v到u的路径最后一个顶点是u, 而从u到w的路径第一个顶点是u，只需打印u一次即可。  
                        {  
                            if(p[u][w][j]!=-1)  
                                p[v][w][i++]=p[u][w][j];  
                            else  
                                break;  
                        }  
                          
                    }  
                    
}  
  
void main()  
{  
    MGraph g;  
    int p[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];  
    int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  
  
    CreateDN(g);  
    for(int  i=0; i<g.vexnum; i++)  
        g.arcs[i][i]=0;  
    ShortestPath_FLOYD(g, p, D);  
  
    cout<<"d矩阵（最短路径长度矩阵）:"<<endl;  
    for(i=0; i<g.vexnum; i++)  
    {  
        for(int j=0; j<g.vexnum; j++)  
            cout<<setw(5)<<D[i][j]<<" ";  
        cout<<endl;  
    }  
  
    cout<<endl;  
    cout<<"各顶点间最短长度及路径如下："<<endl;  
    for(i=0; i<g.vexnum; i++)  
    {  
        for(int j=0; j<g.vexnum; j++)  
        {  
            if(i!=j)  
            {  
                if(D[i][j]!=INFINITY)  
                {  
                    cout<<g.vexs[i]<<"到"<<g.vexs[j]<<"的最短长度为："<<setw(5)<<D[i][j]<<", 最短路径为：";  
                    for(int k=0; k<g.vexnum; k++)  
                    {  
                        if(p[i][j][k]!=-1)  
                            cout<<g.vexs[p[i][j][k]]<<" ";  
                        else  
                            break;  
                    }  
                    cout<<endl;  
                }  
                else  
                    cout<<g.vexs[i]<<"到"<<g.vexs[j]<<"不可达"<<endl;  
            }  
              
        }  
        cout<<endl;         
            
    }  
  
  
  
}  