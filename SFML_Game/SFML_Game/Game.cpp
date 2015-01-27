//
//  Game.cpp
//  SFML_Game
//
//  Created by zpf on 15-1-26.
//  Copyright (c) 2015年 zpf. All rights reserved.
//

#include "Game.h"

Game::Game() :
m_texture()
,m_player(){
    if (!m_texture.loadFromFile("Media/Textures/Eagle.png")) {
        //...
    }
    m_player.setTexture(m_texture);
    m_player.setPosition(100.f, 100.f);
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (m_window.isOpen()) {
        //sf::Time deltaTime = clock.restart();
        handleEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame){
            timeSinceLastUpdate -= TimePerFrame;
            handleEvents();
            update(TimePerFrame);
        }
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

void Game::update(sf::Time deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    float PlayerSpeed = 10.0f;
    if (m_isMovingUp) {
        movement.y -= PlayerSpeed;
    }
    if (m_isMovingDown) {
        movement.y += PlayerSpeed;
    }
    if (m_isMovingLeft) {
        movement.x -= PlayerSpeed;
    }
    if (m_isMovingRight) {
        movement.x += PlayerSpeed;
    }
    
    m_player.move(movement * deltaTime.asSeconds());
}

void Game::render() {
    m_texture.clear();
    m_window.draw(m_player);
    m_window.display();
}