/*
 ============================================================================
 Name        : thick_line.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <math.h>
#include<GL/glut.h>
#define window_width 500
#define window_height 500

int x_1 = 80, y_1 = 120, x_2 = 200, y_2 = 320, thick = 15;

void set_other_parameter();

void draw_line();

void putpixel(GLint x, GLint y);

void slope_zero();

void slope_infinity();

void slope_gentle();

void slope_steep();

int main(int pargc, char **argv) {
	glutInit(&pargc, argv);
	glutInitWindowSize(window_height, window_width);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Bresenham's Line algorithm");
	set_other_parameter();
	glutDisplayFunc(draw_line);
	glutMainLoop();
	return EXIT_SUCCESS;
}

void set_other_parameter() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}

void draw_line() {
	int dx = abs(x_2 - x_1);
	int dy = abs(y_2 - y_1);
	switch (isinf((double )dy / dx)) {
	case 0:
		if ((double) dy / dx == 0.0) {
			slope_zero();
		} else {
			if (dx > dy) {
				slope_gentle();
			} else {
				slope_steep();
			}
		}
		break;
	case 1:
		slope_infinity();
		break;
	}
	glFlush();
}

void putpixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void slope_zero() {
	GLint incx = 1, i, j, count;
	GLint dy = (int) sqrt(pow((x_2 - x_1), 2) + pow((y_2 - y_1), 2))
			/ abs(x_2 - x_1);
	if (x_2 < x_1)
		incx = -1;
	if (thick % 2 == 0) {
		count = thick / 2;
	} else {
		count = (thick - 1) / 2;
	}
	for (i = 0; i < abs(x_2 - x_1); i++) {
		for (j = -count; j <= count; j++) {
			putpixel(x_1, y_1 + (dy * j));
		}
		x_1 += incx;
	}

}

void slope_infinity() {
	GLint incy = 1, i, j, count;
	GLint dx = (int) sqrt(pow((x_2 - x_1), 2) + pow((y_2 - y_1), 2))
			/ abs(y_2 - y_1);
	if (y_2 < y_1)
		incy = -1;
	if (thick % 2 == 0) {
		count = thick / 2;
	} else {
		count = (thick - 1) / 2;
	}
	for (i = 0; i < abs(y_2 - y_1); i++) {
		for (j = -count; j <= count; j++) {
			putpixel(x_1 + (dx * j), y_1);
		}
		y_1 += incy;
	}
}

void slope_gentle() {
	GLint i, G = 2 * abs(y_2 - y_1) - abs(x_2 - x_1), incx = 1, incy = 1, count,
			j;
	GLint dy = (int) sqrt(pow((x_2 - x_1), 2) + pow((y_2 - y_1), 2))
			/ abs(x_2 - x_1);
	if (x_2 < x_1)
		incx = -1;
	if (y_2 < y_1)
		incy = -1;
	if (thick % 2 == 0) {
		count = thick / 2;
	} else {
		count = (thick - 1) / 2;
	}
	for (i = 0; i < abs(x_2 - x_1); i++) {
		for (j = -count; j <= count; j++) {
			putpixel(x_1, y_1 + (dy * j));
		}
		if (G < 0) {
			G += 2 * abs(y_2 - y_1);
		} else {
			G += 2 * abs(y_2 - y_1) - 2 * abs(x_2 - x_1);
			y_1 += incy;
		}
		x_1 += incx;
	}
}

void slope_steep() {
	GLint i, G = 2 * abs(x_2 - x_1) - (y_2 - y_1), incx = 1, incy = 1, count, j;
	GLint dx = (int) sqrt(pow((x_2 - x_1), 2) + pow((y_2 - y_1), 2))
			/ abs(y_2 - y_1);
	if (x_2 < x_1)
		incx = -1;
	if (y_2 < y_1)
		incy = -1;
	if (thick % 2 == 0) {
		count = thick / 2;
	} else {
		count = (thick - 1) / 2;
	}
	for (i = 0; i < abs(y_2 - y_1); i++) {
		for (j = -count; j <= count; j++) {
			putpixel(x_1 + (dx * j), y_1);
		}
		if (G < 0) {
			G += 2 * abs(x_2 - x_1);
		} else {
			G += 2 * (x_2 - x_1) - 2 * (y_2 - y_1);
			x_1 += incx;
		}
		y_1 += incy;
	}
}
