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