#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mylist.h"


typedef struct Data
{
    int id;
    char data[128];
}Data;

typedef struct DataNode
{
    Data d;
    struct list_head ptr;
}DataNode;

//
struct list_head g_head;
void test_list()
{
	int i=0;
	INIT_LIST_HEAD(&g_head);
	for(i=0;i<100;++i)
	{
		DataNode *n=(DataNode*)malloc(sizeof(DataNode));
		n->d.id=100-i;
		list_add(&n->ptr,&g_head);
	}
	DataNode *n1 = list_first_entry(&g_head,DataNode,ptr);
    printf("%p\n", n1);

	return ;
}

int main()
{
	test_list();

	return 0;
}
//haier
