#ifndef MATERIAS_H
#define MATERIAS_H
#include "materia.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class materias {
private:
    materia** lista_materias;
    int cant;
    int cant_max;
    
    void resize();

public:
    materias();
    ~materias();
    
    void addMateria(materia* m);
    int getCantidad() const { return cant; }
    materia* getMateria(int index) const;
    int getIdPorNombre(const char* nombre) const;
    int getIdMateria(string nombre) const { return getIdPorNombre(nombre.c_str()); }
    void mostrarDetalle(int id) const;
    void mostrarMaterias() const;
    void modificar(int id, const char* instrucciones);
    bool eliminar(int id);
    int agregar(const char* nombre);
};

#endif // MATERIAS_H
