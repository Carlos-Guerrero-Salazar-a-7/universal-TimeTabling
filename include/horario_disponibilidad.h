#ifndef HORARIO_DISPONIBILIDAD_H
#define HORARIO_DISPONIBILIDAD_H
#include <cstring>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Estados posibles de una celda del horario
enum EstadoCelda {
    INDEFINIDO = 0,  // No definido en el horario (se muestra vacío)
    DISPONIBLE = 1,  // Disponible para asignar
    OCUPADO = 2      // Ya ocupado/asignado
};

struct CeldaDisponibilidad {
    EstadoCelda estado;
    
    CeldaDisponibilidad() : estado(INDEFINIDO) {}
    
    // Métodos de compatibilidad con código existente
    bool isDisponible() const { return estado == DISPONIBLE; }
    bool isOcupado() const { return estado == OCUPADO; }
    bool isIndefinido() const { return estado == INDEFINIDO; }
};

// Clase para manejar un horario individual (de un grupo)
class horario_disponibilidad {
private:
    static const int DIAS = 5;        // Lunes a Viernes
    static const int FRANJAS = 15;     // Número de franjas horarias
    
    int id_grupo;
    CeldaDisponibilidad matriz[DIAS][FRANJAS];
    
    // Nombres de los días
    static const char* NOMBRES_DIAS[DIAS];
    
    // Franjas horarias
    struct FranjaHoraria {
        char inicio[10];
        char fin[10];
    };
    
    static const FranjaHoraria FRANJAS_HORARIAS[FRANJAS];

public:
    horario_disponibilidad() : id_grupo(-1) {}
    
    horario_disponibilidad(int id) : id_grupo(id) {}

    void marcarDisponibilidad(const char* horario_char) {
        // Limpiar matriz primero (todo a INDEFINIDO)
        limpiarAIndefinido();

        string horario_str = horario_char;
        
        // Detectar formato complejo (empieza con '(')
        if (horario_str.length() > 0 && horario_str[0] == '(') {
            // Remover parentesis inicial y final si existen
            if (horario_str.front() == '(') horario_str.erase(0, 1);
            if (horario_str.back() == ')') horario_str.pop_back();
            
            // Formato: Lunes:7:00-8:50,10:00-12:00;Martes:7:00-15:00
            // Separar por ';'
            size_t pos = 0;
            while ((pos = horario_str.find(';')) != string::npos) {
                string parte = horario_str.substr(0, pos);
                procesarParteCompleja(parte);
                horario_str.erase(0, pos + 1);
            }
            if (!horario_str.empty()) {
                procesarParteCompleja(horario_str);
            }
            return;
        }

        // Formato simple anterior: 7:00-14:00 (Aplica a todos los dias)
        
        // Buscar el guion separador
        int guion = (int)horario_str.find('-');
        if (guion == -1) return; // Formato invalido

        string inicio_str = horario_str.substr(0, guion);
        string fin_str = horario_str.substr(guion + 1);

        int h_ini_disp = 0;
        int h_fin_disp = 0;

        // Parsear hora inicio
        int dos_puntos_ini = (int)inicio_str.find(':');
        if (dos_puntos_ini != -1) {
            h_ini_disp = stoi(inicio_str.substr(0, dos_puntos_ini));
        } else {
            h_ini_disp = stoi(inicio_str);
        }

        // Parsear hora fin
        int dos_puntos_fin = (int)fin_str.find(':');
        if (dos_puntos_fin != -1) {
            h_fin_disp = stoi(fin_str.substr(0, dos_puntos_fin));
        } else {
            h_fin_disp = stoi(fin_str);
        }

        // Evaluar SOLO por hora - marcar como DISPONIBLE
        for (int d = 0; d < DIAS; d++) {
            for (int f = 0; f < FRANJAS; f++) {
                // Parsear horario de la franja usando string
                string inicio_franja_str = FRANJAS_HORARIAS[f].inicio;
                int h_ini_franja = 0;
                int dp_franja = (int)inicio_franja_str.find(':');
                if (dp_franja != -1) {
                    h_ini_franja = stoi(inicio_franja_str.substr(0, dp_franja));
                } else {
                    h_ini_franja = stoi(inicio_franja_str);
                }
                
                // Comparación simple por hora de inicio
                if (h_ini_franja >= h_ini_disp && h_ini_franja < h_fin_disp) {
                    matriz[d][f].estado = DISPONIBLE;
                }
                // Si no cumple, queda INDEFINIDO (ya limpiado)
            }
        }
    }

private:
    void procesarParteCompleja(string parte) {
        // Parte: "Lunes:7:00-9:00,10:00-12:00" o "Lunes:7:00-9:00 10:00"
        int dos_puntos = (int)parte.find(':');
        if (dos_puntos == -1) return;
        
        string dia_str = parte.substr(0, dos_puntos);
        string horas_str = parte.substr(dos_puntos + 1);
        
        // Identificar dia (soporta con y sin acentos)
        int dia_idx = -1;
        for(int i=0; i<DIAS; i++) {
            if (strcasecmp(dia_str.c_str(), NOMBRES_DIAS[i]) == 0) {
                dia_idx = i;
                break;
            }
        }
        
        // Si no se encontró, intentar con variantes sin acento
        if (dia_idx == -1) {
            if (strcasecmp(dia_str.c_str(), "MIERCOLES") == 0) {
                dia_idx = 2; // Miércoles
            }
        }
        
        if (dia_idx == -1) return; // Dia no reconocido
        
        // Procesar horas: "7:00-9:00,10:00-12:00" o "7:00-9:00 10:00"
        for (size_t i = 0; i < horas_str.length(); i++) {
            if (horas_str[i] == ',') {
                horas_str[i] = ' ';
            }
        }
        while(horas_str.length() > 0 && horas_str[0] == ' ') horas_str.erase(0, 1);
        
        // Separar por espacio
        size_t pos = 0;
        while ((pos = horas_str.find(' ')) != string::npos) {
            string token = horas_str.substr(0, pos);
            if (!token.empty()) {  // Evitar tokens vacíos
                procesarTokenHora(dia_idx, token);
            }
            horas_str.erase(0, pos + 1);
            while(horas_str.length() > 0 && horas_str[0] == ' ') horas_str.erase(0, 1);
        }
        if (!horas_str.empty()) {
            procesarTokenHora(dia_idx, horas_str);
        }
    }
    
