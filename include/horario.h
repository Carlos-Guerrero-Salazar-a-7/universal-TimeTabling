#ifndef HORARIO_CLASE_H
#define HORARIO_CLASE_H
#include <cstring>
#include <iostream>

using namespace std;

// Estructura para representar una celda del horario
struct CeldaHorario {
    int id_materia;      // -1 si está vacío
    int id_maestro;      // -1 si está vacío
    int id_salon;        // -1 si está vacío
    int id_grupo;        // -1 si está vacío
    bool ocupado;
    char info[200];      // Texto para mostrar (parsed from CSV)
    char color[20];      // Color hex (parsed from CSV)
    
    CeldaHorario() : id_materia(-1), id_maestro(-1), id_salon(-1), id_grupo(-1), ocupado(false) {
        info[0] = '\0';
        color[0] = '\0';
    }
};

class materias;
class maestros;
class salones;
class grupos;

// Clase para manejar un horario individual (de un grupo)
class Horario {
private:
    static const int DIAS = 5;        // Lunes a Viernes
    static const int FRANJAS = 15;     // Número de franjas horarias
    
    int id_grupo;
    CeldaHorario matriz[DIAS][FRANJAS];
    
    // Nombres de los días
    static const char* NOMBRES_DIAS[DIAS];
    
    // Franjas horarias
    struct FranjaHoraria {
        char inicio[10];
        char fin[10];
    };
    
    static const FranjaHoraria FRANJAS_HORARIAS[FRANJAS];

public:
    Horario() : id_grupo(-1) {}
    
    Horario(int id) : id_grupo(id) {}
    
    // Getters
    int getIdGrupo() const { return id_grupo; }
    
    // Obtener una celda específica
    CeldaHorario* getCelda(int dia, int franja) {
        if (dia >= 0 && dia < DIAS && franja >= 0 && franja < FRANJAS) {
            return &matriz[dia][franja];
        }
        return nullptr;
    }
    
    // Asignar una clase en el horario
    bool asignarClase(int dia, int franja, int id_materia, int id_maestro, int id_salon, int id_grupo_arg = -1) {
        if (dia < 0 || dia >= DIAS || franja < 0 || franja >= FRANJAS) {
            return false;
        }
        
        if (matriz[dia][franja].ocupado) {
            return false; // Ya está ocupado
        }
        
        matriz[dia][franja].id_materia = id_materia;
        matriz[dia][franja].id_maestro = id_maestro;
        matriz[dia][franja].id_salon = id_salon;
        matriz[dia][franja].id_grupo = id_grupo_arg;
        matriz[dia][franja].ocupado = true;
        
        return true;
    }
    
    // Liberar una celda
    void liberarCelda(int dia, int franja) {
        if (dia >= 0 && dia < DIAS && franja >= 0 && franja < FRANJAS) {
            matriz[dia][franja].id_materia = -1;
            matriz[dia][franja].id_maestro = -1;
            matriz[dia][franja].id_salon = -1;
            matriz[dia][franja].id_grupo = -1;
            matriz[dia][franja].ocupado = false;
            matriz[dia][franja].info[0] = '\0';
            matriz[dia][franja].color[0] = '\0';
        }
    }
    
    // Verificar si una celda está ocupada
    bool estaOcupado(int dia, int franja) const {
        if (dia >= 0 && dia < DIAS && franja >= 0 && franja < FRANJAS) {
            return matriz[dia][franja].ocupado;
        }
        return true; // Si está fuera de rango, considerarlo ocupado
    }
    
    // Limpiar todo el horario
    void limpiar() {
        for (int i = 0; i < DIAS; i++) {
            for (int j = 0; j < FRANJAS; j++) {
                liberarCelda(i, j);
            }
        }
    }
    
    // Mostrar el horario en formato tabla
    void mostrar(materias* m_obj, maestros* ma_obj, salones* s_obj) const;
    
    // Exportar horario a formato CSV
    // Formato: lunes:hora(id)[color],...
    void exportarCSV(const char* nombre_entidad, const char* archivo_salida, int tipo_entidad, materias* m_obj, maestros* ma_obj, grupos* g_obj, salones* s_obj) const;
    
    // Importar horario desde CSV string (una linea)
    void importarCSV(const char* linea);
    
    // Métodos estáticos para obtener información
    static int getNumDias() { return DIAS; }
    static int getNumFranjas() { return FRANJAS; }
    static const char* getNombreDia(int dia) {
        if (dia >= 0 && dia < DIAS) return NOMBRES_DIAS[dia];
        return "DESCONOCIDO";
    }
    static const char* getInicioFranja(int franja) {
        if (franja >= 0 && franja < FRANJAS) return FRANJAS_HORARIAS[franja].inicio;
        return "00:00";
    }
    static const char* getFinFranja(int franja) {
        if (franja >= 0 && franja < FRANJAS) return FRANJAS_HORARIAS[franja].fin;
        return "00:00";
    }
    
    // Obtener índice de franja dado un string de hora (ej: "7:00")
    // Retorna -1 si no encuentra coincidencia exacta
    static int getFranjaInicio(const char* hora);
    
    // Obtener índice de franja donde termina esta hora (ej: "13:55")
    // Retorna -1 si no encuentra coincidencia exacta
    static int getFranjaFin(const char* hora);
};

#endif // HORARIO_CLASE_H
