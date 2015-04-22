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
    walkingAnimationRight.addFrame(sf::IntRect(0, 0, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(64, 0, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(128, 0, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(192, 0, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(256, 0, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(320, 0, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(384, 0, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(448, 0, 64, 146));
    
    walkingAnimationRight.addFrame(sf::IntRect(0, 146, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(64, 146, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(128, 146, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(192, 146, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(256, 146, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(320, 146, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(384, 146, 64, 146));
    walkingAnimationRight.addFrame(sf::IntRect(448, 146, 64, 146));

    
}

void Render::Draw(sf::RenderWindow& window, const sf::Vector2f& lastPos, const sf::Vector2f& pos, float interpolacion, AnimatedSprite& animatedSprite){
    

    
    renderPos = sf::Vector2f(
            lastPos.x + ((pos.x - lastPos.x) * interpolacion),
            lastPos.y + ((pos.y - lastPos.y) * interpolacion));
    
    
    animatedSprite.setPosition(renderPos.x, renderPos.y);
    window.draw(animatedSprite);
    
}