#include "../include/universal_time_tabling.h"
#include <cstring> // For strcasecmp, strcmp
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

lista_de_listas* inicializar_listas_grupos(int cantidad_grupos){
    lista_de_listas* ldl = new lista_de_listas;
    ldl->cantidad_grupos = cantidad_grupos;
    ldl->listas_grupos = new lista*[cantidad_grupos];
    
    for(int i = 0; i < cantidad_grupos; i++){
        ldl->listas_grupos[i] = new lista;
        ldl->listas_grupos[i]->inicio = nullptr;
        ldl->listas_grupos[i]->fin = nullptr;
        ldl->listas_grupos[i]->cant = 0;
    }
    
    return ldl;
}


void agregar_nodo_ordenado(nodo* nuevo_nodo, lista* lista_grupo){
    if(lista_grupo->inicio == nullptr){
        lista_grupo->inicio = nuevo_nodo;
        lista_grupo->fin = nuevo_nodo;
        nuevo_nodo->siguiente = nullptr;
        nuevo_nodo->anterior = nullptr;
    } else {
        nodo* actual = lista_grupo->inicio;
        if(nuevo_nodo->prioridad > actual->prioridad){
            nuevo_nodo->siguiente = lista_grupo->inicio;
            nuevo_nodo->anterior = nullptr;
            lista_grupo->inicio->anterior = nuevo_nodo;
            lista_grupo->inicio = nuevo_nodo;
        } else {
            while(actual->siguiente != nullptr && actual->siguiente->prioridad >= nuevo_nodo->prioridad){
                actual = actual->siguiente;
            }
            
            nuevo_nodo->siguiente = actual->siguiente;
            nuevo_nodo->anterior = actual;
            
            if(actual->siguiente != nullptr){
                actual->siguiente->anterior = nuevo_nodo;
            } else {
                lista_grupo->fin = nuevo_nodo;
            }
            
            actual->siguiente = nuevo_nodo;
        }
    }
    lista_grupo->cant++;
}

void crear_prioridad_grupo(int id_grupo, Set* conjunto, materias* Materias, maestros* Maestros, lista* lista_grupo){
    std::cout << "\n--- Creando prioridades para grupo " << id_grupo << " ---" << std::endl;

    int horas_totales_conjunto = 0;
    for(int i = 0; i < conjunto->cant_materias; i++){
        int id_materia = conjunto->materia_ids[i];
        materia* mat = Materias->getMateria(id_materia);
        if(mat != nullptr){
            horas_totales_conjunto += mat->getHorasNecesarias();
        }
    }
    int horas_disponibles_totales = horario_disponibilidad::getNumDias() * horario_disponibilidad::getNumFranjas();
    
    std::cout << "  Horas totales del conjunto: " << horas_totales_conjunto << std::endl;
    std::cout << "  Horas disponibles totales: " << horas_disponibles_totales << std::endl;
    
    for(int i = 0; i < conjunto->cant_materias; i++){
        int id_materia = conjunto->materia_ids[i];
        materia* mat = Materias->getMateria(id_materia);
        if(mat == nullptr) continue;
        
        std::cout << "  Procesando materia: " << mat->getNombre() << std::endl;
        
        // Contar cuántos maestros pueden impartir esta materia
        int num_maestros_disponibles = 0;
        for(int j = 0; j < Maestros->getCantidad(); j++){
            maestro* mae = Maestros->getMaestro(j);
            for(int k = 0; k < mae->getCantidadMaterias(); k++){
                if(mae->getIdMateria(k) == id_materia){
                    num_maestros_disponibles++;
                    break;
                }
            }
        }
        
        // Buscar maestro que imparte esta materia
        for(int j = 0; j < Maestros->getCantidad(); j++){
            maestro* mae = Maestros->getMaestro(j);
            
            // Verificar si este maestro imparte esta materia
            bool imparte_materia = false;
            for(int k = 0; k < mae->getCantidadMaterias(); k++){
                if(mae->getIdMateria(k) == id_materia){
                    imparte_materia = true;
                    break;
                }
            }
            
            if(imparte_materia){
                nodo* nuevo_nodo = new nodo;
                nuevo_nodo->id_materia = id_materia;
                nuevo_nodo->id_grupo = id_grupo;
                nuevo_nodo->id_maestro = mae->getId();
                nuevo_nodo->id_salon = -1;
                nuevo_nodo->contador_intentos = 0;
                
                int franjas_disponibles_maestro = mae->getHorarioDisponibilidad().getCantidadDisponibilidad();
                int horas_necesarias = mat->getHorasNecesarias();
                
                // Prioridad base: inverso del número de maestros (menos maestros = más prioridad)
                int prioridad_escasez_maestros = (num_maestros_disponibles > 0) ? (1000 / num_maestros_disponibles) : 0;
                
                // Prioridad por disponibilidad: menos franjas = más prioridad
                int prioridad_disponibilidad = (franjas_disponibles_maestro > 0) ? (500 / franjas_disponibles_maestro) : 0;
                
                // Prioridad por horas: más horas = más prioridad
                int prioridad_horas = horas_necesarias * 10;
                
                // Prioridad total
                nuevo_nodo->prioridad = prioridad_escasez_maestros + prioridad_disponibilidad + prioridad_horas;
                
                std::cout << "    Maestro: " << mae->getNombre() << std::endl;
                std::cout << "      - Maestros disponibles para esta materia: " << num_maestros_disponibles << std::endl;
                std::cout << "      - Franjas disponibles del maestro: " << franjas_disponibles_maestro << std::endl;
                std::cout << "      - Horas necesarias: " << horas_necesarias << std::endl;
                std::cout << "      - Prioridad por escasez de maestros: " << prioridad_escasez_maestros << std::endl;
                std::cout << "      - Prioridad por disponibilidad: " << prioridad_disponibilidad << std::endl;
                std::cout << "      - Prioridad por horas: " << prioridad_horas << std::endl;
                std::cout << "      - Prioridad TOTAL: " << nuevo_nodo->prioridad << std::endl;
                agregar_nodo_ordenado(nuevo_nodo, lista_grupo);
                
                break;  // Solo un maestro por materia
            }
        }
    }
}

