/* 
 * File:   Pieza.cpp
 * Author: leti
 * 
 * Created on 18 de mayo de 2015, 17:13
 */

#include "Pieza.h"

Pieza::Pieza() {
    vida = 0;
    muerta = true;
    
    sprite = new sf::Sprite();
    texture = new sf::Texture();
    
    if(!texture->loadFromFile("Resources/spriteSheetTotal.png")){
        std::cout<<"Error al cargar la textura"<<std::endl;
    }
    
    sprite->setTexture(*texture);
    sprite->setOrigin(0, 0);
    

}

Pieza::Pieza(const Pieza& orig) {
}

Pieza::~Pieza() {
}

int Pieza::getTipo(){
    return tipo;
}

bool Pieza::getMuerta(){
    return muerta;
}

void Pieza::setMuerta(bool aux){
    muerta = aux;
}

void Pieza::darVuelta(){
    sprite->scale(-1, 0);
}

void Pieza::iniciarPieza(int clase){
    if(clase == 10){
        //random
        srand (time(NULL));
        tipo = rand() % 10;
    }
    else{
        tipo = clase;
    }
    sprite = new sf::Sprite();
    switch(tipo){
        case 1:
            //pierna de robot
            //hay que crear aquÃ­ los rectÃ¡ngulos que representan la vida de la pieza
            //calculando los tiempos, la vida deberÃ­a de durar 25 segundos en este caso
            vida = 50;
            sprite->setTextureRect(sf::IntRect(0,0,1,1)); //aquÃ­ hay que ajustar la pieza del jugador
            break;
        case 2:
            //pierna de atleta
            vida = 50;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 3: 
            //pierna de Usain Bolt
            vida = 30;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 4:
            //pierna reforzada
            vida = 75;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 5:
            //pierna-boing
            vida = 30;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 6:
            //brazo de robot
            vida = 50;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 7:
            //brazo de Chuck Norris
            vida = 20;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 8:
            //brazo-pierna
            vida = 75;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 9:
            //brazo de Midas
            vida = 30;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        default:
            //brazo de algarroba
            vida = 30;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
    }
}

