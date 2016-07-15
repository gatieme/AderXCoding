#include <stdio.h>
#include <stdlib.h>

#define DEBUG

#include "common.h"

typedef struct CStruct
{
    int m_a;
    int m_b;
}CStruct;


int __tmain(void)
{
    CStruct cc = {
        .m_a = 10,
        .m_b = 20,
    };

    int *pa = &(cc.m_a);
    CStruct *pc = container_of(pa, CStruct, m_a);
    printf("%p %p\n", &cc, pc);
    printf("%d %d\n", pc->m_a, pc->m_b);

    return 0;
}
