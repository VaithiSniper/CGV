#define PI 3.142
#define X 0
#define Y 1
#define Z 2
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef GLfloat vertex[3];

vertex vertices[] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0},
                     {-1.0, 1.0, -1.0},  {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0},
                     {1.0, 1.0, 1.0},    {-1.0, 1.0, 1.0}};
vertex normals[] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0},
                    {-1.0, 1.0, -1.0},  {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0},
                    {1.0, 1.0, 1.0},    {-1.0, 1.0, 1.0}};
vertex colors[] = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0},
                   {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0},
                   {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};

static GLfloat theta[] = {0.0, 0.0, 0.0};
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
  theta[axis] += 0.02;
  if (theta[axis] > 360.0)
    theta[axis] -= 360.0;
  glutPostRedisplay();
}

void myInit() {
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("1BI20CS183");
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef(theta[X], 1.0, 0.0, 0.0);
  glRotatef(theta[Y], 0.0, 1.0, 0.0);
  glRotatef(theta[Z], 0.0, 0.0, 1.0);
  cube();
  glFlush();
  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h)
    glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
            2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
  else
    glOrtho(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0,
            2.0, -10.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
}

void mouse(int btn, int state, int x, int y) {
  if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    axis = 0;
  if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    axis = 1;
  if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    axis = 2;
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  myInit();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(spinCube);
  glutMouseFunc(mouse);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}