bool validar_asignacion(nodo* nodo_actual, int dia, int franja, int id_salon, materias* Materias, maestros* Maestros, salones* Salones, Horario* horarios_grupos, Horario* horarios_maestros, Horario* horarios_salones, bool strict_availability){
    int id_materia = nodo_actual->id_materia;
    int id_maestro = nodo_actual->id_maestro;
    int id_grupo = nodo_actual->id_grupo;
    
    materia* mat = Materias->getMateria(id_materia);
    maestro* mae = Maestros->getMaestro(id_maestro);
    salon* sal = Salones->getSalon(id_salon);
    
    if(!mat || !mae || !sal) return false;
    const char* salon_especial = mat->getSalonEspecial();
    bool requiere_salon_especifico = true;
    if(strcasecmp(salon_especial, "ninguna") == 0 || strcasecmp(salon_especial, "ninguno") == 0){
        requiere_salon_especifico = false;
    }
    
    if(requiere_salon_especifico){
        if(strcmp(sal->getTipo(), salon_especial) != 0){
            return false;
        }
    }
    if(horarios_grupos[id_grupo].estaOcupado(dia, franja)){
        return false;
    }
    if(horarios_maestros[id_maestro].estaOcupado(dia, franja)){
        return false;
    }
    if(horarios_salones[id_salon].estaOcupado(dia, franja)){
        return false;
    }
    if(strict_availability){
        if(!mae->getHorarioDisponibilidad().isDisponible(dia, franja)){
            return false;
        }
    } else {
        if(mae->getHorarioDisponibilidad().estaOcupado(dia, franja)){
            return false;
        }
    }
    
    return true;
}

bool maestro_ya_asignado_en_grupo(int id_grupo, int id_maestro, Horario* horarios_grupos){
    for(int d = 0; d < Horario::getNumDias(); d++){
        for(int f = 0; f < Horario::getNumFranjas(); f++){
            CeldaHorario* celda = horarios_grupos[id_grupo].getCelda(d, f);
            if(celda && celda->ocupado && celda->id_maestro == id_maestro){
                return true;
            }
        }
    }
    return false;
}

