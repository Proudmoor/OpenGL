//
//  MyOpenGLView.m
//  Golden Triangle
//
//  Created by zpf on 14-9-21.
//  Copyright (c) 2014年 zpf. All rights reserved.
//

#import <Foundation/Foundation.h>


#import "MyOpenGLView.h"
#include <OpenGL/gl.h>

@implementation MyOpenGLView

-(void) drawRect:(NSRect)bounds
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawAnObject();
    glFlush();    
}

static void drawAnObject()
{
    glColor3f(1.0f, 0.85f, 0.35f);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(0.0, 0.6, 0.0);
        glVertex3f(-0.2, -0.3, 0.0);
        glVertex3f(0.2, -0.3, 0.0);
    }
    glEnd();
}


@end