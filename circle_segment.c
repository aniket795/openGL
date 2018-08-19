/*
 ============================================================================
 Name        : circle_segment.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#define window_height 500
#define window_width 500
#define window_x 0
#define window_y 0

void set_parameter();

void draw_circle();

void putpixel(GLint, GLint);

GLint x_c=150 , y_c=150 , radius=50;

int main(int pargc, char **argv) {
	glutInit(&pargc, argv);
	glutInitWindowSize(window_height, window_width);
	glutInitWindowPosition(window_x, window_y);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Circle Segment");
	set_parameter();
	glutDisplayFunc(draw_circle);
	glutMainLoop();
	return EXIT_SUCCESS;
}

void putpixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void set_parameter() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}

void draw_circle() {
	GLint x;
	for (x = (x_c - radius); x <= (x_c + radius); x++) {
		putpixel(x, y_c + (int) sqrt(pow((radius), 2) - pow((x - x_c), 2)));
		putpixel(x, y_c - (int) sqrt(pow((radius), 2) - pow((x - x_c), 2)));
	}
	glFlush();
}
