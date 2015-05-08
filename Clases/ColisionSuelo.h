/* 
 * File:   ColisionSuelo.h
 * Author: leti
 *
 * Created on 13 de abril de 2015, 13:06
 */

#ifndef COLISIONSUELO_H
#define	COLISIONSUELO_H
#include "Robot.h"
#include "Mapa.h"

class ColisionSuelo {
public:
    ColisionSuelo();
    ColisionSuelo(const ColisionSuelo& orig);
    virtual ~ColisionSuelo();
    void init(Robot*, int, char**);
    void getMapa(int, char**);
    bool comprobarColision();
    bool comprobarColisionDcha();
    
    void creoMatriz();
    void eliminarMatriz(int**a[]);
private:
    Robot* robot;
    Mapa* mapa;
    int** mapaColision;
    int posActualMatriz;
    int fila;
    int columna;
    int posRobotAnteriorX;
    int posRobotAnteriorY;
    
    
    
};

#endif	/* COLISIONSUELO_H */

