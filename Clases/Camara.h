/* 
 * File:   Camara.h
 * Author: pablo
 *
 * Created on 27 de abril de 2015, 16:48
 */

#ifndef CAMARA_H
#define	CAMARA_H

#include <SFML/Graphics.hpp>
class Camara {
public:
    Camara();
    Camara(const Camara& orig);
    virtual ~Camara();
    void creaCamara(int c1, int c2, int tamx, int tamy);
    sf::View* getView(){return vistaCamara;};
   
    void setPos(sf::Vector2f pos);
private:
    sf::View* vistaCamara;
   // Render*                 render;
   // PlayerPhysics*          fisicasCamara;
    sf::Vector2i posicion;

};

#endif	/* CAMARA_H */

