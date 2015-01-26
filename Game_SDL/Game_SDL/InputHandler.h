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
#include <iostream>
#include "Vector2D.h"


enum mouse_buttons{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

const int m_joystickDeadZone = 10000;

class InputHandler{
   
public:
    static InputHandler* Instance() {
        if (s_Instance == 0) {
            s_Instance = new InputHandler();
        }
        return s_Instance;
    }
    
    void update();
    void clean();
    
    void initialiseJoysticks();
    bool joysticksInitialised() {
        return m_bJoysticksInitialised;
    }
    
    bool getButtonState(int joy, int buttonNumber) {
        return m_buttonStates[joy][buttonNumber];
    }
    
    bool getMouseButtonState(int buttonNumber) {
        return m_mouseButtonStates[buttonNumber];
    }
    
    Vector2D* getMousePosition(){
        return m_mousePosition;
    }
    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);
    
private:
    std::vector<SDL_Joystick*> m_joysticks;
    bool m_bJoysticksInitialised;
    std::vector<std::pair<Vector2D*, Vector2D*> > m_joystickValues;
    std::vector<std::vector<bool>> m_buttonStates;
    
    std::vector<bool> m_mouseButtonStates;
    
    Vector2D* m_mousePosition;

    static InputHandler*  s_Instance;
    InputHandler();
    ~InputHandler() {}
    
    
};


typedef InputHandler TheInputHandler;

#endif /* defined(__Game_SDL__InputHandler__) */
