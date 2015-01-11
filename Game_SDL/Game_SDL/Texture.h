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
public:
    
    bool load (std::string fileName, std::string id,
           SDL_Renderer* gRenderer);

   //draw
    void draw(std::string id, int x, int y, int width, int height,
          SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    //draw frame
    void drawFrame(std::string id, int x, int y, int width, int height,
                   int currentRow, int currentFrame, SDL_Renderer* pRenderer,
                   SDL_RendererFlip flip);
    
    static TextureManager* Instance();

    private:
    static TextureManager* s_pInstance;
    TextureManager() {}
    
    std::map<std::string, SDL_Texture*> m_textureMap;
};

#endif /* defined(__Game_SDL__Texture__) */
