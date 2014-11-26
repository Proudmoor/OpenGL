//
//  main.cpp
//  DDA_Line
//
//  Created by zpf on 14-11-22.
//
//

#include <iostream>

#include <GL/glut.h>
#include <cstdlib>
//链接必要的库文件


void LineDDA(int x1,int y1,int x2,int y2)
{
    float x, y, dx, dy;
    int k,i;
    if(abs(x2-x1)>=abs(y2-y1))
    {
        k=abs(x2-x1);
    }
    else
    {
        k=abs(y2-y1);
    }
    dx=(float)(x2-x1)/k;
    dy=(float)(y2-y1)/k;
    x=(float)(x1);
    y=(float)(y1);
    for(i=0;i<k; i++)
    {
        glPointSize(2);
        glBegin (GL_POINTS);
        glColor3f (1.0f, 0.0f, 0.0f);
        glVertex2i ((int)(x+0.5),(int)(y+0.5));
        glEnd ();
        x+=dx;
        y+=dy;
    }
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    //画X轴
    glBegin(GL_LINES);
    glColor3f (0.0f, 0.0f, 0.0f);
    glVertex2f(-50.0f,0.0f);
    glVertex2f(50.0f,0.0f);
    glEnd();
    
    //画Y轴
    glBegin(GL_LINES);
    glColor3f (0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f,-50.0f);
    glVertex2f(0.0f,50.0f);
    glEnd();
    
    //用DDA算法画两条线
    LineDDA(-50,-50,50,50);
    LineDDA(-50, 50, 50,-50);
    glFlush();
}

void ChangeSize(GLsizei w,GLsizei h)
{
    if(h==0)
    {
        h=1;
    }
    //定义视口
    glViewport(0,0,w,h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //定义正交视域体
    if(w<h)
    {
        glOrtho(-150,150,-150*h/w,150*h/w,-150,150);
    }
    else
    {
        glOrtho(-150*w/h,150*w/h,-150,150,-150,150);
    }
    
}

void Init(void)
{
    //背景为白色
    glClearColor(1.0f,1.0f,1.0f,0.0f);
}

int _tmain(int argc, _TCHAR* argv[])
{
    //设置为RGB颜色模式和单缓存窗口
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("DDA算法画直线");
    Init();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
    return 0;
}

