/* 
 * File:   Robot.cpp
 * Author: aletormat
 * 
 * Created on 17 de abril de 2015, 9:38
 */

#include "Robot.h"

Robot::Robot() : 
render()
, playerPhysics() 
, currentAnimation()
, animatedSprite(sf::seconds(0.2), true, false)
, walkingAnimationRight()
, walkingAnimationLeft()

{
}

Robot::Robot(const Robot& orig) {
}

Robot::~Robot() {
}


void Robot::Init(sf::Texture &tex, float pos_x, float pos_y, float vel_x, float vel_y){
    
    render.SetTextura(tex);
    
    walkingAnimationRight = render.getWalkingAnimationRight();
    walkingAnimationLeft = render.getWalkingAnimationLeft();
    
    currentAnimation = &walkingAnimationRight;
    animatedSprite.setPosition(pos_x, pos_y);
    
    
    playerPhysics.setPos(pos_x, pos_y);
    playerPhysics.setVel(vel_x, vel_y);
    
}

void Robot::Update(sf::Vector2f vel, sf::Time elapsedTime){
    playerPhysics.setVel(vel.x, vel.y);
    playerPhysics.Update(elapsedTime);
    
    //Actualizamos las animaciones
    if(vel.x>0 || vel.x==0){
        currentAnimation = &walkingAnimationRight;
    }
    else
        currentAnimation = &walkingAnimationLeft;
    
    animatedSprite.play(*currentAnimation);
    animatedSprite.update(elapsedTime);
    
}

void Robot::Draw(sf::RenderWindow& window, float interpolacion){
    render.Draw(window, playerPhysics.getLastPos(), playerPhysics.getPos(), interpolacion, animatedSprite);
}


float Robot::salta(int y, sf::Clock tiempoDesdeSalto, sf::Time elapsedTime){
    return playerPhysics.saltar(y, tiempoDesdeSalto, elapsedTime);

}