void desasignar_materia(nodo* nodo_actual, Horario* horarios_grupos, Horario* horarios_maestros, Horario* horarios_salones){
    for(int i = 0; i < nodo_actual->horas_asignadas_cnt; i++){
        int d = nodo_actual->asignaciones_realizadas[i].dia;
        int f = nodo_actual->asignaciones_realizadas[i].franja;
        int s = nodo_actual->asignaciones_realizadas[i].id_salon;
        
        horarios_grupos[nodo_actual->id_grupo].liberarCelda(d, f);
        horarios_maestros[nodo_actual->id_maestro].liberarCelda(d, f);
        horarios_salones[s].liberarCelda(d, f);
    }
    nodo_actual->horas_asignadas_cnt = 0;
    nodo_actual->id_salon = -1;
}

bool asignar_materia_a_horario(nodo* nodo_actual, int id_salon_forzado, materias* Materias, maestros* Maestros, salones* Salones, grupos* Grupos, Horario* horarios_grupos, Horario* horarios_maestros, Horario* horarios_salones, bool strict_horizontal, bool strict_availability){
    int id_materia = nodo_actual->id_materia;
    int id_maestro = nodo_actual->id_maestro;
    int id_grupo = nodo_actual->id_grupo;
    
    materia* mat = Materias->getMateria(id_materia);
    if(!mat) return false;
    
    int horas_necesarias = mat->getHorasNecesarias();
    nodo_actual->horas_asignadas_cnt = 0;
    
    const char* salon_especial = mat->getSalonEspecial();
    bool requiere_salon_especifico = true;
    if(strcasecmp(salon_especial, "ninguna") == 0 || strcasecmp(salon_especial, "ninguno") == 0){
        requiere_salon_especifico = false;
    }

    int inicio_s = 0;
    int fin_s = Salones->getCantidad();
    
    if(id_salon_forzado != -1){
        inicio_s = id_salon_forzado;
        fin_s = id_salon_forzado + 1;
    }
    
    // Obtener franja de inicio del grupo
    int franja_inicio_grupo = 0;
    if(Grupos && id_grupo >= 0 && id_grupo < Grupos->getCantidad()){
        grupo* g = Grupos->getGrupo(id_grupo);
        if(g) franja_inicio_grupo = g->getFranjaInicio();
    }

    int max_franjas = Horario::getNumFranjas();
    int num_dias = Horario::getNumDias();
    
    // ITERAR PRIMERO POR FRANJA (TIEMPO) PARA PRIORIZAR HORAS TEMPRANAS
    for(int franja_base = franja_inicio_grupo; franja_base < max_franjas; franja_base++){
        
        // LUEGO ITERAR POR SALONES
        for(int s = inicio_s; s < fin_s; s++){
            salon* sal = Salones->getSalon(s);
            if(id_salon_forzado == -1 && requiere_salon_especifico){
                if(strcmp(sal->getTipo(), salon_especial) != 0){
                    continue; // No es compatible
                }
            }
            
            nodo_actual->id_salon = s;
            
            if(strict_horizontal){
                if(horas_necesarias <= 5){
                    // Verificar si en esta franja_base hay suficientes días
                    int dias_disponibles = 0;
                    for(int dia = 0; dia < num_dias; dia++){
                        if(validar_asignacion(nodo_actual, dia, franja_base, s, Materias, Maestros, Salones, horarios_grupos, horarios_maestros, horarios_salones, strict_availability)){
                            dias_disponibles++;
                        }
                    }
                    
                    if(dias_disponibles >= horas_necesarias){
                        int asignadas = 0;
                        for(int dia = 0; dia < num_dias && asignadas < horas_necesarias; dia++){
                            if(validar_asignacion(nodo_actual, dia, franja_base, s, Materias, Maestros, Salones, horarios_grupos, horarios_maestros, horarios_salones, strict_availability)){
                                horarios_grupos[id_grupo].asignarClase(dia, franja_base, id_materia, id_maestro, s, id_grupo);
                                horarios_maestros[id_maestro].asignarClase(dia, franja_base, id_materia, id_grupo, s, id_grupo);
                                horarios_salones[s].asignarClase(dia, franja_base, id_materia, id_maestro, id_grupo, id_grupo);
                                
                                nodo_actual->asignaciones_realizadas[asignadas].dia = dia;
                                nodo_actual->asignaciones_realizadas[asignadas].franja = franja_base;
                                nodo_actual->asignaciones_realizadas[asignadas].id_salon = s;
                                asignadas++;
                            }
                        }
                        nodo_actual->horas_asignadas_cnt = asignadas;
                        return true; // Éxito
                    }
                } else {
                    // Lógica para > 5 horas (horizontal forzado)
                    // Requiere franja_base completa (5 dias) y resto en franja_base + 1
                    if(franja_base < max_franjas - 1){
                        int dias_f1 = 0;
                        for(int dia = 0; dia < num_dias; dia++){
                            if(validar_asignacion(nodo_actual, dia, franja_base, s, Materias, Maestros, Salones, horarios_grupos, horarios_maestros, horarios_salones, strict_availability)){
                                dias_f1++;
                            }
                        }
                        
                        if(dias_f1 == 5){
                            int resto = horas_necesarias - 5;
                            int dias_f2 = 0;
                            for(int dia = 0; dia < num_dias; dia++){
                                if(validar_asignacion(nodo_actual, dia, franja_base + 1, s, Materias, Maestros, Salones, horarios_grupos, horarios_maestros, horarios_salones, strict_availability)){
                                    dias_f2++;
                                }
                            }
                            
                            if(dias_f2 >= resto){
                                int asignadas = 0;
                                // Asignar franja 1
                                for(int dia = 0; dia < num_dias; dia++){
                                    horarios_grupos[id_grupo].asignarClase(dia, franja_base, id_materia, id_maestro, s, id_grupo);
                                    horarios_maestros[id_maestro].asignarClase(dia, franja_base, id_materia, id_grupo, s, id_grupo);
                                    horarios_salones[s].asignarClase(dia, franja_base, id_materia, id_maestro, id_grupo, id_grupo);
                                    
                                    nodo_actual->asignaciones_realizadas[asignadas].dia = dia;
                                    nodo_actual->asignaciones_realizadas[asignadas].franja = franja_base;
                                    nodo_actual->asignaciones_realizadas[asignadas].id_salon = s;
                                    asignadas++;
                                }
                                
                                // Asignar resto en franja 2
                                for(int dia = 0; dia < num_dias && asignadas < horas_necesarias; dia++){
                                    if(validar_asignacion(nodo_actual, dia, franja_base + 1, s, Materias, Maestros, Salones, horarios_grupos, horarios_maestros, horarios_salones, strict_availability)){
                                        horarios_grupos[id_grupo].asignarClase(dia, franja_base + 1, id_materia, id_maestro, s, id_grupo);
                                        horarios_maestros[id_maestro].asignarClase(dia, franja_base + 1, id_materia, id_grupo, s, id_grupo);
                                        horarios_salones[s].asignarClase(dia, franja_base + 1, id_materia, id_maestro, id_grupo, id_grupo);
                                        
                                        nodo_actual->asignaciones_realizadas[asignadas].dia = dia;
                                        nodo_actual->asignaciones_realizadas[asignadas].franja = franja_base + 1;
                                        nodo_actual->asignaciones_realizadas[asignadas].id_salon = s;
                                        asignadas++;
                                    }
                                }
                                nodo_actual->horas_asignadas_cnt = asignadas;
                                return true;
                            }
                        }
                    }
                }
            } else {
                int horas_asignadas = 0;
                // Verificar primero si la franja_base tiene AL MENOS una hora disponible (para asegurar que empezamos ahí)
                bool empieza_en_base = false;
                for(int dia = 0; dia < num_dias; dia++){
                     if(validar_asignacion(nodo_actual, dia, franja_base, s, Materias, Maestros, Salones, horarios_grupos, horarios_maestros, horarios_salones, strict_availability)){
                         empieza_en_base = true;
                         break;
                     }
                }
                
                if(empieza_en_base){
                    for(int f = franja_base; f < max_franjas && horas_asignadas < horas_necesarias; f++){
                        for(int d = 0; d < num_dias && horas_asignadas < horas_necesarias; d++){
                            if(validar_asignacion(nodo_actual, d, f, s, Materias, Maestros, Salones, horarios_grupos, horarios_maestros, horarios_salones, strict_availability)){
                                // Asignar
                                horarios_grupos[id_grupo].asignarClase(d, f, id_materia, id_maestro, s, id_grupo);
                                horarios_maestros[id_maestro].asignarClase(d, f, id_materia, id_grupo, s, id_grupo);
                                horarios_salones[s].asignarClase(d, f, id_materia, id_maestro, id_grupo, id_grupo);
                                
                                nodo_actual->asignaciones_realizadas[horas_asignadas].dia = d;
                                nodo_actual->asignaciones_realizadas[horas_asignadas].franja = f;
                                nodo_actual->asignaciones_realizadas[horas_asignadas].id_salon = s;
                                horas_asignadas++;
                            }
                        }
                    }
                    
                    nodo_actual->horas_asignadas_cnt = horas_asignadas;
                    
                    if(horas_asignadas == horas_necesarias){
                        return true; // Éxito
                    } else {
                        // Falló, desasignar todo
                        desasignar_materia(nodo_actual, horarios_grupos, horarios_maestros, horarios_salones);
                    }
                }
            }
        }
    }
    
    if(id_salon_forzado == -1 && Salones->getCantidad() > 0){
        bool existe_compatible = false;
        for(int s=0; s<Salones->getCantidad(); s++){
             if(strcasecmp(Salones->getSalon(s)->getTipo(), salon_especial) == 0) existe_compatible = true;
        }
        
        if(requiere_salon_especifico && !existe_compatible){
             std::cout << "  No se encontró salón del tipo " << salon_especial << ", intentando con salón por defecto (0)" << std::endl;
             return asignar_materia_a_horario(nodo_actual, 0, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, strict_horizontal, strict_availability);
        }
    }
    
    return false;
}

