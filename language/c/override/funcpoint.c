#include <stdio.h>
#include <stdlib.h>

typedef struct _int_param
{
    int param1;
    int param2;
}INT_PARAM;

typedef struct _double_param_
{
    double param1;
    double param2;
}DOUBLE_PARAM;


typedef void* (*ADDFUNC)(void*);

void* int_add_func(void* wParam)
{
    INT_PARAM* lParam = (INT_PARAM*)wParam;
    int res = lParam->param1 + lParam->param2;

    printf("result = %d\n", res);
}

void* double_add_func(void* wParam)
{
    DOUBLE_PARAM* lParam = (DOUBLE_PARAM*)wParam;
    double res = lParam->param1 + lParam->param2;

    printf("result = %f\n", res);

}

void* add_func(ADDFUNC f, void* wParam)
{
    return f(wParam);
}

int main()
{
    INT_PARAM val1 = {10, 20};

    DOUBLE_PARAM val2 = {30.5, 40.5};

    add_func(int_add_func, &val1);


    add_func(double_add_func, &val2);



    return 0;
}
