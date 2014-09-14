//
//  GLCoreProfileView.h
//  StoneHengeCocoa
//
//  Created by Richard Wright
//  Copyright (c) 2013 Richard Wright. All rights reserved.
//

#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>
#import <Cocoa/Cocoa.h>
#include "GLStonehenge.h"

@interface GLCoreProfileView : NSOpenGLView
{
    GLStonehenge    stonehenge;
}

- (void) drawRect:(NSRect) bounds;
- (void) prepareOpenGL;
- (void) reshape;

@end
