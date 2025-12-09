#ifndef UNIVERSAL_TIME_TABLING_H
#define UNIVERSAL_TIME_TABLING_H

#include "materias.h"
#include "salones.h"
#include "grupos.h"
#include "maestros.h"
#include "conjunto_materias.h"
#include "horario_disponibilidad.h"
#include "horario.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

struct Coordenada {
    int dia;
    int franja;
    int id_salon;
};

struct nodo{
    int prioridad;
    int id_materia;
    int id_grupo;
    int id_salon;
    int id_maestro;
    struct nodo* siguiente;
    struct nodo* anterior;
    
    // Para backtracking
    Coordenada asignaciones_realizadas[20]; // Guardar qué se asignó para poder deshacer
    int horas_asignadas_cnt = 0;
    int contador_intentos = 0; // Para detectar bucles infinitos
};

struct lista{
    struct nodo* inicio;
    struct nodo* fin;
    int cant;
};

struct lista_de_listas{
    lista** listas_grupos; 
    int cantidad_grupos;
};

lista_de_listas* inicializar_listas_grupos(int cantidad_grupos);
void agregar_nodo_ordenado(nodo* nuevo_nodo, lista* lista_grupo);
void crear_prioridad_grupo(int id_grupo, Set* conjunto, materias* Materias, maestros* Maestros, lista* lista_grupo);
bool validar_asignacion(nodo* nodo_actual, int dia, int franja, int id_salon, materias* Materias, maestros* Maestros, salones* Salones, Horario* horarios_grupos, Horario* horarios_maestros, Horario* horarios_salones, bool strict_availability = true);
bool maestro_ya_asignado_en_grupo(int id_grupo, int id_maestro, Horario* horarios_grupos);
void desasignar_materia(nodo* nodo_actual, Horario* horarios_grupos, Horario* horarios_maestros, Horario* horarios_salones);
bool asignar_materia_a_horario(nodo* nodo_actual, int id_salon_forzado, materias* Materias, maestros* Maestros, salones* Salones, Horario* horarios_grupos, Horario* horarios_maestros, Horario* horarios_salones, bool strict_horizontal = false, bool strict_availability = true);
bool resolver_horario_recursivo(nodo* nodo_actual, int id_grupo, materias* Materias, maestros* Maestros, salones* Salones, grupos* Grupos, Horario* horarios_grupos, Horario* horarios_maestros, Horario* horarios_salones, int profundidad = 0, int* intentos_fallidos = nullptr);
void ejecutar_universal_timetabling_grupo(lista* lista_grupo, int id_grupo, materias* Materias, maestros* Maestros, salones* Salones, grupos* Grupos, Horario* horarios_grupos, Horario* horarios_maestros, Horario* horarios_salones);

// Funciones para backtracking global
lista* crear_lista_global_priorizada(lista_de_listas* listas);
bool ejecutar_universal_timetabling_global(lista* lista_global, materias* Materias, maestros* Maestros, salones* Salones, grupos* Grupos, Horario* horarios_grupos, Horario* horarios_maestros, Horario* horarios_salones);

#endif // UNIVERSAL_TIME_TABLING_H
