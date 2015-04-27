/* 
 * File:   Camara.cpp
 * Author: pablo
 * 
 * Created on 27 de abril de 2015, 16:48
 */

#include "Camara.h"

Camara::Camara() {
}
void Camara::creaCamara(int c1, int c2, int tamx, int tamy) {
    
    sf:: View* view = new sf::View();
    vistaCamara = view;
    vistaCamara->setCenter(c1,c2);
    vistaCamara->setSize(tamx,tamy);
    
    
}

void Camara::setPos(sf::Vector2f pos){
    vistaCamara->setCenter(pos);
}
Camara::Camara(const Camara& orig) {
}

Camara::~Camara() {
}


