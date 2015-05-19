/* 
 * File:   Menu.h
 * Author: sandra
 *
 * Created on 8 de mayo de 2015, 18:09
 */
#include <SFML/Graphics.hpp>
#pragma once

#include<iostream>
#ifndef MENUPUNTODECONTROL_H
#define	MENUPUNTODECONTROL_H
#define MAX_NUMBER_OF_ITEMS 3

class MenuPuntoDeControl {
    
public:
    MenuPuntoDeControl(float width, float height);
    //Menu(const Menu& orig);
    virtual ~MenuPuntoDeControl();
    
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    bool enPuntoControl(int cantidadBloques, float posX);
    int GetPressedItem(){ return selectedItemIndex;}
    
    void setMonedas(int mon);
    void setPuntuacion(int punt);

private:
    int selectedItemIndex;
    sf::Font fuentePUNK;
    sf::Font fuenteNormal;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    
    sf::Text puntuacionConseguida;
    sf::Text monedasConseguidas;
    
    int monedas;
    int puntuacion;

    
};

#endif

