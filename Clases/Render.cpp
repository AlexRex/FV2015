/* 
 * File:   Render.cpp
 * Author: aletormat
 * 
 * Created on 17 de abril de 2015, 9:54
 */

#include "Render.h"

Render::Render() :
renderPos()
, walkingAnimationRight()
, walkingAnimationLeft()
{
}

Render::Render(const Render& orig) {
}

Render::~Render() {
}

void Render::SetTextura(sf::Texture &tex){
    walkingAnimationRight.setSpriteSheet(tex);
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));
    
    walkingAnimationLeft.setSpriteSheet(tex);
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));
    
}

void Render::Draw(sf::RenderWindow& window, const sf::Vector2f& lastPos, const sf::Vector2f& pos, float interpolacion, AnimatedSprite& animatedSprite){
    

    
    renderPos = sf::Vector2f(
            lastPos.x + ((pos.x - lastPos.x) * interpolacion),
            lastPos.y + ((pos.y - lastPos.y) * interpolacion));
    
    
    animatedSprite.setPosition(renderPos.x, renderPos.y);
    window.draw(animatedSprite);
    
}