    void procesarTokenHora(int dia, string token) {
        // Token puede ser rango "7:00-8:50" o simple "10:00"
        int guion = (int)token.find('-');
        if (guion != -1) {
            // Rango: marcar todas las franjas en ese rango como DISPONIBLE
            string inicio_str = token.substr(0, guion);
            string fin_str = token.substr(guion + 1);
            
            int h_ini = parsearHora(inicio_str);
            int h_fin = parsearHora(fin_str);
            
            for (int f = 0; f < FRANJAS; f++) {
                int h_franja = parsearHora(FRANJAS_HORARIAS[f].inicio);
                if (h_franja >= h_ini && h_franja < h_fin) {
                    matriz[dia][f].estado = DISPONIBLE;
                }
            }
        } else {
            // Hora simple, buscar la franja que corresponde
            int h_target = parsearHora(token);
            // Buscar franja exacta
            for (int f = 0; f < FRANJAS; f++) {
                int h_franja = parsearHora(FRANJAS_HORARIAS[f].inicio);
                if (h_franja == h_target) {
                    matriz[dia][f].estado = DISPONIBLE;
                }
            }
        }
    }
    
    int parsearHora(string hora_str) {
        int dos_puntos = (int)hora_str.find(':');
        if (dos_puntos != -1) {
            return stoi(hora_str.substr(0, dos_puntos));
        }
        try {
            return stoi(hora_str);
        } catch(...) { return 0; }
    }

public:
    
    // Getters
    int getIdGrupo() const { return id_grupo; }
    
    // Obtener una celda específica
    CeldaDisponibilidad* getCelda(int dia, int franja) {
        if (dia >= 0 && dia < DIAS && franja >= 0 && franja < FRANJAS) {
            return &matriz[dia][franja];
        }
        return nullptr;
    }
    
