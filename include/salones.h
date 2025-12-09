#ifndef SALONES_H
#define SALONES_H
#include "salon.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class salones {
private:
    salon** lista_salones;
    int cant;
    int cant_max;
    
    void resize();

public:
    salones();
    ~salones();
    
    void addSalon(salon* s);
    int getCantidad() const { return cant; }
    salon* getSalon(int index) const;
    void setColor(const char* c);
    const char* getColor() const;
    void mostrarDetalle(int id) const;
    void mostrarSalones() const;
    void modificar(int id, const char* instrucciones);
};

#endif // SALONES_H
