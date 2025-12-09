#include "../include/conjunto_materias.h"
#include "../include/modificaciones_objetos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

ConjuntoMaterias::ConjuntoMaterias() {
    cant_sets = 0;
    max_sets = 10;
    sets = new Set[max_sets];
}

ConjuntoMaterias::~ConjuntoMaterias() {
    for (int i = 0; i < cant_sets; i++) {
        delete[] sets[i].materia_ids;
    }
    delete[] sets;
}

void ConjuntoMaterias::resizeSets() {
    max_sets *= 2;
    Set* new_sets = new Set[max_sets];
    for (int i = 0; i < cant_sets; i++) {
        new_sets[i] = sets[i];
    }
    delete[] sets;
    sets = new_sets;
}

void ConjuntoMaterias::resizeMaterias(Set& s) {
    if (s.max_materias == 0) s.max_materias = 10;
    else s.max_materias *= 2;
    
    int* new_ids = new int[s.max_materias];
    for (int i = 0; i < s.cant_materias; i++) {
        new_ids[i] = s.materia_ids[i];
    }
    if (s.materia_ids != nullptr) delete[] s.materia_ids;
    s.materia_ids = new_ids;
}

void ConjuntoMaterias::cargarMaterias(materias* m_obj) {
    string archivo = "../src/csv/conjuntos_materias.csv";
    ifstream file(archivo.c_str());
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
        return;
    }
    
    string line;
    Set* currentSet = nullptr;
    
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
            if (cant_sets >= max_sets) resizeSets();
            sets[cant_sets].nombre = "";
            sets[cant_sets].cant_materias = 0;
            sets[cant_sets].max_materias = 10;
            sets[cant_sets].materia_ids = new int[10];
            currentSet = &sets[cant_sets];
        }
        else if ((int)line.find("nombre:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && currentSet != nullptr) {
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
                    currentSet->nombre = valor.substr(v_start, v_end - v_start + 1);
                }
            }
        }
        else if ((int)line.find("materias:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && currentSet != nullptr) {
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
                            int id = m_obj->getIdPorNombre(materia_nombre.c_str());
                            if (id != -1) {
                                if (currentSet->cant_materias >= currentSet->max_materias) resizeMaterias(*currentSet);
                                currentSet->materia_ids[currentSet->cant_materias++] = id;
                            }
                        }
                    }
                }
            }
        }
        else if ((int)line.find('}') != -1) {
            if (currentSet != nullptr) {
                cant_sets++;
                currentSet = nullptr;
            }
        }
    }
    file.close();
    for (int i = 0; i < cant_sets; i++) {
        int* ids = sets[i].materia_ids;
        int count = sets[i].cant_materias;
        
        for (int j = 0; j < count; j++) {
            materia* m = m_obj->getMateria(ids[j]);
            if (m) {
                //anterior
                if (j > 0) {
                    m->setIdAnterior(ids[j-1]);
                } else {
                    m->setIdAnterior(-1);
                }
                //siguiente
                if (j < count - 1) {
                    m->setIdSiguiente(ids[j+1]);
                } else {
                    m->setIdSiguiente(-1);
                }
            }
        }
    }
    
    cout << "Se cargaron " << cant_sets << " conjuntos de materias." << endl;
}

int ConjuntoMaterias::getIdSet(string nombre) {
    for (int i = 0; i < cant_sets; i++) {
        if (sets[i].nombre == nombre) {
            return i; // retorna index
        }
    }
    return -1;
}

int ConjuntoMaterias::getCantidad() {
    return cant_sets;
}

Set* ConjuntoMaterias::getSet(int index) {
    if (index >= 0 && index < cant_sets) {
        return &sets[index];
    }
    return nullptr;
}

void ConjuntoMaterias::mostrarDetalle(int index, materias* materias_obj) {
    Set* s = getSet(index);
    if(s) {
        cout << "\n--- DETALLE DE CONJUNTO ---" << endl;
        cout << "Nombre: " << s->nombre << endl;
        cout << "Materias (" << s->cant_materias << "):" << endl;
        for (int j = 0; j < s->cant_materias; j++) {
            materia* m = materias_obj->getMateria(s->materia_ids[j]);
            if (m) cout << "    - " << m->getNombre() << endl;
        }
    } else {
        cout << "Conjunto no encontrado." << endl;
    }
}

