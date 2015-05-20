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
#include <algorithm>


#ifndef GUARDADO_H
#define	GUARDADO_H

#define SIZE 6


class Guardado {
public:
    Guardado();
    Guardado(const Guardado& orig);
    virtual ~Guardado();
    
    void guardarPartida(int p, int m,int bD, int bI, int pD, int pI);
    bool restaurarPartida();
    
    void guardarRanking(int punt);
    
    bool restaurarRanking();
    
    
    int getPuntuacion() {return puntuacion;}
    int getMonedas() {return monedas;}
    int getBIzq() {return bIzq;}
    int getBDer() {return bDer;}
    int getPIzq() {return pIzq;}
    int getPDer() {return pDer;}
    
    int* getRanking();
    
private:

    int puntuacion;
    int monedas;
    int bDer;
    int bIzq;
    int pDer;
    int pIzq;
    
    int* ranking;
    
    std::ifstream fRead;
    std::ofstream fSave;
};

#endif	/* GUARDADO_H */

