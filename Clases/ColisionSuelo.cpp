/* 
 * File:   ColisionSuelo.cpp
 * Author: leti
 * 
 * Created on 13 de abril de 2015, 13:06
 */

#include "ColisionSuelo.h"
#include <cstdlib>
#include <iostream>

using namespace std;
#define sizeX 29
#define sizeY 20
#define tamTile 32

ColisionSuelo::ColisionSuelo() {
    //robot = new Robot();
    //mapa = new Mapa();
    
   posActualMatriz = 0;
   fila = 0;
   columna = 0;
}

ColisionSuelo::ColisionSuelo(const ColisionSuelo& orig) {
}

ColisionSuelo::~ColisionSuelo() {
}

void ColisionSuelo::init(Robot* roby, int bloques, char** nombreBloques){
    //Robot nuevo = roby;
    robot = roby;
    //prueba = roby;
    posRobotAnteriorX  = robot->getPos().x;
    posRobotAnteriorY  = robot->getPos().y;
    getMapa(bloques, nombreBloques);
}
void ColisionSuelo::getMapa(int bloques, char** nombreBloques){
    
    
    
    
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

bool ColisionSuelo::comprobarColisionDcha(){
    bool hayColisionDcha = false;
    
    int filaAnterior, columnaAnterior;
    
    
    fila = (robot->getPos().y / tamTile);
    columna = (robot->getPos().x / tamTile);
    posActualMatriz = mapaColision[fila+1][columna+1];
    std::cout<<"Pos siguiente: "<<posActualMatriz;
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
    }
    
    //std::cout<<"Fila: "<<fila;
    //std::cout<<" Columna: "<<columna;
    //std::cout<<" Pos actual matriz: "<<mapaColision[fila+1][columna+1]<<std::endl;
    
    if(posActualMatriz != 0 && posActualMatriz<600){
        hayColisionDcha = true;
        if(columna != columnaAnterior){
            robot->mueveA(columna*tamTile, robot->getPos().y);
        }

    }else{
        hayColisionDcha = false;
    }
    filaAnterior = fila;
    columnaAnterior = columna;
    return hayColisionDcha;
    
}


//DA ERROR AQUÍ, voy a debuggear
bool ColisionSuelo::comprobarColision(){
    bool hayColision = false;
    //recogemos la posicion del robot
    int filaAnterior,columnaAnterior;

    
    
    fila = (robot->getPos().y / tamTile);
    columna = ((robot->getPos().x+16) / tamTile) ;
    posActualMatriz = mapaColision[fila+2][columna];
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

void ColisionSuelo::creoMatriz(){
   
    int**a = new int*[sizeX];
    //reserva memoria
    for(int i =0; i< sizeX; i++){
        a[i]= new int[sizeY];
    }
    //Relleno
    for(int i =0; i< sizeX; i++){
        for(int j=0; j < sizeY; j++){
             a[i][j]= 0;
        }
    }
    //haago suelo
    for(int k=0; k < sizeY; k++){
        if(k<6){
             a[3][k]= 1;
        }else{
            a[3][k]= 0;
        }
    }
    
      //imprimo
    for(int i =0; i< sizeX; i++){
        for(int j=0; j < sizeY; j++){
            cout<< a[i][j];
        }
        cout<<endl;
    }

    eliminarMatriz(&a);
    


}

void ColisionSuelo::eliminarMatriz(int**a[]){
      //liberamos memoria
    for(int i =0; i< sizeX; i++){        
        delete[] a[i];
    }
    delete[] a;
    cout<<"se elimina";



}

