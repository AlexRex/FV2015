/* 
 * File:   Camara.cpp
 * Author: pablo
 * 
 * Created on 27 de abril de 2015, 16:48
 */

#include "Camara.h"
#include <iostream>


Camara::Camara() {
}
void Camara::creaCamara(int c1, int c2, int tamx, int tamy, int cantidBloques) {
    
    vistaCamara = new sf::View();
    vistaCamara->setCenter(c1,c2);
    vistaCamara->setSize(tamx,tamy);
    cantBloques = cantidBloques;
    
    
}

void Camara::creaCamaraMenu(int c1, int c2, int tamx, int tamy) {
    
    vistaMenu = new sf::View();
    vistaMenu->setCenter(c1,c2);
    vistaMenu->setSize(tamx,tamy);
}

void Camara::setPos(sf::Vector2f pos, int status){
    
    if(status==0){
        int nBloque = 0;
        int spriteX = 0;
        int pixelBloque = 928;



       // std::cout<<"posX: "<<pos.x<<std::endl;


        nBloque = pos.x/(29*32);
        spriteX = pos.x - (pixelBloque*nBloque);

        //std::cout<<"bloque: "<<nBloque<<" spriteX: "<<spriteX<<std::endl;

        if(nBloque < cantBloques-1)
            vistaCamara->setCenter(pos.x+300.f, 320.f);
        else{

            if(spriteX<192){
                vistaCamara->setCenter(pos.x+300.f, 320.f);
            }
        }
    }
    else{
        vistaCamara->setCenter(480.f, 320.f);
    }
        
}
Camara::Camara(const Camara& orig) {
}

Camara::~Camara() {
    delete vistaCamara;
    delete vistaMenu;
}

void Camara::setCantBloques(int bq){
    cantBloques = bq;
}