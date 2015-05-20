/* 
 * File:   Guardado.h
 * Author: aletormat
 *
 * Created on 19 de mayo de 2015, 19:41
 */

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>


#ifndef GUARDADO_H
#define	GUARDADO_H



class Guardado {
public:
    Guardado();
    Guardado(const Guardado& orig);
    virtual ~Guardado();
    
    void guardarPartida(int p, int m,int bD, int bI, int pD, int pI);
    void restaurarPartida();
    
    int getPuntuacion() {return puntuacion;}
    int getMonedas() {return monedas;}
    int getBIzq() {return bIzq;}
    int getBDer() {return bDer;}
    int getPIzq() {return pIzq;}
    int getPDer() {return pDer;}
private:
    
    int puntuacion;
    int monedas;
    int bDer;
    int bIzq;
    int pDer;
    int pIzq;
    
    std::ifstream fRead;
    std::ofstream fSave;
};

#endif	/* GUARDADO_H */

