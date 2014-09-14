//
//  ViewController.mm
//  StonehengeES
//
//  Created by Richard Wright on 3/16/13.
//  Copyright (c) 2013 Richard Wright. All rights reserved.
//

#import "ViewController.h"

@interface ViewController () {

}
@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;

- (void)setupGL;
- (void)tearDownGL;

@end

@implementation ViewController

- (void)dealloc
{
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    
    [_context release];
    [_effect release];
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2] autorelease];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (void)setupGL
    {
    [EAGLContext setCurrentContext:self.context];
    
    stoneHenge.initModels();
    }

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    
    stoneHenge.cleanupModels();
    
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
    {
    stoneHenge.resized(self.view.bounds.size.width, self.view.bounds.size.height);
    }

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
    {
    stoneHenge.render();
    }


@end
