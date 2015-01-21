//
//  Game.h
//  Game_SDL
//
//  Created by zpf on 15-1-11.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#ifndef __Game_SDL__Game__
#define __Game_SDL__Game__

#include <iostream>
#include <SDL2/SDL.h>
#include "Texture.h"
#include "GameObject.h"
#include "Player.h"
#include <vector>

class Game
{
public:
    
    
    ~Game(){};
    
    bool Init(const char* title, int xpos, int ypos,
              int width, int height, bool fullscreen);
    
    void render();
    SDL_Renderer* getRenderer() const {
        return m_Render;
    }
    
    void update();
    
    void handleEvents();
    
    void clean();
    
    bool IsRun() ;
    
    static Game* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new Game();
            return s_pInstance;
        }
        return s_pInstance;
    }
private:
    Game() {};
    
    static Game* s_pInstance;
    bool m_Running;
    
    std::vector<GameObject* > m_gameObjects;
    
    SDL_Window* m_Window;
    SDL_Renderer* m_Render;
      // dont need with texture manager
//    SDL_Texture* m_Texture;
//    SDL_Rect    m_srcRect;
//    SDL_Rect    m_destRect;
     // instead use
    int m_currentFrame;
    int m_currentRow;
    //TextureManager m_textureManager;
    
};

#endif /* defined(__Game_SDL__Game__) */
