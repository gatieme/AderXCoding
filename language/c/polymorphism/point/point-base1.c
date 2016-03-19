//CÎÄ¼þ:point.c
 
#include "point.h"
 
strcut Point
{
	int x;
	int y;
};
 
point * new_point()
{
	point * new_point_ = (point *) malloc(sizeof(point));
 
	return new_point_;
}
 
void free_point(point *point_)
{
	if(point_ == NULL)
    {
		return;
    }
	free(point_);
 
}