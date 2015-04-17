/* 
 * File:   motorFisico.cpp
 * Author: Pablo
 * 
 * Created on 13 de abril de 2015, 13:13
 */

#include "motorFisico.h"
/* No se por que, hay que incluir de nuevo estas librerias que ya estan en el
  main.
 */
#include <math.h>
#include <iostream>
float acel;
float velIniSalto;
motorFisico::motorFisico() {
    //Parametros calculados "a mano" para simular la velocidad de un salto normal
    acel = 686.89; 
    velIniSalto = 608;
}

motorFisico::motorFisico(const motorFisico& orig) {
}

motorFisico::~motorFisico() {
}

/*saltar
 Recibe la posicion inicial del salto y el tiempo transucrrido desde que ha
 * comenzado el salto. Devuelve la altura del objeto correspondiente al tiempo
 * pasado por parametro.
 */
int motorFisico::saltar(int y, float t){
    
    float altF = y; //altura con decimales
    int altI = 0; //altura en pixeles
    altF = y + velIniSalto * t + 0.5 * acel * pow(t,2); //ecuacion de altura
    altI = int(altF);
    /* Esto es lo mismo que los couts de toda la vida. Lo he puesto asi para
     evitar el uso de "using namespace std" que parece ser que es una mala
     practica
     */
    std::cout<<"altF: "<<altF<<std::endl; 
    std::cout<<"altI: "<<altI<<std::endl;
    return altI;
}

