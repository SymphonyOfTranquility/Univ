#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

struct Tpoint
{
    double x,y;
};

Tpoint point[5];

bool out = false;

const long double pi = 3.1415926535, sin240 = sin(2*pi-2*pi/3), sin60 = sin(pi/3),
                  cos240 = cos(2*pi-2*pi/3),sin300 = sin(2*pi/3), cos300 = cos(2*pi/3);

long double t = 0,x = 0,y = 0,step=0.005, step_pov = 0.005,a, r,firstx,firsty;

long where = 1,step_for_color = 0;

void display()
{
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(point[1].x,point[1].y);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(point[2].x,point[2].y);
    glColor3f(0.0,0.0,1.0);
    glVertex2f(point[3].x,point[3].y);
    glEnd();

    if (step_for_color%4 == 0)
        glColor3f(0.0,1.0,0.0);
    else if (step_for_color%4 == 1)
        glColor3f(0.0,0.0,1.0);
    else if (step_for_color%4 == 2)
        glColor3f(1.0,0.0,0.0);
    else
        glColor3f(1,1,0.0);

    glRectf(x-2,y-2,x+2,y+2);

    glFlush();
}

long double angle(long double x11,long double y11,long double x22,long double y22)
{
    return ((x11*x22+y11*y22)/(sqrt(x11*x11+y11*y11)*sqrt(x22*x22+y22*y22)));
}

long double t1,rad;
bool povorot,znak;
bool first = false;

void Spin()
{
    t1 += step_pov;
    if (where == 1)
    {
        x = -rad*sin(t1)-a/2.0;
        y = -rad*cos(t1)-a/2.0;
        if (abs(t1-2*pi/3.0) <  0.01)
        {
            x = -rad*sin(t1-step_pov)-a/2.0;
            firstx = x;
            y = -rad*cos(t1-step_pov)-a/2.0;
            firsty = y;
            first = false;
            povorot = false;
            where = 2;
            t1 = 0;
        }
    }
    else if (where == 2)
    {
        x = -rad*sin(t1+2*pi/3);
        y = -rad*cos(t1+2*pi/3)+a*sin60-a/2;
        if (abs(t1-2*pi/3.0) <  0.01)
        {
            x = -rad*sin(t1-step_pov+2*pi/3);
            firstx = x;
            y = -rad*cos(t1-step_pov+2*pi/3)+a*sin60-a/2;
            firsty = y;
            first = false;
            povorot = false;
            where = 3;
            t1 = 0;
        }
    }
    else if (where == 3)
    {
        x = -rad*sin(t1+4*pi/3)+a/2;
        y = -rad*cos(t1+4*pi/3)-a/2;
        if (abs(t1-2*pi/3.0) < 0.01)
        {

            x = -rad*sin(t1-step_pov+4*pi/3)+a/2;
            firstx = x;
            y = -rad*cos(t1-step_pov+4*pi/3)-a/2;
            firsty = y;
            first = false;
            povorot = false;
            where = 1;
            t1 = 0;
        }
    }
}
long koef = 0;

void Tick()
{
    t += step;
    if (t >= 2*pi)
        ++koef, t -= 2*pi;
    long double x1 = -(r*(t+2*pi*koef)-r*sin(t)), y1 = -(r-r*cos(t));
    x = x1*cos(2*pi-(where-1)*2*pi/3) - y1*sin(2*pi-(where-1)*2*pi/3);
    y = x1*sin(2*pi-(where-1)*2*pi/3) + y1*cos(2*pi-(where-1)*2*pi/3);
    if (!first)
    {
        firstx -= x;
        firsty -= y;
        first = true;
    }
    x += firstx;
    y += firsty;
    if (abs(angle(x - point[where+1].x,y - point[where+1].y,
                  point[where+1].x - point[where].x,point[where+1].y - point[where].y)) < 0.01)
    {
        povorot = true;
        rad = sqrt((x - point[where+1].x)*(x-point[where+1].x)+(y-point[where+1].y)*(y-point[where+1].y));
        t1 = 0;
        t = t + 2*pi - step;
        if (t >= 2*pi)
            t -= 2*pi;
        koef = 0;
        ++step_for_color;
    }
}

void timer(int = 0)
{
    display();
    if (povorot)
        Spin();
    else
        Tick();

    glutTimerFunc(0,timer,0);
}

void obyava_zminnih()
{
    x = a/2;
    y = -a/2;
    firstx = x;
    firsty = y;
    point[4].x = point[1].x = a/2;
    point[4].y = point[1].y = -a/2;
    point[2].x = -a/2;
    point[2].y = -a/2;
    point[3].x = 0;
    point[3].y = a*sin60-a/2;
}

int main(int argc, char* argv[])
{
    cout << "Enter length of the side of triangle in pixels\n";
    cin >> a;
    cout << "Enter radius of the circle in pixels\n";
    cin >> r;
    obyava_zminnih();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(900, 700);
    glutCreateWindow("triangle and circle");
    gluOrtho2D(-450, 450, -350, 350);
    glutDisplayFunc(display);
    glutTimerFunc(0,timer,0);
    glutMainLoop();
}
