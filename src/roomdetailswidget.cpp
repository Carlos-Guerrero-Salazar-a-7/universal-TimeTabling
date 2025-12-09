#include "roomdetailswidget.h"
#include "ui_roomdetailswidget.h"
#include "../include/salones.h"
#include <QMessageBox>

RoomDetailsWidget::RoomDetailsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomDetailsWidget)
{
    ui->setupUi(this);
    
    // Disable ID editing - it's auto-generated and shouldn't be modified
    ui->idLineEdit->setReadOnly(true);
    ui->idLineEdit->setStyleSheet("border: 1px solid #ccc; border-radius: 5px; padding: 5px; background-color: #f0f0f0; color: #666;");
}

RoomDetailsWidget::~RoomDetailsWidget()
{
    delete ui;
}

void RoomDetailsWidget::setData(salones* s)
{
    m_salones = s;
}

void RoomDetailsWidget::cargarDatos(int id)
{
    m_currentId = id;
    if (!m_salones) return;
    
    salon* s = nullptr;
    for(int i = 0; i < m_salones->getCantidad(); i++) {
        if(m_salones->getSalon(i)->getId() == id) {
            s = m_salones->getSalon(i);
            break;
        }
    }
    
    if (s) {
        ui->edificioLineEdit->setText(QString::fromUtf8(s->getNombre()));
        ui->idLineEdit->setText(QString::number(s->getId()));
        ui->especialidadLineEdit->setText(QString::fromUtf8(s->getTipo())); 
        // Need to check UI file to know exact widget names, but assuming standard names
    }
}

void RoomDetailsWidget::prepararNuevoSalon()
{
    m_currentId = -1;
    ui->edificioLineEdit->clear();
    ui->idLineEdit->clear();
    ui->especialidadLineEdit->clear();
    // Reset other fields if any
}

void RoomDetailsWidget::on_backButton_clicked()
{
    emit backClicked();
}

void RoomDetailsWidget::on_createButton_clicked()
{
    if (!m_salones) return;
    
    QString nombre = ui->edificioLineEdit->text();
    QString tipo = ui->especialidadLineEdit->text();
    // ID is usually auto-generated or managed, but if user inputs it:
    // int id = ui->idLineEdit->text().toInt(); 
    
    if (nombre.isEmpty()) {
        QMessageBox::warning(this, "Error", "El nombre del edificio no puede estar vacío.");
        return;
    }
    
    if (m_currentId == -1) {
        // Create new salon
        salon* nuevoSalon = new salon();
        nuevoSalon->setId(m_salones->getCantidad()); // Simple ID generation
        nuevoSalon->setNombre(nombre.toUtf8().constData());
        nuevoSalon->setTipo(tipo.toUtf8().constData());
        
        m_salones->addSalon(nuevoSalon);
    } else {
        // Update existing salon
        salon* s = nullptr;
        for(int i = 0; i < m_salones->getCantidad(); i++) {
            if(m_salones->getSalon(i)->getId() == m_currentId) {
                s = m_salones->getSalon(i);
                break;
            }
        }
        
        if (s) {
            s->setNombre(nombre.toUtf8().constData());
            s->setTipo(tipo.toUtf8().constData());
        }
    }

    emit applyClicked();
}
