/* 
 * File:   GInter.cpp
 * Author: Carlos
 * 
 * Created on 21 de abril de 2015, 18:20
 */

#include "GInter.h"

GInter::GInter() {
    std::cout<<"Interfaz gráfica creada"<<std::endl;
}

GInter::GInter(const GInter& orig) {
}

GInter::~GInter() {
    std::cout<<"Liberamos memoria de interfaz gráfica"<<std::endl;
}

sf::Color* GInter::varColor(int a, int b, int c, int d){
    sf::Color* color = new sf::Color(a,b,c,d);
    return color;
}

sf::Texture* GInter::varTexture(char archivo[]){
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile(archivo)){
        std::cerr << "Error cargando " << archivo;
        exit(0);
    }
    return texture;
}

sf::Sprite* GInter::varSprite(sf::Texture* texture, int ox, int oy){
    sf::Sprite* sprite = new sf::Sprite();
    sprite->setTexture(*texture);
    sprite->setTextureRect(sf::IntRect(ox, oy, 32, 32));
    return sprite;
}

sf::VideoMode* GInter::varVideomode(int ancho, int alto){
    sf::VideoMode* videomode = new sf::VideoMode(ancho, alto);
    return videomode;
}

sf::Sprite* GInter::setScale(sf::Sprite* sprite, int x, int y){
    sprite->setScale(x, y);
    return sprite;
}

sf::Sprite* GInter::setPosition(sf::Sprite* sprite, int x, int y){
    sprite->setPosition(x,y);
    return sprite;
}

sf::Sprite* GInter::setOrigin(sf::Sprite* sprite, int x, int y){
    sprite->setOrigin(x,y);
    return sprite;
}