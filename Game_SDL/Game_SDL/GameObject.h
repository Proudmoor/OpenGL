//
//  GameObject.h
//  Game_SDL
//
//  Created by zpf on 15-1-12.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#ifndef __Game_SDL__GameObject__
#define __Game_SDL__GameObject__

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

class GameObject {
public:
    
    void load (int x, int y, int width, int height, std::string textureID);

    void draw(SDL_Renderer* pRenderer) ;
    void update();
    void clean() {
        std::cout << "clean game object";
    }
protected:
    
    std::string m_textureID;
    
    int m_currentFrame;
    int m_currentRow;
    
    int m_x;
    int m_y;
    
    int m_width;
    int m_height;
    
};


#endif /* defined(__Game_SDL__GameObject__) */
