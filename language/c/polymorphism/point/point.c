//PointµÄCÎÄ¼þ£ºpoint.c
 
#include "point.h"
 
#include "new.h"
 
#include "point.h"
 
#include "point.r"
 
static void * Point_ctor (void * _self, va_list * app)
{
 
	struct Point * self = _self;
 
	self->x = va_arg(*app, int);
 
	self->y = va_arg(*app, int);
 
	return self;
 
}
 
static void Point_draw (const void * _self)
{
 
	const struct Point * self = _self;
 
	printf("draw (%d,%d)", self -> x, self -> y);
}
 
static const struct Base _Point = 
{
	sizeof(struct Point), Point_ctor, 0, Point_draw
};
 
const void * Point = &_Point;
