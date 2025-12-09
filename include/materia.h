#ifndef MATERIA_H
#define MATERIA_H
#include <cstring>

class materia {
private:
    int id;
    char nombre[100];
    int horas_necesarias;
    char salon_especial[50];
    int id_anterior;
    int id_siguiente;

public:
    // Constructor por defecto
    materia() : id(0), horas_necesarias(0), id_anterior(-1), id_siguiente(-1) {
        nombre[0] = '\0';
        salon_especial[0] = '\0';
    }

    // Constructor con parámetros
    materia(int i, const char* n, int h, const char* s) 
        : id(i), horas_necesarias(h) {
        int j = 0;
        while (j < 99 && n[j] != '\0') {
            nombre[j] = n[j];
            j++;
        }
        nombre[j] = '\0';
        
        j = 0;
        while (j < 49 && s[j] != '\0') {
            salon_especial[j] = s[j];
            j++;
        }
        salon_especial[j] = '\0';
    }

    // Getters
    int getId() const { return id; }
    const char* getNombre() const { return nombre; }
    int getHorasNecesarias() const { return horas_necesarias; }
    const char* getSalonEspecial() const { return salon_especial; }

    // Setters
    void setId(int i) { id = i; }
    
    void setNombre(const char* n) {
        int j = 0;
        while (j < 99 && n[j] != '\0') {
            nombre[j] = n[j];
            j++;
        }
        nombre[j] = '\0';
    }
    
    void setHorasNecesarias(int h) { horas_necesarias = h; }
    
    void setSalonEspecial(const char* s) {
        int j = 0;
        while (j < 49 && s[j] != '\0') {
            salon_especial[j] = s[j];
            j++;
        }
        salon_especial[j] = '\0';
    }
    int getIdAnterior() const { return id_anterior; }
    int getIdSiguiente() const { return id_siguiente; }
    void setIdAnterior(int id) { id_anterior = id; }
    void setIdSiguiente(int id) { id_siguiente = id; }
};

#endif // MATERIA_H
