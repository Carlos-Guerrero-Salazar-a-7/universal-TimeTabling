#include "teacherschedulewidget.h"
#include "ui_teacherschedulewidget.h"
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

TeacherScheduleWidget::TeacherScheduleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherScheduleWidget)
{
    ui->setupUi(this);
    
    // CRITICAL: Remove ALL stylesheets from table to allow cell colors to show
    ui->scheduleTable->setStyleSheet("");
    qDebug() << "TeacherScheduleWidget: Cleared table stylesheet";
    
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

TeacherScheduleWidget::~TeacherScheduleWidget()
{
    delete ui;
}

void TeacherScheduleWidget::setData(maestros* m, materias* mat, grupos* g, salones* s, Horario* h, int cantH)
{
    m_maestros = m;
    m_materias = mat;
    m_grupos = g;
    m_salones = s;
    m_horarios = h;
    m_cantHorarios = cantH;
}

void TeacherScheduleWidget::loadSchedule(int id)
{
    m_currentTeacherId = id;
    cargarTabla();
}

void TeacherScheduleWidget::cargarTabla()
{
    // Limpiar tabla
    for(int f = 0; f < Horario::getNumFranjas(); f++) {
        for(int d = 0; d < Horario::getNumDias(); d++) {
            ui->scheduleTable->setItem(f, d + 1, new QTableWidgetItem(""));
        }
    }
    
    if (!m_maestros || m_currentTeacherId < 0) return;
    
    maestro* foundMaestro = nullptr;
    int teacherIndex = -1;
    
    for(int i = 0; i < m_maestros->getCantidad(); i++) {
        if(m_maestros->getMaestro(i)->getId() == m_currentTeacherId) {
            foundMaestro = m_maestros->getMaestro(i);
            teacherIndex = i;
            break;
        }
    }
    
    if (!foundMaestro || teacherIndex == -1) return;
    
    ui->nameLabel->setText(QString::fromUtf8(foundMaestro->getNombre()));
    
    // Cargar horario
    if (m_horarios && teacherIndex < m_cantHorarios) {
        Horario* h = &m_horarios[teacherIndex];
        
        for(int d=0; d<Horario::getNumDias(); d++) {
            for(int f=0; f<Horario::getNumFranjas(); f++) {
                CeldaHorario* celda = h->getCelda(d, f);
                if (celda && celda->ocupado) {
                    QString info;
                    
                    // Get group color for this cell
                    QColor cellColor(200, 200, 200); // Default gray
                    
                    if (strlen(celda->info) > 0) {
                        // Use parsed info from CSV
                        info = QString::fromUtf8(celda->info);
                        info.replace(" - ", "\n");
                    } else if (celda->id_materia != -1) {
                        // Fallback
                        if (m_materias) {
                            for(int k=0; k<m_materias->getCantidad(); k++) {
                                if(m_materias->getMateria(k)->getId() == celda->id_materia) {
                                    info += QString::fromUtf8(m_materias->getMateria(k)->getNombre());
                                    break;
                                }
                            }
                        }
                        if (m_grupos && celda->id_grupo != -1) {
                            for(int k=0; k<m_grupos->getCantidad(); k++) {
                                if(m_grupos->getGrupo(k)->getId() == celda->id_grupo) {
                                    info += "\n" + QString::fromUtf8(m_grupos->getGrupo(k)->getNombre());
                                    break;
                                }
                            }
                        }
                        if (m_salones && celda->id_salon != -1) {
                            for(int k=0; k<m_salones->getCantidad(); k++) {
                                if(m_salones->getSalon(k)->getId() == celda->id_salon) {
                                    info += "\n" + QString::fromUtf8(m_salones->getSalon(k)->getNombre());
                                    break;
                                }
                            }
                        }
                    }
                    
                    // Get GROUP color for this cell
                    if (m_grupos && celda->id_grupo != -1) {
                        for(int k=0; k<m_grupos->getCantidad(); k++) {
                            if(m_grupos->getGrupo(k)->getId() == celda->id_grupo) {
                                grupo* grp = m_grupos->getGrupo(k);
                                if (strlen(grp->getColor()) > 0) {
                                    QString colorStr = QString::fromUtf8(grp->getColor());
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
                        // Try to get group from info field (for CSV-loaded schedules)
                        if (!info.isEmpty() && m_grupos) {
                            QStringList parts = info.split("\n");
                            if (parts.size() >= 2) {
                                QString groupName = parts[1].trimmed(); // Second line is group name
                                for(int k=0; k<m_grupos->getCantidad(); k++) {
                                    QString grupoName = QString::fromUtf8(m_grupos->getGrupo(k)->getNombre());
                                    if (grupoName == groupName) {
                                        grupo* grp = m_grupos->getGrupo(k);
                                        if (strlen(grp->getColor()) > 0) {
                                            QString colorStr = QString::fromUtf8(grp->getColor());
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
                        
                        // Use GROUP color for teacher schedules
                        item->setBackground(QBrush(cellColor));
                        item->setForeground(QBrush(Qt::black));
                        
                        ui->scheduleTable->setItem(f, d + 1, item);
                    }
                }
            }
        }
    }
}

void TeacherScheduleWidget::on_backButton_clicked()
{
    emit backClicked();
}

void TeacherScheduleWidget::on_exportButton_clicked()
{
    if (m_currentTeacherId < 0 || !m_maestros) {
        QMessageBox::warning(this, "Error", "No hay horario cargado para exportar.");
        return;
    }
    
    maestro* m = nullptr;
    for(int i = 0; i < m_maestros->getCantidad(); i++) {
        if(m_maestros->getMaestro(i)->getId() == m_currentTeacherId) {
            m = m_maestros->getMaestro(i);
            break;
        }
    }
    
    if (!m) return;
    
    exportToCSV(m);
}

void TeacherScheduleWidget::exportToCSV(maestro* m)
{
    QString fileName = QString("horario_%1.csv").arg(QString::fromUtf8(m->getNombre()).replace(" ", "_"));
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
    out << "Horario del Maestro: " << m->getNombre() << "\n\n";
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
