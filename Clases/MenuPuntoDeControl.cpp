/* 
 * File:   Menu.cpp
 * Author: sandra
 * 
 * Created on 8 de mayo de 2015, 18:09
 */

#include "MenuPuntoDeControl.h"

MenuPuntoDeControl::MenuPuntoDeControl(float width, float height) {
    if(!fuentePUNK.loadFromFile("Resources/PUNK.ttf") || !fuenteNormal.loadFromFile("Resources/OpenSans.ttf")){//cargando la fuente
    }
    
    puntuacionConseguida.setFont(fuenteNormal);
    puntuacionConseguida.setColor(sf::Color::White);
    puntuacionConseguida.setString("200 Puntos");
    puntuacionConseguida.setPosition(sf::Vector2f(width/10, height/(MAX_NUMBER_OF_ITEMS)*1.2));
    
    monedasConseguidas.setFont(fuenteNormal);
    monedasConseguidas.setColor(sf::Color::White);
    monedasConseguidas.setString("200 Monedas");
    monedasConseguidas.setPosition(sf::Vector2f(width/10, height/(MAX_NUMBER_OF_ITEMS)*1.5));
    
    
    //menu[0].setScale(0.6,0.6);
    menu[0].setFont(fuentePUNK);
    menu[0].setColor(sf::Color::Blue);
    menu[0].setString("Continuar");
    menu[0].setPosition(sf::Vector2f(width/10, height/(MAX_NUMBER_OF_ITEMS)*2));
    
    //menu[1].setScale(0.6,0.6);
    menu[1].setFont(fuentePUNK);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Tienda");
    menu[1].setPosition(sf::Vector2f(width/10, height/(MAX_NUMBER_OF_ITEMS)*2.3));
    
   menu[2].setFont(fuentePUNK);
   menu[2].setColor(sf::Color::White);
   menu[2].setString("Salir");
   menu[2].setPosition(sf::Vector2f(width/10, height/(MAX_NUMBER_OF_ITEMS)*2.6));
    
    

    selectedItemIndex=0;
    
    if(!texturaFondo.loadFromFile("Resources/menuControl.jpg")){
        std::cerr << "Error cargando las texturas";
        exit(0);
    }
        spriteFondo.setTexture(texturaFondo);
}

//Menu::Menu(const Menu& orig) {
//}

MenuPuntoDeControl::~MenuPuntoDeControl() {
}

void MenuPuntoDeControl::draw(sf::RenderWindow &window){
    window.draw(spriteFondo);
    for(int i=0; i<MAX_NUMBER_OF_ITEMS;i++){
        window.draw(menu[i]);
    }
    window.draw(puntuacionConseguida);
    window.draw(monedasConseguidas);
}

bool MenuPuntoDeControl::enPuntoControl(int cantidadBloques, float posX){
    int nBloque = 0;
    int pixelBloque = 928;
    int lastBloque = 0;    
    
    nBloque = posX/(29*32);
    lastBloque = pixelBloque*cantidadBloques-15;    
    
    if(posX>=lastBloque){
        return true;
    }
    
    return false;
}

void MenuPuntoDeControl::MoveUp(){
    if(selectedItemIndex - 1 >= 0){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Blue);
    }
}
void MenuPuntoDeControl::MoveDown(){
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS){
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Blue);
    }
}

void MenuPuntoDeControl::setMonedas(int mon){
    monedas = mon;
    monedasConseguidas.setString(std::to_string(monedas)+" Monedas");
}

void MenuPuntoDeControl::setPuntuacion(int punt){
    puntuacion = punt;
}