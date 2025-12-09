#include "quarterdetailswidget.h"
#include "ui_quarterdetailswidget.h"
#include "../include/conjunto_materias.h"
#include "../include/materias.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

QuarterDetailsWidget::QuarterDetailsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuarterDetailsWidget)
{
    ui->setupUi(this);
    
    // Configurar tabla
    ui->subjectsTable->setColumnCount(2);
    ui->subjectsTable->setHorizontalHeaderLabels({"Materia", "Horas"});
    ui->subjectsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

QuarterDetailsWidget::~QuarterDetailsWidget()
{
    delete ui;
}

void QuarterDetailsWidget::setData(ConjuntoMaterias* c, materias* m)
{
    m_conjuntos = c;
    m_materias = m;
}

void QuarterDetailsWidget::cargarDatos(int id)
{
    m_currentId = id;
    if (!m_conjuntos || id < 0 || id >= m_conjuntos->getCantidad()) return;
    
    Set* s = m_conjuntos->getSet(id);
    if (!s) return;
    
    ui->titleLabel->setText(QString::fromUtf8(s->nombre.c_str()));
    cargarTabla();
}

void QuarterDetailsWidget::cargarTabla()
{
    if (!m_conjuntos || m_currentId < 0) return;
    
    Set* s = m_conjuntos->getSet(m_currentId);
    if (!s) return;
    
    ui->subjectsTable->setRowCount(0);
    
    for(int i = 0; i < s->cant_materias; i++) {
        int matId = s->materia_ids[i];
        materia* m = m_materias->getMateria(matId);
        
        if (m) {
            int row = ui->subjectsTable->rowCount();
            ui->subjectsTable->insertRow(row);
            
            ui->subjectsTable->setItem(row, 0, new QTableWidgetItem(QString::fromUtf8(m->getNombre())));
            ui->subjectsTable->setItem(row, 1, new QTableWidgetItem(QString::number(m->getHorasNecesarias())));
        }
    }
}

void QuarterDetailsWidget::on_backButton_clicked()
{
    emit backClicked();
}

void QuarterDetailsWidget::on_applyButton_clicked()
{
    // Por ahora no hay nada que aplicar ya que los cambios se hacen directos
    // Pero podríamos usar esto para guardar en CSV si fuera necesario
    emit applyClicked();
}

void QuarterDetailsWidget::on_addSubjectButton_clicked()
{
    if (!m_materias || !m_conjuntos || m_currentId < 0) return;
    
    // Crear lista de materias disponibles
    QStringList items;
    QList<int> ids;
    
    for(int i = 0; i < m_materias->getCantidad(); i++) {
        materia* m = m_materias->getMateria(i);
        if (m) {
            items << QString::fromUtf8(m->getNombre());
            ids << i;
        }
    }
    
    bool ok;
    QString item = QInputDialog::getItem(this, "Agregar Materia", 
                                         "Selecciona una materia:", items, 0, false, &ok);
    if (ok && !item.isEmpty()) {
        int index = items.indexOf(item);
        if (index >= 0 && index < ids.size()) {
            int matId = ids[index];
            
            // Verificar si ya existe en el conjunto
            Set* s = m_conjuntos->getSet(m_currentId);
            bool existe = false;
            for(int i=0; i<s->cant_materias; i++) {
                if(s->materia_ids[i] == matId) {
                    existe = true;
                    break;
                }
            }
            
            if (!existe) {
                m_conjuntos->agregarMateriaASet(m_currentId, matId);
                cargarTabla();
            } else {
                QMessageBox::warning(this, "Error", "La materia ya está en este cuatrimestre.");
            }
        }
    }
}

void QuarterDetailsWidget::prepararNuevo()
{
    m_currentId = -1;
    ui->titleLabel->setText("Nuevo Cuatrimestre");
    ui->subjectsTable->setRowCount(0);
    
    // Ask for name
    bool ok;
    QString nombre = QInputDialog::getText(this, "Nuevo Cuatrimestre",
                                          "Nombre del cuatrimestre:", QLineEdit::Normal,
                                          "", &ok);
    if (ok && !nombre.isEmpty()) {
        // TODO: Create new Set in ConjuntoMaterias
        QMessageBox::information(this, "Información", 
            "Funcionalidad de creación pendiente de implementar en la clase ConjuntoMaterias.\n"
            "Nombre: " + nombre);
        emit backClicked();
    } else {
        emit backClicked();
    }
}

void QuarterDetailsWidget::on_removeSubjectButton_clicked()
{
    if (!m_conjuntos || m_currentId < 0) return;
    
    int currentRow = ui->subjectsTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Error", "Selecciona una materia para eliminar.");
        return;
    }
    
    Set* s = m_conjuntos->getSet(m_currentId);
    if (!s || currentRow >= s->cant_materias) return;
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Eliminar Materia",
        "¿Estás seguro de eliminar esta materia del cuatrimestre?",
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        // TODO: Implement remove materia from set
        QMessageBox::information(this, "Información", 
            "Funcionalidad de eliminación pendiente de implementar en la clase ConjuntoMaterias.");
    }
}

void QuarterDetailsWidget::on_editNameButton_clicked()
{
    if (!m_conjuntos || m_currentId < 0) return;
    
    Set* s = m_conjuntos->getSet(m_currentId);
    if (!s) return;
    
    bool ok;
    QString nuevoNombre = QInputDialog::getText(this, "Editar Nombre",
                                               "Nuevo nombre del cuatrimestre:",
                                               QLineEdit::Normal,
                                               QString::fromStdString(s->nombre), &ok);
    if (ok && !nuevoNombre.isEmpty()) {
        s->nombre = nuevoNombre.toStdString();
        ui->titleLabel->setText(nuevoNombre);
        QMessageBox::information(this, "Éxito", "Nombre actualizado correctamente.");
    }
}
