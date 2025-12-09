#include "../include/grupos.h"
#include "../include/horario.h"
#include "../include/modificaciones_objetos.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

grupos::grupos(ConjuntoMaterias* cm_obj) {
    cant = 0;
    cant_max = 10;
    lista_grupos = new grupo*[cant_max];
    
    string archivo = "../src/csv/grupos.csv";
    ifstream file(archivo.c_str());
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
        return;
    }
    
    string line;
    grupo* g = nullptr;
    int objetoContador = 0;
    
    while (getline(file, line)) {
        int start = 0;
        while (start < (int)line.length() && (line[start] == ' ' || line[start] == '\t' || line[start] == '\r' || line[start] == '\n')) {
            start++;
        }
        
        int end = (int)line.length() - 1;
        while (end >= 0 && (line[end] == ' ' || line[end] == '\t' || line[end] == '\r' || line[end] == '\n')) {
            end--;
        }
        
        if (start > end) continue;
        
        line = line.substr(start, end - start + 1);
        
        if (line[0] == '#') continue;
        
        if ((int)line.find('{') != -1) {
            g = new grupo();
            g->setId(objetoContador);
            objetoContador++;
        }
        else if ((int)line.find("nombre:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && g != nullptr) {
                string valor = line.substr(pos + 1);
                int v_start = 0;
                while (v_start < (int)valor.length() && (valor[v_start] == ' ' || valor[v_start] == '\t')) {
                    v_start++;
                }
                int v_end = (int)valor.length() - 1;
                while (v_end >= 0 && (valor[v_end] == ' ' || valor[v_end] == '\t' || valor[v_end] == ';')) {
                    v_end--;
                }

                if (v_start <= v_end) {
                    valor = valor.substr(v_start, v_end - v_start + 1);
                    g->setNombre(valor.c_str());
                }
            }
        }
        else if ((int)line.find("horario:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && g != nullptr) {
                string valor = line.substr(pos + 1);
                
                // Trim valor
                int v_start = 0;
                while (v_start < (int)valor.length() && (valor[v_start] == ' ' || valor[v_start] == '\t')) {
                    v_start++;
                }
                int v_end = (int)valor.length() - 1;
                while (v_end >= 0 && (valor[v_end] == ' ' || valor[v_end] == '\t' || valor[v_end] == ';')) {
                    v_end--;
                }

                if (v_start <= v_end) {
                    valor = valor.substr(v_start, v_end - v_start + 1);
                    
                    // Parsear rango (ej: 7:00-13:55)
                    int guion = (int)valor.find('-');
                    if (guion != -1) {
                        string inicio_str = valor.substr(0, guion);
                        string fin_str = valor.substr(guion + 1);
                        
                        int f_inicio = Horario::getFranjaInicio(inicio_str.c_str());
                        int f_fin = Horario::getFranjaFin(fin_str.c_str());
                        
                        if (f_inicio != -1 && f_fin != -1) {
                            g->setFranjaInicio(f_inicio);
                            g->setFranjaFin(f_fin);
                        } else {
                            cout << "Advertencia: Horario invalido '" << valor << "' para grupo " << g->getNombre() << endl;
                        }
                    }
                }
            }
        }
        else if ((int)line.find("conjunto de materias:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && g != nullptr) {
                string valor = line.substr(pos + 1);
                int v_start = 0;
                while (v_start < (int)valor.length() && (valor[v_start] == ' ' || valor[v_start] == '\t')) {
                    v_start++;
                }
                int v_end = (int)valor.length() - 1;
                while (v_end >= 0 && (valor[v_end] == ' ' || valor[v_end] == '\t' || valor[v_end] == ';')) {
                    v_end--;
                }

                if (v_start <= v_end) {
                    valor = valor.substr(v_start, v_end - v_start + 1);
                    if (cm_obj != nullptr) {
                         int setId = cm_obj->getIdSet(valor);
                         if (setId != -1) {
                             g->setConjuntoDeMaterias(setId);
                         } else {
                             cout << "Advertencia: Conjunto de materias '" << valor << "' no encontrado para grupo " << g->getNombre() << endl;
                         }
                    }
                }
            }
        }
        else if ((int)line.find("color:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && g != nullptr) {
                string valor = line.substr(pos + 1);
                int v_start = 0;
                while (v_start < (int)valor.length() && (valor[v_start] == ' ' || valor[v_start] == '\t')) {
                    v_start++;
                }
                int v_end = (int)valor.length() - 1;
                while (v_end >= 0 && (valor[v_end] == ' ' || valor[v_end] == '\t' || valor[v_end] == ';')) {
                    v_end--;
                }

                if (v_start <= v_end) {
                    valor = valor.substr(v_start, v_end - v_start + 1);
                    g->setColor(valor.c_str());
                }
            }
        }
        else if ((int)line.find('}') != -1) {
            if (g != nullptr) {
                addGrupo(g);
                g = nullptr;
            }
        }
    }
    
    file.close();
    cout << "Se cargaron " << cant << " grupos desde el archivo CSV." << endl;
}

grupos::~grupos() {
    for (int i = 0; i < cant; i++) {
        delete lista_grupos[i];
    }
    delete[] lista_grupos;
}

void grupos::addGrupo(grupo* g) {
    if (cant >= cant_max) {
        resize();
    }
    lista_grupos[cant] = g;
    cant++;
}

void grupos::resize() {
    cant_max *= 2;
    grupo** nuevo_array = new grupo*[cant_max];
    
    for (int i = 0; i < cant; i++) {
        nuevo_array[i] = lista_grupos[i];
    }
    
    delete[] lista_grupos;
    lista_grupos = nuevo_array;
}

