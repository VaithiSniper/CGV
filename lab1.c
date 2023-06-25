#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

int startx, starty, endx, endy;

void myInit() {
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("1BI20CS183");
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 500, 0, 500);
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void drawPoint(int x, int y) {
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

int absdiff(int a, int b) { return a > b ? a - b : b - a; }

int getIncrement(int p2, int p1) { return p2 < p1 ? -1 : 1; }

void drawLine() {
  int dx = absdiff(startx, endx), dy = absdiff(starty, endy),
      incx = getIncrement(endx, startx), incy = getIncrement(endy, starty);

  int e = 0, inc1 = 0, inc2 = 0;
  // draw first point by default
  drawPoint(startx, starty);

  // check for slope
  if (dy > dx) {
    e = 2 * dx - dy;
    inc1 = 2 * (dx - dy);
    inc2 = 2 * dx;
    for (int i = 0; i < dy; i++) {
      if (e >= 0) {
        startx += incx;
        e += inc1;
      } else {
        e += inc2;
      }
      starty += incy;
      drawPoint(startx, starty);
    }
  } else {
    e = 2 * dy - dx;
    inc1 = 2 * (dy - dx);
    inc2 = 2 * dy;
    for (int i = 0; i < dx; i++) {
      if (e >= 0) {
        starty += incy;
        e += inc1;
      } else {
        e += inc2;
      }
      startx += incx;
      drawPoint(startx, starty);
    }
  }
}

void display() {
  drawLine();
  glFlush();
}

int main(int argc, char *argv[]) {
  printf("Input start and end points\n");
  scanf("%d %d %d %d", &startx, &starty, &endx, &endy);
  glutInit(&argc, argv);
  myInit();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
