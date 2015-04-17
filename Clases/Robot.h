/* 
 * File:   Robot.h
 * Author: aletormat
 *
 * Created on 17 de abril de 2015, 9:38
 */

#ifndef ROBOT_H
#define	ROBOT_H

#include "PlayerPhysics.h"
#include "Render.h"

class Robot {
public:
    Robot();
    Robot(const Robot& orig);
    virtual ~Robot();
    
    void Init(float pos_x, float pos_y, float vel_x=0.f, float vel_y=0.f);
    void Update(sf::Vector2f vel, sf::Time elapsedTime);
    void Draw(sf::RenderWindow& window, float interpolacion);
    
private:
    
    Render render;
    PlayerPhysics playerPhysics;

};

#endif	/* ROBOT_H */

