#include<stdio.h>
#include<stdlib.h>
int getprimer(int index)
{
    int * primer;
    int i,j,t;
    if(index <= 0)     return -1;

    switch(index)
    {
        case 1:
            return 2;
        case 2:
            return 3;
        case 3:
            return 5;
        case 4:
            return 7;
        default:
            primer = (int*)malloc(sizeof(int)*index);
            primer[0]=2;
            primer[1]=3;
            primer[2]=5;
            primer[3]=7;
            for(i = 3; i != index - 1; ++i)
            {
                t = primer[i];
_NOT_PRIMER :
                t = t + 2;
                for(j = 1; primer[j] * primer[j] <= t; ++j)
                {
                    if(t % primer[j] == 0)
                    {
                        goto _NOT_PRIMER;
                    }
                }
                primer[i + 1] = t;
            }
            free(primer);
            return t;
    }

}

int main()
{
    printf("%d\n",getprimer(10000));
}
