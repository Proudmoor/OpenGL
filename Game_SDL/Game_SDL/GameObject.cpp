//
//  GameObject.cpp
//  Game_SDL
//
//  Created by zpf on 15-1-12.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#include "GameObject.h"
#include "Texture.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) :
GameObject(pParams) {
    m_x = pParams -> getX();
    m_y = pParams -> getY();
    m_width = pParams -> getWidth();
    m_height = pParams -> getHeight();
    
    m_textureID = pParams -> getTextureID();
    
    m_currentRow = 1;
    m_currentFrame = 1;
}

void SDLGameObject::draw() {
    TextureManager::Instance() -> drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame,
                                            Game::Instance() -> getRenderer(), SDL_FLIP_NONE);
}