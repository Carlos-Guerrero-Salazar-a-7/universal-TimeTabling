#include "groupschedulewidget.h"
#include "ui_groupschedulewidget.h"
#include "../include/maestros.h"
#include "../include/materias.h"
#include "../include/grupos.h"
#include "../include/salones.h"
#include "../include/horario.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QDebug>

GroupScheduleWidget::GroupScheduleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupScheduleWidget)
{
    ui->setupUi(this);
    
    // CRITICAL: Remove ALL stylesheets from table to allow cell colors to show
    ui->scheduleTable->setStyleSheet("");
    qDebug() << "GroupScheduleWidget: Cleared table stylesheet";
    
    // Configurar tabla
    ui->scheduleTable->setRowCount(Horario::getNumFranjas());
    ui->scheduleTable->setColumnCount(Horario::getNumDias() + 1); // +1 para la columna de hora
    
    QStringList headers;
    headers << "Hora";
    for(int i=0; i<Horario::getNumDias(); i++) {
        headers << Horario::getNombreDia(i);
    }
    ui->scheduleTable->setHorizontalHeaderLabels(headers);
    
    // Llenar columna de horas
    for(int i=0; i<Horario::getNumFranjas(); i++) {
        QString hora = QString("%1 - %2").arg(Horario::getInicioFranja(i)).arg(Horario::getFinFranja(i));
        ui->scheduleTable->setItem(i, 0, new QTableWidgetItem(hora));
    }
    
    ui->scheduleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->scheduleTable->verticalHeader()->setVisible(false);
    
    // Make cells taller to fit text better
    ui->scheduleTable->verticalHeader()->setDefaultSectionSize(80);
    
    // Enable word wrap in cells
    ui->scheduleTable->setWordWrap(true);
}

GroupScheduleWidget::~GroupScheduleWidget()
{
    delete ui;
}

void GroupScheduleWidget::setData(maestros* m, materias* mat, grupos* g, salones* s, Horario* h, int cantH)
{
    m_maestros = m;
    m_materias = mat;
    m_grupos = g;
    m_salones = s;
    m_horarios = h;
    m_cantHorarios = cantH;
}

void GroupScheduleWidget::loadSchedule(int id)
{
    m_currentId = id;
    cargarTabla();
}

