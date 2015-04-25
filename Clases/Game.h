/* 
 * File:   Game.h
 * Author: aletormat
 *
 * Created on 15 de abril de 2015, 9:46
 */

#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <sstream>

#include "Robot.h"
#include "Mapa.h"
#include "GInter.h"

#include "../Includes/AnimatedSprite.hpp"
#include "../Includes/tinyxml2.h"

#ifndef GAME_H
#define	GAME_H


class Game : private sf::NonCopyable {
public:
    Game();
    virtual ~Game();
    void    run();
    void    update(sf::Time elapsedTime);
    void    render(float interpolacion);
    void    processEvents();
    void    controlarRobot(sf::Keyboard::Key key, bool presionada);
    
private:
    GInter*                 gInter;
    static const sf::Time   timePerFrame;
    
    sf::RenderWindow*       window;
    int                     windowHeight;
    int                     windowWidth;
    
    sf::Font*               debugFont;
    sf::Text*               debugText;
    
    sf::Sprite**            sprites;
    sf::Texture*            texturaRobot; //REND
    
    Mapa*                   mapa;
    Robot*                  robot;
    
    float                   interpolacion;
    int                     posIniSalto;
    
    bool                    mDcha;
    bool                    mIzq;
    bool                    saltando;
    bool                    primeraVez;
};

#endif	/* GAME_H */

