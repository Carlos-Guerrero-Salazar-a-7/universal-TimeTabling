#include "groupdetailswidget.h"
#include "ui_groupdetailswidget.h"
#include "../include/grupos.h"
#include "../include/materias.h"
#include "../include/maestros.h"
#include "../include/conjunto_materias.h"
#include "../include/horario.h"
#include <QMessageBox>
#include <QDebug>
#include <QColorDialog>

GroupDetailsWidget::GroupDetailsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupDetailsWidget)
{
    ui->setupUi(this);
    
    // Connect color picker click
    ui->colorPicker->installEventFilter(this);
    
    // Set default color
    m_selectedColor = QColor(255, 0, 0); // Red
    
    // Conectar cambio de índice en combo de cuatrimestres para actualizar materias (opcional)
    // connect(ui->quarterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &GroupDetailsWidget::actualizarMaterias);
}

GroupDetailsWidget::~GroupDetailsWidget()
{
    delete ui;
}

void GroupDetailsWidget::setData(grupos* g, materias* m, maestros* ma, ConjuntoMaterias* c)
{
    m_grupos = g;
    m_materias = m;
    m_maestros = ma;
    m_conjuntos = c;
    
    // Llenar combobox de conjuntos de materias (Cuatrimestres)
    ui->quarterComboBox->clear();
    if (m_conjuntos) {
        for(int i=0; i<m_conjuntos->getCantidad(); i++) {
            Set* s = m_conjuntos->getSet(i);
            if (s) {
                ui->quarterComboBox->addItem(QString::fromStdString(s->nombre), i);
            }
        }
    }
    
    // Llenar combos de horas
    ui->fromComboBox->clear();
    ui->toComboBox->clear();
    for(int i=0; i<Horario::getNumFranjas(); i++) {
        QString hora = QString("%1 - %2").arg(Horario::getInicioFranja(i)).arg(Horario::getFinFranja(i));
        ui->fromComboBox->addItem(hora, i);
        ui->toComboBox->addItem(hora, i);
    }
}

void GroupDetailsWidget::prepararNuevoGrupo()
{
    m_currentGroupId = -1;
    ui->titleLabel->setText("Crear Nuevo Grupo");
    ui->createButton->setText("Crear Grupo");
    ui->deleteButton->setVisible(false);
    
    ui->nameLineEdit->clear();
    ui->quarterComboBox->setCurrentIndex(-1);
    ui->fromComboBox->setCurrentIndex(0); // 7:00
    ui->toComboBox->setCurrentIndex(6);   // 12:55 (aprox)
    
    // Set default color
    m_selectedColor = QColor(255, 0, 0); // Red
    ui->selectedColor->setStyleSheet("background-color: #ff0000; border-radius: 5px;");
}

void GroupDetailsWidget::cargarGrupoForEdit(int id)
{
    if (!m_grupos) return;
    grupo* g = m_grupos->getGrupo(id);
    if (!g) return;
    
    m_currentGroupId = id;
    ui->titleLabel->setText("Editar Grupo");
    ui->createButton->setText("Guardar");
    ui->deleteButton->setVisible(true);
    
    ui->nameLineEdit->setText(QString::fromUtf8(g->getNombre()));
    
    // Seleccionar conjunto de materias
    int setId = g->getConjuntoDeMaterias();
    int index = ui->quarterComboBox->findData(setId);
    if (index != -1) {
        ui->quarterComboBox->setCurrentIndex(index);
    }
    
    // Seleccionar horarios
    int inicio = g->getFranjaInicio();
    int fin = g->getFranjaFin();
    
    if (inicio >= 0 && inicio < ui->fromComboBox->count())
        ui->fromComboBox->setCurrentIndex(inicio);
        
    if (fin >= 0 && fin < ui->toComboBox->count())
        ui->toComboBox->setCurrentIndex(fin);
    
    // Load color
    QString colorStr = QString::fromUtf8(g->getColor());
    if (!colorStr.isEmpty()) {
        QStringList rgb = colorStr.split(',');
        if (rgb.size() == 3) {
            m_selectedColor = QColor(rgb[0].toInt(), rgb[1].toInt(), rgb[2].toInt());
            ui->selectedColor->setStyleSheet(QString("background-color: %1; border-radius: 5px;")
                .arg(m_selectedColor.name()));
        }
    }
}

