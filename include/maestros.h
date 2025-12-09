#ifndef MAESTROS_H
#define MAESTROS_H
#include "maestro.h"
#include <iostream>
#include <fstream>
#include <string>

#include "materias.h"

using namespace std;

class maestros {
private:
    maestro** lista_maestros;
    int cant;
    int cant_max;
    
    void resize();

public:
    maestros(materias* lista_materias_obj = nullptr);
    ~maestros();
    
    void addMaestro(maestro* m);
    int getCantidad() const { return cant; }
    maestro* getMaestro(int index) const;
    void setColor(const char* c);
    const char* getColor() const;
    void mostrarDetalle(int id, materias* materias_obj) const;
    void mostrarMaestros() const;
    void modificar(int id, const char* instrucciones, materias* materias_obj);
    void guardarCSV(materias* materias_obj);
};

#endif // MAESTROS_H
