#ifndef GRUPOS_H
#define GRUPOS_H
#include "grupo.h"
#include "conjunto_materias.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class grupos {
private:
    grupo** lista_grupos;
    int cant;
    int cant_max;
    
    void resize();

public:
    grupos(ConjuntoMaterias* cm_obj);
    ~grupos();
    
    void addGrupo(grupo* g);
    int getCantidad() const { return cant; }
    grupo* getGrupo(int index) const;
    void setColor(const char* c);
    const char* getColor() const;
    void mostrarDetalle(int id, ConjuntoMaterias* conjuntos) const;
    void mostrarGrupos() const;
    void modificar(int id, const char* instrucciones, ConjuntoMaterias* cm_obj);
    void eliminar(int id);
    void guardarCSV(ConjuntoMaterias* cm_obj);
};

#endif // GRUPOS_H
