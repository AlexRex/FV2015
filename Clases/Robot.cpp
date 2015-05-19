/* 
 * File:   Robot.cpp
 * Author: aletormat
 * 
 * Created on 17 de abril de 2015, 9:38
 */

#include "Robot.h"


Robot::Robot()
{
   // std::cout<<"Creo robot"<<std::endl;
    
    render = new Render();
    playerPhysics = new PlayerPhysics();
    
    currentAnimation = new Animation();
    walkingAnimation = new Animation();
    animatedSprite = new AnimatedSprite(sf::seconds(0.05), true, false);
    camara = new Camara();
    datos = new Hud();
    
    inicializarPiezas();
    

}

Robot::Robot(const Robot& orig) {
}

Robot::~Robot() {
    std::cout<<"Liberar memoria robot"<<std::endl;
    delete render;
    delete playerPhysics;
    delete animatedSprite;
    delete currentAnimation;
    delete walkingAnimation;
    delete camara;
    delete datos;
    delete piezas;
}


void Robot::Init(sf::Texture &tex, float pos_x, float pos_y,float coeficiente, float vel_x, float vel_y ){
    
    
    render->SetTextura(tex);
    
    walkingAnimation = render->getWalkingAnimation();
    jumpingAnimation = render->getJumpingAnimation();
    fallingAnimation = render->getFallingAnimation();
   // walkingAnimationLeft = render.getWalkingAnimationLeft();
    
    currentAnimation = walkingAnimation;
    animatedSprite->setPosition(pos_x, pos_y);
    
    
    playerPhysics->setPos(pos_x, pos_y);
    playerPhysics->setVel(vel_x, vel_y);
    
    coeficienteDesintegracion = coeficiente;
    
}

void Robot::Update(sf::Vector2f vel, sf::Time elapsedTime){
    playerPhysics->setVel(vel.x, vel.y);
    playerPhysics->Update(elapsedTime);
    
    //Actualizamos las animaciones
    if(vel.x==0 && vel.y==0){
        currentAnimation = walkingAnimation;
    }
    else if(vel.y<0){
        currentAnimation = jumpingAnimation;
    }
    else if(vel.y>0)
        currentAnimation = fallingAnimation;
    else
        currentAnimation = walkingAnimation;
    
    

    
    animatedSprite->play(*currentAnimation);
    animatedSprite->update(elapsedTime);
    
}

void Robot::Draw(sf::RenderWindow& window, float interpolacion){
    render->Draw(window, playerPhysics->getLastPos(), playerPhysics->getPos(), interpolacion, *animatedSprite);
}

