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
    void creaCamara(int c1, int c2, int tamx, int tamy, int cantidBloques);
    void creaCamaraMenu(int c1, int c2, int tamx, int tamy);
    
    
    void setCantBloques(int bq);

    sf::View* getView(){return vistaCamara;};
    sf::View* getMenuView(){return vistaMenu;}
   
    void setPos(sf::Vector2f pos, int status);
private:
    sf::View* vistaCamara;
    sf::View* vistaMenu;
   // Render*                 render;
   // PlayerPhysics*          fisicasCamara;
    sf::Vector2i posicion;
    
    int          cantBloques;

};

#endif	/* CAMARA_H */

