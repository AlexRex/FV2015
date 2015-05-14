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
    
    vistaCamara = new sf::View();
    vistaCamara->setCenter(c1,c2);
    vistaCamara->setSize(tamx,tamy);
}

void Camara::creaCamaraMenu(int c1, int c2, int tamx, int tamy) {
    
    vistaMenu = new sf::View();
    vistaMenu->setCenter(c1,c2);
    vistaMenu->setSize(tamx,tamy);
}

void Camara::setPos(sf::Vector2f pos){
    vistaCamara->setCenter(pos.x+300.f, 320.f);
}
Camara::Camara(const Camara& orig) {
}

Camara::~Camara() {
    delete vistaCamara;
    delete vistaMenu;
}


