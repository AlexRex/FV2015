/* 
 * File:   ColisionSuelo.h
 * Author: leti
 *
 * Created on 13 de abril de 2015, 13:06
 */

#ifndef COLISIONES_H
#define	COLISIONES_H
#include "Robot.h"
#include "Mapa.h"

class Colisiones {
public:
    Colisiones();
    Colisiones(const Colisiones& orig);
    virtual ~Colisiones();
    void init(Robot*, int, char**);
    void getMapa(int, char**);
    void getMapaMonedas(int, char**);
    bool comprobarColision();
    bool comprobarColisionDcha();
    bool comprobarMoneda(sf::Sprite***spritesMonedas);
    
    void quitarMoneda(sf::Sprite***spriteMonedas, int posX, int posY);
private:
    Robot* robot;
    Mapa* mapa;
    int** mapaColision;
    int** mapaMonedas;
    int posActualMatriz;
    int posActualMatrizDcha;
    int posActualMatrizMonedas;
    int posActualMatrizMonedasCabeza;
    int fila;
    int columna;
    int filaDcha;
    int columnaDcha;
    int filaMoneda;
    int columnaMoneda;
    int posRobotAnteriorX;
    int posRobotAnteriorY;
    
    
    
};

#endif	/* COLISIONSUELO_H */

