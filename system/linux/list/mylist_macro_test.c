#include "mylist.h"

typedef struct Node
{
    int m;
    struct list_head ptr;
}Node;

struct list_head *g_h;

int main()
{
    Node *n;

    size_t ss;
    int x = offsetof(Node,m);
    n = list_entry(g_h,Node,ptr);


    return 0;
}
