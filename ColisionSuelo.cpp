/* 
 * File:   ColisionSuelo.cpp
 * Author: leti
 * 
 * Created on 13 de abril de 2015, 13:06
 */

#include "ColisionSuelo.h"
#include <cstdlib>
#include <iostream>

using namespace std;
#define sizeX 4
#define sizeY 10

ColisionSuelo::ColisionSuelo() {
}

ColisionSuelo::ColisionSuelo(const ColisionSuelo& orig) {
}

ColisionSuelo::~ColisionSuelo() {
}

void ColisionSuelo::creoMatriz(){
   
    int**a = new int*[sizeX];
    //reserva memoria
    for(int i =0; i< sizeX; i++){
        a[i]= new int[sizeY];
    }
    //Relleno
    for(int i =0; i< sizeX; i++){
        for(int j=0; j < sizeY; j++){
             a[i][j]= 0;
        }
    }
    //haago suelo
    for(int k=0; k < sizeY; k++){
        if(k<6){
             a[3][k]= 1;
        }else{
            a[3][k]= 0;
        }
    }
    
      //imprimo
    for(int i =0; i< sizeX; i++){
        for(int j=0; j < sizeY; j++){
            cout<< a[i][j];
        }
        cout<<endl;
    }

    eliminarMatriz(&a);
    


}

void ColisionSuelo::eliminarMatriz(int**a[]){
      //liberamos memoria
    for(int i =0; i< sizeX; i++){        
        delete[] a[i];
    }
    delete[] a;
    cout<<"se elimina";



}

