#include "../include/maestros.h"
#include "../include/modificaciones_objetos.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

maestros::maestros(materias* lista_materias_obj) {
    cant = 0;
    cant_max = 10;
    lista_maestros = new maestro*[cant_max];
    
    string archivo = "../src/csv/maestros.csv";
    ifstream file(archivo.c_str());
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
        return;
    }
    
    string line;
    maestro* m = nullptr;
    int objetoContador = 0;
    int cant_materias_temp = 0;
    
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
            m = new maestro();
            m->setId(objetoContador);
            objetoContador++;
        }
        else if ((int)line.find("nombre:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && m != nullptr) {
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
                    m->setNombre(valor.c_str());
                }
            }
        }
        else if ((int)line.find("materias:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && m != nullptr) {
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
                    stringstream ss(valor);
                    string materia_nombre;
                    
                    while (getline(ss, materia_nombre, ',')) {
                        int m_start = 0;
                        while (m_start < (int)materia_nombre.length() && (materia_nombre[m_start] == ' ' || materia_nombre[m_start] == '\t')) {
                            m_start++;
                        }
                        int m_end = (int)materia_nombre.length() - 1;
                        while (m_end >= 0 && (materia_nombre[m_end] == ' ' || materia_nombre[m_end] == '\t')) {
                            m_end--;
                        }
                        
                        if (m_start <= m_end) {
                            materia_nombre = materia_nombre.substr(m_start, m_end - m_start + 1);
                            
                            int id_real = -1;
                            if (lista_materias_obj != nullptr) {
                                id_real = lista_materias_obj->getIdPorNombre(materia_nombre.c_str());
                            }
                            
                            if (id_real != -1) {
                                m->addIdMateria(id_real);
                            } else {
                                if (lista_materias_obj != nullptr) {
                                     cout << "Advertencia: Materia '" << materia_nombre << "' no encontrada para maestro " << m->getNombre() << endl;
                                }
                                m->addIdMateria(cant_materias_temp++); 
                            }
                        }
                    }
                }
            }
        }
        else if ((int)line.find("color:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && m != nullptr) {
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
                    m->setColor(valor.c_str());
                }
            }
        }
        else if ((int)line.find("horario:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && m != nullptr) {
                string valor = line.substr(pos + 1);
                
                // Check if it starts with '('
                size_t start_paren = valor.find('(');
                if (start_paren != string::npos) {
                    // Complex format: (Lunes:...)
                    // Find closing ')'
                    size_t end_paren = valor.find(')');
                    if (end_paren != string::npos && end_paren > start_paren) {
                        valor = valor.substr(start_paren, end_paren - start_paren + 1);
                        m->setHorario(valor.c_str());
                    }
                } else {
                    // Simple format
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
                        m->setHorario(valor.c_str());
                    }
                }
            }
        }
        else if ((int)line.find('}') != -1) {
            if (m != nullptr) {
                addMaestro(m);
                m = nullptr;
            }
        }
    }
    
    file.close();
    cout << "Se cargaron " << cant << " maestros desde el archivo CSV." << endl;
}

maestros::~maestros() {
    for (int i = 0; i < cant; i++) {
        delete lista_maestros[i];
    }
    delete[] lista_maestros;
}

void maestros::addMaestro(maestro* m) {
    if (cant >= cant_max) {
        resize();
    }
    lista_maestros[cant] = m;
    cant++;
}

void maestros::resize() {
    cant_max *= 2;
    maestro** nuevo_array = new maestro*[cant_max];
    
    for (int i = 0; i < cant; i++) {
        nuevo_array[i] = lista_maestros[i];
    }
    
    delete[] lista_maestros;
    lista_maestros = nuevo_array;
}

maestro* maestros::getMaestro(int index) const {
    if (index >= 0 && index < cant) {
        return lista_maestros[index];
    }
    return nullptr;
}

void maestros::mostrarDetalle(int id, materias* materias_obj) const {
    bool encontrado = false;
    for(int i=0; i<cant; i++) {
        maestro* m = lista_maestros[i];
        if(m && m->getId() == id) {
            cout << "\n--- DETALLE DE MAESTRO ---" << endl;
            cout << "ID: " << m->getId() << endl;
            cout << "Nombre: " << m->getNombre() << endl;
            cout << "Horario: " << m->getHorario() << endl;
            cout << "Materias que imparte (" << m->getCantidadMaterias() << "):" << endl;
            for (int j = 0; j < m->getCantidadMaterias(); j++) {
                materia* mat = materias_obj->getMateria(m->getIdMateria(j));
                if(mat) cout << "    - " << mat->getNombre() << endl;
            }
            encontrado = true;
            break;
        }
    }
    if(!encontrado) cout << "Maestro no encontrado con ID: " << id << endl;
}

void maestros::setColor(const char* c) {
    // Not used directly on the collection, but needed for interface consistency if requested
}

const char* maestros::getColor() const {
    return "";
}

