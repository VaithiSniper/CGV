#define PI 3.142
#define ORIGINAL 1
#define ROTATED 2
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

GLfloat triangle[3][3] = {
    {100.0, 250.0, 175.0}, {100.0, 100.0, 300.0}, {1.0, 1.0, 1.0}};
GLfloat rotatemat[3][3] = {{0}, {0}, {0}};
GLfloat result[3][3] = {{0}, {0}, {0}};
GLfloat fixedX = 0, fixedY = 0;
int theta;

void multiplyMatrices() {
  int i, j, k;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++) {
      result[i][j] = 0;
      for (k = 0; k < 3; k++)
        result[i][j] = result[i][j] + rotatemat[i][k] * triangle[k][j];
    }
}

GLfloat toRadians(float theta) { return theta * PI / 180.0; }

void rotate() {
  GLfloat m = fixedX * (1 - cos(toRadians(theta))) +
              fixedY * (sin(toRadians(theta))),
          n = fixedY * (1 - cos(toRadians(theta))) -
              fixedX * (sin(toRadians(theta)));
  // fixed shid
  rotatemat[2][0] = rotatemat[2][1] = 0;
  rotatemat[2][2] = 1;
  // var shid
  rotatemat[0][0] = rotatemat[1][1] = cos(toRadians(theta));
  rotatemat[0][1] = rotatemat[1][0] = sin(toRadians(theta));
  rotatemat[0][1] *= -1;
  rotatemat[0][2] = m;
  rotatemat[1][2] = n;
  multiplyMatrices();
}

void drawTriangle(int type) {
  glBegin(GL_LINE_LOOP);
  if (type == ORIGINAL) {
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(triangle[0][0], triangle[1][0]);
    glVertex2f(triangle[0][1], triangle[1][1]);
    glVertex2f(triangle[0][2], triangle[1][2]);

  } else {
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(result[0][0], result[1][0]);
    glVertex2f(result[0][1], result[1][1]);
    glVertex2f(result[0][2], result[1][2]);
  }
  glEnd();
}

void myInit() {
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Bresenham's Line Drawing");
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 500, 0, 500);
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display() {
  drawTriangle(ORIGINAL);
  rotate();
  drawTriangle(ROTATED);
  glFlush();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  myInit();
  glutDisplayFunc(display);

  printf("Input angle of rotation\n");
  scanf("%d", &theta);
  int choice;
  printf(
      "You want to :\n1.Rotate about origin\n2.Rotate about a fixed point\n");
  scanf("%d", &choice);
  if (choice == 2) {
    printf("Input x,y\n");
    scanf("%f %f", &fixedX, &fixedY);
  }
  glutMainLoop();
  return 0;
}
