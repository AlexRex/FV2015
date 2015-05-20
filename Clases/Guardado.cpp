/* 
 * File:   Guardado.cpp
 * Author: aletormat
 * 
 * Created on 19 de mayo de 2015, 19:41
 */

#include "Guardado.h"



Guardado::Guardado() :
  puntuacion(0)
, monedas(0)
, bDer(0)
, bIzq(0)
, pDer(0)
, pIzq(0)
{
    
    ranking = new int[SIZE];
    
    ranking[5] = 100;
    ranking[4] = 50;
    ranking[3] = 40;
    ranking[2] = 30;
    ranking[1] = 10;
    ranking[0] = 2;
    
}

Guardado::Guardado(const Guardado& orig) {
}

Guardado::~Guardado() {
    delete ranking;
}


void Guardado::guardarPartida(int p, int m,int bD, int bI, int pD, int pI){
    fSave.open("PartidasGuardadas/guardado.txt"); //Crea fichero
    if(fSave.good()){
        fSave << p<<"" << std::endl;
        fSave << m<<"" << std::endl;
        fSave << bD<<"" << std::endl;
        fSave << bI<<"" << std::endl;
        fSave << pD<<"" << std::endl;
        fSave << pI<<"" << std::endl;


        fSave.close();
    }
}

void Guardado::guardarRanking(int punt){
    ranking[0] = punt;
    //std::cout<<"Sin ordenar:"<<std::endl;
    for(int i = 0; i<SIZE; i++){
       // std::cout<<ranking[i]<<std::endl;
    }
    
    std::sort(ranking, ranking+SIZE);
    //std::cout<<"Ordenado:"<<std::endl;

    for(int i = 0; i<SIZE; i++){
      //  std::cout<<ranking[i]<<std::endl;
    }
    
    fSave.open("PartidasGuardadas/ranking.txt"); //Crea fichero
    if(fSave.good()){
        for(int i = 0; i<SIZE; i++){
            fSave<<ranking[i]<<std::endl;
        }  
    }
    fSave.close();
}

bool Guardado::restaurarRanking(){
    char cadena[3128];
    char linea[50][3000];
    std::string texto;
    int a=0;

    fRead.open("PartidasGuardadas/ranking.txt");//Abre fichero
    // Leeremos mediante getline, si lo hiciéramos
    if(fRead.good()){
        a=0;

        while (!fRead.eof()){
            fRead.getline(cadena,3000); //con getline leemos
            std::string lineacadena (cadena); // añadido: convierto array de char a cadena
           // cout<<"veces"<<endl;
            texto +=lineacadena + '\n';  // añado a la cadena texto.
            strcat(linea[a],cadena); //añadido trabajando con cadenas 
            
            std::istringstream(lineacadena) >> ranking[a];
            a++;

        }
       

        //cout << texto;
        fRead.close();
        return true;
    }
    return false;
}

//
bool Guardado::restaurarPartida(){
    char cadena[3128];
    char linea[50][3000];
    std::string texto;
    int a=0;

    fRead.open("PartidasGuardadas/guardado.txt");//Abre fichero
    // Leeremos mediante getline, si lo hiciéramos
    if(fRead.good()){
        a=-1;
        int pase=0;

        while (!fRead.eof()){
            fRead.getline(cadena,3000); //con getline leemos
            a++;
            std::string lineacadena (cadena); // añadido: convierto array de char a cadena
           // cout<<"veces"<<endl;
            texto +=lineacadena + '\n';  // añado a la cadena texto.
            strcat(linea[a],cadena); //añadido trabajando con cadenas 

            if(pase==0){
                std::istringstream ( lineacadena ) >> puntuacion;
              //  std::cout << puntuacion << std::endl;
            }

            if(pase==1){
                std::istringstream ( lineacadena ) >> monedas;
               // std::cout << monedas << std::endl;
            }
            if(pase==2){
                std::istringstream ( lineacadena ) >> bDer;
               // std::cout << bDer << std::endl;
            }
            if(pase==3){
                std::istringstream ( lineacadena ) >> bIzq;
               // std::cout << bIzq << std::endl;
            }
            if(pase==4){
                std::istringstream ( lineacadena ) >> pDer;
              //  std::cout << pDer << std::endl;
            }
            if(pase==5){
                std::istringstream ( lineacadena ) >> pIzq;
              //  std::cout << pIzq << std::endl;
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
        fRead.close();
        return true;
    }
    return false;
}


int* Guardado::getRanking(){
    return ranking;
}