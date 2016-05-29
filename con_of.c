#include <stdio.h>
#include <stdlib.h>


typedef struct CStruct
{
    int m_a;
    int m_b;
}CStruct;

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

/*
 *  get the struct(type) from the pointer pstr(one of his member)
 *  ptr     : the pointer point to the member whose type is member you know
 *  type    : the type of the struct you want get
 *  member  : the member's name in type struct
 */
#define container_of(ptr, type, member)                             \
({                                                                  \
    const typeof( ((type *)0)->member) *m_ptr = (ptr);              \
    (type *)( (char *)m_ptr - offsetof(type, member) );             \
})



int main(void)
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
