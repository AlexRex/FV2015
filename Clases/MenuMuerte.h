/* 
 * File:   Menu.h
 * Author: sandra
 *
 * Created on 8 de mayo de 2015, 18:09
 */
#include <SFML/Graphics.hpp>
#pragma once

#include<iostream>
#ifndef MENUPUNTOCONTROL_H
#define	MENUPUNTOCONTROL_H
#define MAX_NUMBER_OF_ITEMS 2

class MenuMuerte {
    
public:
    MenuMuerte(float width, float height);
    //Menu(const Menu& orig);
    virtual ~MenuMuerte();
    
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem(){ return selectedItemIndex;}
private:
    int selectedItemIndex;
    sf::Font fuente;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
};

#endif

