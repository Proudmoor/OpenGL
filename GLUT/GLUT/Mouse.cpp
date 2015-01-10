#include <GL/glut.h>

GLsizei winWidth = 400, winHeight = 300;
GLint ptCtr = 0;

class srcPt {
public:
	GLint x, y;
};

void init () {
	glClearColor(0.0, 0.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void display () {
	glClear(GL_COLOR_BUFFER_BIT);
	//glFlush();
}

void winReshape (GLint newWidth , GLint newHeight) {
	glViewport (0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble (newWidth), 0.0, GLdouble (newHeight));

	winWidth = newWidth;
	winHeight = newHeight;
}

void drawLineSegment (srcPt endPt1, srcPt endPt2) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin (GL_LINES);
		glVertex2i (endPt1.x, endPt1.y);
		glVertex2i (endPt2.x, endPt2.y);
	glEnd();
	glFlush();
}

void polyline (GLint button, GLint action, GLint xMouse, GLint yMouse) {
	static  srcPt endPt1, endPt2;

	if (ptCtr == 0) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			endPt1.x = xMouse;
			endPt1.y = winHeight - yMouse;
			ptCtr = 1;
		} else 
			if (button == GLUT_RIGHT_BUTTON)
			exit (0);
	}
	 else 
		 if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){ 
			endPt2.x = xMouse;
			endPt2.y = winHeight - yMouse;

			drawLineSegment(endPt1,endPt2);
			endPt1 = endPt2;
		 }
		 else 
			 if (button == GLUT_RIGHT_BUTTON)
		exit(0);
	
	//glFlush();

}



void main (int argc, char** argv) {
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Draw Lines");

	init ();
	glutDisplayFunc (display);
	glutReshapeFunc(winReshape);
	glutMouseFunc(polyline);

	glutMainLoop();
}

