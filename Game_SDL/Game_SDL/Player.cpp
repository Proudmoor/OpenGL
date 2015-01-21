//
//  Player.cpp
//  Game_SDL
//
//  Created by zpf on 15-1-19.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#include "Player.h"

Player::Player(const LoaderParams* pParams):
SDLGameObject(pParams) {
    
}

void Player::draw() {
    SDLGameObject::draw();
}

void Player::update() {
    m_x -= 1;
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Player::clean() {
    
}