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
#define sizeX 20
#define sizeY 20
#define tamTile 32

ColisionSuelo::ColisionSuelo() {
    //robot = new Robot();
    //mapa = new Mapa();
    mapaColision = new int*[sizeX];    
    for(int i =0; i< sizeX; i++){
        mapaColision[i]= new int[sizeY];
    }
   posActualMatriz = 0;
   fila = 0;
   columna = 0;
}

ColisionSuelo::ColisionSuelo(const ColisionSuelo& orig) {
}

ColisionSuelo::~ColisionSuelo() {
}

void ColisionSuelo::recibirRobot(Robot* roby){
    //Robot nuevo = roby;
    robot = roby;
    //prueba = roby;
    posRobotAnteriorX  = robot->getPos().x;
    posRobotAnteriorY  = robot->getPos().y;
    getMapa();
}
void ColisionSuelo::getMapa(){
    mapaColision = mapa->createColisiones();
    fila = (robot->getPos().y / tamTile);
    columna = (robot->getPos().x / tamTile);
    posActualMatriz = mapaColision[fila][columna];
    std::cout<<endl<<endl<<"PosInicial["<<fila<<"]["<<columna<<"]: "<<posActualMatriz<<endl;
    for(int j=0; j<20;j++){
        std::cout<<"Fila "<<j<<" : ";
        for(int i=0; i<20; i++){
            std::cout<<mapaColision[j][i];
        }
        std::cout<<endl;
        
    }
    
}

//DA ERROR AQUÍ, voy a debuggear
bool ColisionSuelo::comprobarColision(){
    bool hayColision = false;
    //recogemos la posicion del robot
    int filaAnterior,columnaAnterior;
    filaAnterior=0;
    columnaAnterior=0;
    float posRobotActualX = robot->getPos().x;
    float posRobotActualY = robot->getPos().y;
    //std::cout<<"posRobotActual: "<<posRobotActual<<std::endl;
     //cambiamos de casilla en la matriz
    fila = (robot->getPos().y / tamTile);
    columna = (robot->getPos().x / tamTile) ;
    posActualMatriz = mapaColision[fila+1][columna];
    if(filaAnterior != fila || columnaAnterior != columna){
        std::cout<<endl<<endl<<"MatrizColision["<<(fila+1)<<"]["<<columna<<"]: "<<posActualMatriz<<endl;
    }
    
    /*
    if(posRobotActualX - posRobotAnteriorX >= tamTile){
        posRobotAnteriorX = posRobotActualX;
        //cambiamos de columna
        contY++;
        posActualMatriz = mapaColision[cont][contY];
        std::cout<<endl<<endl<<"Voy derecha["<<cont<<"]["<<contY<<"]: "<<posActualMatriz<<endl;
    }
    if(posRobotAnteriorX- posRobotActualX >= tamTile){
        posRobotAnteriorX = posRobotActualX;
        contY--;
        posActualMatriz = mapaColision[contY][cont];
        std::cout<<endl<<endl<<"Voy izquierda["<<cont<<"]["<<contY<<"]: "<<posActualMatriz<<endl;
    }
    //std::cout<<"posRobotActualY: "<<posRobotActualY<<std::endl;
    
        if( posRobotActualY - posRobotAnteriorY>= cambioTiled){//baja
            posRobotAnteriorY = posRobotActualY;
            cont++;
            posActualMatriz = mapaColision[cont][contY];
            std::cout<<endl<<endl<<"Voy abajo["<<cont<<"]["<<contY<<"]: "<<posActualMatriz<<endl;
        }
   

        if(posRobotAnteriorY - posRobotActualY  >= cambioTiled){//sube
            posRobotAnteriorY = posRobotActualY;
            cont--;
            posActualMatriz = mapaColision[cont][contY];
            std::cout<<endl<<endl<<"Voy arriba["<<cont<<"]["<<contY<<"]: "<<posActualMatriz<<endl;
        }
     */
    
    if(posActualMatriz != 0){
        hayColision = true;
        //recolocamos al robot justo encima de la casilla para que no se quede entre medias
        if(fila != filaAnterior){
            robot->mueveA(robot->getPos().x,fila*tamTile);
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

