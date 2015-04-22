/* 
 * File:   Mapa.cpp
 * Author: Carlos
 * 
 * Created on 30 de marzo de 2015, 16:21
 */

#include "Mapa.h"

Mapa::Mapa() {
    std::cout<<"Se crea el mapa"<<std::endl;
}

Mapa::Mapa(const Mapa& orig) {
}

Mapa::~Mapa() {
    std::cout<<"Libero memoria"<<std::endl;
}

sf::Sprite* Mapa::createSprite(sf::Sprite* sp, int offsetx, int offsety, int tilePos) {
    sf::Color blanco;
    switch (tilePos){
        case 22:
            sp->setTextureRect(sf::IntRect(0, tileDim, tileDim, tileDim));
            break;
        case 65:
            sp->setTextureRect(sf::IntRect(tileDim, 3*tileDim, tileDim, tileDim));
            break;
        case 23:
            sp->setTextureRect(sf::IntRect(tileDim, tileDim, tileDim, tileDim));
            break;
        case 24:
            sp->setTextureRect(sf::IntRect(2*tileDim, tileDim, tileDim, tileDim));
            break;
        case 25:
            sp->setTextureRect(sf::IntRect(3*tileDim, tileDim, tileDim, tileDim));
            break;
        case 86:
            sp->setTextureRect(sf::IntRect(tileDim, 4*tileDim, tileDim, tileDim));
            break;
        default:
            sp->setColor(blanco.Transparent);
            break;
    }
    // position of the sprite calculated as offset
    // from the left side of the window
    offsetx = offsetx % windowWidth;

    sp->setOrigin(0,0);
    sp->setPosition(offsetx * tileDim, offsety * tileDim);
    sp->setScale(1,1);
    
    return sp;
}

int** Mapa::crearMapa(){
    txml2::XMLDocument map;
    map.LoadFile("../Resources/prueba2.tmx");
    
    txml2::XMLElement* xmlNode = map.FirstChildElement("map")
                                ->FirstChildElement("layer");
    while(strcmp(xmlNode->Attribute("name"), "Capa de Patrones 1") != 0){
         xmlNode->NextSibling();
    }
    xmlNode = xmlNode->FirstChildElement("data")
                     ->FirstChildElement("tile");
    
    int**lista = new int*[windowHeight];
    for(int i =0; i< windowHeight; i++){
        lista[i]= new int[windowWidth];
    }
    int i = 0, j = 0;
    
    while (xmlNode){
        std::stringstream s(xmlNode->Attribute("gid"));
        xmlNode = xmlNode->NextSiblingElement();
        int tilePos;
        s >> tilePos;
        if(i<windowHeight){
            if(j<windowWidth){
                lista[i][j] = tilePos;
                std::cout<<lista[i][j];
                j++;
            }
            else{
                std::cout<<std::endl;
                j=0;
                i++;
            }
        }
    }
    return lista;
}

int** Mapa::createColisiones(){
    txml2::XMLDocument map;
    map.LoadFile("prueba2.tmx");
    
    txml2::XMLElement* xmlNode = map.FirstChildElement("map")
                                ->FirstChildElement("layer");
    while(strcmp(xmlNode->Attribute("name"), "Colision") != 0){
         xmlNode->NextSibling();
    }
    xmlNode = xmlNode->FirstChildElement("data")
                     ->FirstChildElement("tile");
    
    int**lista = new int*[windowHeight];
    for(int i =0; i< windowHeight; i++){
        lista[i]= new int[windowWidth];
    }
    int i = 0, j = 0;
    
    while (xmlNode){
        std::stringstream s(xmlNode->Attribute("gid"));
        xmlNode = xmlNode->NextSiblingElement();
        int tilePos;
        s >> tilePos;
        if(i<windowHeight){
            if(j<windowWidth){
                lista[i][j] = tilePos;
                std::cout<<lista[i][j];
                j++;
            }
            else{
                std::cout<<std::endl;
                j=0;
                i++;
            }
        }
    }
    return lista;
}

int** Mapa::sitiosMonedas(){
    txml2::XMLDocument map;
    map.LoadFile("prueba2.tmx");
    
    txml2::XMLElement* xmlNode = map.FirstChildElement("map")
                                ->FirstChildElement("layer");
    while(strcmp(xmlNode->Attribute("name"), "Monedas") != 0){
         xmlNode->NextSibling();
    }
    xmlNode = xmlNode->FirstChildElement("data")
                     ->FirstChildElement("tile");
    
    int**lista = new int*[windowHeight];
    for(int i =0; i< windowHeight; i++){
        lista[i]= new int[windowWidth];
    }
    int i = 0, j = 0;
    
    while (xmlNode){
        if(xmlNode->Attribute("gid") != 0)
            std::cout<<"ESTO ES: "<<xmlNode->Attribute("gid")<<std::endl;
        else
            std::cout<<"ESTO ES CERO"<<std::endl;
        std::stringstream s(xmlNode->Attribute("gid"));
        xmlNode = xmlNode->NextSiblingElement();
        int tilePos;
        s >> tilePos;
        if(i<windowHeight){
            if(j<windowWidth){
                lista[i][j] = tilePos;
                std::cout<<lista[i][j];
                j++;
            }
            else{
                std::cout<<std::endl;
                j=0;
                i++;
            }
        }
    }
    return lista;
}