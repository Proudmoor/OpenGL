//
//  main.cpp
//  Game_SDL
//
//  Created by zpf on 15-1-10.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>

SDL_Window* gWindow = 0;
SDL_Renderer* gRenderer = 0;


int main(int argc, const char * argv[]) {

    // insert code
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0){
        gWindow = SDL_CreateWindow("Setting UP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
        if(gWindow != 0) {
            gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
        }
    } else {
        return 1;
    }
    SDL_SetRenderDrawColor(gRenderer, 255, 1, 0, 255);
    
    SDL_RenderClear(gRenderer);
    
    SDL_RenderPresent(gRenderer);
    
    SDL_Delay(5000);
    
    SDL_Quit();
    return 0;
   
   
   
   
   
}

