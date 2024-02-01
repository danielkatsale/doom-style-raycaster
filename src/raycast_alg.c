#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "raycast_alg.h"

/*typedef struct
{
    Point* data;
    size_t capacity;
    size_t size;

}vector_of_points;
*/

int allocatePolygon(Polygon *poly, int sides)
{
    if (poly == NULL) {
        return -1; // or some error code
    }

    if(sides > 3)
        poly->num_vertices = sides;
    else
    {
        printf("number of sides has to be greater than 2");
        return -1;
    }

    poly->vertices = (Point*) malloc(poly->num_vertices * sizeof(Point));

    if (poly->vertices == NULL) {
        return -1; // or some error code
    }

    return 0;
}


int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if(val == 0) return 0; //colinear
        return (val > 0) ? 1 : 2; //clockwise or counter-clockwise

    return 0;
}

bool onSegment(Point p, Point q, Point r)
{
    if(q.x <= fmax(p.x, r.x) && q.x >= fmin(p.x, r.x) && 
        q.y <= fmax(p.y, r.y) && q.y >= fmin(p.y, r.y))
        return true;

    return false;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case

    if(o1 != o2 && o3 != o4)
        return true;


    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if(o1 == 0 && onSegment(p1, p2, q1)) return true;

    if(o2 == 0 && onSegment(p1, q2, q1)) return true;

    if(o3 == 0 && onSegment(p2, p1, q2)) return true;

    if(o4 == 0 && onSegment(p2, q1, q2)) return true;


    return false;


}

bool does_line_intersect_polygon(Polygon *poly, Segment *line)
{

    for(int i = 0; i < poly->num_vertices; i++)
    {
        Point p = poly->vertices[i];
        Point q = poly->vertices[(i + 1) % poly->num_vertices];

        Segment polygonSegment = {p, q};

        if(doIntersect(line->p, line->q, polygonSegment.p, polygonSegment.q))
            return true;

    }



    return false;
}



/*int main()
{
    Polygon poly;
    allocatePolygon(&poly, 4);

    poly.vertices[0] = (Point){0,0};
    poly.vertices[1] = (Point){1,0};
    poly.vertices[2] = (Point){1,1};
    poly.vertices[3] = (Point){0,1};


    //check for line segment to polygon intersection
    Segment line = {{-1, -1}, {-2, -2}};

    // Check for intersection
    if (does_line_intersect_polygon(&poly, &line)) {
        printf("Line segment intersects with the polygon.\n");
    } else {
        printf("Line segment does not intersect with the polygon.\n");
    }



    free(poly.vertices);



    return 0;
}*/