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
    
    void crearHud(sf::Font* fuente, int cantidBloques);
    void recibirDatos(sf::Clock* tiempo);
    void recibirPiezas(sf::Sprite* esquema);
    void setPos(sf::Vector2f pos);
    
    void setVidaPieza(int vida, int i);
    void setVidaRepuesto(int i, int vida);
    
    sf::Sprite getPieza(int n);
    sf::Text* getTiempo();
    sf::RectangleShape* getVida(int n);
    sf::RectangleShape* getVidaRepuesto(int n);
private:
    
    sf::Clock* tiempo;
    sf::Text* mtiempo;
    sf::Font* fuente;
    
    sf::Vector2i lastPos;
    
    sf::RectangleShape* vidaBrIzq;
    sf::RectangleShape* vidaBrDer;
    sf::RectangleShape* vidaPieIzq;
    sf::RectangleShape* vidaPieDer;
    
    sf::RectangleShape* vidaBrIzqRepuesto;
    sf::RectangleShape* vidaBrDerRepuesto;
    sf::RectangleShape* vidaPieIzqRepuesto;
    sf::RectangleShape* vidaPieDerRepuesto;
    
    sf::Sprite*         piezas;
    
    int                 cantBloques;
    
    sf::RectangleShape* getVidaBrIzq();
    sf::RectangleShape* getVidaBrDer();
    sf::RectangleShape* getVidaPieIzq();
    sf::RectangleShape* getVidaPieDer();
    
    sf::RectangleShape* getVidaBrIzqRepuesto();
    sf::RectangleShape* getVidaBrDerRepuesto();
    sf::RectangleShape* getVidaPieIzqRepuesto();
    sf::RectangleShape* getVidaPieDerRepuesto();
    
    void inicializarVidas();
};

#endif	/* HUD_H */
