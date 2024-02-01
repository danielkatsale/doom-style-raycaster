#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512
#define PI 3.1415926535
#define P2 PI / 2
#define P3 3 * PI / 2
#define DR 0.0174533 // one degree in radians
float px, py, pdx, pdy, pa;

float boxPosX = 0.0f, boxPosY = 0.0f;
float px = 300, py = 300;

int mapX = 8, mapY = 8, mapS = 64;

int map[] =
    {
        1,
        1,
        1,
        1,
        1,
        1,
        1,
        1,
        1,
        0,
        0,
        0,
        0,
        0,
        0,
        1,
        1,
        1,
        0,
        0,
        0,
        1,
        1,
        1,
        1,
        0,
        0,
        1,
        0,
        0,
        0,
        1,
        1,
        1,
        0,
        0,
        0,
        1,
        1,
        1,
        1,
        0,
        0,
        0,
        0,
        0,
        0,
        1,
        1,
        1,
        1,
        0,
        0,
        0,
        1,
        1,
        1,
        1,
        1,
        1,
        1,
        1,
        1,
        1,

};

float dist(float ax, float ay, float bx, float by, float ang)
{

    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void drawRays3D()
{
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo, disT;
    ra = pa;

    ra = pa - DR * 30;
    if (ra < 0)
    {
        ra += 2 * PI;
    }

    if (ra > 2 * PI)
    {
        ra -= 2 * PI;
    }

    for (r = 0; r < 60; r++)
    {
        // Horizontal Line Check
        dof = 0;
        float disH = 100000000, hx = px, hy = py;
        float aTan = -1 / tan(ra);
        if (ra > PI)
        { // looking down
            ry = (((int)py >> 6) << 6) - 0.0001;
            rx = (py - ry) * aTan + px;
            yo = -64;
            xo = -yo * aTan;
        }
        if (ra < PI)
        { // looking up
            ry = (((int)py >> 6) << 6) + 64;
            rx = (py - ry) * aTan + px;
            yo = 64;
            xo = -yo * aTan;
        }
        if (ra == 0 || ra == PI) // looking left or right
        {
            rx = px;
            ry = py;
            dof = 8;
        }

        while (dof < 8)
        {
            mx = (int)rx >> 6;
            my = (int)ry >> 6;
            mp = my * mapX + mx;
            if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
            {

                hx = rx;
                hy = ry;
                disH = dist(px, py, hx, hy, ra);
                dof = 8;
            }
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        // Vertical Line Check

        dof = 0;
        float disV = 100000000, vx = px, vy = py;
        float nTan = -tan(ra);
        if (ra > P2 && ra < P3)
        { // looking down
            rx = (((int)px >> 6) << 6) - 0.0001;
            ry = (px - rx) * nTan + py;
            xo = -64;
            yo = -xo * nTan;
        }
        if (ra < P2 || ra > P3)
        { // looking up
            rx = (((int)px >> 6) << 6) + 64;
            ry = (px - rx) * nTan + py;
            xo = 64;
            yo = -xo * nTan;
        }
        if (ra == 0 || ra == PI) // looking left or right
        {
            rx = px;
            ry = py;
            dof = 8;
        }

        while (dof < 8)
        {
            mx = (int)rx >> 6;
            my = (int)ry >> 6;
            mp = my * mapX + mx;
            if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
            {

                vx = rx;
                vy = ry;
                disV = dist(px, py, vx, vy, ra);
                dof = 8;
            }
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            disT = disV;
        }
        if (disV > disH)
        {
            rx = hx;
            ry = hy;
            disT = disH;
        }
        glColor3f(1, 0, 0);
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(rx, ry);
        glEnd();

        //Draw 3D Walls

        float ca = pa - ra;
        if(ca < 0)
        {
            ca += 2*PI;
        }
        if(ca > 2 * PI)
        {
            ca-=2*PI;
        }
        disT = disT*cos(ca); //fisheye fix

        float lineH = (mapS * 320) / disT;
        float lineO = 160 - lineH/2;
        if(lineH > 320)
            lineH = 320;

        glLineWidth(8);
        glBegin(GL_LINES);
        glVertex2i(r*8+530, lineO);
        glVertex2i(r*8+530, lineH + lineO);
        glEnd();





        ra += DR;
        if (ra < 0)
        {
            ra += 2 * PI;
        }

        if (ra > 2 * PI)
        {
            ra -= 2 * PI;
        }
    }
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    const float speed = 5.0f;

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_A:
            pa -= 0.1;
            if (pa < 0)
            {
                pa += 2 * PI;
            }
            pdx = cos(pa) * 5;
            pdy = sin(pa) * 5;
            break;
        case GLFW_KEY_D:
            pa += 0.1;
            if (pa > 2 * PI)
            {
                pa -= 2 * PI;
            }
            pdx = cos(pa) * 5;
            pdy = sin(pa) * 5;
            break;
        case GLFW_KEY_W:
            px += pdx;
            py += pdy;
            break;
        case GLFW_KEY_S:
            px -= pdx;
            py -= pdy;
            break;
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
    glVertex2i(px, py);
    glVertex2i(px + pdx * 5, py + pdy * 5);
    glEnd();
}

void drawMap2D()
{
    int x, y, xo, yo;

    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            if (map[y * mapX + x] == 1)
            {
                glColor3f(1, 1, 1);
            }
            else
            {
                glColor3f(0, 0, 0);
            }
            xo = x * mapS;
            yo = y * mapS;
            glBegin(GL_QUADS);
            glVertex2f(xo + 1, yo + 1);
            glVertex2f(xo + 1, yo + mapS - 1);
            glVertex2f(xo + mapS - 1, yo + mapS - 1);
            glVertex2f(xo + mapS - 1, yo + 1);
            glEnd();
        }
    }
}

int display(GLFWwindow *window)
{
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        return -1;
    }

    glfwSetKeyCallback(window, keyCallback);

    int window_width = 1024, window_height = 512;

    glfwGetFramebufferSize(window, &window_width, &window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window_width, window_height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3, 0.3, 0.3, 0);

        glLoadIdentity();

        drawMap2D();
        drawPlayer();
        drawRays3D();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

int main()
{
    pdx = cos(pa) * 5;
    pdy = sin(pa) * 5;
    px = 300, py = 300;

    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(1024, 512, "Raycaster", NULL, NULL);

    display(window);

    glfwTerminate();
    return 0;
}
