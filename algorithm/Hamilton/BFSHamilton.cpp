#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <iomanip>


#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <ctime>
#include <cmath>

#include <sys/time.h>

#define START 1
//#define MAX_VERTEX 20
int N;
#define MAX_VERTEX 210
#define MAX_VALUE 10000

using namespace std;


//#define DEBUG
//#define RELEASE
/*
class QueueNode
{
private:

    int dadadwe;

    int hkhkhg[2][MAX_VERTEX];

    int gywew[2][MAX_VERTEX];

    int c[MAX_VERTEX][MAX_VERTEX];

public:
	int path[MAX_VERTEX];

    int trygm;

    int yrnfgagh;

    QueueNode(int k, int A[MAX_VERTEX][MAX_VERTEX], int n)
	{
		for(int i = 0;i < 2; i++)
        {
			for(int j = 0;j < N; j++)
			{
				hkhkhg[i][j] = 0;
				gywew[i][j] = 0;
			}
        }
        trygm = n;

        yrnfgagh = 0;

        dadadwe = k;

        for(int i = 0; i < N; i++)
        {
		    path[i] = 0;
        }

        path[dadadwe] = trygm + 1;

        cdfraasf(c, A);

        gy();
	}

	QueueNode(int k, QueueNode A)
	{
		cdfraasf(hkhkhg, A.hkhkhg);
		cdfraasf(gywew, A.gywew);
		trygm = A.trygm + 1;
		dadadwe = k;
		cdfraasf(c, A.c);

        yrnfgagh = A.yrnfgagh+c[A.dadadwe][dadadwe];

        cdfraasf(path,A.path);
		path[dadadwe]=trygm+1;

		for(int i = 0;i < N; i++)
		{
			if(!c[A.dadadwe][i])
			{
				hkhkhg[0][A.dadadwe]--;
				hkhkhg[1][i]--;
			}
			c[A.dadadwe][i] = MAX_VALUE;
		}
		gywew[0][A.dadadwe]=1;

        for(int i = 0; i < N; i++)
		{
			if(!c[i][dadadwe])
			{
				hkhkhg[0][i]--;
				hkhkhg[1][dadadwe]--;
			}
			c[i][dadadwe]=MAX_VALUE;
		}

        gywew[1][dadadwe]=1;

		if(trygm != N - 1)
		{
			if(!c[dadadwe][START-1])
			{
				hkhkhg[0][dadadwe]--;
				hkhkhg[1][START-1]--;
			}
			c[dadadwe][START - 1]=MAX_VALUE;

        }
		gy();
	}

	void gy()
	{
		int j;

		for(int i = 0;i < N; i++)
			if(!gywew[0][i]&&!hkhkhg[0][i])
			{
				int m=lqess(i,c);
				yrnfgagh=yrnfgagh+m;
				for(int j = 0;j < N; j++)
				{
					c[i][j]=c[i][j]-m;
					if(!c[i][j])
					{
						hkhkhg[0][i]++;
						hkhkhg[1][j]++;
					}
				}
			}

			for(int i = 0; i < N; i++)
				if(!gywew[1][i]&&!hkhkhg[1][i])
				{
					int m=cqess(i,c);
					yrnfgagh=yrnfgagh+m;
					for(j = 0;j < N;j++)
					{
						c[j][i]=c[j][i]-m;
						if(!c[j][i])
						{
							hkhkhg[0][j]++;
							hkhkhg[1][i]++;
						}
					}
				}
	}

	void cdfraasf(int A[MAX_VERTEX],int B[MAX_VERTEX])
	{
		for(int i = 0;i < N; i++)
			A[i]=B[i];
	}

	void cdfraasf(int A[MAX_VERTEX][MAX_VERTEX],int B[MAX_VERTEX][MAX_VERTEX])
	{
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				A[i][j]=B[i][j];
	}

	int lqess(int i,int A[MAX_VERTEX][MAX_VERTEX])
	{
		int qess=A[i][0];
		for(int j=0;j<N;j++)
			if(qess>A[i][j])
				qess=A[i][j];
		return qess;
	}

	int cqess(int i,int A[MAX_VERTEX][MAX_VERTEX])
	{
		int qess=A[0][i];
		for(int j=0;j<N;j++)
			if(qess>A[j][i])
				qess=A[j][i];
		return qess;
    }

	bool operator < (const QueueNode &B)const
	 {
		 return yrnfgagh>B.yrnfgagh;
	 }
};
*/



class Graph
{
private :
    //  图的基本信息存储
    int  m_vervex;
    int  m_graph[MAX_VERTEX][MAX_VERTEX];
    bool m_visited[MAX_VERTEX];
    int m_start;
    int m_depth;
    int m_currCost;
    int m_minCost;

