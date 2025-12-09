#ifndef GRUPO_H
#define GRUPO_H
#include <cstring>

class grupo {
private:
    int id;
    char nombre[50];
    int conjunto_de_materias;

public:
    // Constructor por defecto
    grupo() : id(0), franja_inicio(0), franja_fin(14) {
        nombre[0] = '\0';
        color[0] = '\0';
    }

    // Constructor con parámetros
    grupo(int i, const char* n) : id(i), franja_inicio(0), franja_fin(14) {
        int j = 0;
        while (j < 49 && n[j] != '\0') {
            nombre[j] = n[j];
            j++;
        }
        nombre[j] = '\0';
    }

    // Getters
    int getId() const { return id; }
    const char* getNombre() const { return nombre; }
    int getConjuntoDeMaterias() const { return conjunto_de_materias; }

    // Setters
    void setId(int i) { id = i; }
    
    void setNombre(const char* n) {
        int j = 0;
        while (j < 49 && n[j] != '\0') {
            nombre[j] = n[j];
            j++;
        }
        nombre[j] = '\0';
    }

    void setConjuntoDeMaterias(int id_conjunto) {
        conjunto_de_materias = id_conjunto;
    }

    void setFranjaInicio(int f) { franja_inicio = f; }
    void setFranjaFin(int f) { franja_fin = f; }
    
    int getFranjaInicio() const { return franja_inicio; }
    int getFranjaFin() const { return franja_fin; }

    void setColor(const char* c) {
        int i = 0;
        while (i < 19 && c[i] != '\0') {
            color[i] = c[i];
            i++;
        }
        color[i] = '\0';
    }

    const char* getColor() const { return color; }

private:
    int franja_inicio;
    int franja_fin;
    char color[20];
};

#endif // GRUPO_H
