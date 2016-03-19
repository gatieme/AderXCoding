/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  main test.
 *
 *        Created:  12/31/2012 01:00:43 PM
 *
 *         Author:  Fu Haiping (forhappy), haipingf@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */
#include <stdio.h>

#include "animal-base.h"
#include "dog.h"
#include "cat.h"

int main(int argc, const char *argv[])
{
    dog_t *dog = dog_init();
    cat_t *cat = cat_init();

    /* dog ¿‡≤‚ ‘ */
    animal_eat(dog, "bones");
    animal_walk(dog, 5);
    animal_talk(dog, "wuang wuang wuang...");

    /* cat ¿‡≤‚ ‘ */
    animal_eat(cat, "fish");
    animal_walk(cat, 3);
    animal_talk(cat, "miao miao miao...");

}