#ifndef RAYCAST_ALG_H_
#define RAYCAST_ALG_H_
#include <stdbool.h>

typedef struct point
{
    int x, y;
    
}Point;


typedef struct line_segment
{
    Point p, q;

}Segment;


typedef struct polygon
{
    Point* vertices;
    int num_vertices;

}Polygon;

int allocatePolygon(Polygon *poly, int sides);
int orientation(Point p, Point q, Point r);
bool onSegment(Point p, Point q, Point r);
bool doIntersect(Point p1, Point q1, Point p2, Point q2);
bool does_line_intersect_polygon(Polygon *poly, Segment *line);













#endif