void maestros::mostrarMaestros() const {
    cout << "\n=== LISTADO DE MAESTROS ===" << endl;
    cout << "Total: " << cant << " maestros\n" << endl;
    
    for (int i = 0; i < cant; i++) {
        maestro* m = lista_maestros[i];
        cout << "ID: " << m->getId() << endl;
        cout << "  Nombre: " << m->getNombre() << endl;
        cout << "  Horario: " << m->getHorario() << endl;
        cout << "  Materias que imparte (" << m->getCantidadMaterias() << "):" << endl;
        
        for (int j = 0; j < m->getCantidadMaterias(); j++) {
            cout << "    - materias: " << m->getIdMateria(j) << endl;
        }
        cout << "---" << endl;
    }
}

void maestros::modificar(int id, const char* instrucciones, materias* materias_obj) {
    maestro* m = nullptr;
    for (int i = 0; i < cant; i++) {
        if (lista_maestros[i]->getId() == id) {
            m = lista_maestros[i];
            break;
        }
    }

    if (!m) {
        cout << "Error: Maestro con ID " << id << " no encontrado." << endl;
        return;
    }

    char buffer[256];
    if (Modificador::obtenerValor(instrucciones, "nombre", buffer, 256)) {
        m->setNombre(buffer);
        cout << "Nombre actualizado." << endl;
    }

    if (Modificador::obtenerValor(instrucciones, "horario", buffer, 256)) {
        m->setHorario(buffer);
        cout << "Horario actualizado." << endl;
    }

    if (Modificador::obtenerValor(instrucciones, "color", buffer, 256)) {
        m->setColor(buffer);
        cout << "Color actualizado." << endl;
    }

    if (Modificador::obtenerValor(instrucciones, "materias_add", buffer, 256)) {
        int id_mat = atoi(buffer);
        if (id_mat != 0 || strcmp(buffer, "0") == 0) {
            m->addIdMateria(id_mat);
            cout << "Materia agregada." << endl;
        } else {
            cout << "Error: ID invalido." << endl;
        }
    }

    if (Modificador::obtenerValor(instrucciones, "materias_remove", buffer, 256)) {
        int id_mat = atoi(buffer);
        
        int cant = m->getCantidadMaterias();
        int* new_ids = new int[cant]; // Max size
        int new_cant = 0;
        bool found = false;
        
        for(int i=0; i<cant; i++) {
            int current_id = m->getIdMateria(i);
            if (current_id != id_mat) {
                new_ids[new_cant++] = current_id;
            } else {
                found = true;
            }
        }
        
        if (found) {
            m->clearMaterias();
            for(int i=0; i<new_cant; i++) {
                m->addIdMateria(new_ids[i]);
            }
            cout << "Materia eliminada." << endl;
        } else {
            cout << "Materia no encontrada en la lista del maestro." << endl;
        }
        delete[] new_ids;
    }

    if (Modificador::obtenerValor(instrucciones, "materias", buffer, 256)) {
        m->clearMaterias();
        int maxItems = 20;
        char** items = new char*[maxItems];
        for(int i=0; i<maxItems; i++) items[i] = new char[50];
        
        int cantidad = 0;
        Modificador::parsearCadenas(buffer, items, cantidad, maxItems, 50);
        
        for (int i = 0; i < cantidad; ++i) {
            // Asumimos que son IDs enteros
            int id_mat = atoi(items[i]);
            // Validacion basica
            if (id_mat != 0 || strcmp(items[i], "0") == 0) {
                 m->addIdMateria(id_mat);
            } else {
                 cout << "Advertencia: No se pudo interpretar '" << items[i] << "' como ID de materia." << endl;
            }
        }
        
        for(int i=0; i<maxItems; i++) delete[] items[i];
        delete[] items;
        
        cout << "Materias actualizadas." << endl;
    }
    
    // Guardar cambios al CSV
    guardarCSV(materias_obj);
}

void maestros::guardarCSV(materias* materias_obj) {
    string archivo = "../src/csv/maestros.csv";
    ofstream file(archivo.c_str());
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << " para escritura" << endl;
        return;
    }
    
    for (int i = 0; i < cant; i++) {
        maestro* m = lista_maestros[i];
        if (m == nullptr) continue;
        
        file << "{" << endl;
        file << "    nombre:" << m->getNombre() << ";" << endl;
        
        // Escribir materias con sus nombres
        file << "    materias:";
        for (int j = 0; j < m->getCantidadMaterias(); j++) {
            if (j > 0) file << ",";
            
            // Obtener el nombre de la materia
            if (materias_obj != nullptr) {
                materia* mat = materias_obj->getMateria(m->getIdMateria(j));
                if (mat != nullptr) {
                    file << mat->getNombre();
                } else {
                    file << "Materia_" << m->getIdMateria(j);
                }
            } else {
                file << m->getIdMateria(j);
            }
        }
        file << ";" << endl;
        
        // Escribir horario
        file << "    horario: " << m->getHorario() << ";" << endl;
        
        // Escribir color
        file << "    color: " << m->getColor() << ";" << endl;
        
        file << "}" << endl;
    }
    
    file.close();
    cout << "Cambios guardados en " << archivo << endl;
}

