#include "generationwidget.h"
#include "ui_generationwidget.h"
#include <QDebug>
#include <QShowEvent>
#include <QMessageBox>
#include "../include/materias.h"
#include "../include/salones.h"
#include "../include/grupos.h"
#include "../include/maestros.h"
#include "../include/conjunto_materias.h"
#include "../include/horario.h"
#include "../include/universal_time_tabling.h"
#include <iostream>
#include <cstdio>

GenerationWidget::GenerationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GenerationWidget)
{
    ui->setupUi(this);
}

GenerationWidget::~GenerationWidget()
{
    delete ui;
    if (m_horarios_grupos) delete[] m_horarios_grupos;
    if (m_horarios_maestros) delete[] m_horarios_maestros;
    if (m_horarios_salones) delete[] m_horarios_salones;
}

void GenerationWidget::setData(materias* m, salones* s, grupos* g, maestros* ma, ConjuntoMaterias* c)
{
    m_materias = m;
    m_salones = s;
    m_grupos = g;
    m_maestros = ma;
    m_conjuntos = c;
    
    // Inicializar horarios si tenemos los datos
    if (m_grupos && m_maestros && m_salones) {
        if (m_horarios_grupos) delete[] m_horarios_grupos;
        m_horarios_grupos = new Horario[m_grupos->getCantidad()];
        for(int i = 0; i < m_grupos->getCantidad(); i++) m_horarios_grupos[i] = Horario(i);

        if (m_horarios_maestros) delete[] m_horarios_maestros;
        m_horarios_maestros = new Horario[m_maestros->getCantidad()];
        for(int i = 0; i < m_maestros->getCantidad(); i++) m_horarios_maestros[i] = Horario(i);

        if (m_horarios_salones) delete[] m_horarios_salones;
        m_horarios_salones = new Horario[m_salones->getCantidad()];
        for(int i = 0; i < m_salones->getCantidad(); i++) m_horarios_salones[i] = Horario(i);
        
        // Cargar desde CSV si existen
        const char* archivo_grupos = "../src/csv/horario_grupos_generado.csv";
        FILE* fGroups = fopen(archivo_grupos, "r");
        if (fGroups) {
            char line[10000]; // Increased buffer size
            while (fgets(line, sizeof(line), fGroups)) {
                // Parse name to find index
                char* comma = strchr(line, ',');
                if (comma) {
                    char name[256];
                    strncpy(name, line, comma - line);
                    name[comma - line] = '\0';
                    
                    // Find group by name
                    for(int i=0; i<m_grupos->getCantidad(); i++) {
                        if (strcmp(m_grupos->getGrupo(i)->getNombre(), name) == 0) {
                            m_horarios_grupos[i].importarCSV(line);
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
            char line[10000]; // Increased buffer size
            while (fgets(line, sizeof(line), fTeachers)) {
                char* comma = strchr(line, ',');
                if (comma) {
                    char name[256];
                    strncpy(name, line, comma - line);
                    name[comma - line] = '\0';
                    
                    for(int i=0; i<m_maestros->getCantidad(); i++) {
                        if (strcmp(m_maestros->getMaestro(i)->getNombre(), name) == 0) {
                            m_horarios_maestros[i].importarCSV(line);
                            break;
                        }
                    }
                }
            }
            fclose(fTeachers);
        }
        
        emit schedulesUpdated();
    }
}

void GenerationWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    
    // Aquí puedes poner el código que quieres que se ejecute cada vez que se muestra la ventana
    // Por ejemplo: cargar datos de la base de datos, actualizar tablas, etc.
    qDebug() << "GenerationWidget se ha mostrado!";

    // Ejemplo de cómo actualizar los contadores
    // En el futuro, reemplazarás los '0' con las variables que tengan la cuenta real
    int teachersCount = (m_maestros) ? m_maestros->getCantidad() : 0;
    int roomsCount = (m_salones) ? m_salones->getCantidad() : 0;
    int coursesCount = (m_materias) ? m_materias->getCantidad() : 0;
    int groupsCount = (m_grupos) ? m_grupos->getCantidad() : 0;

    QString htmlStyle = "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">%1: </span>%2</p>";

    ui->teachersCountLabel->setHtml(htmlStyle.arg("Maestros").arg(teachersCount));
    ui->roomsCountLabel->setHtml(htmlStyle.arg("Salones").arg(roomsCount));
    ui->coursesCountLabel->setHtml(htmlStyle.arg("Materias").arg(coursesCount));
    ui->groupCountLabel->setHtml(htmlStyle.arg("Grupos").arg(groupsCount));
}

void GenerationWidget::on_deleteSchedule_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmar Reinicio",
        "¿Estás seguro de que deseas borrar todos los horarios generados?\n\n"
        "Esto eliminará:\n"
        "- Horarios en memoria\n"
        "- Archivos CSV generados (*_generado.csv)\n\n"
        "Esta acción no se puede deshacer.",
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply != QMessageBox::Yes) {
        ui->consoleLog->appendPlainText("Operación cancelada por el usuario.");
        return;
    }
    
    ui->consoleLog->appendPlainText("=== REINICIANDO HORARIOS ===");
    
    // Limpiar horarios en memoria
    if (m_horarios_grupos && m_grupos) {
        for(int i=0; i<m_grupos->getCantidad(); i++) m_horarios_grupos[i].limpiar();
        ui->consoleLog->appendPlainText("✓ Horarios de grupos limpiados");
    }
    
    if (m_horarios_maestros && m_maestros) {
        for(int i=0; i<m_maestros->getCantidad(); i++) m_horarios_maestros[i].limpiar();
        ui->consoleLog->appendPlainText("✓ Horarios de maestros limpiados");
    }
    
    if (m_horarios_salones && m_salones) {
        for(int i=0; i<m_salones->getCantidad(); i++) m_horarios_salones[i].limpiar();
        ui->consoleLog->appendPlainText("✓ Horarios de salones limpiados");
    }
    
    // Eliminar archivos CSV generados
    const char* archivo_grupos = "../src/csv/horario_grupos_generado.csv";
    const char* archivo_maestros = "../src/csv/horario_maestros_generado.csv";
    const char* archivo_salones = "../src/csv/horario_salones_generado.csv";
    
    int deleted = 0;
    if (remove(archivo_grupos) == 0) {
        ui->consoleLog->appendPlainText("✓ Eliminado: horario_grupos_generado.csv");
        deleted++;
    }
    if (remove(archivo_maestros) == 0) {
        ui->consoleLog->appendPlainText("✓ Eliminado: horario_maestros_generado.csv");
        deleted++;
    }
    if (remove(archivo_salones) == 0) {
        ui->consoleLog->appendPlainText("✓ Eliminado: horario_salones_generado.csv");
        deleted++;
    }
    
    ui->consoleLog->appendPlainText(QString("=== REINICIO COMPLETADO (%1 archivos eliminados) ===").arg(deleted));
    
    emit schedulesUpdated();
    
    QMessageBox::information(this, "Éxito", 
        QString("Horarios reiniciados correctamente.\n%1 archivos CSV eliminados.").arg(deleted));
}

void GenerationWidget::on_continueSchedule_clicked()
{
    ui->consoleLog->appendPlainText("--- Continuando generación ---");
    ui->consoleLog->appendPlainText("Funcionalidad no implementada completamente.");
}

void GenerationWidget::on_createSchedule_clicked()
{
    ui->consoleLog->clear();
    ui->consoleLog->appendPlainText("=== GENERACIÓN DE HORARIOS ===");
    
    // Validar que todos los datos estén cargados
    if (!m_materias || !m_salones || !m_grupos || !m_maestros || !m_conjuntos) {
        ui->consoleLog->appendPlainText("✗ ERROR: Faltan datos para generar el horario.");
        QMessageBox::critical(this, "Error", 
            "No se pueden generar horarios.\n\n"
            "Asegúrate de que estén cargados:\n"
            "- Materias\n"
            "- Salones\n"
            "- Grupos\n"
            "- Maestros\n"
            "- Conjuntos de materias");
        return;
    }
    
    // Validar que haya datos suficientes
    if (m_grupos->getCantidad() == 0) {
        ui->consoleLog->appendPlainText("✗ ERROR: No hay grupos definidos.");
        QMessageBox::warning(this, "Error", "No hay grupos para generar horarios.");
        return;
    }
    
    if (m_maestros->getCantidad() == 0) {
        ui->consoleLog->appendPlainText("✗ ERROR: No hay maestros definidos.");
        QMessageBox::warning(this, "Error", "No hay maestros para asignar.");
        return;
    }
    
    if (m_salones->getCantidad() == 0) {
        ui->consoleLog->appendPlainText("✗ ERROR: No hay salones definidos.");
        QMessageBox::warning(this, "Error", "No hay salones disponibles.");
        return;
    }
    
    ui->consoleLog->appendPlainText(QString("✓ Grupos: %1").arg(m_grupos->getCantidad()));
    ui->consoleLog->appendPlainText(QString("✓ Maestros: %1").arg(m_maestros->getCantidad()));
    ui->consoleLog->appendPlainText(QString("✓ Salones: %1").arg(m_salones->getCantidad()));
    ui->consoleLog->appendPlainText("");
                    std::cout << "\n========================================" << std::endl;
                    std::cout << "  EJECUTANDO UNIVERSAL TIMETABLING" << std::endl;
                    std::cout << "========================================" << std::endl;
                    lista_de_listas* listas = inicializar_listas_grupos(m_grupos->getCantidad());
                    for(int i = 0; i < m_grupos->getCantidad(); i++){
                        grupo* g = m_grupos->getGrupo(i);
                        if (g != nullptr) {
                            int setId = g->getConjuntoDeMaterias();
                            Set* s = m_conjuntos->getSet(setId);
                            
                            if(s != nullptr){
                                std::cout << "\n>>> Procesando Grupo: " << g->getNombre() << std::endl;
                                std::cout << "    Conjunto: " << s->nombre << std::endl;
                                
                                // Crear prioridades para este grupo específico
                                crear_prioridad_grupo(i, s, m_materias, m_maestros, listas->listas_grupos[i]);
                                
                                std::cout << "    Total de nodos creados: " << listas->listas_grupos[i]->cant << std::endl;
                            }
                        }
                    }

                    
                    std::cout << "  Horarios inicializados" << std::endl;
                    std::cout << "     - Grupos: " << m_grupos->getCantidad() << std::endl;
                    std::cout << "     - Maestros: " << m_maestros->getCantidad() << std::endl;
                    std::cout << "     - Salones: " << m_salones->getCantidad() << std::endl;
                    
                    // Limpiar horarios antes de ejecutar
                    std::cout << "\nLimpiando horarios existentes..." << std::endl;
                    for(int i=0; i<m_grupos->getCantidad(); i++) m_horarios_grupos[i].limpiar();
                    for(int i=0; i<m_maestros->getCantidad(); i++) m_horarios_maestros[i].limpiar();
                    for(int i=0; i<m_salones->getCantidad(); i++) m_horarios_salones[i].limpiar();
                    
                    // Re-inicializar bloqueos de horario de grupos
                     for(int i = 0; i < m_grupos->getCantidad(); i++){
                        grupo* g = m_grupos->getGrupo(i);
                        if (g != nullptr) {
                            int inicio = g->getFranjaInicio();
                            int fin = g->getFranjaFin();
                            for (int d = 0; d < Horario::getNumDias(); d++) {
                                for (int f = 0; f < Horario::getNumFranjas(); f++) {
                                    if (f < inicio || f > fin) {
                                        m_horarios_grupos[i].asignarClase(d, f, -1, -1, -1);
                                    }
                                }
                            }
                        }
                    }

                    // Ejecutar Universal TimeTabling GLOBAL
                    std::cout << "\n>>> Creando lista global priorizada..." << std::endl;
                    lista* lista_global = crear_lista_global_priorizada(listas);
                    std::cout << "    Total de nodos en lista global: " << lista_global->cant << std::endl;

                    std::cout << "\n>>> Ejecutando backtracking global..." << std::endl;
                    if(ejecutar_universal_timetabling_global(lista_global, m_materias, m_maestros, m_salones, m_grupos, m_horarios_grupos, m_horarios_maestros, m_horarios_salones)){
                        std::cout << "   Asignación global exitosa" << std::endl;
                    } else {
                        std::cout <<" No se pudo encontrar una solución global" << std::endl;
                    }

                    // Liberar la lista global (estructura y nodos copiados)
                    nodo* nodo_global = lista_global->inicio;
                    while(nodo_global != nullptr){
                        nodo* temp = nodo_global;
                        nodo_global = nodo_global->siguiente;
                        delete temp;    
                    }
                    delete lista_global;



                    std::cout << "\n========================================" << std::endl;
                    std::cout << "  EXPORTANDO HORARIOS A CSV" << std::endl;
                    std::cout << "========================================" << std::endl;
                    
                    const char* archivo_grupos = "../src/csv/horario_grupos_generado.csv";
                    const char* archivo_maestros = "../src/csv/horario_maestros_generado.csv";
                    const char* archivo_salones = "../src/csv/horario_salones_generado.csv";
    
    //BORRA LOS ANTERIORES PARA COLOCAR LOS ACTUALES
    remove(archivo_grupos);
    remove(archivo_maestros);
    remove(archivo_salones);
    
    //por cada uno se agrega al archivo
    for(int i = 0; i < m_grupos->getCantidad(); i++){
        grupo* g = m_grupos->getGrupo(i);
        if(g != nullptr){
            // 1 = Grupo
            m_horarios_grupos[i].exportarCSV(g->getNombre(), archivo_grupos, 1, m_materias, m_maestros, m_grupos, m_salones);
        }
    }
    
    //por cada uno se agrega al archivo
    for(int i = 0; i < m_maestros->getCantidad(); i++){
        maestro* m = m_maestros->getMaestro(i);
        if(m != nullptr && (int)strlen(m->getNombre()) > 0){
            // 2 = Maestro
            m_horarios_maestros[i].exportarCSV(m->getNombre(), archivo_maestros, 2, m_materias, m_maestros, m_grupos, m_salones);
        }
    }
    
    //por cada uno se agrega al archivo
    for(int i = 0; i < m_salones->getCantidad(); i++){
        salon* s = m_salones->getSalon(i);
        if(s != nullptr){
            // 3 = Salon
            m_horarios_salones[i].exportarCSV(s->getNombre(), archivo_salones, 3, m_materias, m_maestros, m_grupos, m_salones);
        }
    }
    
    ui->consoleLog->appendPlainText("Exportación finalizada.");

    //finalización, limpia la memoria
    for(int i = 0; i < listas->cantidad_grupos; i++){
        nodo* actual = listas->listas_grupos[i]->inicio;
        while(actual != nullptr){
            nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        delete listas->listas_grupos[i];
    }
    delete[] listas->listas_grupos;
    delete listas;
    
    ui->consoleLog->appendPlainText("");
    ui->consoleLog->appendPlainText("=== GENERACIÓN COMPLETADA EXITOSAMENTE ===");
    
    emit schedulesUpdated();
    
    QMessageBox::information(this, "Éxito", 
        "Horarios generados correctamente.\n\n"
        "Los archivos CSV han sido creados en:\n"
        "- horario_grupos_generado.csv\n"
        "- horario_maestros_generado.csv\n"
        "- horario_salones_generado.csv");
}
