//
//  InputHandler.h
//  Game_SDL
//
//  Created by zpf on 15-1-23.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#ifndef __Game_SDL__InputHandler__
#define __Game_SDL__InputHandler__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>
#include "Game.h"

class InputHandler{
public:
    static InputHandler* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
    }
    void update();
    void clean();
    
    void initialiseJoysticks();
    bool joysticksInitialised() {
        return m_bJoysticksInitialised;
    }
    
private:
    std::vector<SDL_Joystick*> m_joysticks;
    bool m_bJoysticksInitialised;
    
    InputHandler() ;
    ~InputHandler() {}
    
    static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;

#endif /* defined(__Game_SDL__InputHandler__) */
