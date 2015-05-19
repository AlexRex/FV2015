/* 
 * File:   tienda.cpp
 * Author: Carlos
 * 
 * Created on 16 de mayo de 2015, 18:25
 */

#include "Tienda.h"

Tienda::Tienda(float width, float height) {
    if(!fuente.loadFromFile("Resources/PUNK.ttf")){//cargando la fuente
        std::cout<<"No se carga la fuente"<<std::endl;
        //return 0;
    }
    tienda[0].setScale(0.6,0.6);
    tienda[0].setFont(fuente);
    tienda[0].setColor(sf::Color::Blue);
    tienda[0].setString("Pierna reforzada");
    tienda[0].setPosition(sf::Vector2f(width/25, height/(MAX_NUMBER_OF_ITEMS + 0)*1));
    
    tienda[1].setScale(0.6,0.6);
    tienda[1].setFont(fuente);
    tienda[1].setColor(sf::Color::Black);
    tienda[1].setString("Pierna boing");
    tienda[1].setPosition(sf::Vector2f(width/25, height/(MAX_NUMBER_OF_ITEMS - 1)*1.5));
    
    tienda[2].setScale(0.6,0.6);
    tienda[2].setFont(fuente);
    tienda[2].setColor(sf::Color::Black);
    tienda[2].setString("Brazo de midas");
    tienda[2].setPosition(sf::Vector2f(width/25, height/(MAX_NUMBER_OF_ITEMS - 1)*2.1));
    
    tienda[3].setScale(0.6,0.6);
    tienda[3].setFont(fuente);
    tienda[3].setColor(sf::Color::Black);
    tienda[3].setString("Brazo-Pierna");
    tienda[3].setPosition(sf::Vector2f(width/25, height/(MAX_NUMBER_OF_ITEMS -1)*2.8));
    
    tienda[4].setScale(0.6,0.6);
    tienda[4].setFont(fuente);
    tienda[4].setColor(sf::Color::Black);
    tienda[4].setString("Brazo de Chuck Norris");
    tienda[4].setPosition(sf::Vector2f(width/25, height/(MAX_NUMBER_OF_ITEMS - 1)*3.5));
    
    

    selectedItemIndex=0;
    
    if(!texturaFondo.loadFromFile("Resources/tiendabuena.jpg")){
        std::cerr << "Error cargando las texturas";
        exit(0);
    }
        spriteFondo.setTexture(texturaFondo);
}

//Tienda::Tienda(const Tienda& orig) {
//}

Tienda::~Tienda() {
}

sf::Text Tienda::getTienda(int numero){
    if(numero>MAX_NUMBER_OF_ITEMS){
        std::cout<<"Error al obtener la tienda[]"<<std::endl;
    }
    return tienda[numero];
}

sf::Sprite Tienda::getSprite(){
    return spriteFondo;
}

void Tienda::draw(sf::RenderWindow &window){
    window.draw(spriteFondo);
    for(int i=0; i<MAX_NUMBER_OF_ITEMS;i++){
        window.draw(tienda[i]);
    }
}

void Tienda::MoveUp(){
    if(selectedItemIndex - 1 >= 0){
        tienda[selectedItemIndex].setColor(sf::Color::Black);
        selectedItemIndex--;
        tienda[selectedItemIndex].setColor(sf::Color::Blue);
    }
}
void Tienda::MoveDown(){
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS){
        tienda[selectedItemIndex].setColor(sf::Color::Black);
        selectedItemIndex++;
        tienda[selectedItemIndex].setColor(sf::Color::Blue);
    }
}

