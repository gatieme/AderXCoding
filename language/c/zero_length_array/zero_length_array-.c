#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH      1024
#define CURR_LENGTH      512

//  0长度数组
struct zero_buffer
{
    int     len;
    char    data[0];
}__attribute((packed));


//  定长数组
struct max_buffer
{
    int     len;
    char    data[MAX_LENGTH];
}__attribute((packed));


//  指针数组
struct point_buffer
{
    int     len;
    char    *data;
}__attribute((packed));

int main(void)
{
    struct zero_buffer  *zbuffer = NULL;
    struct max_buffer   *mbuffer = NULL;
    struct point_buffer *pbuffer = NULL;


    // =====================
    // 0长度数组  占用-开辟-销毁
    // =====================
    ///  占用
    printf("the length of struct test1:%d\n",sizeof(struct zero_buffer));
    ///  开辟
    if ((zbuffer = (struct zero_buffer *)malloc(sizeof(struct zero_buffer) + sizeof(char) * CURR_LENGTH)) != NULL)
    {
        zbuffer->len = CURR_LENGTH;
        memcpy(zbuffer->data, "Hello World", CURR_LENGTH);


        printf("%d, %s\n", zbuffer->len, zbuffer->data);
    }
    ///  销毁
    free(zbuffer);
    zbuffer = NULL;


    // =====================
    // 定长数组  占用-开辟-销毁
    // =====================
    ///  占用
    printf("the length of struct test2:%d\n",sizeof(struct max_buffer));
    ///  开辟
    if ((mbuffer = (struct max_buffer *)malloc(sizeof(struct max_buffer))) != NULL)
    {
        mbuffer->len = CURR_LENGTH;
        memcpy(mbuffer->data, "Hello World", CURR_LENGTH);


        printf("%d, %s\n", mbuffer->len, mbuffer->data);
    }
    /// 销毁
    free(mbuffer);
    mbuffer = NULL;

    // =====================
    // 指针数组  占用-开辟-销毁
    // =====================
    ///  占用
    printf("the length of struct test3:%d\n",sizeof(struct point_buffer));
    ///  开辟
    if ((pbuffer = (struct point_buffer *)malloc(sizeof(struct point_buffer))) != NULL)
    {
        pbuffer->len = CURR_LENGTH;
        if ((pbuffer->data = (char *)malloc(sizeof(char) * CURR_LENGTH)) != NULL)
        {
            memcpy(pbuffer->data, "Hello World", CURR_LENGTH);


            printf("%d, %s\n", pbuffer->len, pbuffer->data);
        }
    }
    /// 销毁
    free(pbuffer->data);
    free(pbuffer);
    pbuffer = NULL;


    return EXIT_SUCCESS;
}
