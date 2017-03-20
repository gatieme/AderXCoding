#include <stdio.h>
#include <stdlib.h>

struct str
{
    int len;
    char s[0];
};

struct foo
{
    struct str *a;
};

int main(void)
{
    struct foo f = { NULL };

    printf("sizeof(struct str) = %d\n", sizeof(struct str));

    printf("before f.a->s.\n");
    if(f.a->s)
    {
        printf("before printf f.a->s.\n");
        printf(f.a->s);
        printf("before printf f.a->s.\n");
    }

    return EXIT_SUCCESS;
}
