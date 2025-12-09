#ifndef MAESTRO_H
#define MAESTRO_H
#include <cstring>
#include "horario_disponibilidad.h"

class maestro {
private:
    int id;
    char nombre[100];
    int* materias_que_imparte;  // Array de IDs de materias (referencias)
    int cant_materias;
    int cant_max_materias;
    horario_disponibilidad horario_disponible;
    char horario_str[512];

public:
    maestro() : id(0), materias_que_imparte(nullptr), cant_materias(0), cant_max_materias(10) {
        nombre[0] = '\0';
        horario_str[0] = '\0';
        color[0] = '\0';
        materias_que_imparte = new int[cant_max_materias];
    }

    ~maestro() {
        delete[] materias_que_imparte;
    }

    // Getters
    int getId() const { return id; }
    const char* getNombre() const { return nombre; }
    const char* getHorario() const { return horario_str; }
    int getCantidadMaterias() const { return cant_materias; }
    int getIdMateria(int index) const {
        if (index >= 0 && index < cant_materias) {
            return materias_que_imparte[index];
        }
        return -1;
    }
    horario_disponibilidad& getHorarioDisponibilidad() { return horario_disponible; }
    const horario_disponibilidad& getHorarioDisponibilidad() const { return horario_disponible; }

    // Setters
    void setId(int i) { id = i; }
    
    void setNombre(const char* n) {
        int i = 0;
        while (i < 99 && n[i] != '\0') {
            nombre[i] = n[i];
            i++;
        }
        nombre[i] = '\0';
    }
    
    void setHorario(const char* h) {
        int i = 0;
        while (i < 511 && h[i] != '\0') {
            horario_str[i] = h[i];
            i++;
        }
        horario_str[i] = '\0';
        horario_disponible.marcarDisponibilidad(h);
    }
    
    void addIdMateria(int id_materia) {
        if (cant_materias >= cant_max_materias) {
            cant_max_materias += 1;
            int* nuevo_array = new int[cant_max_materias];
            for (int i = 0; i < cant_materias; i++) {
                nuevo_array[i] = materias_que_imparte[i];
            }
            delete[] materias_que_imparte;
            materias_que_imparte = nuevo_array;
        }
        materias_que_imparte[cant_materias] = id_materia;
        cant_materias++;
    }
    
    void clearMaterias() {
        cant_materias = 0;
    }

    void setColor(const char* c) {
        // Simple storage, assuming format "R,G,B" fits in 20 chars
        int i = 0;
        while (i < 19 && c[i] != '\0') {
            color[i] = c[i];
            i++;
        }
        color[i] = '\0';
    }

    const char* getColor() const { return color; }

private:
    char color[20]; // Store RGB string like "255,255,255"
};

#endif // MAESTRO_H
