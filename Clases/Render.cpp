/* 
 * File:   Render.cpp
 * Author: aletormat
 * 
 * Created on 17 de abril de 2015, 9:54
 */

#include "Render.h"

Render::Render() :
renderPos()
{
}

Render::Render(const Render& orig) {
}

Render::~Render() {
}

void Render::Draw(sf::RenderWindow& window, const sf::Vector2f& lastPos, const sf::Vector2f& pos, float interpolacion){
    
    sf::CircleShape shape(50);

    // set the shape color to green
    shape.setFillColor(sf::Color(100, 250, 50));    
    
    renderPos = sf::Vector2f(
            lastPos.x + ((pos.x - lastPos.x) * interpolacion),
            lastPos.y + ((pos.y - lastPos.y) * interpolacion));
    
    shape.setPosition(renderPos.x, renderPos.y);
    window.draw(shape);
    
}