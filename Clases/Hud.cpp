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
    delete tiempo;
    delete mtiempo;
    delete fuente;
    delete vidaBrIzq;
    delete vidaBrDer;
    delete vidaPieIzq;
    delete vidaPieDer;
    delete vidaBrIzqRepuesto;
    delete vidaBrDerRepuesto;
    delete vidaPieIzqRepuesto;
    delete vidaPieDerRepuesto;
    
    delete piezas;
}

void Hud::crearHud(sf::Font* font, int cantidBloques){
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
    mtiempo->setCharacterSize(20);
    mtiempo->setColor(sf::Color::Yellow);
    
    cantBloques = cantidBloques;
    
}

void Hud::setPos(sf::Vector2f pos){
    int nBloque = 0;
    int spriteX = 0;
    int pixelBloque = 928;
    

       
    
    nBloque = pos.x/(29*32);
    spriteX = pos.x - (pixelBloque*nBloque);
    
    
    if(nBloque < cantBloques-1){
        this->lastPos.x = pos.x;
        this->lastPos.y = pos.y;

        this->mtiempo->setPosition(lastPos.x-150,20);

        this->vidaBrIzq->setPosition(lastPos.x -150,90);
        this->vidaBrDer->setPosition(lastPos.x -25,90);
        this->vidaPieIzq->setPosition(lastPos.x -150,120);
        this->vidaPieDer->setPosition(lastPos.x -25,120);
        
        this->vidaBrIzqRepuesto->setPosition(lastPos.x -150,100);
        this->vidaBrDerRepuesto->setPosition(lastPos.x -25,100);
        this->vidaPieIzqRepuesto->setPosition(lastPos.x -150,130);
        this->vidaPieDerRepuesto->setPosition(lastPos.x -25,130);

        this->piezas[0].setPosition(lastPos.x -100, 124);
        this->piezas[1].setPosition(lastPos.x -95, 32);
        this->piezas[2].setPosition(lastPos.x -90, 123);
        this->piezas[3].setPosition(lastPos.x -115, 82);
        this->piezas[4].setPosition(lastPos.x -83, 82);
    }
    else{
        
        if(spriteX<192){
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
        
    }
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

sf::RectangleShape* Hud::getVidaRepuesto(int n){
    sf::RectangleShape* barrita = new sf::RectangleShape();
    switch(n){
        case 0:
            barrita = this->getVidaBrIzqRepuesto();
            break;
        case 1:barrita = this->getVidaBrDerRepuesto();
        break;
        case 2: barrita = this->getVidaPieIzqRepuesto();
        break;
        case 3: barrita = this->getVidaPieDerRepuesto();
        break;
        default: barrita = this->getVidaBrIzqRepuesto();
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

void Hud::setVidaPieza(int vida, int i){
    
    float vidaGrafica = vida*0.6*0.2;
    sf::Color nuevoColor= sf::Color(0,255,0);
    
    if(vidaBrIzq != NULL)
        switch(i){
            case 0:
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
                //std::cout<<vida<<" pieza: 1"<<std::endl;
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
                //std::cout<<vida<<" pieza: 2"<<std::endl;
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
                //std::cout<<vida<<" pieza: 3"<<std::endl;
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
               // std::cout<<"implosion"<<std::endl;
        }
    
}

void Hud::setVidaRepuesto(int vida, int i){
    
    float vidaGrafica = vida*0.3*0.2;
    sf::Color nuevoColor= sf::Color(170,50,170);
    
    if(vidaBrIzqRepuesto != NULL)
        switch(i){
            case 0:
                vidaBrIzqRepuesto->setSize(sf::Vector2f(vidaGrafica, 5));
                if(vidaGrafica<10){
                        nuevoColor = sf::Color(255, 0, 0);
                        vidaBrIzqRepuesto->setFillColor(nuevoColor);
                }
                else{
                    if(vidaGrafica<30){
                        nuevoColor= sf::Color(255, 255, 51);
                        vidaBrIzqRepuesto->setFillColor(nuevoColor);
                    }
                    else{
                        nuevoColor= sf::Color(170,50,170);
                    vidaBrIzqRepuesto->setFillColor(nuevoColor);
                    }
                } 
                break;
            case 1:
                //std::cout<<vida<<" pieza: 1"<<std::endl;
                vidaBrDerRepuesto->setSize(sf::Vector2f(vidaGrafica,5));
                if(vidaGrafica<10){
                        nuevoColor = sf::Color(255, 0, 0);
                        vidaBrDerRepuesto->setFillColor(nuevoColor);
                }
                else{
                    if(vidaGrafica<30){
                        nuevoColor= sf::Color(255, 255, 51);
                        vidaBrDerRepuesto->setFillColor(nuevoColor);
                    }
                    else{
                        nuevoColor= sf::Color(170,50,170);
                        vidaBrDerRepuesto->setFillColor(nuevoColor);
                    }
                }  

                break;
            case 2:
                //std::cout<<vida<<" pieza: 2"<<std::endl;
                vidaPieIzqRepuesto->setSize(sf::Vector2f(vidaGrafica,5));
                if(vidaGrafica<10){
                        nuevoColor = sf::Color(255, 0, 0);
                        vidaPieIzqRepuesto->setFillColor(nuevoColor);
                }
                else{
                    if(vidaGrafica<30){
                        nuevoColor= sf::Color(255, 255, 51);
                        vidaPieIzqRepuesto->setFillColor(nuevoColor);
                    }
                    else{
                        nuevoColor= sf::Color(170,50,170);
                    vidaPieIzqRepuesto->setFillColor(nuevoColor);
                    }
                }       
                   
                break;
            case 3:
                //std::cout<<vida<<" pieza: 3"<<std::endl;
                vidaPieDerRepuesto->setSize(sf::Vector2f(vidaGrafica,5));
                if(vidaGrafica<10){
                        nuevoColor = sf::Color(255, 0, 0);
                        vidaPieDerRepuesto->setFillColor(nuevoColor);
                }
                else{
                    if(vidaGrafica<30){
                        nuevoColor= sf::Color(255, 255, 51);
                        vidaPieDerRepuesto->setFillColor(nuevoColor);
                    }
                    else{
                        nuevoColor= sf::Color(170,50,170);
                        vidaPieDerRepuesto->setFillColor(nuevoColor);
                    }
                } 
                    
                break;
               // std::cout<<"implosion"<<std::endl;
        }
    
}
void Hud::inicializarVidas(){
    
    vidaBrIzq = new sf::RectangleShape(sf::Vector2f(60, 10));
    vidaBrDer = new sf::RectangleShape(sf::Vector2f(60, 10));
    vidaPieIzq = new sf::RectangleShape(sf::Vector2f(60, 10));
    vidaPieDer = new sf::RectangleShape(sf::Vector2f(60, 10));
    
    vidaBrIzqRepuesto = new sf::RectangleShape(sf::Vector2f(0, 5));
    vidaBrDerRepuesto = new sf::RectangleShape(sf::Vector2f(0, 5));
    vidaPieIzqRepuesto = new sf::RectangleShape(sf::Vector2f(0, 5));
    vidaPieDerRepuesto = new sf::RectangleShape(sf::Vector2f(0, 5));
    
    vidaBrIzq->setFillColor(sf::Color(0, 255, 0));
    vidaBrIzq->setPosition(40,90);
    
    vidaBrDer->setFillColor(sf::Color(0, 255, 0));
    vidaBrDer->setPosition(165,90);
    
    vidaPieIzq->setFillColor(sf::Color(0, 255, 0));
    vidaPieIzq->setPosition(40,120);
    
    vidaPieDer->setFillColor(sf::Color(0, 255, 0));
    vidaPieDer->setPosition(165,120);
    
    vidaBrIzqRepuesto->setFillColor(sf::Color(170, 50, 170));
    vidaBrIzqRepuesto->setPosition(40,90);
    
    vidaBrDerRepuesto->setFillColor(sf::Color(170, 50, 170));
    vidaBrDerRepuesto->setPosition(165,90);
    
    vidaPieIzqRepuesto->setFillColor(sf::Color(170, 50, 170));
    vidaPieIzqRepuesto->setPosition(40,120);
    
    vidaPieDerRepuesto->setFillColor(sf::Color(170, 50, 170));
    vidaPieDerRepuesto->setPosition(165,120);
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
sf::RectangleShape* Hud::getVidaBrIzqRepuesto(){
    return this->vidaBrIzqRepuesto;
}
sf::RectangleShape* Hud::getVidaBrDerRepuesto(){
    return this->vidaBrDerRepuesto;
}
sf::RectangleShape* Hud::getVidaPieIzqRepuesto(){
    return this->vidaPieIzqRepuesto;
}
sf::RectangleShape* Hud::getVidaPieDerRepuesto(){
    return this->vidaPieDerRepuesto;
}
sf::Text* Hud::getTiempo(){
    return mtiempo;
}
sf::Sprite Hud::getPieza(int n){
    sf::Sprite sprite;
    sprite=this->piezas[n];
    return sprite;
}

void Hud::setCantBloques(int bq){
    cantBloques = bq;
}