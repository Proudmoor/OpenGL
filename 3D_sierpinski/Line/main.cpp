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

//Use OpenGL to darw point ,(x,y) is the coordniate of pixel
void setPixel(int x, int y) {
    GLint vertices[] = {x, y};
    glVertexPointer(2, GL_INT, 0, vertices);
    glDrawArrays(GL_POINTS, 0, 1);
}

//initialize the state of OpenGL (w, h) is the width and height of window
void init2d(int w, int h) {
    width = w;
    height = h;
    //backgroud to white
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // Ortho projection initialize
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w /2 , w / 2, h /2 , -h /2);
    glMatrixMode(GL_MODELVIEW);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
}
//DDA method to draw lines

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
//Bresenham method to draw lines
void drawLineWithBres(int x0, int y0, int xEnd, int yEnd) {
    int dx = fabs(xEnd - x0) ,dy = fabs(yEnd - y0);
    int p  = 2 * dy - dx;
    int twoDy = 2 * dy , deltaDyDx = 2 * (dy - dx);
    int x ,y;
    
    if (x0 > xEnd) {
        x = xEnd; y = yEnd;
        xEnd = x0;
    } else {
        x = x0;
        y = y0;
    }
    //set first pixel
    setPixel(x, y);
    
    while (x < xEnd) {
        x++;
        if (p < 0)
            p += twoDy;
        else {
            y++;
            p += deltaDyDx;
        }
        setPixel(x, y);
    }
}

void drawCirle (int )

void display () {
    
    glColor3f(1.0f, 0.0f, 0.0f);
    drawLineWithBres(0, 0, 300,500 );
    drawLineWithBres(0, 0, 100,90 );
    drawLineWithDDA(0, 0, 300, 200);
    drawLineWithDDA(0, 0, 300, 100);
    
    
}

int main(int argc,  char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Lines");
    init2d(640, 480);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
