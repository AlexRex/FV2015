/* 
 * File:   Mapa.cpp
 * Author: Carlos
 * 
 * Created on 30 de marzo de 2015, 16:21
 */

#include "Mapa.h"

Mapa::Mapa() {
    std::cout<<"Se crea el mapa"<<std::endl;
    texture = new sf::Texture();
    if (!texture->loadFromFile("Resources/tileset.png")){
        std::cerr << "Error cargando las texturas";
        exit(0);
    }
}

Mapa::Mapa(const Mapa& orig) {
}

Mapa::~Mapa() {
    delete texture;
    std::cout<<"Libero memoria"<<std::endl;
}

/*sf::Sprite* Mapa::createSprite(sf::Sprite* sp, int offsetx, int offsety, int tilePos) {
    sf::Color blanco;
    switch (tilePos){
        case 22:
            sp->setTextureRect(sf::IntRect(0, tileDim, tileDim, tileDim));
            break;
        case 65:
            sp->setTextureRect(sf::IntRect(tileDim, 3*tileDim, tileDim, tileDim));
            std::cout<<"65"<<std::endl;
            break;
        case 23:
            sp->setTextureRect(sf::IntRect(tileDim, tileDim, tileDim, tileDim));
            std::cout<<"23"<<std::endl;
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
}*/



sf::Sprite** Mapa::crearMapa(){
    
    txml2::XMLDocument map;
    if(!map.LoadFile("Resources/prueba2.tmx")){
        std::cout<<"Error cargando textura crearMapa"<<std::endl;
    }
    
    txml2::XMLElement* xmlNode = map.FirstChildElement("map")
                                ->FirstChildElement("layer");
    while(strcmp(xmlNode->Attribute("name"), "Capa de Patrones 1") != 0){
         xmlNode->NextSibling();
    }
    xmlNode = xmlNode->FirstChildElement("data")
                     ->FirstChildElement("tile");
    
    //int**lista = new int*[windowHeight];
    /*for(int i =0; i< windowHeight; i++){
        lista[i]= new int[windowWidth];
    }*/
    int i = 0, j = 0;
    
    sf::Sprite** scene = new sf::Sprite*[windowHeight];
    
    while (xmlNode){
        sf::Sprite sp(*texture);
        std::stringstream s(xmlNode->Attribute("gid"));
        //std::cout<<"ENTRO EN CREAR MAPA"<<std::endl;
        xmlNode = xmlNode->NextSiblingElement();
        //std::cout<<"ENTRO EN CREAR MAPA2"<<std::endl;
        int tilePos;
        s >> tilePos;
        if(i<windowHeight){
            scene[i] = new sf::Sprite[windowWidth];
            //std::cout<<"ENTRO EN CREAR MAPA3"<<std::endl;
            if(j<windowWidth){
                    sf::Color blanco;
                    switch (tilePos){
                        case 22:
                            sp.setTextureRect(sf::IntRect(0, tileDim, tileDim, tileDim));
                            std::cout<<"22"<<std::endl;
                            break;
                        case 65:
                            sp.setTextureRect(sf::IntRect(tileDim, 3*tileDim, tileDim, tileDim));
                            std::cout<<"65"<<std::endl;
                            break;
                        case 23:
                            sp.setTextureRect(sf::IntRect(tileDim, tileDim, tileDim, tileDim));
                            std::cout<<"23"<<std::endl;
                            break;
                        case 24:
                            sp.setTextureRect(sf::IntRect(2*tileDim, tileDim, tileDim, tileDim));
                            std::cout<<"24"<<std::endl;
                            break;
                        case 25:
                            sp.setTextureRect(sf::IntRect(3*tileDim, tileDim, tileDim, tileDim));
                            break;
                        case 86:
                            sp.setTextureRect(sf::IntRect(tileDim, 4*tileDim, tileDim, tileDim));
                            break;
                        default:
                            std::cout<<"PASO EL BLANCO"<<std::endl;
                            sp.setColor(blanco.Transparent);
                            break;
                    }
                    //std::cout<<tilePos;
                    // position of the sprite calculated as offset
                    // from the left side of the window
                    //offsetx = offsetx % windowWidth;
                    
                    sp.setOrigin(0,0);
                    //std::cout<<"x: "<<j * tileDim<<" y: "<<i * tileDim << " contenido: "<< tilePos<<std::endl;
                    sp.setPosition(j * tileDim, i * tileDim);
                    sp.setScale(1,1);
                    scene[i][j] = sp;
                    //i++; -> si se pone, pinta, pero en diagonal, y si se quita, no se pinta nada POR QUÉEEEEEEEEEEEE!??
                    j++;
            }
            else{
                //std::cout<<std::endl;
                j=0;
                i++;
            }
        }
    }
    return scene;
}

int** Mapa::createColisiones(){
    txml2::XMLDocument map;
    if(!map.LoadFile("Resources/prueba2.tmx")){
        std::cout<<"Error cargando textura colisiones"<<std::endl;
    }
    
    txml2::XMLElement* xmlNode = map.FirstChildElement("map")
                                ->FirstChildElement("layer");
    while(strcmp(xmlNode->Attribute("name"), "Colision") != 0){
         xmlNode = xmlNode->NextSiblingElement();
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
    if(!map.LoadFile("Resources/prueba2.tmx")){
        std::cout<<"Error cargando textura monedas"<<std::endl;
    }
    
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