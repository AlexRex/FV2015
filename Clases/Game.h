/* 
 * File:   Game.h
 * Author: aletormat
 *
 * Created on 15 de abril de 2015, 9:46
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Robot.h"
#include "../Includes/AnimatedSprite.hpp"

#ifndef GAME_H
#define	GAME_H


class Game : private sf::NonCopyable {
public:
    Game();
    void    run();
    void    update(sf::Time elapsedTime);
    void    render(float interpolacion);
    void    processEvents();
    void    controlarRobot(sf::Keyboard::Key key, bool presionada);
    
private:
    static const sf::Time timePerFrame;
    
    sf::RenderWindow      window;
    
    sf::Font              debugFont;
    sf::Text              debugText;
    
    sf::Texture           texturaRobot; //REND

    
    
    
    Robot                 robot;
    
    float                 interpolacion;
    
    bool                  mDcha;
    bool                  mIzq;
    bool                  saltando;
    bool                  primeraVez;
};

#endif	/* GAME_H */

