/* 
 * File:   Robot.h
 * Author: aletormat
 *
 * Created on 17 de abril de 2015, 9:38
 */

#ifndef ROBOT_H
#define	ROBOT_H

#include "PlayerPhysics.h"
#include "Render.h"
#include "Camara.h"
#include "Hud.h"
#include "Pieza.h"
#include "../Includes/AnimatedSprite.hpp"

class Robot {
public:
    Robot();
    Robot(const Robot& orig);
    virtual ~Robot();
    
    sf::Vector2f getLastPos() const {return playerPhysics->getLastPos();};
    sf::Vector2f getPos() const {return playerPhysics->getPos();};
    sf::Vector2f getVel()  {return playerPhysics->getVel();};
    float getModVel();
    float getModSalto();
    Hud* getHud(){return datos;};
    
    void Init(sf::Texture& tex, float pos_x, float pos_y,  float coeficiente, float vel_x=0.f, float vel_y=0.f);
    void Update(sf::Vector2f vel, sf::Time elapsedTime);
    void Draw(sf::RenderWindow& window, float interpolacion);
    void mueveA(int y, int x);
    void recibirCamara(Camara*);
    void recibirHud(Hud*);
    bool insertarPieza(Pieza* nueva);
    bool insertarBrazo(int);
    bool insertarPierna(int);
    bool actualizaPiezas(sf::Time elapsedTime);
    
    float saltar();
    float getPosSalto(int y, sf::Clock tiempoDesdeSalto, sf::Time elapsedTime);
    float caer(sf::Time tiempoCaida, sf::Time elapsedTime);
    
    Pieza*** getPiezas();
    
    
    
    
    
    
private:
    
    Render*                 render;
    PlayerPhysics*          playerPhysics;
    Camara*                 camara;
    Hud*                    datos;
    
    AnimatedSprite*         animatedSprite;
    Animation*              walkingAnimation;
    Animation*              jumpingAnimation;
    Animation*              fallingAnimation;
    Animation*              currentAnimation;
    
    float                   coeficienteDesintegracion;
    float                   modificadorVel;
    float                   modificadorSalto;
    
    Pieza***                piezas;
    
    void inicializarPiezas();
};

#endif	/* ROBOT_H */
