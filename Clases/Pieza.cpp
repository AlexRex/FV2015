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
    tipo = 0;
    debilidad = 1;
    velocidad = 1;
    salto = 1;
    
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
    delete sprite;
    delete texture;
}

int Pieza::getTipo(){
    return tipo;
}

bool Pieza::getMuerta(){
    return muerta;
}

void Pieza::setMuerta(bool aux){
    muerta = aux;
    if(muerta)
        tipo = -1;
}

void Pieza::darVuelta(){
    sprite->scale(-1, 0);
}

int Pieza::iniciarPieza(int clase){
    if(clase == -1){
        //random
        srand (time(NULL));
        tipo = rand() % 10 + 1;
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
            vida = 500;
            debilidad =1;
            sprite->setTextureRect(sf::IntRect(0,0,1,1)); //aquÃ­ hay que ajustar la pieza del jugador
            std::cout<<"clase: "<<clase<<std::endl;
            break;
        case 2:
            //pierna de atleta
            vida = 500;
            debilidad =1;
            velocidad = 1.2;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 3: 
            //pierna de Usain Bolt
            vida = 500;
            debilidad = 0.7;
            velocidad = 1.5;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 4:
            //pierna reforzada
            vida = 500;
            debilidad = 1.3;
            velocidad = 0.7;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 5:
            //pierna-boing
            vida = 500;
            debilidad = 0.7;
            salto = 1.5;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 6:
            //brazo de robot
            vida = 500;
            debilidad =1;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 7:
            //brazo de Chuck Norris
            vida = 500;
            debilidad = 1.5;
            velocidad = 1.2;
            salto = 1.2;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 8:
            //brazo-pierna
            vida = 500;
            debilidad = 0.7;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        case 9:
            //brazo de Midas
            vida = 500;
            debilidad = 1.3;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
        default:
            //brazo de algarroba
            tipo = 10;
            vida = 500;
            debilidad = 1.3;
            sprite->setTextureRect(sf::IntRect(0,0,1,1));
            break;
    }
    muerta = false;
    return tipo;
}
int Pieza::actualizaVida(sf::Time elapsedTime, float coeficiente){
    vida -= 1*(elapsedTime.asSeconds()*coeficiente*debilidad);
    if(vida <= 0 ){
        muerta=true;
    }
    return vida;
}
int Pieza::getVida(){
    return vida;
}
float Pieza::getVelocidad(){
    return velocidad;
}
float Pieza::getSalto(){
    return salto;
}
void Pieza::setVida(int nuevaVida){
    vida=nuevaVida;
}