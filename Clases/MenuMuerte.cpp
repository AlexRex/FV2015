/* 
 * File:   Menu.cpp
 * Author: sandra
 * 
 * Created on 8 de mayo de 2015, 18:09
 */

#include "MenuMuerte.h"

MenuMuerte::MenuMuerte(float width, float height) {
    if(!fuente.loadFromFile("Resources/PUNK.ttf") || !fuenteNormal.loadFromFile("Resources/OpenSans.ttf")){//cargando la fuente
    }
    
    puntuacionConseguida.setFont(fuenteNormal);
    puntuacionConseguida.setColor(sf::Color::White);
    puntuacionConseguida.setString("200 Puntos");
    puntuacionConseguida.setPosition(sf::Vector2f(width/10, height/(MAX_NUMBER_OF_ITEMS)*1.5));
    
    monedasConseguidas.setFont(fuenteNormal);
    monedasConseguidas.setColor(sf::Color::White);
    monedasConseguidas.setString("200 Monedas");
    monedasConseguidas.setPosition(sf::Vector2f(width/10, height/(MAX_NUMBER_OF_ITEMS)*1.6));
    
    //menu[0].setScale(0.6,0.6);
    menu[0].setFont(fuente);
    menu[0].setColor(sf::Color::Blue);
    menu[0].setString("Reintentar");
    menu[0].setPosition(sf::Vector2f(width/10, height/(MAX_NUMBER_OF_ITEMS)*1));
    
    //menu[1].setScale(0.6,0.6);
    menu[1].setFont(fuente);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Salir");
    menu[1].setPosition(sf::Vector2f(width/10, height/(MAX_NUMBER_OF_ITEMS)*1.2));
    
   
    
    for(int i = 0; i<5; i++){
        rankingLabel[i].setFont(fuenteNormal);
        rankingLabel[i].setColor(sf::Color::White);
        rankingLabel[i].setString("rank");
        rankingLabel[i].setPosition(sf::Vector2f(width-305.f, 500-(60.f)*i));
    }

    selectedItemIndex=0;
    
    if(!texturaFondo.loadFromFile("Resources/menuMuerte.jpg")){
        std::cerr << "Error cargando las texturas";
        exit(0);
    }
        spriteFondo.setTexture(texturaFondo);
}

//Menu::Menu(const Menu& orig) {
//}

MenuMuerte::~MenuMuerte() {
}

void MenuMuerte::draw(sf::RenderWindow &window){
    window.draw(spriteFondo);
    for(int i=0; i<MAX_NUMBER_OF_ITEMS;i++){
        window.draw(menu[i]);
    }
    for(int i = 0; i<5; i++){
        window.draw(rankingLabel[i]);
    }
    window.draw(puntuacionConseguida);
    window.draw(monedasConseguidas);
}

void MenuMuerte::MoveUp(){
    if(selectedItemIndex - 1 >= 0){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Blue);
    }
}
void MenuMuerte::MoveDown(){
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Blue);
    }
}

void MenuMuerte::setMonedas(int mon){
    monedas = mon;
    monedasConseguidas.setString(std::to_string(monedas)+" Monedas");
}

void MenuMuerte::setPuntuacion(int punt){
    puntuacion = punt;
    puntuacionConseguida.setString(std::to_string(puntuacion)+" Puntos");

}

void MenuMuerte::setRanking(int *rank){
    ranking = rank;
    for(int i = 0;i<5; i++){
        rankingLabel[i].setString(std::to_string(ranking[i+1])+" Puntos");
    }
}