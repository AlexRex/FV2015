/* 
 * File:   Mapa.cpp
 * Author: Carlos
 * 
 * Created on 30 de marzo de 2015, 16:21
 */

#include "Mapa.h"
#include <stdlib.h>

const int tileDim = 32; // in pixel: 32x32px
    const int windowHeight = 12; // height of the window in number of tiles
    const int windowWidth = 160; // width of the window in number of tiles
    const int windowArea = windowWidth * windowHeight; // total number of tiles in the whole window area
    

Mapa::Mapa() {
    std::cout<<"Se crea el mapa"<<std::endl;
    texture = new sf::Texture();
    if (!texture->loadFromFile("Resources/alien2.png")){
        std::cerr << "Error cargando las texturas";
        exit(0);
    }
    
    texturaMoneda = new sf::Texture();
    if (!texturaMoneda->loadFromFile("Resources/moneda64x32.png")){
        std::cerr << "Error cargando las texturas";
        exit(0);
    }
    
    texturaObjAleatorio = new sf::Texture();
    if (!texturaObjAleatorio->loadFromFile("Resources/barril64x32.png")){
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
            sp.setTextureRect(sf::IntRect(0, tileDim, tileDim, tileDim));
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
            break;
        case 25:
            sp.setTextureRect(sf::IntRect(3*tileDim, tileDim, tileDim, tileDim));
            break;
        case 86:
            sp.setTextureRect(sf::IntRect(tileDim, 4*tileDim, tileDim, tileDim));
            break;
        default:
            sp.setColor(blanco.Transparent);
            break;
    }
    // position of the sprite calculated as offset
    // from the left side of the window
    offsetx = offsetx % windowWidth;

    sp.setOrigin(0,0);
    sp.setPosition(offsetx * tileDim, offsety * tileDim);
    sp.setScale(1,1);
    
    return sp;
}*/



