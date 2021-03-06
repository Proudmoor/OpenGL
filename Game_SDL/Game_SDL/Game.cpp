//
//  Game.cpp
//  Game_SDL
//
//  Created by zpf on 15-1-11.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#include "Game.h"
#include <SDL2_image/SDL_image.h>

typedef TextureManager TheTextureManager;

Game* Game::s_pInstance = 0;
bool Game::Init(const char *title, int xpos, int ypos,
                int width, int height, bool fullscreen) {
    

    
    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 640, 480, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));
    
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
    
    //load Texture  use textmanager
    //m_textureManager.load("char2.png", "animate", m_Render);
    if(!TheTextureManager::Instance() -> load("spritesheet.png", "animate", m_Render)) {
        return false;
    }
    
    TheInputHandler::Instance() -> initialiseJoysticks();
    
    SDL_ShowCursor(false);
    SDL_SetWindowGrab(m_Window, SDL_TRUE);
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    
     // start the main loop
    std::cout << "init success"<<std::endl;
    m_Running = true;
    return true;
}

void Game::render() {
    SDL_RenderClear(m_Render);
    
    for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i] -> draw();
    }
    
    SDL_RenderPresent(m_Render);
}

void Game::handleEvents() {
    TheInputHandler::Instance() -> update();
}

void Game::clean() {
    
    TheInputHandler::Instance() -> clean();
    std::cout << "cleanning the game" << std::endl;
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Render);
    SDL_Quit();
}

bool Game::IsRun() {
    return m_Running;
}

void Game::update() {
    for (std::vector<GameObject* >::size_type i = 0; i != m_gameObjects.size(); i++){
        m_gameObjects[i] -> update();
    }
}





