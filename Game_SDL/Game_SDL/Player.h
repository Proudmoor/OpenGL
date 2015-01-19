//
//  Player.h
//  Game_SDL
//
//  Created by zpf on 15-1-19.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#ifndef __Game_SDL__Player__
#define __Game_SDL__Player__

#include <stdio.h>
#include "GameObject.h"

class Player : public GameObject{
public:
    void load(int x, int y, int width, int height, std::string textureID);
    void draw(SDL_Renderer* pRenderer);
    void update();
    void clean();
};



#endif /* defined(__Game_SDL__Player__) */
