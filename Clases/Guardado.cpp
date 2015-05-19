/* 
 * File:   Guardado.cpp
 * Author: aletormat
 * 
 * Created on 19 de mayo de 2015, 19:41
 */

#include "Guardado.h"

Guardado::Guardado() {
}

Guardado::Guardado(const Guardado& orig) {
}

Guardado::~Guardado() {
}


void Guardado::guardarPartida(int p, int m,int bD, int bI, int pD, int pI){
    fs.open("PartidasGuardadas/guardado.txt"); //Crea fichero

    fs << p<<"" << std::endl;
    fs << m<<"" << std::endl;
    fs << bD<<"" << std::endl;
    fs << bI<<"" << std::endl;
    fs << pD<<"" << std::endl;
    fs << pI<<"" << std::endl;
    
    
    fs.close();
}


void Guardado::restaurarPartida(){
    char cadena[3128];
    char linea[50][3000];
    std::string texto;
    std::string lineacadena;
    int a=0;

    fe.open("PartidasGuardadas/guardado.txt");//Abre fichero
    // Leeremos mediante getline, si lo hiciéramos
    std::cout<<"e"<<std::endl;
    a=-1;
    int pase=0;

    while (!fe.eof()){
        fe.getline(cadena,3000); //con getline leemos
        a++;
        std::string lineacadena (cadena); // añadido: convierto array de char a cadena
       // cout<<"veces"<<endl;
        texto +=lineacadena + '\n';  // añado a la cadena texto.
        strcat(linea[a],cadena); //añadido trabajando con cadenas 

        if(pase==0){
            std::istringstream ( lineacadena ) >> puntuacion;
            std::cout << puntuacion << std::endl;
        }

        if(pase==1){
            std::istringstream ( lineacadena ) >> monedas;
            std::cout << monedas << std::endl;
        }
        if(pase==2){
            std::istringstream ( lineacadena ) >> bDer;
            std::cout << bDer << std::endl;
        }
        if(pase==3){
            std::istringstream ( lineacadena ) >> bIzq;
            std::cout << bIzq << std::endl;
        }
        if(pase==4){
            std::istringstream ( lineacadena ) >> pDer;
            std::cout << pDer << std::endl;
        }
        if(pase==5){
            std::istringstream ( lineacadena ) >> pIzq;
            std::cout << pIzq << std::endl;
        }
        pase=pase+1;
        //cout<<pase<<endl;
    }
    /*
    for(b=0;b<=a;b++){//muestra lo que ha
    cout << linea[b];
    cout << "\n";
    }*/

    //cout << texto;
    fe.close();
}