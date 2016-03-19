//Í·ÎÄ¼þ£ºpoint.h
 
#ifndef POINT_H
 
#define POINT_H
 
struct Point;
 
typedef struct Point point;
 
point * new_point(); //newer a point object
 
void free_point(point *point_);// free the allocated space
 
#endif