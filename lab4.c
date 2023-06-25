#define PI 3.142
#define X 0
#define Y 1
#define Z 2
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef GLfloat vertex[3];
typedef GLdouble viewerType[3];

vertex vertices[] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0},
                     {-1.0, 1.0, -1.0},  {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0},
                     {1.0, 1.0, 1.0},    {-1.0, 1.0, 1.0}};
vertex normals[] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0},
                    {-1.0, 1.0, -1.0},  {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0},
                    {1.0, 1.0, 1.0},    {-1.0, 1.0, 1.0}};
vertex colors[] = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0},
                   {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0},
                   {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};

static viewerType viewer = {0.0, 0.0, 5.0};
static vertex theta = {0.0, 0.0, 0.0};
static GLint axis = Z;

void square(int a, int b, int c, int d) {
  glBegin(GL_POLYGON);
  glColor3fv(colors[a]);
  glNormal3fv(normals[a]);
  glVertex3fv(vertices[a]);

  glColor3fv(colors[b]);
  glNormal3fv(normals[b]);
  glVertex3fv(vertices[b]);

  glColor3fv(colors[c]);
  glNormal3fv(normals[c]);
  glVertex3fv(vertices[c]);

  glColor3fv(colors[d]);
  glNormal3fv(normals[d]);
  glVertex3fv(vertices[d]);

  glEnd();
}

void cube() {
  square(0, 3, 2, 1);
  square(2, 3, 7, 6);
  square(0, 4, 7, 3);
  square(4, 5, 6, 7);
  square(0, 1, 5, 4);
  square(1, 2, 6, 5);
}

void spinCube() {
  theta[axis] += 2.0;
  if (theta[axis] > 360.0)
    theta[axis] -= 360.0;
}

void myInit() {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("1BI20CS183");
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glRotatef(theta[X], 1.0, 0.0, 0.0);
  glRotatef(theta[Y], 0.0, 1.0, 0.0);
  glRotatef(theta[Z], 0.0, 0.0, 1.0);
  cube();
  glFlush();
  glutSwapBuffers();
}

void keys(unsigned char key, int x, int y) {
  switch (key) {
  case 'x':
    viewer[0] -= 1.0;
    break;
  case 'X':
    viewer[0] += 1.0;
    break;
  case 'y':
    viewer[0] -= 1.0;
    break;
  case 'Y':
    viewer[0] += 1.0;
    break;
  case 'z':
    viewer[0] -= 1.0;
    break;
  case 'Z':
    viewer[0] += 1.0;
    break;
  }
  display();
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h)
    glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
              2.0 * (GLfloat)h / (GLfloat)w, 2.0, 20.0);
  else
    glFrustum(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h,
              -2.0, 2.0, 2.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
}

void mouse(int btn, int state, int x, int y) {
  if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    axis = 0;
  if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    axis = 1;
  if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    axis = 2;
  spinCube();
  display();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  myInit();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keys);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}
