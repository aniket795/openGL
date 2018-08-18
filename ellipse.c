/*
 ============================================================================
 Name        : ellipse.c
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

void putpixel_first_pixel();

void put_segment_pixel(GLint, GLint);

void draw_ellipse();

void set_parameter();

GLint r_x = 160, r_y = 100, x_c = 50, y_c = 50;

int main(int pargc, char **argv) {
	glutInit(&pargc, argv);
	glutInitWindowSize(window_height, window_width);
	glutInitWindowPosition(window_x, window_y);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Ellipse");
	set_parameter();
	glutDisplayFunc(draw_ellipse);
	glutMainLoop();
	return 0;
}

void putpixel_first_pixel() {
	glBegin(GL_POINTS);
	glVertex2i(0, r_y);
	glVertex2i(r_x, 0);
	glVertex2i(0, -r_y);
	glVertex2i(-r_x, 0);
	glEnd();
}

void put_segment_pixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glVertex2i(x, -y);
	glVertex2i(-x, -y);
	glVertex2i(-x, y);
	glEnd();
}

void set_parameter() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-500, 500, -500, 500);
}

void draw_ellipse() {
	GLint x = 0, y = r_y;
	long int decision_parameter = (int) pow(r_y, 2)
			+ (int) (pow(r_x, 2) * (0.25 - r_y));
	putpixel_first_pixel();
	while (((int) pow(r_x, 2) * y) >= ((int) pow(r_y, 2) * x)) {
		if (decision_parameter < 0) {
			decision_parameter += (2 * x * r_y * r_y) + (3 * r_y * r_y);
		} else {
			decision_parameter += 2 * ((x * r_y * r_y) - (y * r_x * r_x))
					+ (2 * r_x * r_x) + (3 * r_y * r_y);
			y -= 1;
		}
		x += 1;
		put_segment_pixel(x, y);
	}
	decision_parameter = ((int) pow((x + 0.5), 2) * pow(r_y, 2))
			+ ((int) pow((y - 1), 2) * pow(r_x, 2))
			- (pow(r_x, 2) * pow(r_y, 2));
	while (y != 0) {
		if (decision_parameter < 0) {
			decision_parameter += (2 * r_y * r_y * (x + 1))
					- (r_x * r_x * (2 * y - 3));
			x += 1;
		} else {
			decision_parameter -= (r_x * r_x * (2 * y - 3));
		}
		y -= 1;
		put_segment_pixel(x, y);
	}
	glFlush();
}

