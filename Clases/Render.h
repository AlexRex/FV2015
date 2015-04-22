/* 
 * File:   Render.h
 * Author: aletormat
 *
 * Created on 17 de abril de 2015, 9:54
 */

#ifndef RENDER_H
#define	RENDER_H

#include <SFML/Graphics.hpp>
#include "../Includes/AnimatedSprite.hpp"

class Render {
public:
    Render();
    Render(const Render& orig);
    virtual ~Render();
    
    void Draw(sf::RenderWindow &window, const sf::Vector2f &lastPos, const sf::Vector2f &pos, float interpolacion, AnimatedSprite& animatedSprite);
    void SetTextura(sf::Texture &tex);
    
    Animation getWalkingAnimationRight() const { return walkingAnimationRight; }
    Animation getWalkingAnimationLeft() const { return walkingAnimationLeft; }

    
    
    sf::Vector2f getRenderPos() const { return renderPos; }
private:
    
    sf::Vector2f        renderPos;
    Animation           walkingAnimationRight;
    Animation           walkingAnimationLeft;


};

#endif	/* RENDER_H */

