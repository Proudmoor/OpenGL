//
//  Game.cpp
//  Game_SDL
//
//  Created by zpf on 15-1-11.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#include "Game.h"
#include <SDL2_image/SDL_image.h>

bool Game::Init(const char *title, int xpos, int ypos,
                int width, int height, bool fullscreen) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL Init Success\n";
        
        int flags = 0;
        if (fullscreen) {
            flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        
        m_Window = SDL_CreateWindow(title, xpos, ypos, width, height,flags);
        if (m_Window != 0) {
            std::cout << "window creation success" << std::endl;
            m_Render = SDL_CreateRenderer(m_Window, -1, 0);
            
            if (m_Render != 0) {
                std::cout << "Render creation success" << std::endl;
                SDL_SetRenderDrawColor(m_Render, 255, 255, 255, 255);
            } else {
                std::cout << "render failed\n";
                return false;
            }
        }else {
            std::cout << "window creation failed" << std::endl;
            return false;
        }
    } else {
        std::cout << "SDL Init fail\n";
        return false;
    }
    
    //load Texture
    SDL_Surface* gTempSurface = IMG_Load("char2.png");
    m_Texture  = SDL_CreateTextureFromSurface(m_Render, gTempSurface);
    
    SDL_FreeSurface(gTempSurface);
    SDL_QueryTexture(m_Texture, nullptr, NULL, &m_srcRect.w, &m_srcRect.h);
    m_srcRect.w =   100;        m_srcRect.h= 100;
    m_destRect.x = 0;       m_srcRect.x = 0; // define the origin of rect
    m_destRect.y = 0;       m_srcRect.y = 80;
    m_destRect.w = 640;
    m_destRect.h = 480;
    
     // start the main loop
    std::cout << "init success"<<std::endl;
    m_Running = true;
    return true;
}

void Game::render() {
    SDL_RenderClear(m_Render);
    
    // draw something
    SDL_RenderCopyEx(m_Render, m_Texture, &m_srcRect, &m_destRect, 0, 0, SDL_FLIP_HORIZONTAL);
    
    SDL_RenderPresent(m_Render);
}

void Game::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_Running = false;
                break;
                
            default:
                break;
        }
    }
}

void Game::clean() {
    
    std::cout << "cleanning the game" << std::endl;
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Render);
    SDL_Quit();
}

bool Game::IsRun() {
    return m_Running;
}

void Game::update() {
    m_srcRect.x = 128 * int(((SDL_GetTicks() / 100) % 6));
}




