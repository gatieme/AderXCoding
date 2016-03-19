/*
 * =============================================================================
 *
 *       Filename:  cat.c
 *
 *    Description:  cat class derived from animal base class.
 *
 *        Created:  12/31/2012 12:52:26 PM
 *
 *         Author:  Fu Haiping (forhappy), haipingf@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cat.h"

static void eat(char *food);

static void walk(int steps);

static void talk(char *msg);

cat_t * cat_init()
{
    cat_t *cat = (cat_t *)malloc(sizeof(cat_t));
    animal_t *animal = (animal_t *)animal_init("cat");
    memcpy(&(cat->base), animal, sizeof(animal_t));

    cat->base.animal_ops->eat = eat;
    cat->base.animal_ops->walk = walk;
    cat->base.animal_ops->talk = talk;

    free(animal);
    return cat;
}

void cat_die(cat_t *cat)
{
    /* nothing to do here. */
}

static void eat(char *food)
{
    printf("I'm a cat, I eat %s\n", food);
}

static void walk(int steps)
{
    printf("I'm a cat, I can jump %d steps one time\n", steps);
}

static void talk(char *msg)
{
    printf("I'm a cat, I talk my language %s\n", msg);
}
¸´ÖÆ´úÂë