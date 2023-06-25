#include <GL/freeglut_std.h>
#include <GL/gl.h>
#define UP_ARROW 1
#define DOWN_ARROW 2
#define EXIT 3
#define PI 3.142
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct PointValues {
  GLfloat x;
  GLfloat y;
  GLfloat z;
} Point;

Point crtlPoints[4] = {
    {20, 100, 0}, {30, 110, 0}, {50, 90, 0}, {60, 100, 0}}; // flag arc shape
int noOfControlPoints = 4, noOfCurvePoints = 20;
int size, submenu;
static float theta = 0;

void setBinomial(GLint n, GLint *C) {
  for (int i = 0; i <= n; i++) {
    C[i] = 1;
    for (int j = n; j >= i + 1; j--)
      C[i] *= j;
    for (int j = n - i; j >= 2; j--)
      C[i] /= j;
  }
}

void myInit() {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("1BI20CS183");
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 1.0);
}

float toRadians(float theta) { return theta * PI / 180.0; }

void menu(int n) {
  switch (n) {
  case UP_ARROW:
    crtlPoints[1].x += 10 * sin(toRadians(theta));
    crtlPoints[1].y += 5 * sin(toRadians(theta));
    crtlPoints[2].x -= 10 * sin(toRadians(theta + 30));
    crtlPoints[2].y -= 10 * sin(toRadians(theta + 30));
    crtlPoints[3].x -= 4 * sin(toRadians(theta));
    crtlPoints[3].y += sin(toRadians(theta - 30));
    theta += 0.1;
    break;
  case DOWN_ARROW:
    crtlPoints[1].x -= 10 * sin(toRadians(theta));
    crtlPoints[1].y -= 5 * sin(toRadians(theta));
    crtlPoints[2].x += 10 * sin(toRadians(theta + 30));
    crtlPoints[2].y += 10 * sin(toRadians(theta + 30));
    crtlPoints[3].x += 4 * sin(toRadians(theta));
    crtlPoints[3].y -= sin(toRadians(theta - 30));
    theta -= 0.1;
    break;
  case EXIT:
    exit(0);
  }
}

void menuInit() {
  glutCreateMenu(menu);
  glutAddMenuEntry("Down arrow", UP_ARROW);
  glutAddMenuEntry("Up arrow", DOWN_ARROW);
  glutAddMenuEntry("Exit", EXIT);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 150, 0, 150);
  glClear(GL_COLOR_BUFFER_BIT);
}

void computeBezierPoints(GLfloat t, Point *bezPts, GLint noOfControlPoints,
                         Point *ctrlPts, GLint *C) {
  bezPts->x = bezPts->y = bezPts->z = 0.0;
  GLint maxN = noOfControlPoints - 1;
  GLfloat bezTerm = 0;
  for (int i = 0; i < noOfControlPoints; i++) {
    bezTerm = C[i] * pow(t, i) * pow((1 - t), maxN - i);
    bezPts->x += crtlPoints[i].x * bezTerm;
    bezPts->y += crtlPoints[i].y * bezTerm;
    bezPts->z += crtlPoints[i].z * bezTerm;
  }
}

void bezier(Point *ctrlPts, GLint noOfControlPoints, GLint noOfCurvePoints) {
  Point singlePoint;
  GLfloat t;
  GLint C[noOfControlPoints];
  setBinomial(noOfControlPoints - 1, C);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i <= noOfCurvePoints; i++) {
    t = (GLfloat)i / (GLfloat)noOfCurvePoints;
    computeBezierPoints(t, &singlePoint, noOfControlPoints, ctrlPts, C);
    glVertex2f(singlePoint.x, singlePoint.y);
  }
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  glPointSize(5);
  glLineWidth(5);
  glPushMatrix();
  glColor3f(1, 153 / 255.0, 51 / 255.0);
  for (int i = 0; i < 8; i++) {
    glTranslatef(0, -0.8, 0);
    bezier(crtlPoints, noOfControlPoints, noOfCurvePoints);
  }
  glColor3f(1, 1, 1);
  for (int i = 0; i < 8; i++) {
    glTranslatef(0, -0.8, 0);
    bezier(crtlPoints, noOfControlPoints, noOfCurvePoints);
  }
  glColor3f(19 / 255.0, 136 / 255.0, 8 / 255.0);
  for (int i = 0; i < 8; i++) {
    glTranslatef(0, -0.8, 0);
    bezier(crtlPoints, noOfControlPoints, noOfCurvePoints);
  }
  glPopMatrix();
  glColor3f(0.7, 0.5, 0.3);
  glLineWidth(5);
  glBegin(GL_LINES);
  glVertex2f(20, 100);
  glVertex2f(20, 40);
  glEnd();
  glFlush();
  glutPostRedisplay();
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  myInit();
  menuInit();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
