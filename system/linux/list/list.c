//#ifndef __LIST_H_INCLUDE__
//#define __LIST_H_INCLUDE__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * 该示例参见linux-kernel中内核链表list的实现
 *
 * 文件list.h
 * http://lxr.free-electrons.com/source/scripts/kconfig/list.h#L18
 */
typedef struct list_head
{
    struct list_head    *m_prev;
    struct list_head    *m_next;
}list_head;


typedef struct fox
{
    unsigned long       m_tail_length;          /*  尾巴长度, 以厘米为单位  */
    unsigned long       m_weight;               /*  重量, 以千克为单位      */
    bool                m_is_fantastic;         /*  这只狐狸奇妙么          */
    struct list_head    m_list;
}fox;

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)


#define container_of(ptr, type, member)                     \
{                                                           \
    const_typeof( ((type *)0)->member *m_ptr = (ptr);       \
    (type *)( (char *)m_ptr - offset(type, member))         \
}


#define list_entry(ptr, type, member)                       \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
int main(void)
{
    fox f;
    f.m_tail_length = 100;
    f.m_weight = 100;
    f.m_is_fantastic = true;

    list_head *pl = &(f.m_list);
    fox *pf = list_entry(pl, fox, m_list);

    printf("%p == %p\n", pf, &f);
    printf("tail_length  = %ld\n", pf->m_tail_length);
    printf("weight       = %ld\n", pf->m_weight);
    printf("is_fantastic = %d\n", pf->m_is_fantastic);
    return 0;
}


//#endif  //#define __LIST_H_INCLUDE__
