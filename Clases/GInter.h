/* 
 * File:   GInter.h
 * Author: Carlos
 *
 * Created on 21 de abril de 2015, 18:20
 */

#ifndef GINTER_H
#define	GINTER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class GInter {
public:
    GInter();
    GInter(const GInter& orig);
    virtual ~GInter();
    sf::VideoMode* varVideomode(int, int);
    sf::Font* varFont();

    sf::RenderWindow* varRenderWindow(sf::VideoMode*, char[]);

    sf::Text* varText();
    sf::Time* varTime();
    sf::Sprite* varSprite(sf::Texture*, int, int);
    sf::Texture* varTexture(char[]);
    sf::Color* varColor(int, int, int, int);
    sf::Sprite* crearSprites();
    sf::Sprite* setScale(sf::Sprite*, int, int);
    sf::Sprite* setPosition(sf::Sprite*, int, int);
    sf::Sprite* setOrigin(sf::Sprite*, int, int);
private:
    
};

#endif	/* GINTER_H */