nodo* encontrar_nodo_por_grupo_materia(nodo* inicio, nodo* limite, int id_grupo_buscar, int id_materia_buscar){
    nodo* actual = inicio;
    while(actual != nullptr && actual != limite){
        if(actual->id_grupo == id_grupo_buscar && actual->id_materia == id_materia_buscar){
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool resolver_horario_recursivo(nodo* nodo_actual, int id_grupo, materias* Materias, maestros* Maestros, salones* Salones, grupos* Grupos, Horario* horarios_grupos, Horario* horarios_maestros, Horario* horarios_salones, int profundidad, int* intentos_fallidos){
    // Límite de profundidad para evitar bucles infinitos
    const int MAX_PROFUNDIDAD = 10000;
    if(profundidad > MAX_PROFUNDIDAD){
        std::cout << "   [Backtracking] Límite de profundidad alcanzado (" << MAX_PROFUNDIDAD << "), abortando..." << std::endl;
        return false;
    }

    const int MAX_INTENTOS = 20000; 
    if(intentos_fallidos && *intentos_fallidos > MAX_INTENTOS){
        if(*intentos_fallidos == MAX_INTENTOS + 1){
             std::cout << "\n   [Backtracking] Límite de intentos totales alcanzado (" << MAX_INTENTOS << "), abortando..." << std::endl;
             (*intentos_fallidos)++; // Para no imprimir más veces
        }
        return false;
    }
    
    // Caso base: si no hay más nodos, hemos terminado exitosamente
    if(nodo_actual == nullptr){
        return true;
    }
    
    // Si id_grupo es -1, estamos en modo global: usar el id_grupo del nodo
    int grupo_actual = (id_grupo == -1) ? nodo_actual->id_grupo : id_grupo;
    
    materia* mat = Materias->getMateria(nodo_actual->id_materia);
    if(!mat) return resolver_horario_recursivo(nodo_actual->siguiente, id_grupo, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, profundidad + 1, intentos_fallidos);

    std::cout << "  [Backtracking] Procesando: " << mat->getNombre() << " (Grupo " << grupo_actual << ", Prof: " << profundidad << ")" << std::endl;
    
    int maestro_original = nodo_actual->id_maestro;

    int* todos_maestros = new int[Maestros->getCantidad()];
    int num_todos_maestros = 0;
    
    for(int i = 0; i < Maestros->getCantidad(); i++){
        maestro* mae = Maestros->getMaestro(i);
        
        // Verificar si imparte la materia
        bool imparte = false;
        for(int k = 0; k < mae->getCantidadMaterias(); k++){
            if(mae->getIdMateria(k) == nodo_actual->id_materia){
                imparte = true;
                break;
            }
        }
        
        if(imparte){
            todos_maestros[num_todos_maestros++] = mae->getId();
        }
    }
    
    // 2. Separar en candidatos disponibles y ocupados
    int* candidatos_disponibles = new int[num_todos_maestros];
    int* candidatos_ocupados = new int[num_todos_maestros];
    int num_disponibles = 0;
    int num_ocupados = 0;
    
// Función auxiliar para calcular intersección de disponibilidad
    auto calcular_interseccion_disponibilidad = [&](int id_maestro, int id_grupo, int horas_necesarias) -> int {
        int interseccion = 0;
        maestro* m = Maestros->getMaestro(id_maestro);
        for(int d = 0; d < Horario::getNumDias(); d++){
            for(int f = 0; f < Horario::getNumFranjas(); f++){
                // 1. El maestro debe estar disponible (preferencia)
                if(!m->getHorarioDisponibilidad().isDisponible(d, f)) continue;
                
                // 2. El maestro no debe estar ocupado ya
                if(horarios_maestros[id_maestro].estaOcupado(d, f)) continue;
                
                // 3. El grupo no debe estar ocupado ya
                if(horarios_grupos[id_grupo].estaOcupado(d, f)) continue;
                
                interseccion++;
            }
        }
        return interseccion;
    };

    for(int i = 0; i < num_todos_maestros; i++){
        int id_mae = todos_maestros[i];
        
        // verificacion estricta de disponibilidad
        // Si el maestro no tiene suficientes horas disponibles que coincidan con los huecos del grupo,
        // no lo consideramos ni siquiera como candidato.
        int horas_posibles = calcular_interseccion_disponibilidad(id_mae, grupo_actual, mat->getHorasNecesarias());
        
        if(horas_posibles < mat->getHorasNecesarias()){
             std::cout << "    [Filtro] Maestro " << Maestros->getMaestro(id_mae)->getNombre() 
                       << " descartado. Intersección (" << horas_posibles 
                       << ") < Necesarias (" << mat->getHorasNecesarias() << ")" << std::endl;
             continue;
        }

        if(maestro_ya_asignado_en_grupo(grupo_actual, id_mae, horarios_grupos)){
            // Ya está en este grupo, no podemos usarlo
            continue;
        } else {
            // Verificar si está ocupado en OTRO grupo
            bool ocupado_otro_grupo = false;
            int num_grupos = Grupos->getCantidad();
            for(int g = 0; g < num_grupos; g++){
                if(g != grupo_actual && maestro_ya_asignado_en_grupo(g, id_mae, horarios_grupos)){
                    ocupado_otro_grupo = true;
                    break;
                }
            }
            
            if(ocupado_otro_grupo){
                candidatos_ocupados[num_ocupados++] = id_mae;
            } else {
                candidatos_disponibles[num_disponibles++] = id_mae;
            }
        }
    }
    
    std::cout << "    Maestros disponibles: " << num_disponibles << ", ocupados en otros grupos: " << num_ocupados << std::endl;
    
    // Si no hay ningún maestro (ni disponible ni ocupado), retornar false
    if(num_disponibles == 0 && num_ocupados == 0){
        std::cout << "   [Backtracking] No hay maestros para: " << mat->getNombre() << " - FORZANDO BACKTRACKING..." << std::endl;
        delete[] todos_maestros;
        delete[] candidatos_disponibles;
        delete[] candidatos_ocupados;
        return false;
    }
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(candidatos_disponibles, candidatos_disponibles + num_disponibles, std::default_random_engine(seed));
    
    for(int i = 0; i < num_disponibles; i++){
        int id_maestro_candidato = candidatos_disponibles[i];
        maestro* mae = Maestros->getMaestro(id_maestro_candidato);
        nodo_actual->id_maestro = mae->getId();
        
        // Intentar modo estricto (availability=true)
        if(asignar_materia_a_horario(nodo_actual, -1, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, true, true)){
            if(resolver_horario_recursivo(nodo_actual->siguiente, id_grupo, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, profundidad + 1, intentos_fallidos)){
                delete[] todos_maestros;
                delete[] candidatos_disponibles;
                delete[] candidatos_ocupados;
                return true;
            }
            desasignar_materia(nodo_actual, horarios_grupos, horarios_maestros, horarios_salones);
        }
        
        // Intentar modo relajado (availability=true)
        if(asignar_materia_a_horario(nodo_actual, -1, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, false, true)){
            if(resolver_horario_recursivo(nodo_actual->siguiente, id_grupo, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, profundidad + 1, intentos_fallidos)){
                delete[] todos_maestros;
                delete[] candidatos_disponibles;
                delete[] candidatos_ocupados;
                return true;
            }
            desasignar_materia(nodo_actual, horarios_grupos, horarios_maestros, horarios_salones);
        }
    }
    for(int i = 0; i < num_disponibles; i++){
        int id_maestro_candidato = candidatos_disponibles[i];
        maestro* mae = Maestros->getMaestro(id_maestro_candidato);
        nodo_actual->id_maestro = mae->getId();
        if(asignar_materia_a_horario(nodo_actual, -1, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, true, false)){
            if(resolver_horario_recursivo(nodo_actual->siguiente, id_grupo, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, profundidad + 1, intentos_fallidos)){
                delete[] todos_maestros;
                delete[] candidatos_disponibles;
                delete[] candidatos_ocupados;
                return true;
            }
            desasignar_materia(nodo_actual, horarios_grupos, horarios_maestros, horarios_salones);
        }
        if(asignar_materia_a_horario(nodo_actual, -1, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, false, false)){
            if(resolver_horario_recursivo(nodo_actual->siguiente, id_grupo, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, profundidad + 1, intentos_fallidos)){
                delete[] todos_maestros;
                delete[] candidatos_disponibles;
                delete[] candidatos_ocupados;
                return true;
            }
            desasignar_materia(nodo_actual, horarios_grupos, horarios_maestros, horarios_salones);
        }
    }
    if(num_disponibles == 0 && num_ocupados > 0){
        std::cout << "  🔄 [Backtracking Inteligente] No hay maestros disponibles, intentando con ocupados (" << num_ocupados << ") para: " << mat->getNombre() << std::endl;
        
        std::shuffle(candidatos_ocupados, candidatos_ocupados + num_ocupados, std::default_random_engine(seed));
        
        for(int i = 0; i < num_ocupados; i++){
            int id_maestro_candidato = candidatos_ocupados[i];
            maestro* mae = Maestros->getMaestro(id_maestro_candidato);
            nodo_actual->id_maestro = mae->getId();
            
            // Intentar modo estricto (availability=true)
            if(asignar_materia_a_horario(nodo_actual, -1, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, true, true)){
                if(resolver_horario_recursivo(nodo_actual->siguiente, id_grupo, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, profundidad + 1, intentos_fallidos)){
                    delete[] todos_maestros;
                    delete[] candidatos_disponibles;
                    delete[] candidatos_ocupados;
                    return true;
                }
                desasignar_materia(nodo_actual, horarios_grupos, horarios_maestros, horarios_salones);
            }
            
            // Intentar modo relajado (availability=true)
            if(asignar_materia_a_horario(nodo_actual, -1, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, false, true)){
                if(resolver_horario_recursivo(nodo_actual->siguiente, id_grupo, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, profundidad + 1, intentos_fallidos)){
                    delete[] todos_maestros;
                    delete[] candidatos_disponibles;
                    delete[] candidatos_ocupados;
                    return true;
                }
                desasignar_materia(nodo_actual, horarios_grupos, horarios_maestros, horarios_salones);
            }
        }
        
        // Fallback para ocupados también (availability=false)
        for(int i = 0; i < num_ocupados; i++){
            int id_maestro_candidato = candidatos_ocupados[i];
            maestro* mae = Maestros->getMaestro(id_maestro_candidato);
            nodo_actual->id_maestro = mae->getId();
            
            if(asignar_materia_a_horario(nodo_actual, -1, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, true, false)){
                if(resolver_horario_recursivo(nodo_actual->siguiente, id_grupo, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, profundidad + 1, intentos_fallidos)){
                    delete[] todos_maestros;
                    delete[] candidatos_disponibles;
                    delete[] candidatos_ocupados;
                    return true;
                }
                desasignar_materia(nodo_actual, horarios_grupos, horarios_maestros, horarios_salones);
            }
            
            if(asignar_materia_a_horario(nodo_actual, -1, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, false, false)){
                if(resolver_horario_recursivo(nodo_actual->siguiente, id_grupo, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, profundidad + 1, intentos_fallidos)){
                    delete[] todos_maestros;
                    delete[] candidatos_disponibles;
                    delete[] candidatos_ocupados;
                    return true;
                }
                desasignar_materia(nodo_actual, horarios_grupos, horarios_maestros, horarios_salones);
            }
        }
        
        std::cout << "  [Backtracking] No se pudo asignar con maestros ocupados: " << mat->getNombre() << std::endl;
    }
    
    std::cout << "  [Backtracking] No se pudo asignar: " << mat->getNombre() << " (Disponibles: " << num_disponibles << ", Ocupados: " << num_ocupados << ")" << std::endl;
    
    delete[] todos_maestros;
    delete[] candidatos_disponibles;
    delete[] candidatos_ocupados;
    nodo_actual->id_maestro = maestro_original;
    
    if(intentos_fallidos) (*intentos_fallidos)++;
    return false; 
}


void ejecutar_universal_timetabling_grupo(lista* lista_grupo, int id_grupo, materias* Materias, maestros* Maestros, salones* Salones, grupos* Grupos, Horario* horarios_grupos, Horario* horarios_maestros, Horario* horarios_salones){
    std::cout << "\n=== Ejecutando Universal TimeTabling para grupo (BACKTRACKING) ===" << std::endl;
    
    int intentos_fallidos = 0;
    if(resolver_horario_recursivo(lista_grupo->inicio, id_grupo, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, 0, &intentos_fallidos)){
        std::cout << "  Asignación exitosa para el grupo " << id_grupo << std::endl;
    } else {
        std::cout << "  No se pudo encontrar una solución completa para el grupo " << id_grupo << std::endl;
    }
}

lista* crear_lista_global_priorizada(lista_de_listas* listas){
    std::cout << "\n--- Creando lista global priorizada ---" << std::endl;
    
    // Crear nueva lista global
    lista* lista_global = new lista;
    lista_global->inicio = nullptr;
    lista_global->fin = nullptr;
    lista_global->cant = 0;
    
    // Recorrer todas las listas de grupos
    for(int i = 0; i < listas->cantidad_grupos; i++){
        lista* lista_grupo = listas->listas_grupos[i];
        nodo* actual = lista_grupo->inicio;
        
        std::cout << "  Procesando grupo " << i << " (" << lista_grupo->cant << " nodos)" << std::endl;
        while(actual != nullptr){
        
        // Recorrer todos los nodos de este grupo
            // Crear una COPIA del nodo para la lista global
            nodo* nodo_copia = new nodo;
            nodo_copia->prioridad = actual->prioridad;
            nodo_copia->id_materia = actual->id_materia;
            nodo_copia->id_grupo = actual->id_grupo;
            nodo_copia->id_salon = actual->id_salon;
            nodo_copia->id_maestro = actual->id_maestro;
            nodo_copia->horas_asignadas_cnt = 0;
            nodo_copia->siguiente = nullptr;
            nodo_copia->anterior = nullptr;
            
            // Agregar a la lista global ordenadamente
            agregar_nodo_ordenado(nodo_copia, lista_global);
            
            actual = actual->siguiente;
        }
    }
    
    std::cout << " Lista global creada con " << lista_global->cant << " nodos totales" << std::endl;
    
    return lista_global;
}


bool ejecutar_universal_timetabling_global(lista* lista_global, materias* Materias, maestros* Maestros, salones* Salones, grupos* Grupos, Horario* horarios_grupos, Horario* horarios_maestros, Horario* horarios_salones){
    std::cout << "\n=== Ejecutando Universal TimeTabling GLOBAL (BACKTRACKING) ===" << std::endl;
    std::cout << "  Total de materias a asignar: " << lista_global->cant << std::endl;
    
    int intentos_fallidos = 0;
    if(resolver_horario_recursivo(lista_global->inicio, -1, Materias, Maestros, Salones, Grupos, horarios_grupos, horarios_maestros, horarios_salones, 0, &intentos_fallidos)){
        std::cout << "\n Asignación global exitosa para todos los grupos" << std::endl;
        return true;
    } else {
        std::cout << "\n  No se pudo encontrar una solución global completa" << std::endl;
        return false;
    }
}

