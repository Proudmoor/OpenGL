//
//  Game.h
//  Game_SDL
//
//  Created by zpf on 15-1-11.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#ifndef __Game_SDL__Game__
#define __Game_SDL__Game__

#include <iostream>
#include <SDL2/SDL.h>

class Game
{
public:
    
    Game() {};
    
    ~Game(){};
    
    bool Init(const char* title, int xpos, int ypos,
              int width, int height, int flags);
    
    void render();
    
    void update();
    
    void handleEvents();
    
    void clean();
    
    bool IsRun() ;
private:
    bool m_Running;
    
    SDL_Window* m_Window;
    SDL_Renderer* m_Render;
    
};

#endif /* defined(__Game_SDL__Game__) */
