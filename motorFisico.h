/* 
 * File:   motorFisico.h
 * Author: Pablo
 *
 * Created on 13 de abril de 2015, 13:13
 */

#ifndef MOTORFISICO_H
#define	MOTORFISICO_H

class motorFisico {
public:
    motorFisico();
    motorFisico(const motorFisico& orig);
    virtual ~motorFisico();
    int saltar(int y, float t);
private:

};

#endif	/* MOTORFISICO_H */