grupo* grupos::getGrupo(int index) const {
    if (index >= 0 && index < cant) {
        return lista_grupos[index];
    }
    return nullptr;
}

void grupos::setColor(const char* c) {
    // Not used directly
}

const char* grupos::getColor() const {
    return "";
}

void grupos::mostrarDetalle(int id, ConjuntoMaterias* conjuntos) const {
    bool encontrado = false;
    for(int i=0; i<cant; i++) {
        grupo* g = lista_grupos[i];
        if(g && g->getId() == id) {
            cout << "\n--- DETALLE DE GRUPO ---" << endl;
            cout << "ID: " << g->getId() << endl;
            cout << "Nombre: " << g->getNombre() << endl;
            int setId = g->getConjuntoDeMaterias();
            Set* s = conjuntos->getSet(setId);
            cout << "Conjunto de Materias: " << (s ? s->nombre : "Ninguno") << endl;
            cout << "Horario preferente: " << Horario::getInicioFranja(g->getFranjaInicio()) 
                      << " - " << Horario::getFinFranja(g->getFranjaFin()) << endl;
            encontrado = true;
            break;
        }
    }
    if(!encontrado) cout << "Grupo no encontrado con ID: " << id << endl;
}

void grupos::mostrarGrupos() const {
    cout << "\n=== LISTADO DE GRUPOS ===" << endl;
    cout << "Total: " << cant << " grupos\n" << endl;
    
    for (int i = 0; i < cant; i++) {
        grupo* g = lista_grupos[i];
        cout << "ID: " << g->getId() << " - Nombre: " << g->getNombre() << endl;
    }
    cout << "---" << endl;
}

void grupos::modificar(int id, const char* instrucciones, ConjuntoMaterias* cm_obj) {
    grupo* g = nullptr;
    for (int i = 0; i < cant; i++) {
        if (lista_grupos[i]->getId() == id) {
            g = lista_grupos[i];
            break;
        }
    }

    if (!g) {
        cout << "Error: Grupo con ID " << id << " no encontrado." << endl;
        return;
    }

    char buffer[256];

    if (Modificador::obtenerValor(instrucciones, "nombre", buffer, 256)) {
        g->setNombre(buffer);
        cout << "Nombre actualizado." << endl;
    }

    if (Modificador::obtenerValor(instrucciones, "horario", buffer, 256)) {
        char* guion = strchr(buffer, '-');
        if (guion != nullptr) {
            *guion = '\0'; // Split string
            char* inicio_str = buffer;
            char* fin_str = guion + 1;
            
            int f_inicio = Horario::getFranjaInicio(inicio_str);
            int f_fin = Horario::getFranjaFin(fin_str);
            
            if (f_inicio != -1 && f_fin != -1) {
                g->setFranjaInicio(f_inicio);
                g->setFranjaFin(f_fin);
                cout << "Horario actualizado." << endl;
            } else {
                cout << "Error: Horario invalido." << endl;
            }
        }
    }

    if (Modificador::obtenerValor(instrucciones, "conjunto", buffer, 256)) {
        if (cm_obj != nullptr) {
             int setId = cm_obj->getIdSet(buffer);
             if (setId != -1) {
                 g->setConjuntoDeMaterias(setId);
                 cout << "Conjunto de materias actualizado." << endl;
             } else {
                 cout << "Error: Conjunto de materias '" << buffer << "' no encontrado." << endl;
             }
        }
    }

    if (Modificador::obtenerValor(instrucciones, "color", buffer, 256)) {
        g->setColor(buffer);
        cout << "Color actualizado." << endl;
    }
}


void grupos::eliminar(int id) {
    int index = -1;
    for (int i = 0; i < cant; i++) {
        if (lista_grupos[i]->getId() == id) {
            index = i;
            break;
        }
    }
    
    if (index != -1) {
        delete lista_grupos[index];
        for (int i = index; i < cant - 1; i++) {
            lista_grupos[i] = lista_grupos[i + 1];
        }
        cant--;
        cout << "Grupo eliminado con ID: " << id << endl;
    } else {
        cout << "Error: Grupo con ID " << id << " no encontrado para eliminar." << endl;
    }
}

void grupos::guardarCSV(ConjuntoMaterias* cm_obj) {
    string archivo = "../src/csv/grupos.csv";
    ofstream file(archivo.c_str());
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << " para escritura" << endl;
        return;
    }
    
    for (int i = 0; i < cant; i++) {
        grupo* g = lista_grupos[i];
        if (!g) continue;
        
        file << "{" << endl;
        file << "    nombre:" << g->getNombre() << ";" << endl;
        
        // Escribir horario
        string horaInicio = Horario::getInicioFranja(g->getFranjaInicio());
        string horaFin = Horario::getFinFranja(g->getFranjaFin());
        file << "    horario:" << horaInicio << "-" << horaFin << ";" << endl;
        
        // Escribir conjunto de materias
        int setId = g->getConjuntoDeMaterias();
        if (cm_obj && setId >= 0 && setId < cm_obj->getCantidad()) {
            Set* s = cm_obj->getSet(setId);
            if (s) {
                file << "    conjunto de materias:" << s->nombre << ";" << endl;
            }
        }
        
        // Escribir color
        file << "    color: " << g->getColor() << ";" << endl;
        file << "}" << endl;
    }
    
    file.close();
    cout << "Cambios guardados en " << archivo << endl;
}
