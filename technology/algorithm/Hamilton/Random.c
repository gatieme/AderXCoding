/*************************************************************************
    > File Name: Random.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2015年11月30日 星期一 15时48分20秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_VERTEX 200

int graph[MAX_VERTEX][MAX_VERTEX];

int main(void)
{
    int row, col;
    freopen("input2.txt", "w", stdout);

    srand(time(NULL));

    for(int vertex = 5; vertex <= MAX_VERTEX; vertex += 5)     //  顶点数目为vertex
    {
        for(row = 0; row < vertex; row++)                 //  循环每行
        {
            graph[row][row] = 10000;

            for(col = row + 1; col < MAX_VERTEX; col++)
            {
                graph[row][col] = graph[col][row] = rand() % 100 + 1;
            }

        }

        printf("%d\n", vertex);
        for(row = 0; row < vertex; row++)
        {
            for(col = 0; col < vertex; col++)
            {
                printf("%6d", graph[row][col]);
            }
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}
