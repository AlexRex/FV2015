/* 
 * File:   Mapa.h
 * Author: Carlos
 *
 * Created on 30 de marzo de 2015, 16:21
 */

#ifndef MAPA_H
#define	MAPA_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "../Includes/tinyxml2.h"

namespace txml2 = tinyxml2;

class Mapa {
public:
    Mapa();
    Mapa(const Mapa& orig);
    virtual ~Mapa();
    sf::Sprite* createSprite(sf::Sprite*, int, int, int);
    int** createColisiones();
    sf::Sprite** crearMapa();
    int** sitiosMonedas();
private:
    sf::Texture* texture;
    
};

#endif	/* MAPA_H */

