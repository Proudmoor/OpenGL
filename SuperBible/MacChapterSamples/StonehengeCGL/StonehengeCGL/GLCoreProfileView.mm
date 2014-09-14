//
//  GLCoreProfileView.mm
//  StonehengeCocoa
//
//  Created by Richard Wright
//  Copyright (c) 2013 Richard Wright. All rights reserved.
//

#import "GLCoreProfileView.h"
#include "StopWatch.h"

/////////////////////////////////////////////////////////
#define MOVE_NONE_BIT       0X00
#define MOVE_FORWARD_BIT    0x01
#define MOVE_BACKWARD_BIT   0x02
#define MOVE_LEFT_BIT       0x04
#define MOVE_RIGHT_BIT      0x08
GLuint  moveFlags = 0x0;

@implementation GLCoreProfileView


- (void)prepareOpenGL
    {
    stonehenge.initModels();
        
    // Set up timer to draw as fast as possible
    NSTimer *pTimer = [NSTimer timerWithTimeInterval: 0.0f target:self selector:@selector(idle:) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop]addTimer:pTimer forMode:NSDefaultRunLoopMode];
    
    // Set the swap interval to once per vertical retrace
    GLint sync = 1;
    CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &sync);
    
    // Enable the multithreaded core
    CGLEnable(CGLGetCurrentContext(), kCGLCEMPEngine);
    
    [self setWantsBestResolutionOpenGLSurface:YES];
    }

- (void)idle:(NSTimer*)pTimer
    {
    [self drawRect:[self bounds]];
    }


- (void) reshape
    {
    // Get the dimensions of the screen
	NSRect bounds = [self bounds];
    
    ////////////////////////////////////////////////////////////////////////
    // Reduces the back buffer by half
//    GLint dim[2] = { int(NSWidth(bounds)) / 2, int(NSHeight(bounds)) / 2  };
//    CGLSetParameter(CGLGetCurrentContext(), kCGLCPSurfaceBackingSize, dim);
//    CGLEnable(CGLGetCurrentContext(), kCGLCESurfaceBackingSize);
//	stonehenge.resized(NSWidth(bounds)/2, NSHeight(bounds)/2);
    ////////////////////////////////////////////////////////////////////////
    
    
    ////////////////////////////////////////////////////////////////////////
    // Back buffer is the same size as the front
	//stonehenge.resized(NSWidth(bounds), NSHeight(bounds));
    ////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////
    // Retina display ready... and we want ALL the pixels
    NSRect backRect = [self convertRectToBacking:bounds];
    stonehenge.resized(NSWidth(backRect), NSHeight(backRect));
    ////////////////////////////////////////////////////////////////////////
    }


- (BOOL)acceptsFirstResponder
    {
        printf("asked\r\n");
//    [[self window] makeFirstResponder:self];
    return YES;
    }

//- (BOOL)becomeFirstResponder
//    {
//    return  YES;
//    }
//
//- (BOOL)resignFirstResponder
//    {
//    return YES;
//    }


//////////////////////////////////////////////////////////////////
// When the key is up, turn the bit off
- (void)keyUp:(NSEvent *)event
    {
    int key = (int)[[event characters] characterAtIndex:0];
    
    switch(key)
        {
        case NSUpArrowFunctionKey:
            moveFlags &= ~MOVE_FORWARD_BIT;
            break;
        case NSDownArrowFunctionKey:
            moveFlags &= ~MOVE_BACKWARD_BIT;
            break;
        case NSLeftArrowFunctionKey:
            moveFlags &= ~MOVE_LEFT_BIT;
            break;
        case NSRightArrowFunctionKey:
            moveFlags &= ~MOVE_RIGHT_BIT;
            break;
        }
    }

///////////////////////////////////////////////////////////////////
// When the key goes down, turn the bit on
- (void)keyDown:(NSEvent*)event
    {
    int key = (int)[[event characters] characterAtIndex:0];
    
    switch(key)
        {
        case NSUpArrowFunctionKey:
            moveFlags |= MOVE_FORWARD_BIT;
            break;
        case NSDownArrowFunctionKey:
            moveFlags |= MOVE_BACKWARD_BIT;
            break;
        case NSLeftArrowFunctionKey:
            moveFlags |= MOVE_LEFT_BIT;
            break;
        case NSRightArrowFunctionKey:
            moveFlags |= MOVE_RIGHT_BIT;
            break;
        }
    }


- (void)drawRect:(NSRect)bounds
    {
    static float fDistance = 0.025f;
    static CStopWatch cameraTimer;
    float deltaT = cameraTimer.GetElapsedSeconds();
    cameraTimer.Reset();
    
    if(moveFlags & MOVE_FORWARD_BIT)
        stonehenge.moveForward(fDistance * deltaT);
    
    if(moveFlags & MOVE_BACKWARD_BIT)
        stonehenge.moveForward(fDistance * -deltaT);
    
    if(moveFlags & MOVE_LEFT_BIT)
        stonehenge.rotateLocalY(fDistance * 30.0f * deltaT);
    
    if(moveFlags & MOVE_RIGHT_BIT)
        stonehenge.rotateLocalY(fDistance * -30.0f * deltaT);
    
    stonehenge.render();
        
    [[self openGLContext] flushBuffer];
    }


@end
