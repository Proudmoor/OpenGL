//
//  Game.cpp
//  SFML_Game
//
//  Created by zpf on 15-1-26.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#include "Game.h"

Game::Game() :
m_window(sf::VideoMode(640, 480), "SFML GAME")
,m_player(){
    m_player.setRadius(40.0f);
    m_player.setPosition(100.f, 100.f);
    m_player.setFillColor(sf::Color::Cyan);
}

void Game::run() {
    while (m_window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
                
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
                
            case sf::Event::Closed:
                m_window.close();
                break;
                
            default:
                break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W) {
        m_isMovingUp = isPressed;
    } else if (key == sf::Keyboard::S) {
        m_isMovingDown = isPressed;
    } else if (key == sf::Keyboard::A) {
        m_isMovingLeft = isPressed;
    } else if (key == sf::Keyboard::D) {
        m_isMovingRight = isPressed;
    }
}
void Game::update() {
    sf::Vector2f movement(0.f, 0.f);
    if (m_isMovingUp) {
        movement.y -= 1.f;
    }
    if (m_isMovingDown) {
        movement.y += 1.f;
    }
    if (m_isMovingLeft) {
        movement.x -= 1.f;
    }
    if (m_isMovingRight) {
        movement.x += 1.f;
    }
    
    m_player.move(movement);
}

void Game::render() {
    m_window.clear();
    m_window.draw(m_player);
    m_window.display();
}