/* 
 * File:   main.cpp
 * Author: Pablo
 *
 * Created on 11 de abril de 2015, 8:40
 */
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "update.h"
#include "render.h"
using namespace std;
//FuncionSaltar2
/*
 * 
 */
#define kUpdateTime 1000/15
#define kRenderTime 1000/60
int main(int argc, char** argv) {
    cout<< "jurrrrrrrrrrrrrrrrr";
    //probandooooooo
    sf::Clock tiempoUp; //Reloj de update
    sf::Clock tiempoRen; //Reloj de render
    sf::Clock segundos; //Reloj para contar segundos
    

    /* Crear objeto tipo update */
    update* miUpdate;
    miUpdate= new update();
    /* Crear objeto tipo render */
    render* miRender;
    miRender= new render();
    
    /*variables para controlar el bucle*/
    int estado=0; 
    int contSegundos=0;
    
    int contUpdate=0; //contador para saber los updates que se han hecho
    int contRender=0; //contador para saber los render que se han hecho
    
    /* variables auxiliares para contar el tiempo entre llamadas */
    int tUpdate = tiempoUp.getElapsedTime().asMilliseconds();
    int tRender = tiempoRen.getElapsedTime().asMilliseconds();
    int tSec = segundos.getElapsedTime().asMilliseconds();
    
    
    while(estado==0){
        /*Si el tiempo transcurrido desde el ultimo update es mayor que el tiempo
        de intervalo entre updates 
         Tiempo transcurrido desde el ultimo update = tiempo del reloj Update - 
         tiempo almacenado en var auxiliar */
        if(tiempoUp.getElapsedTime().asMilliseconds() - tUpdate >= kUpdateTime){    
            
            /* Llamada al método imprimeInfo del objeto miUpdate
             se le pasa direccion de var entero para que cuando se modifique
             en el metodo se modifique tambien aqui*/
            miUpdate->imprimeInfo(&contUpdate); 
            /*Equivaldria a:
              
            cout<<"Update: "<<contUpdate<<endl;
            contUpdate++;
             * */
            tiempoUp.restart();
            tUpdate = tiempoUp.getElapsedTime().asMilliseconds();
        }
        //Igual que update
        if(tiempoRen.getElapsedTime().asMilliseconds()-tRender >= kRenderTime){
           
            miRender->imprimeInfo(&contRender);
            tiempoRen.restart();
            tRender = tiempoRen.getElapsedTime().asMilliseconds();
        }

        if(segundos.getElapsedTime().asMilliseconds()-tSec >= 1000){
            cout<<"Ha pasado un segundo"<<endl;
            segundos.restart();
            tSec = segundos.getElapsedTime().asMilliseconds();
            contSegundos++;
        }
        if(contSegundos > 3){
            estado++;
        }    
    }
    /* Liberamos memoria */
    delete miUpdate;
    delete miRender;
    
    return 0;
}

