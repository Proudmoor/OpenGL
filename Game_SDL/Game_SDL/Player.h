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

class Player : public SDLGameObject{
public:
    Player(const LoaderParams* pParams);
    
    virtual void draw();
    virtual void update();
    virtual void clean();
};

class Enemy: public SDLGameObject {
public:
    Enemy(const LoaderParams* pParams);
    
    virtual void draw();
    virtual void update();
    virtual void clean();
};



#endif /* defined(__Game_SDL__Player__) */
