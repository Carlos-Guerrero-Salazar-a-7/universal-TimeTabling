#include "../include/materias.h"
#include "../include/modificaciones_objetos.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;
materias::materias() {
    cant = 0;
    cant_max = 10;  // Capacidad inicial
    lista_materias = new materia*[cant_max];
    
    string archivo = "../src/csv/materias.csv";
    ifstream file(archivo.c_str());
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
        return;
    }
    
    string line;
    materia* m = nullptr;
    int objetoContador = 0;
    
    while (getline(file, line)) {
        // Eliminar espacios en blanco al inicio y final
        int start = 0;
        while (start < (int)line.length() && (line[start] == ' ' || line[start] == '\t' || line[start] == '\r' || line[start] == '\n')) {
            start++;
        }
        
        int end = (int)line.length() - 1;
        while (end >= 0 && (line[end] == ' ' || line[end] == '\t' || line[end] == '\r' || line[end] == '\n')) {
            end--;
        }
        
        if (start > end) continue; // Línea vacía
        
        line = line.substr(start, end - start + 1);
        
        // Ignorar comentarios
        if (line[0] == '#') continue;
        
        // Detectar inicio de un nuevo objeto
        if ((int)line.find('{') != -1) {
            m = new materia();
            m->setId(objetoContador);
            objetoContador++;
        }
        // Parsear nombre
        else if ((int)line.find("nombre:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && m != nullptr) {
                string valor = line.substr(pos + 1);
                // Eliminar espacios y punto y coma
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
        // Parsear horas necesarias
        else if ((int)line.find("horas_necesarias:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && m != nullptr) {
                string valor = line.substr(pos + 1);
                // Eliminar espacios y punto y coma
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
                    m->setHorasNecesarias(atoi(valor.c_str()));
                }
            }
        }
        // Parsear salón especial
        else if ((int)line.find("salon_especial:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && m != nullptr) {
                string valor = line.substr(pos + 1);
                // Eliminar espacios y punto y coma
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
                    m->setSalonEspecial(valor.c_str());
                }
            }
        }
        // Detectar fin de objeto
        else if ((int)line.find('}') != -1) {
            if (m != nullptr) {
                addMateria(m);
                m = nullptr;
            }
        }
    }
    
    file.close();
    cout << "Se cargaron " << cant << " materias desde el archivo CSV." << endl;
}

// Destructor - libera la memoria
materias::~materias() {
    for (int i = 0; i < cant; i++) {
        delete lista_materias[i];
    }
    delete[] lista_materias;
}

// Método para agregar una materia al listado
void materias::addMateria(materia* m) {
    if (cant >= cant_max) {
        resize();
    }
    lista_materias[cant] = m;
    cant++;
}

// Método privado para redimensionar el array
void materias::resize() {
    cant_max *= 2;  // Duplicar la capacidad
    materia** nuevo_array = new materia*[cant_max];
    
    // Copiar los punteros al nuevo array
    for (int i = 0; i < cant; i++) {
        nuevo_array[i] = lista_materias[i];
    }
    
    // Liberar el array antiguo (solo el array, no los objetos)
    delete[] lista_materias;
    
    // Actualizar el puntero
    lista_materias = nuevo_array;
}

// Getter para obtener una materia por índice
materia* materias::getMateria(int index) const {
    if (index >= 0 && index < cant) {
        return lista_materias[index];
    }
    return nullptr;
}

// Buscar ID de materia por nombre
int materias::getIdPorNombre(const char* nombre) const {
    for (int i = 0; i < cant; i++) {
        if (strcmp(lista_materias[i]->getNombre(), nombre) == 0) {
            return lista_materias[i]->getId();
        }
    }
    return -1;
}

// Método para mostrar detalle de una materia por ID
void materias::mostrarDetalle(int id) const {
    bool encontrado = false;
    for(int i=0; i<cant; i++) {
        materia* m = lista_materias[i];
        if(m && m->getId() == id) {
            cout << "\n--- DETALLE DE MATERIA ---" << endl;
            cout << "ID: " << m->getId() << endl;
            cout << "Nombre: " << m->getNombre() << endl;
            cout << "Horas necesarias: " << m->getHorasNecesarias() << endl;
            cout << "Salon Especial: " << m->getSalonEspecial() << endl;
            encontrado = true;
            break;
        }
    }
    if(!encontrado) cout << "Materia no encontrada con ID: " << id << endl;
}

// Método para mostrar todas las materias
void materias::mostrarMaterias() const {
    cout << "\n=== LISTADO DE MATERIAS ===" << endl;
    cout << "Total: " << cant << " materias\n" << endl;
    
    for (int i = 0; i < cant; i++) {
        materia* m = lista_materias[i];
        cout << "ID: " << m->getId() << endl;
        cout << "  Nombre: " << m->getNombre() << endl;
        cout << "  Horas necesarias: " << m->getHorasNecesarias() << endl;
        cout << "  Salón especial: " << m->getSalonEspecial() << endl;
        cout << "---" << endl;
    }
}

void materias::modificar(int id, const char* instrucciones) {
    materia* m = nullptr;
    for (int i = 0; i < cant; i++) {
        if (lista_materias[i]->getId() == id) {
            m = lista_materias[i];
            break;
        }
    }

    if (!m) {
        cout << "Error: Materia con ID " << id << " no encontrada." << endl;
        return;
    }

    char buffer[256];

    if (Modificador::obtenerValor(instrucciones, "nombre", buffer, 256)) {
        m->setNombre(buffer);
        cout << "Nombre actualizado." << endl;
    }

    if (Modificador::obtenerValor(instrucciones, "horas_necesarias", buffer, 256)) {
        int horas = atoi(buffer);
        if (horas > 0) {
            m->setHorasNecesarias(horas);
            cout << "Horas necesarias actualizadas." << endl;
        } else {
            cout << "Error: Valor invalido para horas necesarias." << endl;
        }
    }

    if (Modificador::obtenerValor(instrucciones, "salon_especial", buffer, 256)) {
        m->setSalonEspecial(buffer);
        cout << "Salon especial actualizado." << endl;
    }
}

bool materias::eliminar(int id) {
    int index = -1;
    for (int i = 0; i < cant; i++) {
        if (lista_materias[i]->getId() == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        return false;
    }
    
    delete lista_materias[index];
    
    for (int i = index; i < cant - 1; i++) {
        lista_materias[i] = lista_materias[i + 1];
    }
    
    cant--;
    return true;
}

int materias::agregar(const char* nombre) {
    materia* m = new materia();
    m->setId(cant);
    m->setNombre(nombre);
    m->setHorasNecesarias(5);
    m->setSalonEspecial("ninguno");
    
    addMateria(m);
    
    string archivo = "../src/csv/materias.csv";
    ofstream file(archivo.c_str());
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir " << archivo << endl;
        return -1;
    }
    
    for (int i = 0; i < cant; i++) {
        materia* mat = lista_materias[i];
        if (mat == nullptr) continue;
        
        file << "{" << endl;
        file << "    nombre:" << mat->getNombre() << ";" << endl;
        file << "    horas_necesarias: " << mat->getHorasNecesarias() << ";" << endl;
        file << "    salon_especial: " << mat->getSalonEspecial() << ";" << endl;
        file << "}" << endl;
    }
    
    file.close();
    return m->getId();
}
