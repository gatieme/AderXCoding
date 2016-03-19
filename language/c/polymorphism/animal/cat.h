/*
 * =============================================================================
 *
 *       Filename:  cat.h
 *
 *    Description:  cat class derived from animal base class.
 *
 *        Created:  12/31/2012 12:44:05 PM
 *
 *         Author:  Fu Haiping (forhappy), haipingf@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */
#include "animal-base.h"

typedef struct cat_s_ cat_t;

struct cat_s_ {
    animal_t base; /* 继承自 animal 基类 */

    /* 以下还可以添加与 cat 相关的属性和方法(函数指针), 如: */
    /* char *owner; // cat 的主人 */
    /* void (*hunt)(const char *rabbit); // 猎兔犬 */
};

extern cat_t * cat_init();
extern void cat_die(cat_t * cat);
复制代码