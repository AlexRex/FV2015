/* 
 * File:   Pieza.h
 * Author: leti
 *
 * Created on 18 de mayo de 2015, 17:13
 */

#ifndef PIEZA_H
#define	PIEZA_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string.h>

class Pieza {
public:
    Pieza();
    Pieza(const Pieza& orig);
    virtual ~Pieza();
    
    int iniciarPieza(int);
    int actualizaVida(sf::Time, float coeficiente);
    
    void darVuelta();
    int getVida();
    int getTipo();
    sf::Sprite* getSprite();
    void setMuerta(bool);
    bool getMuerta();
    float getVelocidad();
    float getSalto();
    
private:
    int tipo;
    int vida;
    int debilidad;
    float velocidad;
    float salto;
    bool muerta;
    sf::Sprite* sprite;
    sf::Texture* texture;
};

#endif	/* PIEZA_H */

