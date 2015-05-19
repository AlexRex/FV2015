/* 
 * File:   Hud.cpp
 * Author: Pablo
 * 
 * Created on 16 de mayo de 2015, 8:04
 */

#include "Hud.h"

Hud::Hud() {
}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
}

void Hud::crearHud(sf::Font* font){
    tiempo = new sf::Clock();
    mtiempo = new sf::Text();
    fuente = new sf::Font();
    
    piezas = new sf::Sprite[5];
    
    this->inicializarVidas();
    
    
    fuente = font;
    lastPos.x = 0;
    lastPos.y = 0;
    
    mtiempo->setFont(*fuente);
    mtiempo->setPosition(lastPos.x,lastPos.y);
    mtiempo->setCharacterSize(13);
    mtiempo->setColor(sf::Color::Black);
    
}

void Hud::setPos(sf::Vector2f pos){
    this->lastPos.x = pos.x;
    this->lastPos.y = pos.y;
    
    this->mtiempo->setPosition(lastPos.x-150,20);
    
    this->vidaBrIzq->setPosition(lastPos.x -150,90);
    this->vidaBrDer->setPosition(lastPos.x -25,90);
    this->vidaPieIzq->setPosition(lastPos.x -150,120);
    this->vidaPieDer->setPosition(lastPos.x -25,120);
    
    this->piezas[0].setPosition(lastPos.x -100, 124);
    this->piezas[1].setPosition(lastPos.x -95, 32);
    this->piezas[2].setPosition(lastPos.x -90, 123);
    this->piezas[3].setPosition(lastPos.x -115, 82);
    this->piezas[4].setPosition(lastPos.x -83, 82);
}


sf::RectangleShape* Hud::getVida(int n){
    sf::RectangleShape* barrita = new sf::RectangleShape();
    switch(n){
        case 0:
            barrita = this->getVidaBrIzq();
            break;
        case 1:barrita = this->getVidaBrDer();
        break;
        case 2: barrita = this->getVidaPieIzq();
        break;
        case 3: barrita = this->getVidaPieDer();
        break;
        default: barrita = this->getVidaBrIzq();
        break;
    }
    
    return barrita;
}
void Hud::recibirDatos(sf::Clock* tiempo){
    
    float t = tiempo->getElapsedTime().asSeconds();
    t = round(t*100) / 100;
    std::ostringstream oss;
    oss << t;
    std::string aux = oss.str();
    
    mtiempo->setString(aux);
}
void Hud::recibirPiezas(sf::Sprite* esquema){
    
    for(int i=0; i<5; i++){
        piezas[i] = esquema[i];
    }
}
void Hud::inicializarVidas(){
    
    vidaBrIzq = new sf::RectangleShape(sf::Vector2f(60, 10));
    vidaBrDer = new sf::RectangleShape(sf::Vector2f(60, 10));
    vidaPieIzq = new sf::RectangleShape(sf::Vector2f(60, 10));
    vidaPieDer = new sf::RectangleShape(sf::Vector2f(60, 10));
    
    vidaBrIzq->setFillColor(sf::Color(0, 255, 0));
    vidaBrIzq->setPosition(40,90);
    
    vidaBrDer->setFillColor(sf::Color(0, 255, 0));
    vidaBrDer->setPosition(165,90);
    
    vidaPieIzq->setFillColor(sf::Color(0, 255, 0));
    vidaPieIzq->setPosition(40,120);
    
    vidaPieDer->setFillColor(sf::Color(0, 255, 0));
    vidaPieDer->setPosition(165,120);
}
sf::RectangleShape* Hud::getVidaBrIzq(){
    return this->vidaBrIzq;
}
sf::RectangleShape* Hud::getVidaBrDer(){
    return this->vidaBrDer;
}
sf::RectangleShape* Hud::getVidaPieIzq(){
    return this->vidaPieIzq;
}
sf::RectangleShape* Hud::getVidaPieDer(){
    return this->vidaPieDer;
}
sf::Text* Hud::getTiempo(){
    return mtiempo;
}
sf::Sprite Hud::getPieza(int n){
    sf::Sprite sprite;
    sprite=this->piezas[n];
    return sprite;
}

void Hud::setVidaPieza(int vida, int i){
    
    float vidaGrafica = vida*0.6*0.2;
    sf::Color nuevoColor= sf::Color(0,255,0);
    
    if(vidaBrIzq != NULL)
        switch(i){
            case 0:
                /*
                std::cout<<vida<<" pieza: 0"<<std::endl;
                nuevo=*getVida(0);
                std::cout<<vida<<"muerte en switch"<<std::endl;
                nuevo.setSize(mivector);
                *vidaBrIzq = nuevo;
                std::cout<<vida<<"rica hamburguesa"<<std::endl;
                 *              * 
                
                
                 * */
                vidaBrIzq->setSize(sf::Vector2f(vidaGrafica, 10));
                if(vidaGrafica<20){
                        nuevoColor = sf::Color(255, 0, 0);
                        vidaBrIzq->setFillColor(nuevoColor);
                }
                else{
                    if(vidaGrafica<40){
                        nuevoColor= sf::Color(255, 255, 51);
                        vidaBrIzq->setFillColor(nuevoColor);
                    }
                    else{
                        nuevoColor= sf::Color(0, 255, 0);
                    vidaBrIzq->setFillColor(nuevoColor);
                    }
                } 
                break;
            case 1:
                std::cout<<vida<<" pieza: 1"<<std::endl;
                vidaBrDer->setSize(sf::Vector2f(vidaGrafica,10));
                if(vidaGrafica<20){
                        nuevoColor = sf::Color(255, 0, 0);
                        vidaBrDer->setFillColor(nuevoColor);
                }
                else{
                    if(vidaGrafica<40){
                        nuevoColor= sf::Color(255, 255, 51);
                        vidaBrDer->setFillColor(nuevoColor);
                    }
                    else{
                        nuevoColor= sf::Color(0, 255, 0);
                        vidaBrDer->setFillColor(nuevoColor);
                    }
                }  

                break;
            case 2:
                std::cout<<vida<<" pieza: 2"<<std::endl;
                vidaPieIzq->setSize(sf::Vector2f(vidaGrafica,10));
                if(vidaGrafica<20){
                        nuevoColor = sf::Color(255, 0, 0);
                        vidaPieIzq->setFillColor(nuevoColor);
                }
                else{
                    if(vidaGrafica<40){
                        nuevoColor= sf::Color(255, 255, 51);
                        vidaPieIzq->setFillColor(nuevoColor);
                    }
                    else{
                        nuevoColor= sf::Color(0, 255, 0);
                    vidaPieIzq->setFillColor(nuevoColor);
                    }
                }       
                   
                break;
            case 3:
                std::cout<<vida<<" pieza: 3"<<std::endl;
                vidaPieDer->setSize(sf::Vector2f(vidaGrafica,10));
                if(vidaGrafica<20){
                        nuevoColor = sf::Color(255, 0, 0);
                        vidaPieDer->setFillColor(nuevoColor);
                }
                else{
                    if(vidaGrafica<40){
                        nuevoColor= sf::Color(255, 255, 51);
                        vidaPieDer->setFillColor(nuevoColor);
                    }
                    else{
                        nuevoColor= sf::Color(0, 255, 0);
                    vidaPieDer->setFillColor(nuevoColor);
                    }
                } 
                    
                break;
                std::cout<<"implosion"<<std::endl;
        }
    
}