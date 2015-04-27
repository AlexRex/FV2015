/* 
 * File:   Mapa.cpp
 * Author: Carlos
 * 
 * Created on 30 de marzo de 2015, 16:21
 */

#include "Mapa.h"

const int tileDim = 32; // in pixel: 32x32px
    const int windowHeight = 20; // height of the window in number of tiles
    const int windowWidth = 30; // width of the window in number of tiles
    const int windowArea = windowWidth * windowHeight; // total number of tiles in the whole window area
    

Mapa::Mapa() {
    std::cout<<"Se crea el mapa"<<std::endl;
    texture = new sf::Texture();
    if (!texture->loadFromFile("Resources/tileset.png")){
        std::cerr << "Error cargando las texturas";
        exit(0);
    }
    
    texturaMoneda = new sf::Texture();
    if (!texturaMoneda->loadFromFile("Resources/moneda64x32.png")){
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
    map.LoadFile("prueba2.tmx");
    
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
    //int i = 0, j = 0;
    
    sf::Sprite** scene = new sf::Sprite*[windowHeight];
    
    std::vector<int> tilePos;
    while (xmlNode) {
        std::stringstream s(xmlNode->Attribute("gid"));
        xmlNode = xmlNode->NextSiblingElement();
        int tp;
        s >> tp;
        tilePos.push_back(tp);
    }
    
    sf::Sprite sp(*texture);
        
    int k = 0;
    for(int i = 0; i < windowHeight; ++i) {
        scene[i] = new sf::Sprite[windowWidth];
        for (int j = 0; j < windowWidth; ++j) {
            sf::Color blanco;
            switch (tilePos[k]){
                case 22:
                    sp.setTextureRect(sf::IntRect(0, tileDim, tileDim, tileDim));
                    //std::cout<<"22"<<std::endl;
                    break;
                case 65:
                    sp.setTextureRect(sf::IntRect(tileDim, 3*tileDim, tileDim, tileDim));
                    //std::cout<<"65"<<std::endl;
                    break;
                case 23:
                    sp.setTextureRect(sf::IntRect(tileDim, tileDim, tileDim, tileDim));
                    //std::cout<<"23"<<std::endl;
                    break;
                case 24:
                    sp.setTextureRect(sf::IntRect(2*tileDim, tileDim, tileDim, tileDim));
                    //std::cout<<"24"<<std::endl;
                    break;
                case 25:
                    sp.setTextureRect(sf::IntRect(3*tileDim, tileDim, tileDim, tileDim));
                    //std::cout<<"25"<<std::endl;
                    break;
                case 86:
                    sp.setTextureRect(sf::IntRect(tileDim, 4*tileDim, tileDim, tileDim));
                    //std::cout<<"86"<<std::endl;
                    break;
                default:
                    //std::cout<<"WHITE"<<std::endl;
                    sp.setTextureRect(sf::IntRect(11*tileDim, tileDim, tileDim, tileDim));
                    //sp.setColor(sf::Color::Transparent);
                    break;
            }
            //std::cout << "tilepos[" << k << "] = " << tilePos[k] << std::endl;
            ++k;
            
            sp.setOrigin(0,0);
            sp.setPosition(j * tileDim, i * tileDim);
            sp.setScale(1,1);
            scene[i][j] = sp;
        }
    }
   
    return scene;
}

int** Mapa::createColisiones(){
    txml2::XMLDocument map;
    map.LoadFile("prueba2.tmx");
    
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
       // std::cout<<"I: "<<i;
       // std::cout<<" J: "<<j<<std::endl;

        if(i<windowHeight){
            if(j<windowWidth-1){
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

sf::Sprite** Mapa::sitiosMonedas(){
    txml2::XMLDocument map;
    map.LoadFile("prueba2.tmx");
    
    txml2::XMLElement* xmlNode = map.FirstChildElement("map")
                                ->FirstChildElement("layer");
    while(strcmp(xmlNode->Attribute("name"), "Monedas") != 0){
          xmlNode = xmlNode->NextSiblingElement();
    }
    xmlNode = xmlNode->FirstChildElement("data")
                     ->FirstChildElement("tile");
    
   
    
    sf::Sprite** scene = new sf::Sprite*[windowHeight];
    
    std::vector<int> tilePos;
    while (xmlNode) {
        std::stringstream s(xmlNode->Attribute("gid"));
        xmlNode = xmlNode->NextSiblingElement();
        int tp;
        s >> tp;
        tilePos.push_back(tp);
    }
    
    sf::Sprite sp(*texturaMoneda);
        
    int k = 0;
    for(int i = 0; i < windowHeight; ++i) {
        scene[i] = new sf::Sprite[windowWidth];
        for (int j = 0; j < windowWidth; ++j) {
            if(tilePos[k]==0){
                sp.setTextureRect(sf::IntRect(tileDim, 0*tileDim, tileDim, tileDim));
            }
            else{
                sp.setTextureRect(sf::IntRect(0*tileDim, 0*tileDim, tileDim, tileDim));
            }

            ++k;
            
            sp.setOrigin(0,0);
            sp.setPosition(j * tileDim, i * tileDim);
            sp.setScale(1,1);
            scene[i][j] = sp;
        }
    }
   
    return scene;
}