void GroupScheduleWidget::cargarTabla()
{
    // Limpiar tabla
    for(int f = 0; f < Horario::getNumFranjas(); f++) {
        for(int d = 0; d < Horario::getNumDias(); d++) {
            ui->scheduleTable->setItem(f, d + 1, new QTableWidgetItem(""));
        }
    }
    
    if (!m_grupos || m_currentId < 0) return;
    
    grupo* foundGrupo = nullptr;
    int groupIndex = -1;
    
    for(int i=0; i<m_grupos->getCantidad(); i++) {
        if(m_grupos->getGrupo(i)->getId() == m_currentId) {
            foundGrupo = m_grupos->getGrupo(i);
            groupIndex = i;
            break;
        }
    }
    
    if (!foundGrupo || groupIndex == -1) return;
    
    ui->nameLabel->setText(QString::fromUtf8(foundGrupo->getNombre()));
    
    // Cargar horario
    if (m_horarios && groupIndex < m_cantHorarios) {
        Horario* h = &m_horarios[groupIndex];
        
        for(int d=0; d<Horario::getNumDias(); d++) {
            for(int f=0; f<Horario::getNumFranjas(); f++) {
                CeldaHorario* celda = h->getCelda(d, f);
                if (celda && celda->ocupado) {
                    QString info;
                    
                    // Get teacher color for this cell
                    QColor cellColor(200, 200, 200); // Default gray
                    
                    if (strlen(celda->info) > 0) {
                        // Use parsed info from CSV
                        info = QString::fromUtf8(celda->info);
                        // Replace " - " with newline for better formatting
                        info.replace(" - ", "\n");
                    } else if (celda->id_materia != -1) {
                         // Fallback
                        // Materia
                        if (m_materias) {
                            for(int k=0; k<m_materias->getCantidad(); k++) {
                                if(m_materias->getMateria(k)->getId() == celda->id_materia) {
                                    info += QString::fromUtf8(m_materias->getMateria(k)->getNombre());
                                    break;
                                }
                            }
                        }
                        // Maestro
                        if (m_maestros && celda->id_maestro != -1) {
                            for(int k=0; k<m_maestros->getCantidad(); k++) {
                                if(m_maestros->getMaestro(k)->getId() == celda->id_maestro) {
                                    info += "\n" + QString::fromUtf8(m_maestros->getMaestro(k)->getNombre());
                                    break;
                                }
                            }
                        }
                        // Salon
                        if (m_salones && celda->id_salon != -1) {
                            for(int k=0; k<m_salones->getCantidad(); k++) {
                                if(m_salones->getSalon(k)->getId() == celda->id_salon) {
                                    info += "\n" + QString::fromUtf8(m_salones->getSalon(k)->getNombre());
                                    break;
                                }
                            }
                        }
                    }
                    
                    // Get teacher color for this cell
                    if (m_maestros && celda->id_maestro != -1) {
                        for(int k=0; k<m_maestros->getCantidad(); k++) {
                            if(m_maestros->getMaestro(k)->getId() == celda->id_maestro) {
                                maestro* teacher = m_maestros->getMaestro(k);
                                if (strlen(teacher->getColor()) > 0) {
                                    QString colorStr = QString::fromUtf8(teacher->getColor());
                                    colorStr = colorStr.remove('"').remove('\'');
                                    QStringList rgb = colorStr.split(",");
                                    if (rgb.size() == 3) {
                                        int r = rgb[0].trimmed().toInt();
                                        int g = rgb[1].trimmed().toInt();
                                        int b = rgb[2].trimmed().toInt();
                                        cellColor = QColor(r, g, b);
                                    }
                                }
                                break;
                            }
                        }
                    } else {
                        // Try to get teacher from info field (for CSV-loaded schedules)
                        if (!info.isEmpty() && m_maestros) {
                            QStringList parts = info.split("\n");
                            if (parts.size() >= 2) {
                                QString teacherName = parts[1].trimmed();
                                for(int k=0; k<m_maestros->getCantidad(); k++) {
                                    QString maestroName = QString::fromUtf8(m_maestros->getMaestro(k)->getNombre());
                                    if (maestroName == teacherName) {
                                        maestro* teacher = m_maestros->getMaestro(k);
                                        if (strlen(teacher->getColor()) > 0) {
                                            QString colorStr = QString::fromUtf8(teacher->getColor());
                                            colorStr = colorStr.remove('"').remove('\'');
                                            QStringList rgb = colorStr.split(",");
                                            if (rgb.size() == 3) {
                                                int r = rgb[0].trimmed().toInt();
                                                int g = rgb[1].trimmed().toInt();
                                                int b = rgb[2].trimmed().toInt();
                                                cellColor = QColor(r, g, b);
                                            }
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    
                    if (!info.isEmpty()) {
                        QTableWidgetItem* item = new QTableWidgetItem(info);
                        item->setTextAlignment(Qt::AlignCenter);
                        item->setBackground(QBrush(cellColor));
                        item->setForeground(QBrush(Qt::black));
                        
                        ui->scheduleTable->setItem(f, d + 1, item);
                    }
                }
            }
        }
    }
}

void GroupScheduleWidget::on_backButton_clicked()
{
    emit backClicked();
}

void GroupScheduleWidget::on_exportButton_clicked()
{
    if (m_currentId < 0 || !m_grupos) {
        QMessageBox::warning(this, "Error", "No hay horario cargado para exportar.");
        return;
    }
    
    grupo* g = nullptr;
    for(int i = 0; i < m_grupos->getCantidad(); i++) {
        if(m_grupos->getGrupo(i)->getId() == m_currentId) {
            g = m_grupos->getGrupo(i);
            break;
        }
    }
    
    if (!g) return;
    
    exportToCSV(g);
}

void GroupScheduleWidget::exportToCSV(grupo* g)
{
    QString fileName = QString("horario_%1.csv").arg(QString::fromUtf8(g->getNombre()).replace(" ", "_"));
    QString filePath = QFileDialog::getSaveFileName(this, "Guardar Horario", fileName, "CSV Files (*.csv)");
    
    if (filePath.isEmpty()) return;
    
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo crear el archivo.");
        return;
    }
    
    QTextStream out(&file);
    out.setCodec("UTF-8");
    
    // Header
    out << "Horario del Grupo: " << g->getNombre() << "\n\n";
    out << "Hora";
    for(int d = 0; d < Horario::getNumDias(); d++) {
        out << "," << Horario::getNombreDia(d);
    }
    out << "\n";
    
    // Data
    for(int f = 0; f < Horario::getNumFranjas(); f++) {
        out << Horario::getInicioFranja(f) << " - " << Horario::getFinFranja(f);
        for(int d = 0; d < Horario::getNumDias(); d++) {
            QTableWidgetItem* item = ui->scheduleTable->item(f, d + 1);
            if (item && !item->text().isEmpty()) {
                out << ",\"" << item->text() << "\"";
            } else {
                out << ",";
            }
        }
        out << "\n";
    }
    
    file.close();
    QMessageBox::information(this, "Éxito", "Horario exportado correctamente a:\n" + filePath);
}
