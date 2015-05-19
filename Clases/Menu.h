/* 
 * File:   Menu.h
 * Author: sandra
 *
 * Created on 8 de mayo de 2015, 18:09
 */
#include <SFML/Graphics.hpp>
#pragma once

#include<iostream>
#ifndef MENU_H
#define	MENU_H
#define MAX_NUMBER_OF_ITEMS 3

class Menu {
    
public:
    Menu(float width, float height);
    //Menu(const Menu& orig);
    virtual ~Menu();
    
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

