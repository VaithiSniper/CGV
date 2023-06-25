#include <GL/gl.h>
#include <GL/glu.h>
#define PI 3.142
#define X 0
#define Y 1
#define Z 2
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef GLfloat light[4];

light ambient = {0.7, 0.7, 0.7, 1.0};
light diffuse = {0.5, 0.5, 0.5, 0.1};
light specular = {1.0, 1.0, 1.0, 1.0};
const GLfloat shininess[] = {50.0};
light light_intensity = {0.7, 0.7, 0.7, 1.0};
light light_position = {2.0, 6.0, 3.0, 0.0};

void myInit() {
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("1BI20CS183");
  glClearColor(0.1, 0.1, 0.1, 0.1);
  glViewport(0, 0, 640, 480);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(2.0, 1.0, 2.0, 0.0, 0.2, 0.0, 0.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void materialInit() {
  // glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  // glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_intensity);
}

void leftleg() {
  glPushMatrix();
  glTranslatef(-0.5, -0.7, 0.5);
  glScaled(0.5, 7.0, 0.5);
  glutSolidCube(0.1);
  glPopMatrix();
}

void rightleg() {
  glPushMatrix();
  glTranslatef(0.5, -0.7, -0.5);
  glScaled(0.5, 7.0, 0.5);
  glutSolidCube(0.1);
  glPopMatrix();
}

void frontleg() {
  glPushMatrix();
  glTranslatef(0.5, -0.7, 0.5);
  glScaled(0.5, 7.0, 0.5);
  glutSolidCube(0.1);
  glPopMatrix();
}

void backleg() {
  glPushMatrix();
  glTranslatef(-0.5, -0.7, -0.5);
  glScaled(0.5, 7.0, 0.5);
  glutSolidCube(0.1);
  glPopMatrix();
}

void tabletop() {
  glPushMatrix();
  glTranslatef(0.0, -0.3, 0.0);
  glScaled(7.0, 0.5, 7.0);
  glutSolidCube(0.2);
  glPopMatrix();
}

void teapot() {
  glPushMatrix();
  glTranslatef(0.4, 0.0, 0.4);
  glRotated(30, 0, 1, 0);
  glutSolidTeapot(0.2);
  glPopMatrix();
}

void bottomfloor() {
  glPushMatrix();
  glTranslatef(0.0, -1.0, 0.0);
  glScaled(10.0, 0.5, 10.0);
  glutSolidCube(0.2);
  glPopMatrix();
}

void rightwall() {
  glPushMatrix();
  glTranslatef(0.0, 0.0, -1.0);
  glScaled(10.0, 10.0, 0.1);
  glutSolidCube(0.2);
  glPopMatrix();
}

void leftwall() {
  glPushMatrix();
  glTranslatef(-1.0, 0.0, 0.0);
  glScaled(0.5, 10.0, 10.0);
  glutSolidCube(0.2);
  glPopMatrix();
}

void display() {
  teapot();
  tabletop();
  frontleg();
  leftleg();
  rightleg();
  backleg();
  bottomfloor();
  rightwall();
  leftwall();
  glFlush();
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  myInit();
  materialInit();
  glutDisplayFunc(display);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glutMainLoop();
  return 0;
}
