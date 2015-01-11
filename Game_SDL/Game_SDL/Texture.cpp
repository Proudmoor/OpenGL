//
//  Texture.cpp
//  Game_SDL
//
//  Created by zpf on 15-1-11.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#include "Texture.h"
#include <SDL2_image/SDL_image.h>

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer){
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    
    if (pTempSurface == 0) {
        return false;
    }
    
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    
    if (pTexture != 0) {
        m_textureMap [id] = pTexture;
        return true;
    }
    
    return false;
}