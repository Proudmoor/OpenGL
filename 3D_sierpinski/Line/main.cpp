//
//  main.cpp
//  Line
//
//  Created by zpf on 14-12-17.
//
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <cmath>
static int width, height;

void setPixel(int x, int y) {
    GLint vertices[] = {x, y};
    glVertexPointer(2, GL_INT, 0, vertices);
    glDrawArrays(GL_POINTS, 0, 1);
}

void init2d(int w, int h) {
    width = w;
    height = h;
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w /2 , w / 2, -h /2 , h /2);
    glMatrixMode(GL_MODELVIEW);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
}

void drawLineWithDDA(int x0, int y0, int xEnd, int yEnd) {

    int dx = xEnd - x0;
    int dy = yEnd - y0;
    float x = x0;
    float y = y0;
    
    int steps = fmax(abs(dx), abs(dy));
    
    float xIncrement = float(dx) / steps;
    float yIncrement = float(dy) / steps;
    
    setPixel(x, y);
    for (int i = 0; i <= steps; ++i) {
        x += xIncrement;
        y += yIncrement;
        setPixel(roundf(x), roundf(y));
    }
}

void display () {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawLineWithDDA(0, 0, 300, 100);
    
}

int main(int argc,  char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Lines");
    init2d(640, 480);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
