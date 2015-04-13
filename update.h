/* 
 * File:   update.h
 * Author: Pablo
 *
 * Created on 11 de abril de 2015, 8:44
 */

#ifndef UPDATE_H
#define	UPDATE_H
#include <iostream>
#include <sstream>
#include <cstdlib>

class update {
public:
    update();
    update(const update& orig);
    virtual ~update();
   // void imprimeInfo(int n);
    void imprimeInfo(int *n);

private:

};

#endif	/* UPDATE_H */

