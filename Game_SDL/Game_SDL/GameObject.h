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

class GameObject {
public:
    void draw() {
        std::cout << "draw game object";
    }
    
    void update() {
        std::cout << "update game object";
    }
    
    void clean() {
        std::cout << "clean game object";
    }
protected:
    int m_x;
    int m_y;
    
};
#endif /* defined(__Game_SDL__GameObject__) */
