#include "../include/salones.h"
#include "../include/modificaciones_objetos.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

salones::salones() {
    cant = 0;
    cant_max = 10;
    lista_salones = new salon*[cant_max];
    
    string archivo = "../src/csv/salones.csv";
    ifstream file(archivo.c_str());
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
        return;
    }
    
    string line;
    salon* s = nullptr;
    int objetoContador = 0;
    
    while (getline(file, line)) {
        // Trim manual
        int start = 0;
        while (start < (int)line.length() && (line[start] == ' ' || line[start] == '\t' || line[start] == '\r' || line[start] == '\n')) {
            start++;
        }
        
        int end = (int)line.length() - 1;
        while (end >= 0 && (line[end] == ' ' || line[end] == '\t' || line[end] == '\r' || line[end] == '\n')) {
            end--;
        }
        
        if (start > end) continue; // Linea vacia
        
        line = line.substr(start, end - start + 1);
        
        if (line[0] == '#') continue;
        
        if ((int)line.find('{') != -1) {
            s = new salon();
            s->setId(objetoContador);
            objetoContador++;
        }
        else if ((int)line.find("nombre:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && s != nullptr) {
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
                    s->setNombre(valor.c_str());
                }
            }
        }
        else if ((int)line.find("salon:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && s != nullptr) {
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
                    s->setTipo(valor.c_str());
                }
            }
        }
        else if ((int)line.find("color:") != -1) {
            int pos = (int)line.find(':');
            if (pos != -1 && s != nullptr) {
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
                    s->setColor(valor.c_str());
                }
            }
        }
        else if ((int)line.find('}') != -1) {
            if (s != nullptr) {
                addSalon(s);
                s = nullptr;
            }
        }
    }
    
    file.close();
    cout << "Se cargaron " << cant << " salones desde el archivo CSV." << endl;
}

salones::~salones() {
    for (int i = 0; i < cant; i++) {
        delete lista_salones[i];
    }
    delete[] lista_salones;
}

void salones::addSalon(salon* s) {
    if (cant >= cant_max) {
        resize();
    }
    lista_salones[cant] = s;
    cant++;
}

void salones::resize() {
    cant_max *= 2;
    salon** nuevo_array = new salon*[cant_max];
    
    for (int i = 0; i < cant; i++) {
        nuevo_array[i] = lista_salones[i];
    }
    
    delete[] lista_salones;
    lista_salones = nuevo_array;
}

salon* salones::getSalon(int index) const {
    if (index >= 0 && index < cant) {
        return lista_salones[index];
    }
    return nullptr;
}

void salones::setColor(const char* c) {
    // Not used directly
}

const char* salones::getColor() const {
    return "";
}

void salones::modificar(int id, const char* instrucciones) {
    salon* s = nullptr;
    for (int i = 0; i < cant; i++) {
        if (lista_salones[i]->getId() == id) {
            s = lista_salones[i];
            break;
        }
    }

    if (!s) {
        cout << "Error: Salon con ID " << id << " no encontrado." << endl;
        return;
    }

    char buffer[256];

    if (Modificador::obtenerValor(instrucciones, "nombre", buffer, 256)) {
        s->setNombre(buffer);
        cout << "Nombre actualizado." << endl;
    }

    if (Modificador::obtenerValor(instrucciones, "tipos_de_salon", buffer, 256)) {
        s->setTipo(buffer);
        cout << "Tipo de salon actualizado." << endl;
    }
}

void salones::mostrarDetalle(int id) const {
    bool encontrado = false;
    for(int i=0; i<cant; i++) {
        salon* s = lista_salones[i];
        if(s && s->getId() == id) {
            cout << "\n--- DETALLE DE SALON ---" << endl;
            cout << "ID: " << s->getId() << endl;
            cout << "Nombre: " << s->getNombre() << endl;
            cout << "Tipo: " << s->getTipo() << endl;
            encontrado = true;
            break;
        }
    }
    if(!encontrado) cout << "Salon no encontrado con ID: " << id << endl;
}

void salones::mostrarSalones() const {
    cout << "\n=== LISTADO DE SALONES ===" << endl;
    cout << "Total: " << cant << " salones\n" << endl;
    
    for (int i = 0; i < cant; i++) {
        salon* s = lista_salones[i];
        cout << "ID: " << s->getId() << endl;
        cout << "  Nombre: " << s->getNombre() << endl;
        cout << "  Tipo: " << s->getTipo() << endl;
        cout << "---" << endl;
    }
}