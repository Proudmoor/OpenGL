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
#define MOVE_LOOKUP_BIT     0X10
#define MOVE_LOOKDOWN_BIT   0X20
GLuint  moveFlags = 0x0;

@implementation GLCoreProfileView

-(id)initWithCoder:(NSCoder *)aDecoder
{
    NSOpenGLPixelFormatAttribute pixelFormatAttributes[] =
        {
        NSOpenGLPFAColorSize,       32,
        NSOpenGLPFADepthSize,       24,
        NSOpenGLPFAStencilSize,     8,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        0
        };
    
    NSOpenGLPixelFormat *pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes] autorelease];
    NSOpenGLContext* openGLContext = [[[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil] autorelease];
    [super initWithCoder:aDecoder];
    [self setOpenGLContext:openGLContext];
    [openGLContext makeCurrentContext];
    
    return self;
}


- (void)prepareOpenGL
    {
    stonehenge.initModels();
        
    NSTimer *pTimer = [NSTimer timerWithTimeInterval: 0.0f target:self selector:@selector(idle:) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop]addTimer:pTimer forMode:NSDefaultRunLoopMode];
    }

- (void)idle:(NSTimer*)pTimer
    {
    [self drawRect:[self bounds]];
    }


- (void) reshape
    {
	NSRect bounds = [self bounds];
	stonehenge.resized(NSWidth(bounds), NSHeight(bounds));
    }


- (BOOL)acceptsFirstResponder
    {
    [[self window] makeFirstResponder:self];
    return YES;
    }

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
        case 'a':
            moveFlags &= ~MOVE_LOOKUP_BIT;
            break;
        case 'z':
            moveFlags &= ~MOVE_LOOKDOWN_BIT;
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
        case 97:
            moveFlags |= MOVE_LOOKUP_BIT;
            break;
        case 122:
            moveFlags |= MOVE_LOOKDOWN_BIT;
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
        stonehenge.moveForward(fDistance * deltaT * 500.0f);
    
    if(moveFlags & MOVE_BACKWARD_BIT)
        stonehenge.moveForward(fDistance * -deltaT * 500.0f);
    
    if(moveFlags & MOVE_LEFT_BIT)
        stonehenge.rotateLocalY(fDistance * 30.0f * deltaT);
    
    if(moveFlags & MOVE_RIGHT_BIT)
        stonehenge.rotateLocalY(fDistance * -30.0f * deltaT);
    
    if(moveFlags & MOVE_LOOKUP_BIT)
        stonehenge.addTilt(fDistance * 30.0f * deltaT);
        
    if(moveFlags & MOVE_LOOKDOWN_BIT)
        stonehenge.addTilt(fDistance * -30.0f * deltaT);
    
    
    stonehenge.render();
    glFlush();
    }


@end
