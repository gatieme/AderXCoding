#include <stdio.h>
#define maxver 10
#define maxright 100
// http://blog.niwota.com/a/357226.htm?visitorid=-1&artid=357226

int G[maxver][maxver],record=0,touched[maxver][maxver];
int circle=0;
int FindCircle(int,int,int,int);


int main( )
{
    int path[maxver][2],used[maxver][maxver];
    int i,j,k,t,min=maxright,exsit=0;
    int v1,v2,num,temp,status=0;
restart:
    printf("Please enter the number of vertex(s) in the graph:\n");
    scanf("%d",&num);
    if(num > maxver || num < 0)
    {
        printf("Error!Please reinput!\n");
        goto restart;
    }
    for(j = 0; j < num; j++)
        for(k = 0; k < num; k++)
        {
            if(j == k)
            {
                G[j][k]=maxright;
                used[j][k]=1;
                touched[j][k]=0;
            }
            else if(j < k)
            {
re:
                printf("Please input the right between vertex %d and vertex %d,if no edge exists please input -1:\n",j+1,k+1);
scanf("%d",&temp);
if(temp>=maxright||temp<-1)
{
printf("Invalid input!\n");
goto re;
}
if(temp==-1)
temp=maxright;
G[j][k]=G[k][j]=temp;
used[j][k]=used[k][j]=0;
touched[j][k]=touched[k][j]=0;
}
}
for(j=0;j<num;j++)
{
path[j][0]=0;
path[j][1]=0;
}
for(j=0;j<num;j++)
{
status=0;
for(k=0;k<num;k++)
if(G[j][k]<maxright)
{
status=1;
break;
}
if(status==0)
break;
}
for(i=0;i<num-1&&status;i++)
{
for(j=0;j<num;j++)
for(k=0;k<num;k++)
if(G[j][k]<min&&!used[j][k])
{
v1=j;
v2=k;
min=G[j][k];
}
if(!used[v1][v2])
{
used[v1][v2]=1;
used[v2][v1]=1;
touched[v1][v2]=1;
touched[v2][v1]=1;
path[i][0]=v1;
path[i][1]=v2;
for(t=0;t<record;t++)
FindCircle(path[t][0],path[t][0],num,path[t][0]);
if(circle)
{/*if a circle exsits,roll back*/
circle=0;
i--;
exsit=0;
touched[v1][v2]=0;
touched[v2][v1]=0;
min=maxright;
}
else
{
record++;
min=maxright;
}
}
}
if(!status)
printf("We cannot deal with it because the graph is not connected!\n");
else
{
for(i=0;i<num-1;i++)
printf("Path %d:vertex %d to vertex %d\n",i+1,path[i][0]+1,path[i][1]+1);
}
return 1;
}
int FindCircle(int start,int begin,int times,int pre)
{ /* to judge whether a circle is produced*/
int i;
for(i=0;i<times;i++)
if(touched[begin][i]==1)
{
if(i==start&&pre!=start)
{
circle=1;
return 1;
break;
}
else
if(pre!=i)
FindCircle(start,i,times,begin);
else
continue;
}
return 1;
}