    // Asignar una clase en el horario
    bool asignarClase(int dia, int franja) {
        if (dia < 0 || dia >= DIAS || franja < 0 || franja >= FRANJAS) {
            return false;
        }
        
        if (matriz[dia][franja].estado != DISPONIBLE) {
            return false; // No está disponible
        }
        
        matriz[dia][franja].estado = OCUPADO; // Marcar como ocupado
        
        return true;
    }
    
    // Liberar una celda (volver a DISPONIBLE)
    void liberarCelda(int dia, int franja) {
        if (dia >= 0 && dia < DIAS && franja >= 0 && franja < FRANJAS) {
            if (matriz[dia][franja].estado == OCUPADO) {
                matriz[dia][franja].estado = DISPONIBLE;
            }
        }
    }
    
    // Verificar si una celda está ocupada
    bool estaOcupado(int dia, int franja) const {
        if (dia >= 0 && dia < DIAS && franja >= 0 && franja < FRANJAS) {
            return matriz[dia][franja].estado == OCUPADO;
        }
        return true; // Si está fuera de rango, considerarlo ocupado
    }

    // Verificar si una celda está disponible (es decir, es horario laboral del maestro)
    bool isDisponible(int dia, int franja) const {
        if (dia >= 0 && dia < DIAS && franja >= 0 && franja < FRANJAS) {
            return matriz[dia][franja].estado == DISPONIBLE;
        }
        return false;
    }
    
    // Limpiar todo el horario (volver todo a INDEFINIDO)
    void limpiarAIndefinido() {
        for (int i = 0; i < DIAS; i++) {
            for (int j = 0; j < FRANJAS; j++) {
                matriz[i][j].estado = INDEFINIDO;
            }
        }
    }
    
    // Limpiar ocupaciones (OCUPADO -> DISPONIBLE, mantiene INDEFINIDO)
    void limpiar() {
        for (int i = 0; i < DIAS; i++) {
            for (int j = 0; j < FRANJAS; j++) {
                if (matriz[i][j].estado == OCUPADO) {
                    matriz[i][j].estado = DISPONIBLE;
                }
            }
        }
    }
    
    // Mostrar el horario en formato tabla
    void mostrar(int id) const {
        cout << "\n╔════════════════════════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    HORARIO DEL maestro " << id << "                                      ║" << endl;
        cout << "╠═══════════╦═══════════╦═══════════╦═══════════╦═══════════╦═══════════════════╣" << endl;
        cout << "║  HORARIO  ║   LUNES   ║   MARTES  ║ MIÉRCOLES ║  JUEVES   ║   VIERNES         ║" << endl;
        cout << "╠═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════════════╣" << endl;
        
        for (int f = 0; f < FRANJAS; f++) {
            // Mostrar franja horaria
            cout << "║ " << FRANJAS_HORARIAS[f].inicio << "-" << FRANJAS_HORARIAS[f].fin << " ║";
            
            for (int d = 0; d < DIAS; d++) {
                switch(matriz[d][f].estado) {
                    case DISPONIBLE:
                        cout << " Disponible ║";
                        break;
                    case OCUPADO:
                        cout << "  Ocupado   ║";
                        break;
                    case INDEFINIDO:
                    default:
                        cout << "           ║";  // Vacío
                        break;
                }
            }
            cout << endl;
            
            if (f < FRANJAS - 1) {
                cout << "╠═══════════╬═══════════╬═══════════╬═══════════╬═══════════╬═══════════════════╣" << endl;
            }
        }
        
        cout << "╚═══════════╩═══════════╩═══════════╩═══════════╩═══════════╩═══════════════════╝" << endl;
    }
    
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

    int getCantidadDisponibilidad() const {
        int contador = 0;
        for (int d = 0; d < DIAS; d++) {
            for (int f = 0; f < FRANJAS; f++) {
                if (matriz[d][f].estado == DISPONIBLE) contador++;
            }
        }
        return contador;
    }
};

#endif // HORARIO_DISPONIBILIDAD_H
