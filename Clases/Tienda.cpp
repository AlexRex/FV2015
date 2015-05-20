/* 
 * File:   tienda.cpp
 * Author: Carlos
 * 
 * Created on 16 de mayo de 2015, 18:25
 */

#include "Tienda.h"

Tienda::Tienda(float width, float height) {
    if(!fuentePUNK.loadFromFile("Resources/PUNK.ttf") || !fuenteMonedas.loadFromFile("Resources/OpenSans.ttf")){//cargando la fuente
        std::cout<<"No se carga la fuente"<<std::endl;
        //return 0;
    }
    
    
    monedas = 0;
    
    monedasDisponibles.setScale(1.2, 1.2);
    monedasDisponibles.setFont(fuenteMonedas);
    monedasDisponibles.setColor(sf::Color::Yellow);
    monedasDisponibles.setString(std::to_string(monedas)+ " Monedas");
    monedasDisponibles.setPosition(sf::Vector2f(width-300.f, 10.f));
    //tiendaLabel[5].setScale(0.6,0.6);
    tiendaLabel[0].setFont(fuentePUNK);
    tiendaLabel[0].setColor(sf::Color::White);
    tiendaLabel[0].setString("Salir");
    tiendaLabel[0].setPosition(sf::Vector2f(width/25, height/(MAX_NUMBER_OF_ITEMS + 5)));
    
    tiendaLabel[1].setScale(0.6,0.6);
    tiendaLabel[1].setFont(fuentePUNK);
    tiendaLabel[1].setColor(sf::Color::Blue);
    tiendaLabel[1].setString("Pierna reforzada");
    tiendaLabel[1].setPosition(sf::Vector2f(width/25, height/(MAX_NUMBER_OF_ITEMS + 0)*1.2));
    
    tiendaLabel[2].setScale(0.6,0.6);
    tiendaLabel[2].setFont(fuentePUNK);
    tiendaLabel[2].setColor(sf::Color::White);
    tiendaLabel[2].setString("Pierna boing");
    tiendaLabel[2].setPosition(sf::Vector2f(width/25, height/(MAX_NUMBER_OF_ITEMS - 1)*1.8));
    
    tiendaLabel[3].setScale(0.6,0.6);
    tiendaLabel[3].setFont(fuentePUNK);
    tiendaLabel[3].setColor(sf::Color::White);
    tiendaLabel[3].setString("Brazo de midas");
    tiendaLabel[3].setPosition(sf::Vector2f(width/25, height/(MAX_NUMBER_OF_ITEMS - 1)*2.7));
    
    tiendaLabel[4].setScale(0.6,0.6);
    tiendaLabel[4].setFont(fuentePUNK);
    tiendaLabel[4].setColor(sf::Color::White);
    tiendaLabel[4].setString("Brazo-Pierna");
    tiendaLabel[4].setPosition(sf::Vector2f(width/25, height/(MAX_NUMBER_OF_ITEMS -1)*3.5));
    
    tiendaLabel[5].setScale(0.6,0.6);
    tiendaLabel[5].setFont(fuentePUNK);
    tiendaLabel[5].setColor(sf::Color::White);
    tiendaLabel[5].setString("Brazo de Chuck Norris");
    tiendaLabel[5].setPosition(sf::Vector2f(width/25, height/(MAX_NUMBER_OF_ITEMS - 1)*4.5));
    
  
    
    

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
    return tiendaLabel[numero];
}

sf::Sprite Tienda::getSprite(){
    return spriteFondo;
}

void Tienda::draw(sf::RenderWindow &window){
    window.draw(spriteFondo);
    for(int i=0; i<MAX_NUMBER_OF_ITEMS;i++){
        window.draw(tiendaLabel[i]);
    }
    window.draw(monedasDisponibles);
}

void Tienda::MoveUp(){
    if(selectedItemIndex - 1 >= 0){
        tiendaLabel[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        tiendaLabel[selectedItemIndex].setColor(sf::Color::Blue);
    }
}
void Tienda::MoveDown(){
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS){
        tiendaLabel[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        tiendaLabel[selectedItemIndex].setColor(sf::Color::Blue);
    }
}

bool Tienda::enTienda(int cantidadBloques, float posX){
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


void Tienda::setMonedas(int mon){
    monedas = mon;
    monedasDisponibles.setString(std::to_string(monedas)+" Monedas");
}