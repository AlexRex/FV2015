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
#define cambioTiled 32

ColisionSuelo::ColisionSuelo() {
    //robot = new Robot();
    //mapa = new Mapa();
    mapaColision = new int*[sizeX];    
    for(int i =0; i< sizeX; i++){
        mapaColision[i]= new int[sizeY];
    }
   posActualMatriz = 0;
   cont =4;
   contY =9;
}

ColisionSuelo::ColisionSuelo(const ColisionSuelo& orig) {
}

ColisionSuelo::~ColisionSuelo() {
}

void ColisionSuelo::recibirRobot(Robot* roby){
    robot = roby;
    posRobotAnteriorX  = robot->getPos().x;
    posRobotAnteriorY  = robot->getPos().y;
    getMapa();
}
void ColisionSuelo::getMapa(){
    mapaColision = mapa->createColisiones();
    posActualMatriz = mapaColision[9][4];
}

//DA ERROR AQUÍ, voy a debuggear
bool ColisionSuelo::comprobarColision(){
    bool hayColision = false;
    //recogemos la posicion del robot

    float posRobotActualX = robot->getPos().x;
    float posRobotActualY = robot->getPos().y;
    //std::cout<<"posRobotActual: "<<posRobotActual<<std::endl;
     //cambiamos de casilla en la matriz
    if(posRobotActualX - posRobotAnteriorX >= cambioTiled){
        posRobotAnteriorX = posRobotActualX;
        cont++;
        posActualMatriz = mapaColision[contY][cont];        
    }
    std::cout<<"posRobotActualY: "<<posRobotActualY<<std::endl;
    if(posRobotActualY - posRobotAnteriorY >= cambioTiled){
        posRobotAnteriorY = posRobotActualY;
        contY++;
        posActualMatriz = mapaColision[contY][cont];        
    }
    if(posActualMatriz != 0){
        hayColision = true;
    }else{
        hayColision = false;
    }
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

