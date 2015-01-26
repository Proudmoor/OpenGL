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

void Player::handleInput(){
    if (InputHandler::Instance()->joysticksInitialised()) {
        if (InputHandler::Instance() -> xvalue(0, 1) > 0 ||
            InputHandler::Instance() -> xvalue(0, 1) < 0) {
            m_velocity.setX(1 * InputHandler::Instance() -> xvalue(0, 1));
        }
        
        if (InputHandler::Instance() -> yvalue(0, 1) > 0 ||
            InputHandler::Instance() -> yvalue(0, 1) < 0) {
            m_velocity.setX(1 * InputHandler::Instance() -> yvalue(0, 1));
        }
        
        if (InputHandler::Instance() -> xvalue(0, 2) > 0 ||
            InputHandler::Instance() -> xvalue(0, 2) < 0) {
            m_velocity.setX(1 * InputHandler::Instance() -> xvalue(0, 2));
        }
        
        if (InputHandler::Instance() -> yvalue(0, 2) > 0 ||
            InputHandler::Instance() -> yvalue(0, 2) < 0) {
            m_velocity.setX(1 * InputHandler::Instance() -> yvalue(0, 2));
        }
        
        if (TheInputHandler::Instance() -> getButtonState(0, 3)) {
            m_velocity.setX(1);
        }
        
        if (TheInputHandler::Instance() -> getMouseButtonState(LEFT)) {
            m_velocity.setX(1);
        }
        
        Vector2D* vec = TheInputHandler::Instance() -> getMousePosition();
        m_velocity = (*vec - m_position);
    }
}

void Player::update() {
    m_velocity.setX(0);
    m_velocity.setY(0);
    
    handleInput();
    
    m_currentFrame = int(((SDL_GetTicks() / 1000) % 6));
    //m_acceleration.setX(1);
    SDLGameObject::update();
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