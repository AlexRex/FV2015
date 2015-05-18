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
    int getTipo();
    sf::Sprite* getSprite();
    void setMuerta(bool);
    bool getMuerta();
    void iniciarPieza(int);
    void darVuelta();
private:
    int tipo;
    int vida;
    bool muerta;
    sf::Sprite* sprite;
    sf::Texture* texture;
};

#endif	/* PIEZA_H */

