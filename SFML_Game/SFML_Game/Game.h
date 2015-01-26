//
//  Game.h
//  SFML_Game
//
//  Created by zpf on 15-1-26.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#ifndef __SFML_Game__Game__
#define __SFML_Game__Game__

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();
    
private:
    void handleEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update();
    void render();
    
    sf::RenderWindow m_window;
    sf::CircleShape  m_player;
    
    bool m_isMovingUp, m_isMovingDown, m_isMovingLeft, m_isMovingRight;
};

#endif /* defined(__SFML_Game__Game__) */
