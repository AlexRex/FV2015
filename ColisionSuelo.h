/* 
 * File:   ColisionSuelo.h
 * Author: leti
 *
 * Created on 13 de abril de 2015, 13:06
 */

#ifndef COLISIONSUELO_H
#define	COLISIONSUELO_H

class ColisionSuelo {
public:
    ColisionSuelo();
    ColisionSuelo(const ColisionSuelo& orig);
    virtual ~ColisionSuelo();
    void creoMatriz();
    void eliminarMatriz(int**a[]);
private:

};

#endif	/* COLISIONSUELO_H */

