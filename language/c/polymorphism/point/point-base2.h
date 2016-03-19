#ifndef POINT _H
 
#define POINT_H
 
typedef struct Point point;
 
typedef struct pointPrivate pointPrivate;
 
strcut Point
 
{
 
Struct pointPrivate *pp;
 
};
 
int get_x(point *point_);
 
int get_y(point *point_);
 
point * new_point(); //newer a point object
 
void free_point(point *point_);// free the allocated space
 
#endif
 
