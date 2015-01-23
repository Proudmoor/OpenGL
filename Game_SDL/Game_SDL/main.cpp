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

typedef Game TheGame;
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, const char * argv[]) {
    Uint32 frameStart, frameTime;
    
    std::cout << "game init attempt...\n";
    
    if (TheGame::Instance() -> Init("Chapter 1", 100, 100, 640, 480, false)) {
        frameStart = SDL_GetTicks();
        
        std::cout << "game init success! \n";
        while (TheGame::Instance() -> IsRun()) {
            TheGame::Instance() -> handleEvents();
            TheGame::Instance() -> update();
            TheGame::Instance() -> render();
            
            frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < DELAY_TIME) {
                SDL_Delay((int) (DELAY_TIME - frameTime));
            }
        }
    } else {
        std::cout << "game init failed : " << SDL_GetError() << "\n";
        return -1;
    }
    
    std::cout << "game closing...\n";
    TheGame::Instance() -> clean();
    
    return 0;

}


