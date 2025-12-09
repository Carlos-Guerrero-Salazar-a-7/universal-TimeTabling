#ifndef SALON_H
#define SALON_H
#include <cstring>
#include "horario_disponibilidad.h"

class salon {
private:
    int id;
    char nombre[50];
    char tipo[50];
    horario_disponibilidad horario_disponible;

public:
    salon() : id(0) {
        nombre[0] = '\0';
        tipo[0] = '\0';
        color[0] = '\0';
    }

    salon(int i, const char* n, const char* t) : id(i) {
        int j = 0;
        while (j < 49 && n[j] != '\0') {
            nombre[j] = n[j];
            j++;
        }
        nombre[j] = '\0';
        
        j = 0;
        while (j < 49 && t[j] != '\0') {
            tipo[j] = t[j];
            j++;
        }
        tipo[j] = '\0';
    }

    int getId() const { return id; }
    const char* getNombre() const { return nombre; }
    const char* getTipo() const { return tipo; }
    horario_disponibilidad& getHorarioDisponibilidad() { return horario_disponible; }
    const horario_disponibilidad& getHorarioDisponibilidad() const { return horario_disponible; }

    void setId(int i) { id = i; }
    
    void setNombre(const char* n) {
        int j = 0;
        while (j < 49 && n[j] != '\0') {
            nombre[j] = n[j];
            j++;
        }
        nombre[j] = '\0';
    }
    
    void setTipo(const char* t) {
        int j = 0;
        while (j < 49 && t[j] != '\0') {
            tipo[j] = t[j];
            j++;
        }
        tipo[j] = '\0';
    }
    
    void setHorarioDisponibilidad(const char* horario_str) {
        horario_disponible.marcarDisponibilidad(horario_str);
    }

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
    char color[20];
};

#endif // SALON_H
