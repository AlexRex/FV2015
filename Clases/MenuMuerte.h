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
    
    void setRanking(int* rank);
    void setMonedas(int mon);
    void setPuntuacion(int punt);

private:
    int selectedItemIndex;
    sf::Font fuente;
    sf::Font fuenteNormal;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    
    
    sf::Text puntuacionConseguida;
    sf::Text monedasConseguidas;
    sf::Text rankingLabel[5];
    
    int* ranking;
    int monedas;
    int puntuacion;

};

#endif