    //  优先队列
    queue<int> m_queue;
    int     hami[MAX_VERTEX];
public:
    friend istream& operator>>(istream& in, Graph& hami)
    {
        int i, j;
#ifdef DEBUG
        cout <<"There are " <<N <<" points in this graph" <<endl;
#endif
        for(i = 1;i <= N; i++)
        {
	        for(j = 1;j <= N; j++)
	        {
                in >>hami.m_graph[i][j];
#ifdef DEBUG
                cout <<std::setw(5)<<hami.m_graph[i][j] <<" ";
#endif
            }
#ifdef DEBUG
	        cout <<endl;
#endif
        }

        return in;
    }

    //  判断路径是否可行
    int IsPathOk(int depth, int current, int next)
    {
        if(m_visited[next] == true)       //  如果当前顶点已经被访问
        {
            //printf("point:%d has been visited\n", next);
            return 0;
        }

        if(depth < N)   //  内部顶点判断是否有路径即可
        {
            //printf("%d\n", __LINE__);
		    return m_graph[current][next] && m_graph[current][next] != MAX_VALUE;
        }
	    else        //  最后一个顶点处理要判断是否有路径, 还需要判断是否可以形成环路
	    {
            //printf("graph[%d][%d] == %d\n", hami[depth - 1], hami[depth], graph[hami[depth - 1]][hami[depth]]);
   		    return m_graph[current][next] && m_graph[current][m_start] && m_graph[current][m_start] != MAX_VALUE;
	    }
    }
    void GenMinHamilton( )
    {
        m_depth = 1;
        m_start = 1;
        m_currCost  = 0;
        memset(m_visited, 0, MAX_VERTEX);
        //  起始元素入队列
        this->m_queue.push(m_start);

        while(this->m_queue.empty() != true)
        {
            int curr = this->m_queue.front(); //  取出对头元素

            //cout <<"Pop " <<curr <<endl;
            this->m_queue.pop();

            m_visited[curr] = true;
#ifdef DEBUG
            cout <<"visited " <<curr <<endl;
#endif
            this->hami[m_depth] = curr;
            if(m_depth > 1)
            {
#ifdef DEBUG
                cout <<" depth" <<m_depth <<", add line" <<hami[m_depth - 1] <<" -=> "<<hami[m_depth] <<", Cost = " <<m_graph[hami[m_depth - 1]][hami[m_depth]] <<endl;
#endif
                m_currCost += m_graph[hami[m_depth - 1]][hami[m_depth]];
            }

            if(N == m_depth)
            {
#ifdef DEBUG
                cout <<"add back line " <<curr <<" -=> "<<START <<", Cost =" << m_graph[curr][START]<<endl;
#endif
                m_currCost += m_graph[curr][START];
                //cout <<this->m_queue.size() <<endl;
                break;
            }
            else
            {
                m_depth++;
            }

            for(int next = 1; next <= N; next++)
            {
#ifdef DEBUG
                cout <<endl <<curr <<" -=> "<<next <<", Cost = " <<m_graph[curr][next] <<endl;
#endif
                if(IsPathOk(m_depth, curr, next) != 0)
                {
                    this->m_queue.push(next);
                }
            }
        }

    }

    void ClearQueue()
    {
        while(this->m_queue.empty() != true)
        {
            this->m_queue.pop();
        }
    }

    void PrintHamilton()
    {
        this->ClearQueue();
        cout <<"Cost :" <<this->m_currCost;
        for(int i = 1; i <= m_depth + 1; i++)
        {
            if(i == m_depth + 1)
            {
                cout <<setw(3) <<hami[1] <<endl;
            }
            else
            {
                cout <<setw(3) <<hami[i] <<" -=>";
            }
        }
    }
};

int main()
{
#ifdef DEBUG
    ifstream fin("in2.txt");
    cin.rdbuf(fin.rdbuf());
#endif

#ifdef RELEASE
    ifstream fin("input2.txt");
    cin.rdbuf(fin.rdbuf());

    ofstream fout("BFSOutput.txt");
    cout.rdbuf(fout.rdbuf());
#endif

    Graph graph;
    while(cin >>N)
    {

#ifdef DEBUG
        cout <<"=================START=================" <<endl <<endl;
#endif

        cin >>graph;                         //  输入哈密顿环的信息

        //  计算运行时间
        struct timeval start, end;
        gettimeofday(&start, NULL);


        graph.GenMinHamilton();     //  生成哈密顿回路的信息
#ifdef DEBUG
        graph.PrintHamilton();
#endif
        //wndbgn Ret(A);
	    //Ret.opwbngjgf(0, 0);
        //Ret.prin();

		gettimeofday(&end, NULL);
        int timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

#ifdef DEBUG
        cout <<endl <<"N = " <<std::setw(5) <<N <<", " <<std::setw(10)<<timeuse <<"us" <<endl <<endl;
        cout <<"==================END==================" <<endl <<endl <<endl;
#endif

#ifdef RELEASE
        cout <<std::setw(5) <<N <<std::setw(10)<<timeuse <<endl;
#endif

    }
	return EXIT_SUCCESS;
}

