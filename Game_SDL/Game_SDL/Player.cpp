//
//  Player.cpp
//  Game_SDL
//
//  Created by zpf on 15-1-19.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#include "Player.h"

void Player::load(int x, int y, int width, int height, std::string textureID){
    GameObject::load(x, y, width, height, textureID);
}

void Player::draw(SDL_Renderer *pRenderer){
    GameObject::draw(pRenderer);
}

void Player::update() {
    m_x -=1;
}