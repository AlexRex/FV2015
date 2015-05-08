/* 
 * File:   Game.h
 * Author: aletormat
 *
 * Created on 15 de abril de 2015, 9:46
 */

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <sstream>

#include "Robot.h"
#include "Mapa.h"
#include "ColisionSuelo.h"
#include "Camara.h"

#include "../Includes/AnimatedSprite.hpp"

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
    static const sf::Time   timePerFrame;
    
    sf::RenderWindow*       window;
    int                     windowHeight;
    int                     windowWidth;
    
    sf::Font*               debugFont;
    sf::Text*               debugText;
    
    sf::Sprite**            spritesObjetosAleatorios;
    sf::Sprite**            spritesMapa;
    sf::Sprite**            spritesMapa2;
    sf::Sprite**            spritesMonedas;
    sf::Sprite*             piezas;
    sf::Texture*            texturaRobot; //REND
    
    sf::RectangleShape*     vida1;
    sf::RectangleShape*     vida2;
    sf::RectangleShape*     vida3;
    sf::RectangleShape*     vida4;
    
    
    Mapa*                   mapa;
    Robot*                  robot;
    ColisionSuelo*          colision;
    Camara*                 camara;
    
    float                   interpolacion;
    int                     posIniSalto;
    
    int                     cantidadBloques;
    int                     posiblesBloques;
    
    bool                    mDcha;
    bool                    mIzq;
    bool                    caiendo;
    bool                    primeraVez;
};

#endif	/* GAME_H */