void ConjuntoMaterias::mostrarConjuntos() {
    std::cout << "--- Conjuntos de Materias ---" << std::endl;
    for (int i = 0; i < cant_sets; i++) {
        std::cout << "Set " << i << ": " << sets[i].nombre << " (" << sets[i].cant_materias << " materias)" << std::endl;
    }
}

void ConjuntoMaterias::modificar(int id, const char* instrucciones, materias* m_obj) {
    Set* s = getSet(id);
    if (!s) {
        cout << "Error: Conjunto con ID " << id << " no encontrado." << endl;
        return;
    }

    char buffer[256];

    if (Modificador::obtenerValor(instrucciones, "nombre", buffer, 256)) {
        s->nombre = buffer;
        cout << "Nombre actualizado." << endl;
    }

    if (Modificador::obtenerValor(instrucciones, "materias_add", buffer, 256)) {
        if (m_obj != nullptr) {
            int id_mat = m_obj->getIdPorNombre(buffer);
            if (id_mat != -1) {
                if (s->cant_materias >= s->max_materias) resizeMaterias(*s);
                s->materia_ids[s->cant_materias++] = id_mat;
                cout << "Materia agregada." << endl;
            } else {
                cout << "Error: Materia '" << buffer << "' no encontrada." << endl;
            }
        }
    }

    if (Modificador::obtenerValor(instrucciones, "materias_remove", buffer, 256)) {
        if (m_obj != nullptr) {
            int id_mat = m_obj->getIdPorNombre(buffer);
            if (id_mat != -1) {
                bool found = false;
                for(int i=0; i<s->cant_materias; i++) {
                    if (s->materia_ids[i] == id_mat) {
                        found = true;
                        for(int j=i; j<s->cant_materias-1; j++) {
                            s->materia_ids[j] = s->materia_ids[j+1];
                        }
                        s->cant_materias--;
                        break;
                    }
                }
                if (found) cout << "Materia eliminada." << endl;
                else cout << "Materia no encontrada en el conjunto." << endl;
            } else {
                cout << "Error: Materia '" << buffer << "' no encontrada." << endl;
            }
        }
    }

    if (Modificador::obtenerValor(instrucciones, "materias", buffer, 256)) {
        s->cant_materias = 0;
        int maxItems = 20;
        char** items = new char*[maxItems];
        for(int i=0; i<maxItems; i++) items[i] = new char[50];
        
        int cantidad = 0;
        Modificador::parsearCadenas(buffer, items, cantidad, maxItems, 50);
        
        for (size_t i = 0; i < cantidad; ++i) {
            char* materia_nombre = items[i];
            while(*materia_nombre == ' ' || *materia_nombre == '\t') materia_nombre++;
            int len = strlen(materia_nombre);
            while(len > 0 && (materia_nombre[len-1] == ' ' || materia_nombre[len-1] == '\t')) {
                materia_nombre[len-1] = '\0';
                len--;
            }
            
            if (m_obj != nullptr) {
                int id_mat = m_obj->getIdPorNombre(materia_nombre);
                if (id_mat != -1) {
                    if (s->cant_materias >= s->max_materias) resizeMaterias(*s);
                    s->materia_ids[s->cant_materias++] = id_mat;
                } else {
                    cout << "Advertencia: Materia '" << materia_nombre << "' no encontrada." << endl;
                }
            }
        }
        
        for(int i=0; i<maxItems; i++) delete[] items[i];
        delete[] items;
        
        cout << "Materias actualizadas." << endl;
    }
}

void ConjuntoMaterias::agregarMateriaASet(int idSet, int idMateria) {
    Set* s = getSet(idSet);
    if (s) {
        if (s->cant_materias >= s->max_materias) {
            resizeMaterias(*s);
        }
        s->materia_ids[s->cant_materias++] = idMateria;
    }
}
