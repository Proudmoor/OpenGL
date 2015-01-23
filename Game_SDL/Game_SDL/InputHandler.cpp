//
//  InputHandler.cpp
//  Game_SDL
//
//  Created by zpf on 15-1-23.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#include "InputHandler.h"
#include <iostream>

void InputHandler::initialiseJoysticks(){
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }
    
    if(SDL_NumJoysticks() > 0) {
        for (int i = 0; i < SDL_NumJoysticks(); i++) {
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            if (SDL_JoystickGetAttached(joy) == 1) {
                m_joysticks.push_back(joy);
            } else
            {
                std::cout << SDL_GetError();
            }
        }
        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;
        
        std::cout << "Initialised" << m_joysticks.size() << "joysticks";
    } else {
        m_bJoysticksInitialised = false;
    }
}

void InputHandler::clean() {
    if (m_bJoysticksInitialised) {
        for (unsigned int i = 0; i < SDL_NumJoysticks(); i++){
            SDL_JoystickClose(m_joysticks[i]);
        }
    }
}

void InputHandler::update() {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            Game::Instance() -> clean();
        }
    }
}