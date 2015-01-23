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
    m_position.setX(m_position.getX() + 1);
    m_currentFrame = int(((SDL_GetTicks() / 1000) % 6));
}

void Player::clean() {
    
}

Enemy::Enemy(const LoaderParams* pParams):
SDLGameObject(pParams) {
    
}

void Enemy::draw() {
    SDLGameObject::draw();
}

void Enemy::update() {
    m_position.setX(m_position.getX() + 1);
    m_position.setY(m_position.getY() + 1);
    m_currentFrame = int (((SDL_GetTicks() / 80) % 6));
}

void Enemy::clean() {
    
}