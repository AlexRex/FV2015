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
    void getMapaPiezas(int, char**);
    bool comprobarColision();
    bool comprobarColisionDcha();
    bool comprobarMoneda(sf::Sprite***spritesMonedas);
    bool comprobarPieza( sf::Sprite***spritesPiezas );
    
    void quitarMoneda(sf::Sprite***spriteMonedas, int posX, int posY);
    void quitarPieza(sf::Sprite***spritePiezas, int posX, int posY);
private:
    Robot* robot;
    Mapa* mapa;
    int** mapaColision;
    int** mapaMonedas;
    int** mapaPiezas;
    int posActualMatriz;
    int posActualMatrizDcha;
    int posActualMatrizMonedas;
    int posActualMatrizPiezas;
    int posActualMatrizMonedasCabeza;
    int posActualMatrizPiezasCabeza;
    int fila;
    int columna;
    int filaDcha;
    int columnaDcha;
    int filaMoneda;
    int filaPieza;
    int columnaMoneda;
    int columnaPieza;
    int posRobotAnteriorX;
    int posRobotAnteriorY;
    
    
    
};

#endif	/* COLISIONSUELO_H */

