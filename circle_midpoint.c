/*
 ============================================================================
 Name        : circle_midpoint.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define window_height 500
#define window_width 500
#define window_x 0
#define window_y 0

void putpixel(GLint, GLint);

void put_segment_pixel(GLint, GLint);

void draw_circle();

void set_parameter();

int x_c = 150, y_c = 150, radius = 200;

int main(int pargc, char **argv) {
	glutInit(&pargc, argv);
	glutInitWindowSize(window_height, window_width);
	glutInitWindowPosition(window_x, window_y);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Circle");
	set_parameter();
	glutDisplayFunc(draw_circle);
	glutMainLoop();
	return 0;
}

void putpixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x_c, y_c + radius);
	glVertex2i(x_c + radius, y_c);
	glVertex2i(x_c, y_c - radius);
	glVertex2i(x_c - radius, y_c);
	glEnd();
}

void put_segment_pixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x + x_c, y + y_c);
	glVertex2i(y + x_c, x + y_c);
	glVertex2i(y + x_c, y_c - x);
	glVertex2i(x_c + x, y_c - y);
	glVertex2i(x_c - y, y_c - x);
	glVertex2i(x_c - x, y_c - y);
	glVertex2i(x_c - y, y_c + x);
	glVertex2i(x_c - x, y + y_c);
	glEnd();
}

void set_parameter() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}

void draw_circle() {
	GLint x = 0, y = radius, decision_parameter = (5 / 4) - radius;
	putpixel(x, y);
	while (x <= y) {
		if (decision_parameter < 0) {
			decision_parameter += 2 * x + 3;
		} else {
			decision_parameter += 2 * (x - y) + 5;
			y -= 1;
		}
		x += 1;
		put_segment_pixel(x, y);
	}
	glFlush();
}
