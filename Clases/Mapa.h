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
#include <string.h>
#include <SFML/Graphics.hpp>
#include "../Includes/tinyxml2.h"

namespace txml2 = tinyxml2;

class Mapa {
public:
    Mapa();
    Mapa(const Mapa& orig);
    virtual ~Mapa();
    sf::Sprite* createSprite(sf::Sprite*, int, int, int);
    int** createColisiones(int, char**);
    sf::Sprite** crearMapa(int , char[] );
    sf::Sprite** sitiosMonedas();
    sf::Sprite** objetosAleatorios();
    sf::Sprite* crearEsquema();
    sf::Sprite** crearFondo();
    
    char** generarMapa(int, int);
    
private:
    sf::Texture* texturaMapa;
    sf::Texture* texturaMoneda;
    sf::Texture* texturaObjAleatorio;
    sf::Texture* texturaEsquema;
    
    sf::Texture* texturaFondo;
    
};

#endif	/* MAPA_H */

