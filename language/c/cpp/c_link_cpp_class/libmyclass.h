#ifndef __LIB_MY_CLASS_H_INCLUDE__
#define __LIB_MY_CLASS_H_INCLUDE__


#ifdef __cplusplus
extern "C"
{
#endif



void* create_myclass( );

void destroy_myclass(void* thisC);

int call_myclass_func(void *thismc, int i);


#ifdef __cplusplus
}
#endif



#endif  //  #define __LIB_MY_CLASS_H_INCLUDE__
