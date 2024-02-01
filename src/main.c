#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512
#define PI 3.1415926535

float px, py, pdx, pdy, pa;

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

void drawRays3D()
{
    int r, mx, my, mp, dof; 
    float rx, ry, ra, xo, yo;
    ra = pa;



}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    const float speed = 5.0f;

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_A: pa-=0.1; if(pa < 0){ pa+=2*PI;} pdx=cos(pa) * 5; pdy=sin(pa) * 5; break;
            case GLFW_KEY_D: pa+=0.1; if(pa > 2*PI){ pa-=2*PI;} pdx=cos(pa) * 5; pdy=sin(pa) * 5; break;
            case GLFW_KEY_W: px+=pdx; py+=pdy; break;
            case GLFW_KEY_S: px-=pdx; py-=pdy; break;
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


        drawMap2D();
        drawPlayer();

        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    return 0;

}


int main() {
    pdx = cos(pa) * 5; pdy = sin(pa) * 5;
    px = 300, py = 300;

    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1024, 512, "Raycaster", NULL, NULL);

    display(window);

    glfwTerminate();
    return 0;
}
