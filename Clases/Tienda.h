/* 
 * File:   tienda.h
 * Author: Carlos
 *
 * Created on 16 de mayo de 2015, 18:25
 */

#ifndef TIENDA_H
#define	TIENDA_H
#include <SFML/Graphics.hpp>
#pragma once

#include<iostream>
#define MAX_NUMBER_OF_ITEMS 5

class Tienda {
    
public:
    Tienda(float width, float height);
    //Tienda(const Tienda& orig);
    virtual ~Tienda();
    
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem(){ return selectedItemIndex;}
    sf::Text getTienda(int);
    sf::Sprite getSprite();
    bool enTienda(int cantidadBloques, float posX);
    void setMonedas(int mon);
    
private:
    int selectedItemIndex;
    sf::Font fuentePUNK;
    sf::Font fuenteMonedas;
    sf::Text tiendaLabel[MAX_NUMBER_OF_ITEMS];
    sf::Text monedasDisponibles;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    int monedas;
};

#endif