sf::Sprite** Mapa::crearMapa(){
    txml2::XMLDocument map;
    if(!map.LoadFile("mapaLargo.tmx")){
        std::cout<<"Mapa no cargado."<<std::endl;
        return 0;
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
                 case 1:
            sp.setTextureRect(sf::IntRect(0, 0, tileDim, tileDim));
            break;
        case 2: 
            sp.setTextureRect(sf::IntRect(tileDim, 0, tileDim, tileDim));
            break;
        case 3: 
        sp.setTextureRect(sf::IntRect(2*tileDim, 0, tileDim, tileDim));
            break;
        case 4: 
            sp.setTextureRect(sf::IntRect(3*tileDim, 0, tileDim, tileDim));
            break;
        case 13: 
            sp.setTextureRect(sf::IntRect(0, tileDim, tileDim, tileDim));
            break;
        case 14: 
            sp.setTextureRect(sf::IntRect(tileDim,tileDim , tileDim, tileDim));
            break;
        case 15: 
            sp.setTextureRect(sf::IntRect(2*tileDim, tileDim, tileDim, tileDim));
            break;
        case 16: 
            sp.setTextureRect(sf::IntRect(3*tileDim, tileDim, tileDim, tileDim));
            break;
        case 36: 
            sp.setTextureRect(sf::IntRect(0, 2*tileDim, tileDim, tileDim));
            break;
        case 37: 
            sp.setTextureRect(sf::IntRect(tileDim, 2*tileDim, tileDim, tileDim));
            break;
         case 38: 
            sp.setTextureRect(sf::IntRect(2*tileDim, 2*tileDim, tileDim, tileDim));
            break;
        case 39: 
            sp.setTextureRect(sf::IntRect(3*tileDim, 2*tileDim, tileDim, tileDim));
            break;
        case 49: 
            sp.setTextureRect(sf::IntRect(0, 3*tileDim, tileDim, tileDim));
            break;
        case 50: 
            sp.setTextureRect(sf::IntRect(tileDim, 3*tileDim, tileDim, tileDim));
            break;
         case 51: 
            sp.setTextureRect(sf::IntRect(2*tileDim, 3*tileDim, tileDim, tileDim));
            break; 
        case 52: 
            sp.setTextureRect(sf::IntRect(3*tileDim, 3*tileDim, tileDim, tileDim));
            break;
        //bloque de una fila 1*4
        case 7:
            sp.setTextureRect(sf::IntRect(6*tileDim, 0, tileDim, tileDim));
            break;
        case 8:
            sp.setTextureRect(sf::IntRect(7*tileDim, 0, tileDim, tileDim));
            break;
        case 9:
            sp.setTextureRect(sf::IntRect(8*tileDim, 0, tileDim, tileDim));
            break;
        case 10:
            sp.setTextureRect(sf::IntRect(9*tileDim, 0, tileDim, tileDim));
            break;
         //objeto de 3*3 con huecos en medio
        case 19:
            sp.setTextureRect(sf::IntRect(6*tileDim, tileDim, tileDim, tileDim));
            break;
           
         case 20:
            sp.setTextureRect(sf::IntRect(7*tileDim, tileDim, tileDim, tileDim));
            break;
         case 21:
            sp.setTextureRect(sf::IntRect(8*tileDim, tileDim, tileDim, tileDim));
            break;
         case 31:
            sp.setTextureRect(sf::IntRect(6*tileDim, 2*tileDim, tileDim, tileDim));
            break;
        case 32:
            sp.setTextureRect(sf::IntRect(7*tileDim, 2*tileDim, tileDim, tileDim));
            break;
        case 33:
            sp.setTextureRect(sf::IntRect(8*tileDim, 2*tileDim, tileDim, tileDim));
            break;
        case 43:
            sp.setTextureRect(sf::IntRect(6*tileDim, 3*tileDim, tileDim, tileDim));
            break;
         case 44:
            sp.setTextureRect(sf::IntRect(7*tileDim, 3*tileDim, tileDim, tileDim));
            break;
         case 45:
            sp.setTextureRect(sf::IntRect(8*tileDim, 3*tileDim, tileDim, tileDim));
            break;
        //objeto unico 1*1
         case 55:
            sp.setTextureRect(sf::IntRect(6*tileDim, 4*tileDim, tileDim, tileDim));
            break;
        //grieta grande***********
            case 58:
            sp.setTextureRect(sf::IntRect(9*tileDim, 4*tileDim, tileDim, tileDim));
            break;
            case 59:
            sp.setTextureRect(sf::IntRect(10*tileDim, 4*tileDim, tileDim, tileDim));
            break;
            case 46:
            sp.setTextureRect(sf::IntRect(9*tileDim, 3*tileDim, tileDim, tileDim));
            break;
            case 47:
            sp.setTextureRect(sf::IntRect(10*tileDim, 3*tileDim, tileDim, tileDim));
            break;
            //fila1
         case 68:
            sp.setTextureRect(sf::IntRect(7*tileDim, 5*tileDim, tileDim, tileDim));
            break;
         case 69:
            sp.setTextureRect(sf::IntRect(8*tileDim, 5*tileDim, tileDim, tileDim));
            break;
        case 70:
            sp.setTextureRect(sf::IntRect(9*tileDim, 5*tileDim, tileDim, tileDim));
            break;
        case 71:
            sp.setTextureRect(sf::IntRect(10*tileDim, 5*tileDim, tileDim, tileDim));
            break;
        case 72:
            sp.setTextureRect(sf::IntRect(11*tileDim, 5*tileDim, tileDim, tileDim));
            break;
        case 80:
            sp.setTextureRect(sf::IntRect(7*tileDim, 6*tileDim, tileDim, tileDim));
            break;
        case 81:
            sp.setTextureRect(sf::IntRect(8*tileDim, 6*tileDim, tileDim, tileDim));
            break;
        case 82:
            sp.setTextureRect(sf::IntRect(9*tileDim, 6*tileDim, tileDim, tileDim));
            break;
        case 83:
            sp.setTextureRect(sf::IntRect(10*tileDim, 6*tileDim, tileDim, tileDim));
            break;
        case 84:
            sp.setTextureRect(sf::IntRect(11*tileDim, 6*tileDim, tileDim, tileDim));
            break;
            
        case 92:
            sp.setTextureRect(sf::IntRect(7*tileDim, 7*tileDim, tileDim, tileDim));
            break;
        case 93:
            sp.setTextureRect(sf::IntRect(8*tileDim, 7*tileDim, tileDim, tileDim));
            break;
        case 94:
            sp.setTextureRect(sf::IntRect(9*tileDim, 7*tileDim, tileDim, tileDim));
            break;
        case 95:
            sp.setTextureRect(sf::IntRect(10*tileDim, 7*tileDim, tileDim, tileDim));
            break;
        //cosa larga de 1*5
            case 12:
            sp.setTextureRect(sf::IntRect(11*tileDim, 0, tileDim, tileDim));
            break;
            case 24:
            sp.setTextureRect(sf::IntRect(11*tileDim, tileDim, tileDim, tileDim));
            break;
           /* case 36:
            sp.setTextureRect(sf::IntRect(11*tileDim, 2*tileDim, tileDim, tileDim));
            break;*/
            case 48:
            sp.setTextureRect(sf::IntRect(12*tileDim, 2*tileDim, tileDim, tileDim));
            break;
            case 60:
            sp.setTextureRect(sf::IntRect(13*tileDim, 2*tileDim, tileDim, tileDim));
            break;
            //bloque primero color morado
            case 361:
            sp.setTextureRect(sf::IntRect(0, 30*tileDim, tileDim, tileDim));
            break;
            case 362:
            sp.setTextureRect(sf::IntRect(tileDim, 30*tileDim, tileDim, tileDim));
            break;
            case 363:
            sp.setTextureRect(sf::IntRect(2*tileDim, 30*tileDim, tileDim, tileDim));
            break;
            case 364:
            sp.setTextureRect(sf::IntRect(3*tileDim, 30*tileDim, tileDim, tileDim));
            break;
            case 373:
            sp.setTextureRect(sf::IntRect(0, 31*tileDim, tileDim, tileDim));
            break;
            case 374:
            sp.setTextureRect(sf::IntRect(tileDim, 31*tileDim, tileDim, tileDim));
            break;
            case 375:
            sp.setTextureRect(sf::IntRect(2*tileDim, 31*tileDim, tileDim, tileDim));
            break;
            case 376:
            sp.setTextureRect(sf::IntRect(3*tileDim, 31*tileDim, tileDim, tileDim));
            break;
            case 385:
            sp.setTextureRect(sf::IntRect(0, 32*tileDim, tileDim, tileDim));
            break;
            case 386:
            sp.setTextureRect(sf::IntRect(tileDim, 32*tileDim, tileDim, tileDim));
            break;
            case 387:
            sp.setTextureRect(sf::IntRect(2*tileDim, 32*tileDim, tileDim, tileDim));
            break;
            case 388:
            sp.setTextureRect(sf::IntRect(3*tileDim, 32*tileDim, tileDim, tileDim));
            break;
            case 397:
            sp.setTextureRect(sf::IntRect(0, 33*tileDim, tileDim, tileDim));
            break;
            case 398:
            sp.setTextureRect(sf::IntRect(tileDim, 33*tileDim, tileDim, tileDim));
            break;
            case 399:
            sp.setTextureRect(sf::IntRect(2*tileDim, 33*tileDim, tileDim, tileDim));
            break;
            case 400:
            sp.setTextureRect(sf::IntRect(3*tileDim, 33*tileDim, tileDim, tileDim));
            break;
            case 409:
            sp.setTextureRect(sf::IntRect(0, 34*tileDim, tileDim, tileDim));
            break;
            case 410:
            sp.setTextureRect(sf::IntRect(tileDim, 34*tileDim, tileDim, tileDim));
            break;
            case 411:
            sp.setTextureRect(sf::IntRect(2*tileDim, 34*tileDim, tileDim, tileDim));
            break;
            case 412:
            sp.setTextureRect(sf::IntRect(3*tileDim, 34*tileDim, tileDim, tileDim));
            break;
            //cuestas moradas
            case 459:
            sp.setTextureRect(sf::IntRect(2*tileDim, 37*tileDim, tileDim, tileDim));
            break;
            case 460:
            sp.setTextureRect(sf::IntRect(3*tileDim, 37*tileDim, tileDim, tileDim));
            break;
            case 461:
            sp.setTextureRect(sf::IntRect(4*tileDim, 37*tileDim, tileDim, tileDim));
            break;
            case 462:
            sp.setTextureRect(sf::IntRect(5*tileDim, 37*tileDim, tileDim, tileDim));
            break;
            case 447:
            sp.setTextureRect(sf::IntRect(2*tileDim, 36*tileDim, tileDim, tileDim));
            break;
            case 448:
            sp.setTextureRect(sf::IntRect(3*tileDim, 36*tileDim, tileDim, tileDim));
            break;
            case 449:
            sp.setTextureRect(sf::IntRect(4*tileDim, 36*tileDim, tileDim, tileDim));
            break;
            case 450:
            sp.setTextureRect(sf::IntRect(5*tileDim, 36*tileDim, tileDim, tileDim));
            break;
            case 471:
            sp.setTextureRect(sf::IntRect(2*tileDim, 37*tileDim, tileDim, tileDim));
            break;
            case 472:
            sp.setTextureRect(sf::IntRect(3*tileDim, 37*tileDim, tileDim, tileDim));
            break;
            case 473:
            sp.setTextureRect(sf::IntRect(4*tileDim, 37*tileDim, tileDim, tileDim));
            break;
            case 474:
            sp.setTextureRect(sf::IntRect(5*tileDim, 37*tileDim, tileDim, tileDim));
            break;
            
            //mini grieta morada
            case 428:
            sp.setTextureRect(sf::IntRect(7*tileDim, 35*tileDim, tileDim, tileDim));
            break;
            case 440:
            sp.setTextureRect(sf::IntRect(7*tileDim, 36*tileDim, tileDim, tileDim));
            break;
            case 452:
            sp.setTextureRect(sf::IntRect(7*tileDim, 37*tileDim, tileDim, tileDim));
            break;
            case 453:
            sp.setTextureRect(sf::IntRect(8*tileDim, 37*tileDim, tileDim, tileDim));
            break;
            case 432:
            sp.setTextureRect(sf::IntRect(11*tileDim, 35*tileDim, tileDim, tileDim));
            break;
            case 444:
            sp.setTextureRect(sf::IntRect(11*tileDim, 36*tileDim, tileDim, tileDim));
            break;
            
            //piedra marron
            case 241:
            sp.setTextureRect(sf::IntRect(0, 20*tileDim, tileDim, tileDim));
            break;
            case 242:
            sp.setTextureRect(sf::IntRect(tileDim, 20*tileDim, tileDim, tileDim));
            break;
            case 243:
            sp.setTextureRect(sf::IntRect(2*tileDim, 20*tileDim, tileDim, tileDim));
            break;
            case 244:
            sp.setTextureRect(sf::IntRect(3*tileDim, 20*tileDim, tileDim, tileDim));
            break;
            case 247:
            sp.setTextureRect(sf::IntRect(6*tileDim, 20*tileDim, tileDim, tileDim));
            break;
            case 248:
            sp.setTextureRect(sf::IntRect(7*tileDim, 20*tileDim, tileDim, tileDim));
            break;
            case 249:
            sp.setTextureRect(sf::IntRect(8*tileDim, 20*tileDim, tileDim, tileDim));
            break;
            /*case 247:
            sp.setTextureRect(sf::IntRect(9*tileDim, 20*tileDim, tileDim, tileDim));
            break;*/
            //colorines
            case 517:
            sp.setTextureRect(sf::IntRect(0, 43*tileDim, tileDim, tileDim));
            break;
            case 518:
            sp.setTextureRect(sf::IntRect(tileDim, 43*tileDim, tileDim, tileDim));
            break;
             case 519:
            sp.setTextureRect(sf::IntRect(2*tileDim, 43*tileDim, tileDim, tileDim));
            break;
            case 520:
            sp.setTextureRect(sf::IntRect(3*tileDim, 43*tileDim, tileDim, tileDim));
            break;
           //piedras y flores
            case 493:
            sp.setTextureRect(sf::IntRect(0, 41*tileDim, tileDim, tileDim));
            break;
            case 494:
            sp.setTextureRect(sf::IntRect(tileDim, 41*tileDim, tileDim, tileDim));
            break;
            case 495:
            sp.setTextureRect(sf::IntRect(2*tileDim, 41*tileDim, tileDim, tileDim));
            break;
            case 496:
            sp.setTextureRect(sf::IntRect(3*tileDim, 41*tileDim, tileDim, tileDim));
            break;
            case 497:
            sp.setTextureRect(sf::IntRect(4*tileDim, 41*tileDim, tileDim, tileDim));
            break;
            case 498:
            sp.setTextureRect(sf::IntRect(5*tileDim, 41*tileDim, tileDim, tileDim));
            break;
            case 505:
            sp.setTextureRect(sf::IntRect(0, 42*tileDim, tileDim, tileDim));
            break;
            case 506:
            sp.setTextureRect(sf::IntRect(tileDim, 42*tileDim, tileDim, tileDim));
            break;
             case 507:
            sp.setTextureRect(sf::IntRect(2*tileDim, 42*tileDim, tileDim, tileDim));
            break;
             case 508:
            sp.setTextureRect(sf::IntRect(3*tileDim, 42*tileDim, tileDim, tileDim));
            break;
             case 509:
            sp.setTextureRect(sf::IntRect(4*tileDim, 42*tileDim, tileDim, tileDim));
            break;
             case 510:
            sp.setTextureRect(sf::IntRect(5*tileDim, 42*tileDim, tileDim, tileDim));
            break;
             case 511:
            sp.setTextureRect(sf::IntRect(6*tileDim, 42*tileDim, tileDim, tileDim));
            break;
             case 512:
            sp.setTextureRect(sf::IntRect(7*tileDim, 42*tileDim, tileDim, tileDim));
            break;
            case 513:
            sp.setTextureRect(sf::IntRect(8*tileDim, 42*tileDim, tileDim, tileDim));
            break;
            case 514:
            sp.setTextureRect(sf::IntRect(9*tileDim, 42*tileDim, tileDim, tileDim));
            break;
            default:
                //std::cout<<"WHITE"<<std::endl;
                sp.setTextureRect(sf::IntRect(8*tileDim, tileDim, tileDim, tileDim));
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
    if(!map.LoadFile("mapaLargo.tmx")){
        std::cout<<"no carga mapa"<<std::endl;
        return 0;
    }
    std::cout<<"no carga mapa 2"<<std::endl;
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
                //std::cout<<lista[i][j];
                j++;
            }
            else{
                //std::cout<<std::endl;
                j=0;
                i++;
            }
        }
    }
    return lista;
}

