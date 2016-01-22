/*************************************************************************
    > File Name: 1.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2015年12月03日 星期四 23时37分01秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>



#define N 15

int curLightestWeight = 1000000;
int curDepth = 0;
int curVertex = 0;
int curWeight = 0;
int depth;
int curCircle[N],bestCircle[N];
bool used[N];
int p[N][N];

void update();
void show();

void genGraphic(int maxWeight)
{
	for(int i = 0;i < N;i++)
	{
		for(int j = 0;j < N;j++)
		{
			if(i == j)
				p[i][j] = 0;
			else
				p[i][j] = rand()%maxWeight + 1;
		}
	}
	for(int i = 0;i < N;i++)
	{
		for(int j = 0;j < N;j++)
		{
			printf("   ");

		}
		printf("%d\n", curLightestWeight);
	{
		curDepth--;
		used[curVertex] = false;
		return;
	}
	else if(curDepth == depth)
	{
		int thisWeight = p[curVertex][0];
		curWeight += thisWeight;
		if(curWeight < curLightestWeight)
		{
			curLightestWeight = curWeight;
			update();
		}
		curDepth--;
		used[curVertex] = false;
		curWeight -= thisWeight;
		return;
	}
	else
	{
		for(int i = 0;i < N;i++)
		{
			if(i == curVertex || used[i] == true)
				continue;
			int thisWeight = p[curVertex][i];
			curWeight += thisWeight;
			MHC_recursion(i);
			curWeight -= thisWeight;
		}
	}
	used[curVertex] = false;
	curDepth--;
	return;
}

void update()
{
	for(int i = 0;i < N;i++)
		bestCircle[i] = curCircle[i];
}

void show()
{
	for(int i = 0;i < N;i++)
		printf("-=>");
	printf("The weight of the circle is ");
}
