/* 
 * File:   Robot.cpp
 * Author: aletormat
 * 
 * Created on 17 de abril de 2015, 9:38
 */

#include "Robot.h"
#include "Camara.h"

Robot::Robot()
{
    std::cout<<"Creo robot"<<std::endl;
    
    render = new Render();
    playerPhysics = new PlayerPhysics();
    
    currentAnimation = new Animation();
    walkingAnimation = new Animation();
    animatedSprite = new AnimatedSprite(sf::seconds(0.05), true, false);
    camara = new Camara();
    

}

Robot::Robot(const Robot& orig) {
}

Robot::~Robot() {
    std::cout<<"Liberar memoria robot"<<std::endl;
    delete render;
    delete playerPhysics;
    delete animatedSprite;
    delete currentAnimation;
    delete walkingAnimation;
    delete camara;
}


void Robot::Init(sf::Texture &tex, float pos_x, float pos_y, float vel_x, float vel_y){
    
    
    render->SetTextura(tex);
    
    walkingAnimation = render->getWalkingAnimation();
    jumpingAnimation = render->getJumpingAnimation();
    fallingAnimation = render->getFallingAnimation();
   // walkingAnimationLeft = render.getWalkingAnimationLeft();
    
    currentAnimation = walkingAnimation;
    animatedSprite->setPosition(pos_x, pos_y);
    
    
    playerPhysics->setPos(pos_x, pos_y);
    playerPhysics->setVel(vel_x, vel_y);
    
}

void Robot::Update(sf::Vector2f vel, sf::Time elapsedTime){
    playerPhysics->setVel(vel.x, vel.y);
    playerPhysics->Update(elapsedTime);
    
    //Actualizamos las animaciones
    if(vel.x==0 && vel.y==0){
        currentAnimation = walkingAnimation;
    }
    else if(vel.y<0){
        currentAnimation = jumpingAnimation;
    }
    else if(vel.y>0)
        currentAnimation = fallingAnimation;
    else
        currentAnimation = walkingAnimation;
    
    

    
    animatedSprite->play(*currentAnimation);
    animatedSprite->update(elapsedTime);
    
}

void Robot::Draw(sf::RenderWindow& window, float interpolacion){
    render->Draw(window, playerPhysics->getLastPos(), playerPhysics->getPos(), interpolacion, *animatedSprite);
}


float Robot::getPosSalto(int y, sf::Clock tiempoDesdeSalto, sf::Time elapsedTime){
    return playerPhysics->getPosSalto(y, tiempoDesdeSalto, elapsedTime);
}

void Robot::mueveA(int x, int y){
    playerPhysics->setPos(x, y);
}
float Robot::saltar(){
    return playerPhysics->saltar();
}
float Robot::caer(sf::Time tiempoCaida, sf::Time elapsedTime){
    return playerPhysics->caer(tiempoCaida, elapsedTime);
}
void Robot::recibirCamara (Camara* micam){
    render->recibirCamara(micam);
}

