//
//  AppDelegate.m
//  StonehengeCGL
//
//  Created by Richard Wright on 1/13/13.
//  Copyright (c) 2013 Richard Wright. All rights reserved.
//

#import "AppDelegate.h"
#import "GLCoreProfileView.h"
@implementation AppDelegate

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
    {
    // Insert code here to initialize your application
    NSRect mainDisplayRect = [[NSScreen mainScreen] frame];
    
    
    NSWindow *fullScreenWindow = [[NSWindow alloc] initWithContentRect:
                                    mainDisplayRect styleMask:NSBorderlessWindowMask
                                    backing:NSBackingStoreBuffered defer:YES];
    
    [fullScreenWindow setLevel:NSMainMenuWindowLevel+1];
    [fullScreenWindow setOpaque:YES];
    [fullScreenWindow setHidesOnDeactivate:YES];
    
    NSOpenGLPixelFormatAttribute pixelFormatAttributes[] =
    {
        NSOpenGLPFAColorSize,       32,
        NSOpenGLPFADepthSize,       24,
        NSOpenGLPFAStencilSize,     8,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,        
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        0
    };

    
    NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc]
                                        initWithAttributes:pixelFormatAttributes];
    
    NSRect viewRect = NSMakeRect(0.0, 0.0, mainDisplayRect.size.width,
                                 mainDisplayRect.size.height);
    
    GLCoreProfileView *fullScreenView = [[GLCoreProfileView alloc] initWithFrame:viewRect pixelFormat: pixelFormat];
    [fullScreenWindow setContentView: fullScreenView];
    
    //[fullScreenView setMainController:self];
        
    [fullScreenWindow makeKeyAndOrderFront:self];

//    [[fullScreenView window] makeFirstResponder:fullScreenView];
    
    }

@end
