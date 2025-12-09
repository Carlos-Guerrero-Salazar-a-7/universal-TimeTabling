#ifndef CONJUNTO_MATERIAS_H
#define CONJUNTO_MATERIAS_H

#include <string>
#include "materias.h"

using namespace std;

struct Set {
    string nombre;
    int* materia_ids;
    int cant_materias;
    int max_materias;

    Set() : materia_ids(nullptr), cant_materias(0), max_materias(0) {}
};

class ConjuntoMaterias {
private:
    Set* sets;
    int cant_sets;
    int max_sets;

    void resizeSets();
    void resizeMaterias(Set& s);

public:
    ConjuntoMaterias();
    ~ConjuntoMaterias();
    void cargarMaterias(materias* m_obj);
    int getIdSet(string nombre);
    int getCantidad();
    Set* getSet(int index);
    void mostrarDetalle(int index, materias* materias_obj);
    void mostrarConjuntos();
    void modificar(int id, const char* instrucciones, materias* m_obj);
    void agregarMateriaASet(int idSet, int idMateria);
};

#endif // CONJUNTO_MATERIAS_H
