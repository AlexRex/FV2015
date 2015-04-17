/* 
 * File:   PlayerPhysics.cpp
 * Author: aletormat
 * 
 * Created on 17 de abril de 2015, 9:41
 */

#include "PlayerPhysics.h"

PlayerPhysics::PlayerPhysics() :
lastPos(sf::Vector2f(0.f, 0.f))
,pos(sf::Vector2f(0.f, 0.f))
,velocidad(sf::Vector2f(0.f, 0.f))
,acel(-686.89)
,velIniSalto(608)
{
}

PlayerPhysics::PlayerPhysics(const PlayerPhysics& orig) {
}

PlayerPhysics::~PlayerPhysics() {
}

void PlayerPhysics::setPos(float pos_x, float pos_y){
    lastPos = sf::Vector2f(pos_x, pos_y);
    pos = sf::Vector2f(pos_x, pos_y);
}

void PlayerPhysics::setVel(float vel_x, float vel_y){
    velocidad = sf::Vector2f(vel_x, vel_y);
}

void PlayerPhysics::Update(sf::Time elapsedTime){
    
    lastPos = pos;
    pos.x += velocidad.x * elapsedTime.asSeconds();
    pos.y += velocidad.y * elapsedTime.asSeconds();
}

int PlayerPhysics::saltar(int y, sf::Clock tiempoDesdeSalto){
    
    float altF = y; //altura con decimales
    int altI = 0; //altura en pixeles
    altF = y - velIniSalto * tiempoDesdeSalto.getElapsedTime().asSeconds() - 0.5 * acel * pow(tiempoDesdeSalto.getElapsedTime().asSeconds(),2); //ecuacion de altura
    altI = int(altF);
    /* Esto es lo mismo que los couts de toda la vida. Lo he puesto asi para
     evitar el uso de "using namespace std" que parece ser que es una mala
     practica
     */
    std::cout<<"Timpo: "<<tiempoDesdeSalto.getElapsedTime().asSeconds()<<std::endl;
    std::cout<<"Y: "<<y<<std::endl;
    std::cout<<"altF: "<<altF<<std::endl; 
    //std::cout<<"altI: "<<altI<<std::endl;
    
    
    pos.y = altF;
    
    std::cout<<"Pos Pel: "<<pos.y<<std::endl;
    
    return altI;
}