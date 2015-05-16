/* 
 * File:   Hud.h
 * Author: Pablo
 *
 * Created on 16 de mayo de 2015, 8:04
 */

#ifndef HUD_H
#define	HUD_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <math.h>
#include <SFML/System.hpp>


class Hud {
public:
    Hud();
    Hud(const Hud& orig);
    virtual ~Hud();
    
    void crearHud(sf::Font* fuente);
    void recibirDatos(sf::Clock* tiempo);
    void recibirPiezas(sf::Sprite* esquema);
    void setPos(sf::Vector2f pos);
    
    sf::Sprite getPieza(int n);
    sf::Text* getTiempo();
    sf::RectangleShape* getVida(int n);
private:
    
    sf::Clock* tiempo;
    sf::Text* mtiempo;
    sf::Font* fuente;
    
    sf::Vector2i lastPos;
    
    sf::RectangleShape* vidaBrIzq;
    sf::RectangleShape* vidaBrDer;
    sf::RectangleShape* vidaPieIzq;
    sf::RectangleShape* vidaPieDer;
    
    sf::Sprite*         piezas;
    
    sf::RectangleShape* getVidaBrIzq();
    sf::RectangleShape* getVidaBrDer();
    sf::RectangleShape* getVidaPieIzq();
    sf::RectangleShape* getVidaPieDer();
    
    void inicializarVidas();
};

#endif	/* HUD_H */

