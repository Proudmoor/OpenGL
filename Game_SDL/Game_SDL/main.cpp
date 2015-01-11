//
//  main.cpp
//  Game_SDL
//
//  Created by zpf on 15-1-10.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

Game* gGame = 0;

int main(int argc, const char * argv[]) {
    
    gGame = new Game();
    
    gGame -> Init("Chapter 1", 100, 100, 640, 480, false);
    
    while (gGame -> IsRun()) {
        gGame -> handleEvents();
        //gGame -> update();
        gGame -> render();
    }
    
    gGame -> clean();
    
    return 0;

}


