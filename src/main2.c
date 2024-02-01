#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "raycast_alg.h"
#define PI 3.1415926535

float px, py, pdx, pdy, pa;
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

float boxPosX = 0.0f, boxPosY = 0.0f;
float px = 300, py = 300;

int mapX=8,mapY=8,mapS=64;

int map[] = 
{
    1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,1,0,0,0,1,1,1,
    1,0,0,1,0,0,0,1,
    1,1,0,0,0,1,1,1,
    1,0,0,0,0,0,0,1,
    1,1,1,0,0,0,1,1,
    1,1,1,1,1,1,1,1,


};

Polygon poly;
Segment line = {{100, 300}, {500, 200}};




void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    const float speed = 5.0f;

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W: pa-=0.1; if(pa < 0){ pa+=2*PI;} pdx=cos(pa) * 5; pdy=sin(pa) * 5; break;
            case GLFW_KEY_S: pa+=0.1; if(pa > 2*PI){ pa-=2*PI;} pdx=cos(pa) * 5; pdy=sin(pa) * 5; break;
            case GLFW_KEY_A: px+=pdx; py+=pdy; break;
            case GLFW_KEY_D: px-=pdx; py-=pdy; break;
        }
    }
}

void drawPlayer()
{
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2f(px, py);          
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px,py);
    glVertex2i(px+pdx*5, py+pdy*5);
    glEnd();
    

}

void draw_polygon_with_line(Polygon *poly, Segment *line)
{
    
    

    

    //for(int i = 0; i < poly.num_vertices; i++)
    //{
        //Point p = poly.vertices[i];
        //Point q = poly.vertices[(i + 1) % poly.num_vertices];

        //Segment polygonSegment = {p, q};
            glBegin(GL_QUADS);
                glVertex2f(poly->vertices[0].x,poly->vertices[0].y);
                glVertex2f(poly->vertices[1].x,poly->vertices[1].y);
                glVertex2f(poly->vertices[2].x, poly->vertices[2].y);
                glVertex2f(poly->vertices[3].x, poly->vertices[3].y);
            glEnd();

            glBegin(GL_LINES);
                glVertex2f(line->p.x, line->p.y);
                glVertex2f(line->q.x, line->q.y);

            glEnd();


    //}
}

void drawMap2D()
{
    int x,y,xo,yo;

    for(y = 0;y<mapY;y++)
    {
        for(x = 0;x<mapX;x++)
        {
            if(map[y*mapX+x] == 1){ glColor3f(1,1,1); } else {glColor3f(0,0,0);}
            xo=x*mapS; yo = y*mapS;
            glBegin(GL_QUADS);
                glVertex2f(xo + 1,yo + 1);
                glVertex2f(xo + 1,yo+mapS-1);
                glVertex2f(xo+mapS-1, yo+mapS-1);
                glVertex2f(xo+mapS-1, yo+1);
            glEnd();

        }
    }
}

int display(GLFWwindow *window)
{


    



     if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        return -1;
    }

    glfwSetKeyCallback(window, keyCallback);

    int window_width = 1024, window_height = 512;


    glfwGetFramebufferSize(window, &window_width, &window_height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, window_width, window_height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3,0.3,0.3, 0);

        glLoadIdentity();

        draw_polygon_with_line(&poly, &line);
        //drawMap2D();
        //drawPlayer();

        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    return 0;

}


int main() {

    pdx=cos(pa) * 5; pdy=sin(pa) * 5;
    float px = 300, py = 300;

    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1024, 512, "Raycaster", NULL, NULL);

    allocatePolygon(&poly, 4);
    poly.vertices[0] = (Point){0,0};
    poly.vertices[1] = (Point){51,0};
    poly.vertices[2] = (Point){1,100};
    poly.vertices[3] = (Point){700,200};

    display(window);

    glfwTerminate();
    return 0;
}
