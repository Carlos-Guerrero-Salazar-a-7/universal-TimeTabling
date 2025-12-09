#include "mainwindow.h"
#include "materias.h"
#include "salones.h"
#include "grupos.h"
#include "maestros.h"
#include "conjunto_materias.h"
#include "horario_disponibilidad.h"
#include "horario.h"
#include "universal_time_tabling.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <limits>

#include <QApplication>

int main(int argc, char *argv[])
{
    bool ejecutar_universal_timetabling = false;
    std::cout << "========================================" << std::endl;
    std::cout << "  SISTEMA DE HORARIOS UNIVERSITARIOS" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    std::cout << "Cargando datos desde CSV..." << std::endl;
    materias *Materias = new materias();
    
    ConjuntoMaterias *Conjuntos = new ConjuntoMaterias();
    Conjuntos->cargarMaterias(Materias);
    
    salones *Salones = new salones();
    grupos *Grupos = new grupos(Conjuntos);
    maestros *Maestros = new maestros(Materias);
    
    Horario* horarios_grupos = new Horario[Grupos->getCantidad()];
    for(int i = 0; i < Grupos->getCantidad(); i++){
        horarios_grupos[i] = Horario(i);
        
        // Marcar como ocupadas las franjas fuera del horario del grupo
        grupo* g = Grupos->getGrupo(i);
        if (g != nullptr) {
            int inicio = g->getFranjaInicio();
            int fin = g->getFranjaFin();
            
            std::cout << "  Grupo " << g->getNombre() << " horario: " 
                 << Horario::getInicioFranja(inicio) << " - " << Horario::getFinFranja(fin) << std::endl;
            
            for (int d = 0; d < Horario::getNumDias(); d++) {
                for (int f = 0; f < Horario::getNumFranjas(); f++) {
                    if (f < inicio || f > fin) {
                        // Marcar como ocupado (usando -1 para ids para indicar bloqueo por horario)
                        horarios_grupos[i].asignarClase(d, f, -1, -1, -1);
                    }
                }
            }
        }
    }
    
    Horario* horarios_maestros = new Horario[Maestros->getCantidad()];
    for(int i = 0; i < Maestros->getCantidad(); i++){
        horarios_maestros[i] = Horario(i);
    }
    
    Horario* horarios_salones = new Horario[Salones->getCantidad()];
    for(int i = 0; i < Salones->getCantidad(); i++){
        horarios_salones[i] = Horario(i);
    }
    
    // Load generated schedules from CSV if they exist
    const char* archivo_grupos = "../src/csv/horario_grupos_generado.csv";
    FILE* fGroups = fopen(archivo_grupos, "r");
    if (fGroups) {
        std::cout << "Cargando horarios generados de grupos..." << std::endl;
        char line[10000];
        while (fgets(line, sizeof(line), fGroups)) {
            char* comma = strchr(line, ',');
            if (comma) {
                char name[256];
                strncpy(name, line, comma - line);
                name[comma - line] = '\0';
                
                for(int i=0; i<Grupos->getCantidad(); i++) {
                    if (strcmp(Grupos->getGrupo(i)->getNombre(), name) == 0) {
                        horarios_grupos[i].importarCSV(line);
                        break;
                    }
                }
            }
        }
        fclose(fGroups);
    }
    
    const char* archivo_maestros = "../src/csv/horario_maestros_generado.csv";
    FILE* fTeachers = fopen(archivo_maestros, "r");
    if (fTeachers) {
        std::cout << "Cargando horarios generados de maestros..." << std::endl;
        char line[10000];
        while (fgets(line, sizeof(line), fTeachers)) {
            char* comma = strchr(line, ',');
            if (comma) {
                char name[256];
                strncpy(name, line, comma - line);
                name[comma - line] = '\0';
                
                for(int i=0; i<Maestros->getCantidad(); i++) {
                    if (strcmp(Maestros->getMaestro(i)->getNombre(), name) == 0) {
                        horarios_maestros[i].importarCSV(line);
                        break;
                    }
                }
            }
        }
        fclose(fTeachers);
    }
    
    std::cout << "RESUMEN DE CARGA:" << std::endl;
    std::cout << "  - Materias: " << Materias->getCantidad() << std::endl;
    std::cout << "  - Salones: " << Salones->getCantidad() << std::endl;
    std::cout << "  - Grupos: " << Grupos->getCantidad() << std::endl;
    std::cout << "  - Maestros: " << Maestros->getCantidad() << std::endl;
    std::cout << "  - Conjuntos de materias: " << Conjuntos->getCantidad() << std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.setData(Materias, Salones, Grupos, Maestros, Conjuntos, horarios_grupos, Grupos->getCantidad(), horarios_maestros, Maestros->getCantidad());
    w.show();
    int ret = a.exec();

    // Liberar memoria de horarios
    delete[] horarios_grupos;
    delete[] horarios_maestros;
    delete[] horarios_salones;
    
    // Liberar memoria
    delete Materias;
    delete Salones;
    delete Grupos;
    delete Maestros;
    delete Conjuntos;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "  Programa finalizado correctamente" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return ret;
}
