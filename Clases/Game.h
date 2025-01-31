/* 
 * File:   Game.h
 * Author: aletormat
 *
 * Created on 15 de abril de 2015, 9:46
 */

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <sstream>

#include "Robot.h"
#include "Mapa.h"
#include "Colisiones.h"
#include "Camara.h"
#include "Hud.h"
#include "Tienda.h"
#include "Menu.h"
#include "MenuMuerte.h"
#include "MenuPuntoDeControl.h"
#include "Guardado.h"

#include "../Includes/AnimatedSprite.hpp"

#ifndef GAME_H
#define	GAME_H


class Game : private sf::NonCopyable {
public:
    Game();
    virtual          ~Game();
    bool             run();
    void             update(sf::Time elapsedTime);
    void             render(float interpolacion);
    void             processEvents();
    void             controlarRobot(sf::Keyboard::Key key, bool presionada);
    void             controlarJuego(sf::Keyboard::Key key);
    void             controlarMenus(sf::Keyboard::Key key);
    void             controlarTienda(sf::Keyboard::Key key);
    void             controlarMenuMuerte(sf::Keyboard::Key key);
    void             controlarPuntoControl(sf::Keyboard::Key key);

    void             mostrarMenuMuerte();
    sf::Sprite***    construirMapas();
    void             construirFondos();
    
    
private:
    static const sf::Time   timePerFrame;
    
    sf::RenderWindow*       window;
    int                     windowHeight;
    int                     windowWidth;
    int                     status;
    
    sf::SoundBuffer         buffer;
    sf::Sound               sound;
    sf::Music               musica;
    
    sf::Font*               debugFont;
    sf::Text*               debugText;
    
    sf::Clock*               tiempoPartida;
    sf::Time                tiempoSaltoPause;
    
    sf::Sprite**            spritesObjetosAleatorios;
    sf::Sprite***           spritesMonedas;
    sf::Sprite***           spritesBloques;
    sf::Sprite***           spritesPiezas;
    
    sf::Sprite*             piezas;
    sf::RectangleShape*     barrasVida;
    sf::RectangleShape*     barrasVidaRepuesto;
    
    
    sf::Sprite***           spritesFondos;
    sf::Sprite*             spriteFondo;
    sf::Sprite*             fondo;
    
    sf::Texture*            texturaRobot; //REND
    sf::Texture             texturaFondo;
    sf::Vector2i            posInicial;

    
    sf::RectangleShape*     vida1;
    sf::RectangleShape*     vida2;
    sf::RectangleShape*     vida3;
    sf::RectangleShape*     vida4;
    
    
    Mapa*                   mapa;
    Robot*                  robot;
    Colisiones*             colision;
    Camara*                 camara;
    Camara*                 camaraMenu;
    Hud*                    hud;
    Pieza*                  nuevaPieza;
    Guardado*               guardado;
    
    Tienda*                 tienda;
    Menu*                   menu;
    MenuMuerte*             menuMuerte;
    MenuPuntoDeControl*     menuPuntoControl;
    
    
    float                   interpolacion;
    int                     posIniSalto;
    
    int                     cantidadBloques;
    int                     posiblesBloques;    
    char**                  nombreBloques;
    
    int                     puntuacion;
    int                     monedasRecogidas;
    int*                    ranking;
    
    float                   coeficienteDesintegracion;
    
    bool                    mDcha;
    bool                    mIzq;
    bool                    caiendo;
    bool                    primeraVez;
    bool                    muerto;
    bool                    pause;
    
    void pintarHud();
};

#endif	/* GAME_H */

