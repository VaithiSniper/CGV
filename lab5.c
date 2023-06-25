#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;
const int TOP = 8;
const int BOTTOM = 4;
const int RIGHT = 2;
const int LEFT = 1;
double endpoints[8][4];
int n;
int ComputeOutCode(double x, double y);
void CohenSutherLandLineClipAndDraw(double x0, double y0, double x1,
                                    double y1) {
  int outCode0, outCode1, outCodeOut;
  bool accept = false, done = false;
  outCode0 = ComputeOutCode(x0, y0);
  outCode1 = ComputeOutCode(x1, y1);
  do {
    if ((outCode0 | outCode1) == 0) {
      accept = true;
      done = true;
    } else if (outCode0 & outCode1)
      done = true;
    else {
      double x, y;
      outCodeOut = outCode0 ? outCode0 : outCode1;
      float slope = (y1 - y0) / (x1 - x0);
      if (outCodeOut & TOP) {
        x = x0 + (1 / slope) * (ymax - y0);
        y = ymax;
      } else if (outCodeOut & BOTTOM) {
        x = x0 + (1 / slope) * (ymin - y0);
        y = ymin;
      } else if (outCodeOut & RIGHT) {
        y = y0 + slope * (xmax - x0);
        x = xmax;
      } else {
        y = y0 + slope * (xmin - x0);
        x = xmin;
      }
      if (outCodeOut == outCode0) {
        x0 = x;
        y0 = y;
        outCode0 = ComputeOutCode(x0, y0);
      } else {
        x1 = x;
        y1 = y;
        outCode1 = ComputeOutCode(x1, y1);
      }
    }
  } while (!done);
  if (accept) {
    double sx = (xvmax - xvmin) / (xmax - xmin);
    double sy = (yvmax - yvmin) / (ymax - ymin);
    double vx0 = xvmin + (x0 - xmin) * sx;
    double vy0 = yvmin + (y0 - ymin) * sy;
    double vx1 = xvmin + (x1 - xmin) * sx;
    double vy1 = yvmin + (y1 - ymin) * sy;
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xvmin, yvmin);
    glVertex2f(xvmax, yvmin);
    glVertex2f(xvmax, yvmax);
    glVertex2f(xvmin, yvmax);
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2d(vx0, vy0);
    glVertex2d(vx1, vy1);
    glEnd();
  }
}
int ComputeOutCode(double x, double y) {
  int code = 0;
  if (y > ymax)
    code |= TOP;
  else if (y < ymin)
    code |= BOTTOM;
  if (x > xmax)
    code |= RIGHT;
  else if (x < xmin)
    code |= LEFT;
  return code;
}

void drawtext(float x, float y, float z, char *s) {
  int i;
  glRasterPos3f(x, y, z);
  for (i = 0; s[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}
void display() {
  int i;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0.0, 0.0);
  double x0 = 60, y0 = 20, x1 = 80, y1 = 120;
  drawtext(50.0, 299.0, 0.0, "1BI20CS183");
  glBegin(GL_LINES);
  glVertex2d(x0, y0);
  glVertex2d(x1, y1);
  glEnd();
  CohenSutherLandLineClipAndDraw(x0, y0, x1, y1);

  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(xmin, ymin);
  glVertex2f(xmax, ymin);
  glVertex2f(xmax, ymax);
  glVertex2f(xmin, ymax);
  glEnd();
  // CohenSutherLandLineClipAndDraw(x0, y0, x1, y1);
  glFlush();
}
void myinit() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);
  glPointSize(1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}
void main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Cohen Sutherland");
  glutDisplayFunc(display);
  myinit();
  glutMainLoop();
}