sf::Sprite** Mapa::sitiosMonedas(){
    txml2::XMLDocument map;
    if(!map.LoadFile("mapaLargo.tmx")){
        std::cout<<"no carga mapa"<<std::endl;
        return 0;
    }
    
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
            if(tilePos[k]==0 ){
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

sf::Sprite** Mapa::objetosAleatorios(){
    txml2::XMLDocument map;
    if(!map.LoadFile("mapaLargo.tmx")){
        std::cout<<"no carga mapa"<<std::endl;
        return 0;
    }
    
    txml2::XMLElement* xmlNode = map.FirstChildElement("map")
                                ->FirstChildElement("layer");
    while(strcmp(xmlNode->Attribute("name"), "objAleatorios") != 0){
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
    
    
    srand (time(NULL));

    
    sf::Sprite sp(*texturaObjAleatorio);
    
    int k = 0;
    for(int i = 0; i < windowHeight; ++i) {
        scene[i] = new sf::Sprite[windowWidth];
        for (int j = 0; j < windowWidth; ++j) {
            int visible = rand() % 4;
            std::cout<<"visible: "<<visible<<std::endl;
            if(tilePos[k]==0){
                sp.setTextureRect(sf::IntRect(tileDim, 0*tileDim, tileDim, tileDim));
            }
            else if(visible==0){
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