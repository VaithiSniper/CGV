#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#define PI 3.142
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

typedef GLfloat point[3];
typedef GLfloat rgb[3];
point vertex[] = {
    {-1.0, -0.5, 0.0}, {1.0, -0.5, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
rgb color[] = {
    {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}};
int n;

GLfloat toRadians(float theta) { return theta * PI / 180.0; }

void myInit() {
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("1BI20CS183");
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST);
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void triangle(point a, point b, point c) {
  glBegin(GL_POLYGON);
  glVertex3fv(a); //
  glVertex3fv(b); // 3 dimension not 2D
  glVertex3fv(c); //
  glEnd();        // forgot
}

void tetrahedron(point a, point b, point c, point d) {
  glColor3fv(color[0]);
  triangle(a, b, c);
  glColor3fv(color[1]);
  triangle(a, b, d);
  glColor3fv(color[2]);
  triangle(a, c, d);
  glColor3fv(color[3]);
  triangle(b, c, d);
}

void divide_tetra(point a, point b, point c, point d, int n) {
  point mid[6];
  if (n == 0) {
    tetrahedron(a, b, c, d);
  } else {
    for (int i = 0; i < 3; i++) {
      mid[0][i] = (a[i] + b[i]) / 2.0;
      mid[1][i] = (a[i] + c[i]) / 2.0;
      mid[2][i] = (a[i] + d[i]) / 2.0;
      mid[3][i] = (b[i] + c[i]) / 2.0;
      mid[4][i] = (c[i] + d[i]) / 2.0;
      mid[5][i] = (b[i] + d[i]) / 2.0;
    }
    divide_tetra(a, mid[0], mid[1], mid[2], n - 1);
    divide_tetra(mid[0], b, mid[3], mid[5], n - 1);
    divide_tetra(mid[1], mid[3], c, mid[4], n - 1);
    divide_tetra(mid[2], mid[5], mid[4], d, n - 1);
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0); // 4 param
  divide_tetra(vertex[0], vertex[1], vertex[2], vertex[3], n);
  glFlush();
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  if (w <= h)
    glOrtho(-1.0, 1.0, -1.0 * ((GLfloat)h / (GLfloat)w),
            1.0 * ((GLfloat)h / (GLfloat)w), -1.0, 1.0);
  else
    glOrtho(-1.0 * ((GLfloat)w / (GLfloat)h), 1.0 * ((GLfloat)w / (GLfloat)h),
            -1.0, 1.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  myInit();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glEnable(GL_DEPTH_TEST);
  printf("Input no. of divisions\n");
  scanf("%d", &n);
  glutMainLoop();
  return 0;
}
