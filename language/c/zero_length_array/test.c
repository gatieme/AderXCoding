#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct zerodemo{
        int num;
        char zero[0];
};

struct ptrdemo{
        int num;
        char *zero;
};

#define LEN (sizeof(char)*100)

int main(){
        struct zerodemo *zd =(struct zerodemo *)malloc(sizeof(struct zerodemo) + LEN);
        zd->num = 10;
        memset(zd->zero,'a', LEN);

        struct ptrdemo *pd = (struct ptrdemo *)malloc(sizeof(struct ptrdemo));
        pd->zero = (char *)malloc(LEN);
        pd->num = 10;
        memset(pd->zero, 'a', LEN);

        return EXIT_SUCCESS;
}
