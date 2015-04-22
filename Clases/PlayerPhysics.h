/* 
 * File:   PlayerPhysics.h
 * Author: aletormat
 *
 * Created on 17 de abril de 2015, 9:41
 */

#ifndef PLAYERPHYSICS_H
#define	PLAYERPHYSICS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "../Includes/AnimatedSprite.hpp"


class PlayerPhysics {
public:
    PlayerPhysics();
    PlayerPhysics(const PlayerPhysics& orig);
    virtual ~PlayerPhysics();
    
    sf::Vector2f getLastPos() const { return lastPos; }
    sf::Vector2f getPos() const { return pos; }
    sf::Vector2f getNextPos(sf::Time elapsedTime) const;
    sf::Vector2f getVel() const { return velocidad; }
    
    
    
    void setVel(float vel_x, float vel_y);
    void setPos(float pos_x, float pos_y);
    void Update(sf::Time elapsedTime);
    
   
    
    float saltar(int y, sf::Clock tiempoDesdeSalto, sf::Time elapsedTime);
    
private:
    
    sf::Vector2f    lastPos;
    sf::Vector2f    pos;
    sf::Vector2f    velocidad;
    
    float           acel;
    float           velIniSalto;
    

};

#endif	/* PLAYERPHYSICS_H */

