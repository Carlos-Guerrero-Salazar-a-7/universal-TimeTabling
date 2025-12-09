#include "../include/horario.h"
#include "../include/materias.h"
#include "../include/maestros.h"
#include "../include/grupos.h"
#include "../include/salones.h"
#include <cstdio>
#include <cstring>

const char* Horario::NOMBRES_DIAS[Horario::DIAS] = {
    "Lunes", "Martes", "Miercoles", "Jueves", "Viernes"
};

const Horario::FranjaHoraria Horario::FRANJAS_HORARIAS[Horario::FRANJAS] = {
    {"7:00", "7:55"}, {"7:55", "8:50"}, {"8:50", "9:45"}, {"9:45", "10:10"},
    {"10:10", "11:05"}, {"11:05", "12:00"}, {"12:00", "12:55"}, {"12:55", "13:50"},
    {"13:50", "13:55"}, {"14:00", "14:55"}, {"14:55", "15:50"}, {"15:50", "16:45"},
    {"16:45", "17:10"}, {"17:10", "18:05"}, {"18:05", "19:00"}
};

void Horario::mostrar(materias* m_obj, maestros* ma_obj, salones* s_obj) const {

}

void Horario::exportarCSV(const char* nombre_entidad, const char* archivo_salida, int tipo_entidad, materias* m_obj, maestros* ma_obj, grupos* g_obj, salones* s_obj) const {
    FILE* f = fopen(archivo_salida, "a");
    if (f == NULL) {
        printf("Error al abrir archivo para escritura: %s\n", archivo_salida);
        return;
    }
    fprintf(f, "%s,", nombre_entidad);
    
    bool primero = true;
    for (int d = 0; d < DIAS; d++) {
        for (int fr = 0; fr < FRANJAS; fr++) {
            if (matriz[d][fr].ocupado && matriz[d][fr].id_materia != -1) {
                if (!primero) fprintf(f, ";");
                
                // Obtener datos
                int id_mat = matriz[d][fr].id_materia;
                int id_mae = matriz[d][fr].id_maestro;
                int id_sal = matriz[d][fr].id_salon;
                int id_gru = matriz[d][fr].id_grupo;
                
                fprintf(f, "%s:%s-%s", NOMBRES_DIAS[d], FRANJAS_HORARIAS[fr].inicio, FRANJAS_HORARIAS[fr].fin);
                
                // Agregar info extra entre parentesis
                fprintf(f, "(");
                materia* m = m_obj->getMateria(id_mat);
                if (m) fprintf(f, "%s", m->getNombre());
                
                if (tipo_entidad == 1) { // Grupo
                    if (id_mae != -1) {
                        maestro* ma = ma_obj->getMaestro(id_mae);
                        if (ma) fprintf(f, " - %s", ma->getNombre());
                    }
                    if (id_sal != -1) {
                        salon* s = s_obj->getSalon(id_sal);
                        if (s) fprintf(f, " - %s", s->getNombre());
                    }
                } else if (tipo_entidad == 2) { // Maestro
                    if (id_gru != -1) {
                        grupo* g = g_obj->getGrupo(id_gru);
                        if (g) fprintf(f, " - %s", g->getNombre());
                    }
                    if (id_sal != -1) {
                        salon* s = s_obj->getSalon(id_sal);
                        if (s) fprintf(f, " - %s", s->getNombre());
                    }
                } else if (tipo_entidad == 3) { // Salon
                    if (id_gru != -1) {
                        grupo* g = g_obj->getGrupo(id_gru);
                        if (g) fprintf(f, " - %s", g->getNombre());
                    }
                    if (id_mae != -1) {
                        maestro* ma = ma_obj->getMaestro(id_mae);
                        if (ma) fprintf(f, " - %s", ma->getNombre());
                    }
                }
                fprintf(f, ")");
                fprintf(f, "[#AED6F1]"); 
                
                primero = false;
            }
        }
    }
    fprintf(f, "\n");
    fclose(f);
}

int Horario::getFranjaInicio(const char* hora) {
    for (int i = 0; i < FRANJAS; i++) {
        if (strcmp(FRANJAS_HORARIAS[i].inicio, hora) == 0) {
            return i;
        }
    }
    return -1;
}

int Horario::getFranjaFin(const char* hora) {
    for (int i = 0; i < FRANJAS; i++) {
        if (strcmp(FRANJAS_HORARIAS[i].fin, hora) == 0) {
            return i;
        }
    }
    return -1;
}

void Horario::importarCSV(const char* linea) {
    const char* ptr = strchr(linea, ',');
    if (!ptr) return;
    ptr++;
    
    char buffer[10000];
    strncpy(buffer, ptr, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    char* token = strtok(buffer, ";");
    while (token) {
        
        char diaStr[20] = {0};
        char inicioStr[10] = {0};
        char finStr[10] = {0};
        char infoStr[200] = {0};
        char colorStr[20] = {0};
        
        //delimitadores
        char* colon1 = strchr(token, ':');
        char* dash = strchr(token, '-');
        char* parenOpen = strchr(token, '(');
        char* parenClose = strrchr(token, ')'); 
        char* bracketOpen = strchr(token, '[');
        char* bracketClose = strchr(token, ']');
        
        if (colon1 && dash && parenOpen && parenClose && bracketOpen && bracketClose) {
            // saca el dia
            strncpy(diaStr, token, colon1 - token);
            strncpy(inicioStr, colon1 + 1, dash - (colon1 + 1));
            strncpy(finStr, dash + 1, parenOpen - (dash + 1));
            strncpy(infoStr, parenOpen + 1, parenClose - (parenOpen + 1));
            strncpy(colorStr, bracketOpen + 1, bracketClose - (bracketOpen + 1));
            strncpy(colorStr, bracketOpen + 1, bracketClose - (bracketOpen + 1));
            int diaIdx = -1;
            for(int i=0; i<DIAS; i++) {
                if (strcmp(NOMBRES_DIAS[i], diaStr) == 0) {
                    diaIdx = i;
                    break;
                }
            }
            int franjaIdx = getFranjaInicio(inicioStr);
            
            if (diaIdx != -1 && franjaIdx != -1) {
                matriz[diaIdx][franjaIdx].ocupado = true;
                strcpy(matriz[diaIdx][franjaIdx].info, infoStr);
                strcpy(matriz[diaIdx][franjaIdx].color, colorStr);
                matriz[diaIdx][franjaIdx].id_materia = 0;
            }
        }
        
        token = strtok(NULL, ";");
    }
}
