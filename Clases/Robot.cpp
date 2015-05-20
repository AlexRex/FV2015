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
    
    modificadorSalto = 1;
    modificadorVel = 0;
    
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
                datos->setVidaRepuesto(0,piezas[0][1]->getVida());
            }
            else{
                if(piezas[1][1]->getMuerta()){
                    piezas[1][1]->iniciarPieza(n);
                    datos->setVidaRepuesto(1,piezas[1][1]->getVida());
                }
                else{
                    return false;
                }
            }
        }
    }
    std::cout<<"Tipo Brazo 1:"<<piezas[0][0]->getTipo()<<std::endl;
    std::cout<<"Tipo Brazo 2:"<<piezas[1][0]->getTipo()<<std::endl;
    return insertado;
    
}

bool Robot::insertarPierna(int n){
    bool insertado = true;
    std::cout<<"Tipo inicial:  "<<n<<std::endl;
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
                std::cout<<"Vida barra: "<<piezas[2][1]->getVida()<<std::endl;
                datos->setVidaRepuesto(2,50);
            }
            else{
                if(piezas[3][1]->getMuerta()){
                    piezas[3][1]->iniciarPieza(n);
                    std::cout<<"Vida barra: "<<piezas[3][1]->getVida()<<std::endl;
                    datos->setVidaRepuesto(3,piezas[3][1]->getVida());
                }
                else{
                    return false;
                }
            }
        }
    }
    std::cout<<"Tipo Pierna 1:"<<piezas[2][0]->getTipo()<<std::endl;
    std::cout<<"Tipo Pierna 2:"<<piezas[3][0]->getTipo()<<std::endl;
    return insertado;
    
}
    

float Robot::getPosSalto(int y, sf::Clock tiempoDesdeSalto, sf::Time elapsedTime){
    return playerPhysics->getPosSalto(y, tiempoDesdeSalto, elapsedTime);
}

void Robot::mueveA(int x, int y){
    playerPhysics->setPos(x, y);
}
float Robot::saltar(){
    this->getModSalto();
    return playerPhysics->saltar(modificadorSalto);
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


bool Robot::actualizaPiezas(sf::Time elapsedTime){
    
    bool pierdePieza = false;
    int vida=1;
    bool muere=false;
    bool tengoBrazoPierna = false;
    bool meFaltaPierna = false;
    int posBrazoPierna;
    int posPiernaRota;
    
  
    //Actualizar vidas
    for(int i = 0; i<4; i++){
        //for(int j=0; j<2; j++){
            if(!piezas[i][0]->getMuerta()){
                vida=piezas[i][0]->actualizaVida(elapsedTime,coeficienteDesintegracion);
                //datos->setVidaPieza(i,vida);
                //datos->setVidaRepuesto(i,vida);
                
                if(vida<1 && !pierdePieza){
                    pierdePieza = true;
                }else{
                    if(!piezas[i][0]->getMuerta()){
                        datos->setVidaPieza(vida,i);
                        if(i<2){
                            if(piezas[i][0]->getTipo() == 8 && !tengoBrazoPierna){
                                tengoBrazoPierna = true;
                                posBrazoPierna = i;
                            }
                        }
                    }
                    if(!piezas[i][1]->getMuerta()){
                        datos->setVidaRepuesto(i,50);
                    }
                }
            }
            if(i>1){
                if(piezas[i][0]->getMuerta()){
                    meFaltaPierna = true;
                    posPiernaRota = i;
                }
            }
        //}
    }
    if(pierdePieza){
        for(int i = 0; i<4; i++){
            if(piezas[i][0]->getMuerta()){
                if(!piezas[i][1]->getMuerta()){
                    
                    *piezas[i][0] = *piezas[i][1]; //Copia los valores de la pieza de repuesto
                    
                    piezas[i][1]->setVida(1);
                    datos->setVidaRepuesto(i,0);
                    piezas[i][1]->setMuerta(true);
                    std::cout<<piezas[i][0]->getMuerta()<<std::endl;
                    std::cout<<piezas[i][1]->getMuerta()<<std::endl;
                }
                if(i>1){
                    
                    if(piezas[2][0]->getMuerta() && piezas[3][0]->getMuerta()){
                        //Muere
                        muere=true;
                    }
                }
            }
            
        }

    }
    if(tengoBrazoPierna && meFaltaPierna){
         //sustituir pierna rota por brazo-pierna
        int vidaBrazo= piezas[posBrazoPierna][0]->getVida();
        piezas[posPiernaRota][0]->iniciarPieza(1);
        piezas[posPiernaRota][0]->setVida(vidaBrazo);
        
        datos->setVidaRepuesto(posPiernaRota,vidaBrazo);
        datos->setVidaRepuesto(posBrazoPierna,1);
        piezas[posBrazoPierna][0]->setVida(1);
        muere=false;
    } 
    return muere;
}
Pieza*** Robot::getPiezas(){
    return piezas; 
}
float Robot::getModVel(){
    float modPieza = 1;
    float modTotal = 1;
    for(int i = 0; i<4; i++){
        modPieza=piezas[i][0]->getVelocidad();
        if(modPieza<1)
            modTotal -= .25;
        else
            modTotal += modPieza-1;
    }
    modificadorVel=modTotal;
    return modTotal;
    
}
float Robot::getModSalto(){
    float modPieza = 1;
    float modTotal = 1;
    for(int i = 0; i<4; i++){
        modPieza=piezas[i][0]->getSalto();
        std::cout<<"Mod Salto Pieza: "<<piezas[i][0]->getSalto()<<std::endl;
        modTotal += modPieza-1;
        std::cout<<"Modificador salto: "<<modTotal<<std::endl;
        std::cout<<"Modificador pieza: "<<modPieza<<std::endl;
    }
    modificadorSalto=modTotal;
    std::cout<<"Modificador salto: "<<modificadorSalto<<std::endl;
    return modTotal;
}
