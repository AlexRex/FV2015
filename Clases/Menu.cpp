/* 
 * File:   Menu.cpp
 * Author: sandra
 * 
 * Created on 8 de mayo de 2015, 18:09
 */

#include "Menu.h"

Menu::Menu(float width, float height) {
    if(!fuente.loadFromFile("fuentes/PUNK.ttf")){//cargando la fuente
    }
    menu[0].setFont(fuente);
    menu[0].setColor(sf::Color::Blue);
    menu[0].setString("Jugar");
    menu[0].setPosition(sf::Vector2f(width/2.5, height/(MAX_NUMBER_OF_ITEMS + 0)*1));
    
    menu[1].setFont(fuente);
    menu[1].setColor(sf::Color::Black);
    menu[1].setString("Tienda");
    menu[1].setPosition(sf::Vector2f(width/2.5, height/(MAX_NUMBER_OF_ITEMS + 0)*1.5));
    
    menu[2].setFont(fuente);
    menu[2].setColor(sf::Color::Black);
    menu[2].setString("Salir");
    menu[2].setPosition(sf::Vector2f(width/2.5, height/(MAX_NUMBER_OF_ITEMS + 0)*2));

    selectedItemIndex=0;
    
    if(!texturaFondo.loadFromFile("fondo.jpg")){
        std::cerr << "Error cargando las texturas";
        exit(0);
    }
        spriteFondo.setTexture(texturaFondo);
}

//Menu::Menu(const Menu& orig) {
//}

Menu::~Menu() {
}

void Menu::draw(sf::RenderWindow &window){
    window.draw(spriteFondo);
    for(int i=0; i<MAX_NUMBER_OF_ITEMS;i++){
        window.draw(menu[i]);
    }
}

void Menu::MoveUp(){
    if(selectedItemIndex - 1 >= 0){
        menu[selectedItemIndex].setColor(sf::Color::Black);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Blue);
    }
}
void Menu::MoveDown(){
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS){
        menu[selectedItemIndex].setColor(sf::Color::Black);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Blue);
    }
}