void GroupDetailsWidget::on_createButton_clicked()
{
    if (ui->nameLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "El nombre del grupo no puede estar vacío.");
        return;
    }
    
    if (ui->quarterComboBox->currentIndex() == -1) {
        QMessageBox::warning(this, "Error", "Debe seleccionar un cuatrimestre (conjunto de materias).");
        return;
    }
    
    QString nombre = ui->nameLineEdit->text();
    int setId = ui->quarterComboBox->currentData().toInt();
    int inicio = ui->fromComboBox->currentData().toInt();
    int fin = ui->toComboBox->currentData().toInt();
    
    if (inicio > fin) {
        QMessageBox::warning(this, "Error", "La hora de inicio debe ser menor o igual a la hora de fin.");
        return;
    }
    
    // Get color as RGB string
    QString colorStr = QString("%1,%2,%3")
        .arg(m_selectedColor.red())
        .arg(m_selectedColor.green())
        .arg(m_selectedColor.blue());
    
    if (m_currentGroupId == -1) {
        // Crear nuevo grupo
        grupo* nuevoGrupo = new grupo();
        nuevoGrupo->setId(m_grupos->getCantidad()); // Asignar nuevo ID
        nuevoGrupo->setNombre(nombre.toUtf8().constData());
        nuevoGrupo->setConjuntoDeMaterias(setId);
        nuevoGrupo->setFranjaInicio(inicio);
        nuevoGrupo->setFranjaFin(fin);
        nuevoGrupo->setColor(colorStr.toUtf8().constData());
        
        m_grupos->addGrupo(nuevoGrupo);
    } else {
        // Editar grupo existente
        grupo* g = m_grupos->getGrupo(m_currentGroupId);
        if (g) {
            g->setNombre(nombre.toUtf8().constData());
            g->setConjuntoDeMaterias(setId);
            g->setFranjaInicio(inicio);
            g->setFranjaFin(fin);
            g->setColor(colorStr.toUtf8().constData());
        }
    }
    
    // Save to CSV
    m_grupos->guardarCSV(m_conjuntos);
    
    emit applyClicked();
    emit finalizado();
}

void GroupDetailsWidget::on_backButton_clicked()
{
    emit backClicked();
}

void GroupDetailsWidget::cargarDatos(int id)
{
    cargarGrupoForEdit(id);
}

void GroupDetailsWidget::on_deleteButton_clicked()
{
    if (m_currentGroupId == -1 || !m_grupos) return;
    
    grupo* g = m_grupos->getGrupo(m_currentGroupId);
    if (!g) return;
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Eliminar Grupo",
        QString("¿Estás seguro de eliminar el grupo '%1'?\n\nEsta acción no se puede deshacer.")
            .arg(QString::fromUtf8(g->getNombre())),
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        m_grupos->eliminar(m_currentGroupId);
        m_grupos->guardarCSV(m_conjuntos);
        QMessageBox::information(this, "Éxito", "Grupo eliminado correctamente.");
        emit finalizado();
    }
}

bool GroupDetailsWidget::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == ui->colorPicker && event->type() == QEvent::MouseButtonPress) {
        QColor color = QColorDialog::getColor(m_selectedColor, this, "Seleccionar Color");
        if (color.isValid()) {
            m_selectedColor = color;
            ui->selectedColor->setStyleSheet(QString("background-color: %1; border-radius: 5px;")
                .arg(color.name()));
        }
        return true;
    }
    return QWidget::eventFilter(obj, event);
}
