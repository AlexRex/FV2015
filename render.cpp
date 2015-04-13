/* 
 * File:   render.cpp
 * Author: Pablo
 * 
 * Created on 11 de abril de 2015, 8:44
 */
#include <iostream>
#include "render.h"

using namespace std;
render::render() {
}

render::render(const render& orig) {
}

render::~render() {
}
void render::imprimeInfo(int *n){
    cout<<"Render: "<<*n<<endl;
    *n +=1;
}
