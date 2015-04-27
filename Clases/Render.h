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

#include <iostream>

class Render {
public:
    Render();
    Render(const Render& orig);
    virtual ~Render();
    
    void Draw(sf::RenderWindow &window, const sf::Vector2f &lastPos, const sf::Vector2f &pos, float interpolacion, AnimatedSprite& animatedSprite);
    void SetTextura(sf::Texture &tex);
    
    Animation* getWalkingAnimation() const { return walkingAnimation; }
    Animation* getJumpingAnimation() const { return jumpingAnimation; }
    Animation* getFallingAnimation() const { return fallingAnimation; }



    
    
    sf::Vector2f* getRenderPos() const { return renderPos; }
private:
    
    sf::Vector2f*        renderPos;
    Animation*           walkingAnimation;
    Animation*           jumpingAnimation;
    Animation*           fallingAnimation;


};

#endif	/* RENDER_H */

