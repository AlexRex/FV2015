/* 
 * File:   update.cpp
 * Author: Pablo
 * 
 * Created on 11 de abril de 2015, 8:44
 */
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "update.h"
using namespace std;
update::update() {
}

update::update(const update& orig) {
}

update::~update() {
}
/*
void update::imprimeInfo(int n){
    cout<<"Update: "<<n<<endl;
}
 * */
void update::imprimeInfo(int *n){
    cout<<"Update: "<<*n<<endl;
    *n +=1;
}