bool Robot::insertarPieza(Pieza* nueva){
    bool insertada = false;
    
    if(nueva->getTipo() >= 0 && nueva != NULL && insertada == false){
        if(nueva->getTipo() <=5){
            //Comprobar hueco pierna
            //Comprobar casillas vacias
            if(piezas[0][0] == NULL){
                piezas[0][0]->iniciarPieza(nueva->getTipo());
                insertada = true;
                std::cout<<"cambio pierna 1 vacia"<<std::endl;
            }
            else{
                if(piezas[1][0] == NULL){
                    piezas[1][0] = nueva;
                    insertada = true;
                    std::cout<<"cambio pierna 2 vacia"<<std::endl;
                }
                else{
                    //Comprobar extremidades normales
                    if(piezas[0][0]->getTipo() == 1){
                        /*
                        delete piezas[0][0]; //??????
                         * */
                        delete piezas[0][0];
                        piezas[0][0] = nueva;
                        insertada = true;
                        std::cout<<"cambio pierna 1 normal"<<std::endl;
                    }
                    else{
                        if(piezas[1][0]->getTipo() == 1){
                            /*
                            delete piezas[0][0]; //??????
                             * */
                            delete piezas[1][0];
                            piezas[1][0] = nueva;
                            insertada = true;
                            std::cout<<"cambio pierna 2 normal"<<std::endl;
                        }
                        else{
                            if(piezas[0][0]->getVida() < nueva->getVida()){
                                /*
                                delete piezas[0][0]; //??????
                                 * */
                                delete piezas[0][0];
                                piezas[0][0] = nueva;
                                insertada = true;
                                std::cout<<"cambio pierna 1 vida"<<std::endl;
                            }
                            else{
                                //Compruebas si es igual
                                if(piezas[1][0]->getVida() < nueva->getVida()){
                                    /*
                                    delete piezas[0][0]; //??????
                                     * */
                                    delete piezas[1][0];
                                    piezas[1][0] = nueva;
                                    insertada = true;
                                    std::cout<<"cambio pierna 2 vida"<<std::endl;
                                }
                            }
                        }
                    }
                }
            }
            
            
            
            
        }
        else{
            
            //Comprobar casillas vacias
            if(piezas[2][0] == NULL){
                piezas[2][0] = nueva;
                insertada = true;
                std::cout<<"cambio brazo 1 vacio"<<std::endl;
            }
            else{
                if(piezas[3][0] == NULL){
                    piezas[3][0] = nueva;
                    insertada = true;
                    std::cout<<"cambio brazo 2 vacio"<<std::endl;
                }
                else{
                    //Comprobar extremidades normales
                    if(piezas[2][0]->getTipo() == 6){
                        
                        delete piezas[2][0]; 
                         
                        piezas[2][0] = nueva;
                        insertada = true;
                        std::cout<<"cambio brazo 1 normal"<<std::endl;
                    }
                    else{
                        if(piezas[3][0]->getTipo() == 6){
                            /*
                            delete piezas[0][0]; //??????
                             * */
                            delete piezas[3][0];
                            piezas[3][0] = nueva;
                            insertada = true;
                            std::cout<<"cambio brazo 2 normal"<<std::endl;
                        }
                        else{
                            if(piezas[2][0]->getVida() < nueva->getVida()){
                                /*
                                delete piezas[0][0]; //??????
                                 * */
                                delete piezas[2][0];
                                piezas[2][0] = nueva;
                                insertada = true;
                                std::cout<<"cambio brazo 1 vida"<<std::endl;
                            }
                            else{
                                //Compruebas si es igual
                                if(piezas[3][0]->getVida() < nueva->getVida()){
                                    /*
                                    delete piezas[0][0]; //??????
                                     * */
                                    std::cout<<"cambio brazo vida 2"<<std::endl;
                                    piezas[3][0] = nueva;
                                    delete piezas[3][0];
                                    insertada = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return insertada;
}
bool Robot::insertarBrazo(int n){
    bool insertado = true;
    
    if(piezas[0][0]->getMuerta()){
        piezas[0][0]->iniciarPieza(n);
    }
    else{
        if(piezas[1][0]->getMuerta()){
            piezas[1][0]->iniciarPieza(n);
        }
        else{
            if(piezas[0][1]->getMuerta()){
                piezas[0][1]->iniciarPieza(n);
            }
            else{
                if(piezas[1][1]->getMuerta()){
                    piezas[1][1]->iniciarPieza(n);
                }
                else{
                    return false;
                }
            }
        }
    }
    return insertado;
    
}

bool Robot::insertarPierna(int n){
    bool insertado = true;
    
    if(piezas[2][0]->getMuerta()){
        piezas[2][0]->iniciarPieza(n);
    }
    else{
        if(piezas[3][0]->getMuerta()){
            piezas[3][0]->iniciarPieza(n);
        }
        else{
            if(piezas[2][1]->getMuerta()){
                piezas[2][1]->iniciarPieza(n);
            }
            else{
                if(piezas[3][1]->getMuerta()){
                    piezas[3][1]->iniciarPieza(n);
                }
                else{
                    return false;
                }
            }
        }
    }
    return insertado;
    
}
    

float Robot::getPosSalto(int y, sf::Clock tiempoDesdeSalto, sf::Time elapsedTime){
    return playerPhysics->getPosSalto(y, tiempoDesdeSalto, elapsedTime);
}

void Robot::mueveA(int x, int y){
    playerPhysics->setPos(x, y);
}
float Robot::saltar(){
    return playerPhysics->saltar();
}
float Robot::caer(sf::Time tiempoCaida, sf::Time elapsedTime){
    return playerPhysics->caer(tiempoCaida, elapsedTime);
}
void Robot::recibirCamara (Camara* micam){
    render->recibirCamara(micam);
}
void Robot::recibirHud(Hud* mihud){
    datos = mihud;
    render->recibirHud(mihud);
}
void Robot::inicializarPiezas(){
    
    //almacenaje de las piezas
    //orden: i=1 brazo izquierdo ; i=2 brazo derecho ; i=3 pierna izquierda ; i=4 pierna derecha
    piezas = new Pieza**[4];
    for(int i = 0; i < 4; i++){
        piezas[i] = new Pieza*[2];
        for(int j = 0; j < 2; j++){
            piezas[i][j] = new Pieza();
            piezas[i][j]->setMuerta(false);
            if(j>0){
                piezas[i][j]->setMuerta(true);
            }
        }
    }
    
    piezas[0][0]->iniciarPieza(1);
    piezas[1][0]->iniciarPieza(1);
    piezas[1][0]->darVuelta();
    piezas[2][0]->iniciarPieza(6);
    piezas[3][0]->iniciarPieza(6);
    piezas[3][0]->darVuelta();
}


void Robot::actualizaPiezas(sf::Time elapsedTime){
    
    bool pierdePieza = false;
    int vida=1;
    
  
    //Actualizar vidas
    for(int i = 0; i<4; i++){
        //for(int j=0; j<2; j++){
            if(!piezas[i][0]->getMuerta()){
                vida=piezas[i][0]->actualizaVida(elapsedTime,coeficienteDesintegracion);
                
                if(vida<1 && !pierdePieza){
                    pierdePieza = true;
                }else{
                    if(!piezas[i][0]->getMuerta()){
                        datos->setVidaPieza(vida,i);
                    }
                }
            }
        //}
    }
    if(pierdePieza){
        for(int i = 0; i<4; i++){
            if(piezas[i][0]->getMuerta()){
                if(!piezas[i][1]->getMuerta()){
                    piezas[i][0] = piezas[i][1];
                    piezas[i][1]->setMuerta(true); 
                }   
            }
        }
    }
}
Pieza*** Robot::getPiezas(){
    return piezas; 
}

