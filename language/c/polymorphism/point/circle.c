//CricleµÄCÎÄ¼þ£ºCricle.c
 
#include "new.h"
 
#include "point.h"
#include "point.r"
 
#include "circle.h"
#include "circle.r"

	static void * Cricle_ctor (void * _self, va_list * app)
{
 
	struct Cricle * self = _self;
 
	self->x = va_arg(*app, int);
 
	self->y = va_arg(*app, int);
 
	return self;
 
}
 
static void Cricle_draw (const void *_self)
{
 
	const struct Cricle * self = _self;
 
	printf("draw (%d,%d), radius = %d", self->x, self->y, self->radius);
}
 
static const struct Base _Cricle = 
{
	sizeof(struct Cricle), Cricle_ctor, 0, Cricle_draw
};
 
const void * Cricle = &_Cricle;
