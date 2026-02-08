/* =========================================================
   COMMON HEADER FILES (USED BY ALL PROGRAMS)
   ========================================================= */

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* =========================================================
   PROGRAM 1: Midpoint Circle Drawing Algorithm
   ========================================================= */

void drawCirclePoints(int xc, int yc, int x, int y)
{
    putpixel(xc + x, yc + y, WHITE);
    putpixel(xc - x, yc + y, WHITE);
    putpixel(xc + x, yc - y, WHITE);
    putpixel(xc - x, yc - y, WHITE);
    putpixel(xc + y, yc + x, WHITE);
    putpixel(xc - y, yc + x, WHITE);
    putpixel(xc + y, yc - x, WHITE);
    putpixel(xc - y, yc - x, WHITE);
}

void midpointCircle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int p = 1 - r;

    while (x <= y)
    {
        drawCirclePoints(xc, yc, x, y);
        x++;

        if (p < 0)
            p = p + 2*x + 1;
        else
        {
            y--;
            p = p + 2*(x - y) + 1;
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    int xc, yc, r;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    printf("Enter center (xc yc): ");
    scanf("%d %d", &xc, &yc);

    printf("Enter radius: ");
    scanf("%d", &r);

    midpointCircle(xc, yc, r);

    getch();
    closegraph();
    return 0;
}


/* =========================================================
   PROGRAM 2: Bresenham Line Drawing Algorithm
   ========================================================= */

void bresenham(int x1, int y1, int x2, int y2)
{
    int dx, dy, p, x, y;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    x = x1;
    y = y1;

    p = 2 * dy - dx;

    putpixel(x, y, WHITE);

    while (x < x2)
    {
        x++;

        if (p < 0)
            p = p + 2 * dy;
        else
        {
            y++;
            p = p + 2 * (dy - dx);
        }

        putpixel(x, y, WHITE);
    }
}

int main()
{
    int gd = DETECT, gm;
    int x1, y1, x2, y2;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    printf("Enter x1 y1: ");
    scanf("%d %d", &x1, &y1);

    printf("Enter x2 y2: ");
    scanf("%d %d", &x2, &y2);

    bresenham(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}


/* =========================================================
   PROGRAM 3: Midpoint Line Clipping Algorithm
   ========================================================= */

int xmin = 100, ymin = 100, xmax = 300, ymax = 300;

int inside(int x, int y)
{
    if (x >= xmin && x <= xmax && y >= ymin && y <= ymax)
        return 1;
    else
        return 0;
}

void midpointClip(int x1, int y1, int x2, int y2)
{
    int mx, my;

    if (inside(x1, y1) && inside(x2, y2))
    {
        line(x1, y1, x2, y2);
        return;
    }

    if ((abs(x2 - x1) < 2) && (abs(y2 - y1) < 2))
        return;

    mx = (x1 + x2) / 2;
    my = (y1 + y2) / 2;

    midpointClip(x1, y1, mx, my);
    midpointClip(mx, my, x2, y2);
}

int main()
{
    int gd = DETECT, gm;
    int x1, y1, x2, y2;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    rectangle(xmin, ymin, xmax, ymax);

    printf("Enter line x1 y1: ");
    scanf("%d %d", &x1, &y1);

    printf("Enter line x2 y2: ");
    scanf("%d %d", &x2, &y2);

    setcolor(RED);
    line(x1, y1, x2, y2);

    setcolor(WHITE);
    midpointClip(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}


/* =========================================================
   PROGRAM 4: 2D Transformations (Translation, Scaling, Rotation)
   ========================================================= */

void drawTriangle(int x1,int y1,int x2,int y2,int x3,int y3)
{
    line(x1,y1,x2,y2);
    line(x2,y2,x3,y3);
    line(x3,y3,x1,y1);
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

    int x1=100, y1=100;
    int x2=150, y2=50;
    int x3=200, y3=100;

    setcolor(WHITE);
    drawTriangle(x1,y1,x2,y2,x3,y3);

    getch();

    int tx = 80, ty = 60;

    setcolor(YELLOW);
    drawTriangle(x1+tx,y1+ty,
                 x2+tx,y2+ty,
                 x3+tx,y3+ty);

    getch();

    float sx = 1.5, sy = 1.5;

    setcolor(GREEN);
    drawTriangle(x1*sx,y1*sy,
                 x2*sx,y2*sy,
                 x3*sx,y3*sy);

    getch();

    float angle = 45;
    float rad = angle * 3.14159 / 180;

    int xr1 = x1*cos(rad) - y1*sin(rad);
    int yr1 = x1*sin(rad) + y1*cos(rad);

    int xr2 = x2*cos(rad) - y2*sin(rad);
    int yr2 = x2*sin(rad) + y2*cos(rad);

    int xr3 = x3*cos(rad) - y3*sin(rad);
    int yr3 = x3*sin(rad) + y3*cos(rad);

    setcolor(RED);
    drawTriangle(xr1,yr1,xr2,yr2,xr3,yr3);

    getch();
    closegraph();
    return 0;
}


/* =========================================================
   PROGRAM 5: Midpoint Ellipse Drawing Algorithm
   ========================================================= */

void plot4(int xc,int yc,int x,int y)
{
    putpixel(xc + x, yc + y, WHITE);
    putpixel(xc - x, yc + y, WHITE);
    putpixel(xc + x, yc - y, WHITE);
    putpixel(xc - x, yc - y, WHITE);
}

void midpointEllipse(int xc,int yc,int rx,int ry)
{
    float x = 0, y = ry;
    float rx2 = rx * rx;
    float ry2 = ry * ry;

    float dx = 2 * ry2 * x;
    float dy = 2 * rx2 * y;

    float d1 = ry2 - rx2 * ry + 0.25 * rx2;

    while (dx < dy)
    {
        plot4(xc,yc,x,y);

        if (d1 < 0)
        {
            x++;
            dx += 2 * ry2;
            d1 += dx + ry2;
        }
        else
        {
            x++;
            y--;
            dx += 2 * ry2;
            dy -= 2 * rx2;
            d1 += dx - dy + ry2;
        }
    }

    float d2 = ry2*(x+0.5)*(x+0.5) +
               rx2*(y-1)*(y-1) -
               rx2*ry2;

    while (y >= 0)
    {
        plot4(xc,yc,x,y);

        if (d2 > 0)
        {
            y--;
            dy -= 2 * rx2;
            d2 += rx2 - dy;
        }
        else
        {
            y--;
            x++;
            dx += 2 * ry2;
            dy -= 2 * rx2;
            d2 += dx - dy + rx2;
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    int xc, yc, rx, ry;

    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

    printf("Enter center coordinates (xc yc): ");
    scanf("%d %d",&xc,&yc);

    printf("Enter x-radius and y-radius: ");
    scanf("%d %d",&rx,&ry);

    midpointEllipse(xc,yc,rx,ry);

    getch();
    closegraph();
    return 0;
}
