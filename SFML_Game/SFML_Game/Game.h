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
const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

class Game {
public:
    Game();
    void run();
    
private:
    void handleEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time deltaTime);
    void render();
    
    sf::RenderWindow m_window;
    //sf::CircleShape  m_player;
    
    sf::Texture m_texture;
    sf::Sprite m_player;
    
    bool m_isMovingUp, m_isMovingDown, m_isMovingLeft, m_isMovingRight;
    int m_speed = 1;
};

#endif /* defined(__SFML_Game__Game__) */
