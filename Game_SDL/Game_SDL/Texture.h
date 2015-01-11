//
//  Texture.h
//  Game_SDL
//
//  Created by zpf on 15-1-11.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#ifndef __Game_SDL__Texture__
#define __Game_SDL__Texture__

#include <iostream>
#include <SDL2_image/SDL_image.h>
#include <map>

class TextureManager{
    
bool load (std::string fileName, std::string id,
           SDL_Renderer* gRenderer);

//draw
void draw(std::string id, int x, int y, int width, int height,
          SDL_Renderer gRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

std::map<std::string, SDL_Texture*> m_textureMap;
};

#endif /* defined(__Game_SDL__Texture__) */
