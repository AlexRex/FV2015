/* 
 * File:   Render.cpp
 * Author: aletormat
 * 
 * Created on 17 de abril de 2015, 9:54
 */

#include "Render.h"

Render::Render(){
    renderPos = new sf::Vector2f();
    walkingAnimation = new Animation();
    jumpingAnimation = new Animation();
    fallingAnimation = new Animation();
}

Render::Render(const Render& orig) {
}

Render::~Render() {
    std::cout<<"Liberar memoria render"<<std::endl;
    delete renderPos;
    delete walkingAnimation;
}

void Render::SetTextura(sf::Texture &tex){
    walkingAnimation->setSpriteSheet(tex);
    walkingAnimation->addFrame(sf::IntRect(0, 0, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(32, 0, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(64, 0, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(96, 0, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(128, 0, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(160, 0, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(192, 0, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(224, 0, 32, 64));
    
    walkingAnimation->addFrame(sf::IntRect(0, 64, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(32, 64, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(64, 64, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(96, 64, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(128, 64, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(160, 64, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(192, 64, 32, 64));
    walkingAnimation->addFrame(sf::IntRect(224, 64, 32, 64));
   
    fallingAnimation->setSpriteSheet(tex);
    fallingAnimation->addFrame(sf::IntRect(32, 192, 32, 64));

    
    jumpingAnimation->setSpriteSheet(tex);
    jumpingAnimation->addFrame(sf::IntRect(160, 128, 32, 64));

    
    
    //walkingAnimation->addFrame(sf::IntRect(0,0,32,64));

    
}

void Render::Draw(sf::RenderWindow& window, const sf::Vector2f& lastPos, const sf::Vector2f& pos, float interpolacion, AnimatedSprite& animatedSprite){
    
    *renderPos = sf::Vector2f(
            lastPos.x + ((pos.x - lastPos.x) * interpolacion),
            lastPos.y + ((pos.y - lastPos.y) * interpolacion));
    
    
    animatedSprite.setPosition(renderPos->x, renderPos->y);
    
    camara->setPos(*renderPos, 0);
    hud->setPos(*renderPos);
    window.draw(animatedSprite);
    
}
void Render::recibirCamara (Camara *cam){
    camara = cam;
}
void Render::recibirHud(Hud* mihud){
    hud = mihud;
}
