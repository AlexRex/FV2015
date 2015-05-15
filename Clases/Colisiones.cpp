/* 
 * File:   ColisionSuelo.cpp
 * Author: leti
 * 
 * Created on 13 de abril de 2015, 13:06
 */

#include "Colisiones.h"
#include <cstdlib>
#include <iostream>

using namespace std;
#define sizeX 29
#define sizeY 19
#define tamTile 32

Colisiones::Colisiones() {
    //robot = new Robot();
    //mapa = new Mapa();
    
   posActualMatriz = 0;
   posActualMatrizMonedas =0;
   fila = 0;
   columna = 0;
}

Colisiones::Colisiones(const Colisiones& orig) {
}

Colisiones::~Colisiones() {
}

void Colisiones::init(Robot* roby, int bloques, char** nombreBloques){
    //Robot nuevo = roby;
    robot = roby;
    //prueba = roby;
    posRobotAnteriorX  = robot->getPos().x;
    posRobotAnteriorY  = robot->getPos().y;
    getMapa(bloques, nombreBloques);
    getMapaMonedas(bloques, nombreBloques);
}


void Colisiones::getMapaMonedas(int bloques, char** nombreBloques){    
    mapaMonedas =  mapa->getColisionesMonedas(bloques, nombreBloques);
    filaMoneda = (robot->getPos().y / tamTile);
    columnaMoneda = (robot->getPos().x / tamTile);
    posActualMatrizMonedas = mapaMonedas[filaMoneda][columnaMoneda];
 
    
}
void Colisiones::getMapa(int bloques, char** nombreBloques){
    
    /* CON ESTO COGES LA MATRIZ DE MONEDAS*/
   // mapa->getColisionesMonedas(bloques, nombreBloques);
    
    mapaColision = mapa->createColisiones(bloques, nombreBloques);
    fila = (robot->getPos().y / tamTile);
    columna = (robot->getPos().x / tamTile);
    posActualMatriz = mapaColision[fila][columna];
    //std::cout<<endl<<endl<<"PosInicial["<<fila<<"]["<<columna<<"]: "<<posActualMatriz<<endl;
    /*for(int j=0; j<20;j++){
        std::cout<<"Fila "<<j<<" : ";
        for(int i=0; i<20; i++){
            std::cout<<mapaColision[j][i];
        }
        std::cout<<endl;
        
    }*/
    
}

bool Colisiones::comprobarColisionDcha(){
    bool hayColisionDcha = false;
    
    int filaAnterior, columnaAnterior;
    filaDcha = (robot->getPos().y / tamTile);
    columnaDcha = (robot->getPos().x / tamTile);
    posActualMatrizDcha = mapaColision[filaDcha+1][columnaDcha+1];
    /*std::cout<<"Pos siguiente: "<<posActualMatriz;
    std::cout<<" Fila: "<<fila;
    std::cout<<" Columna: "<<columna<<std::endl;
    for(int i=0; i<20; i++){
        for(int j=0; j<60; j++){
            std::cout<<mapaColision[i][j];
            if(mapaColision[i][j]==64){
                std::cout<<"i: "<<i;
                std::cout<<" j: "<<j;
            }
        }
        std::cout<<std::endl;
    }*/
    
    //std::cout<<"Fila: "<<fila;
    //std::cout<<" Columna: "<<columna;
    //std::cout<<" Pos actual matriz: "<<mapaColision[fila+1][columna+1]<<std::endl;
    
    if(posActualMatrizDcha != 0 && posActualMatrizDcha<600){
        hayColisionDcha = true;
        if(columnaDcha != columnaAnterior){
            robot->mueveA(columnaDcha*tamTile, robot->getPos().y);
        }

    }else{
        hayColisionDcha = false;
    }
    filaAnterior = filaDcha;
    columnaAnterior = columnaDcha;
    return hayColisionDcha;
    
}


//DA ERROR AQUÍ, voy a debuggear
bool Colisiones::comprobarColision(){
    bool hayColision = false;
    //recogemos la posicion del robot
    int filaAnterior,columnaAnterior;
    
    fila = (robot->getPos().y / tamTile);
    columna = ((robot->getPos().x+16) / tamTile) ;
    posActualMatriz = mapaColision[fila+2][columna-1];
    if(filaAnterior != fila && columnaAnterior != columna){
        //std::cout<<endl<<endl<<"MatrizColision["<<(fila+2)<<"]["<<columna<<"]: "<<posActualMatriz<<endl;
    }
    
    if(posActualMatriz != 0 && posActualMatriz<700){
        hayColision = true;
        //recolocamos al robot justo encima de la casilla para que no se quede entre medias
        if(fila != filaAnterior){
            robot->mueveA(robot->getPos().x ,fila*tamTile);
        }
    }else{
        hayColision = false;
    }
    filaAnterior = fila;
    columnaAnterior = columna;
    return hayColision;


}

bool Colisiones::comprobarMoneda(sf::Sprite*** spritesMonedas){
    
    bool hayMoneda = false;
    
    
    filaMoneda = ((robot->getPos().y-0) / tamTile);
    columnaMoneda = (robot->getPos().x / tamTile);
    posActualMatrizMonedas = mapaMonedas[filaMoneda+1][columnaMoneda+1];
    posActualMatrizMonedasCabeza = mapaMonedas[filaMoneda][columnaMoneda+1];
    
    //std::cout<<"PosX: "<<columnaMoneda<<" PosY: "<<filaMoneda<<std::endl;
    
    
    
    if((posActualMatrizMonedas != 0 || posActualMatrizMonedasCabeza !=0) && posActualMatrizMonedas<600){
        hayMoneda = true;
        if(posActualMatrizMonedas!=0){
            mapaMonedas[filaMoneda+1][columnaMoneda+1] = 0;
            this->quitarMoneda(spritesMonedas, (columnaMoneda+1), (filaMoneda+1));
        }
        else{
            mapaMonedas[filaMoneda][columnaMoneda+1] = 0;
            this->quitarMoneda(spritesMonedas, (columnaMoneda+1), (filaMoneda));
        }


    }else{
        hayMoneda = false;
    }

    return hayMoneda;

}


void Colisiones::quitarMoneda(sf::Sprite*** spriteMonedas, int posX, int posY){
    int nBloque = 0;
    int spriteX = 0;
    int spriteY = 0;
    
    nBloque = posX/29;
    spriteX = (posX-(nBloque*29))-nBloque;
    spriteY = posY;
    
    std::cout<<"nBloques: "<<nBloque<<" spriteX: "<<spriteX<<" spriteY: "<<spriteY<<std::endl;
    
    std::cout<<"posX*tamTile: "<<posX*tamTile<<std::endl;
    
    float posM=spriteMonedas[nBloque][spriteY][spriteX].getPosition().x;
    std::cout<<"PosM: "<<posM<<std::endl;
    spriteMonedas[nBloque][spriteY][spriteX].setTextureRect(sf::IntRect(tamTile, 0*tamTile, tamTile, tamTile));

    
}