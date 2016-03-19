//≤‚ ‘≥Ã–Ú£∫main.c
 
#include "point.h"
 
#include "new.h"
 
int main (int argc, char ** argv)
{
 	void * p = new(Point, 1, 2);
 
	draw(p);
 
	delete(p);
}