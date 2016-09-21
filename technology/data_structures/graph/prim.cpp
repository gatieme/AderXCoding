#include<iostream>
#include<fstream>
#include <cstring>
using  namespace std;

#define MAX 100

long graph[MAX][MAX];

long prim(long graph[][MAX], int n)
{
    long lowcost[MAX];
    long mst[MAX];
    int i, j, min, minid, sum = 0;
    for (i = 2; i <= n; i++)
    {
        lowcost[i] = graph[1][i];
        mst[i] = 1;
    }
    mst[1] = 0;
    for (i = 2; i <= n; i++)
    {
        min = INT_MAX;
        minid = 0;
        for (j = 2; j <= n; j++)
        {
            if (lowcost[j] < min && lowcost[j] != 0)
            {
                min = lowcost[j];
                minid = j;
            }
        }
        cout << "V" << mst[minid] << "-V" << minid << "=" << min << endl;
        sum += min;
        lowcost[minid] = 0;
        for (j = 2; j <= n; j++)
        {
            if (graph[minid][j] < lowcost[j])
            {
                lowcost[j] = graph[minid][j];
                mst[j] = minid;
            }
        }
    }
    return sum;
}

int main()
{
    int i, j, k, m/*顶点数目*/, n/*边的数目*/;
    int cost;
#ifdef READ_BY_DELIM

    ifstream cin("in.txt");
    char s[1024];
    char *delim = ",";
    char *p;

    int row = 1, col = 1;
    cin >>m;
    while(cin >>s)
    {
        cout <<s <<endl;
        p = strtok(s, delim);
        while(p != NULL)
        {
            //cout <<p <<endl;
            sscanf(p, "%d", &graph[row][col++]);
            if(col - 1 == row)
            {
                graph[row][col - 1] = INT_MAX;
            }
            //cout <<graph[row][col - 1] <<"  ";
            p = strtok(NULL, delim);
            if(col == m + 1)
            {
                col = 1;
                row++;
                //cout <<endl;
            }
        }
    }
#else // READ_BY_DELIM
    ifstream cin("in2.txt");
    while(cin >>m >>n)
    {
        for(int i = 0; i < n; i++)
        {
            cin >>i >>j;
            cin >>graph[i][j];
        }
    }

#endif // READ_BY_DELIM

    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cout <<graph[i][j] <<" ";
        }
        cout <<endl;
    }


    //求解最小生成树
    cost = prim(graph, m);
    //输出最小权值和
    cout <<cost <<endl;
    return 0;
}
