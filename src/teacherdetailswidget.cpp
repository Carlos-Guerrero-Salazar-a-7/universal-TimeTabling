#include "teacherdetailswidget.h"
#include "ui_teacherdetailswidget.h"
#include "../include/maestros.h"
#include "../include/materias.h"
#include "../include/horario_disponibilidad.h"
#include <QMessageBox>
#include <QPushButton>
#include <QColorDialog>
#include <QListWidget>
#include <QLabel>
#include <QFrame>

TeacherDetailsWidget::TeacherDetailsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherDetailsWidget)
{
    ui->setupUi(this);
    
    // Connect color picker click
    ui->colorPicker->installEventFilter(this);
    
    // Initialize selected subjects list
    m_selectedSubjects.clear();
    
    // Create subject lists dynamically
    createSubjectLists();
}

TeacherDetailsWidget::~TeacherDetailsWidget()
{
    delete ui;
}


void TeacherDetailsWidget::createSubjectLists()
{
    // Create frame for available subjects
    QFrame* availableFrame = new QFrame(this);
    availableFrame->setGeometry(160, 330, 520, 180);
    availableFrame->setStyleSheet(
        "QFrame {"
        "    background-color: #f9f9f9;"
        "    border: 2px solid #ccc;"
        "    border-radius: 10px;"
        "}"
    );
    
    // Label for available subjects
    QLabel* availableLabel = new QLabel("Materias Disponibles", availableFrame);
    availableLabel->setGeometry(10, 10, 200, 25);
    availableLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #555; background: transparent; border: none;");
    
    // Create available subjects list
    m_availableList = new QListWidget(availableFrame);
    m_availableList->setGeometry(10, 40, 500, 100);
    m_availableList->setStyleSheet(
        "QListWidget {"
        "    background-color: white;"
        "    border: 2px solid #3498db;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    font-size: 12px;"
        "}"
        "QListWidget::item {"
        "    padding: 5px;"
        "    border-bottom: 1px solid #eee;"
        "}"
        "QListWidget::item:selected {"
        "    background-color: #3498db;"
        "    color: white;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: #e8f4f8;"
        "}"
    );
    
    // Create add button
    QPushButton* addBtn = new QPushButton("Agregar >>", availableFrame);
    addBtn->setGeometry(390, 145, 120, 30);
    addBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #2ecc71;"
        "    color: white;"
        "    border-radius: 5px;"
        "    font-weight: bold;"
        "    font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #27ae60;"
        "}"
    );
    addBtn->setCursor(Qt::PointingHandCursor);
    connect(addBtn, &QPushButton::clicked, this, &TeacherDetailsWidget::onAddSubject);
    
    // Create frame for assigned subjects
    QFrame* assignedFrame = new QFrame(this);
    assignedFrame->setGeometry(700, 330, 520, 180);
    assignedFrame->setStyleSheet(
        "QFrame {"
        "    background-color: #f9f9f9;"
        "    border: 2px solid #ccc;"
        "    border-radius: 10px;"
        "}"
    );
    
    // Label for assigned subjects
    QLabel* assignedLabel = new QLabel("Materias que Puede Impartir", assignedFrame);
    assignedLabel->setGeometry(10, 10, 250, 25);
    assignedLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #555; background: transparent; border: none;");
    
    // Create assigned subjects list
    m_assignedList = new QListWidget(assignedFrame);
    m_assignedList->setGeometry(10, 40, 500, 100);
    m_assignedList->setStyleSheet(
        "QListWidget {"
        "    background-color: white;"
        "    border: 2px solid #e74c3c;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    font-size: 12px;"
        "}"
        "QListWidget::item {"
        "    padding: 5px;"
        "    border-bottom: 1px solid #eee;"
        "}"
        "QListWidget::item:selected {"
        "    background-color: #e74c3c;"
        "    color: white;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: #fce8e6;"
        "}"
    );
    
    // Create remove button
    QPushButton* removeBtn = new QPushButton("<< Quitar", assignedFrame);
    removeBtn->setGeometry(10, 145, 120, 30);
    removeBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #e74c3c;"
        "    color: white;"
        "    border-radius: 5px;"
        "    font-weight: bold;"
        "    font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #c0392b;"
        "}"
    );
    removeBtn->setCursor(Qt::PointingHandCursor);
    connect(removeBtn, &QPushButton::clicked, this, &TeacherDetailsWidget::onRemoveSubject);
}

void TeacherDetailsWidget::setData(maestros* ma, materias* m)
{
    m_maestros = ma;
    m_materias = m;
    
    // Populate time range combo boxes
    ui->fromComboBox->clear();
    ui->toComboBox->clear();
    for(int i = 0; i < horario_disponibilidad::getNumFranjas(); i++) {
        QString hora = QString("%1 - %2")
            .arg(horario_disponibilidad::getInicioFranja(i))
            .arg(horario_disponibilidad::getFinFranja(i));
        ui->fromComboBox->addItem(hora, i);
        ui->toComboBox->addItem(hora, i);
    }
    
    // Populate available subjects list
    loadAvailableSubjects();
}



void TeacherDetailsWidget::cargarDatos(int id)
{
    m_currentId = id;
    if (!m_maestros) return;
    
    maestro* m = nullptr;
    for(int i = 0; i < m_maestros->getCantidad(); i++) {
        if(m_maestros->getMaestro(i)->getId() == id) {
            m = m_maestros->getMaestro(i);
            break;
        }
    }
    
    if (m) {
        // Load name
        ui->nameLineEdit->setText(QString::fromUtf8(m->getNombre()));
        
        // Load specialty (if available)
        ui->specialtyLineEdit->clear();
        
        // Load color
        QString colorStr = QString::fromUtf8(m->getColor());
        if (!colorStr.isEmpty()) {
            QStringList rgb = colorStr.split(',');
            if (rgb.size() == 3) {
                m_selectedColor = QColor(rgb[0].toInt(), rgb[1].toInt(), rgb[2].toInt());
                ui->selectedColor->setStyleSheet(QString("background-color: %1; border-radius: 5px;")
                    .arg(m_selectedColor.name()));
            }
        }
        
        // Load subjects teacher can teach
        m_selectedSubjects.clear();
        for(int i = 0; i < m->getCantidadMaterias(); i++) {
            m_selectedSubjects.insert(m->getIdMateria(i));
        }
        
        // Refresh subject lists
        loadAvailableSubjects();
        loadAssignedSubjects();
        
        // Parse availability schedule to get time range
        // For simplicity, we'll just set default range
        ui->fromComboBox->setCurrentIndex(0); // 7:00
        ui->toComboBox->setCurrentIndex(8);   // 14:00
        
        ui->titleLabel->setText("Editar Maestro");
        ui->createButton->setText("Guardar");
        ui->deleteButton->setVisible(true);
    }
}

void TeacherDetailsWidget::prepararNuevoMaestro()
{
    m_currentId = -1;
    ui->nameLineEdit->clear();
    ui->specialtyLineEdit->clear();
    
    // Set default time range
    ui->fromComboBox->setCurrentIndex(0); // 7:00
    ui->toComboBox->setCurrentIndex(8);   // 14:00
    
    // Set default color
    m_selectedColor = QColor(255, 0, 0); // Red
    ui->selectedColor->setStyleSheet("background-color: #ff0000; border-radius: 5px;");
    
    // Clear subject selections
    m_selectedSubjects.clear();
    loadAvailableSubjects();
    loadAssignedSubjects();
    
    ui->titleLabel->setText("Crear Nuevo Maestro");
    ui->createButton->setText("Crear Maestro");
    ui->deleteButton->setVisible(false);
}

void TeacherDetailsWidget::on_backButton_clicked()
{
    emit backClicked();
}

void TeacherDetailsWidget::on_createButton_clicked()
{
    if (!m_maestros) return;
    
    // Validate name
    QString nombre = ui->nameLineEdit->text().trimmed();
    if (nombre.isEmpty()) {
        QMessageBox::warning(this, "Error", "El nombre del maestro no puede estar vacío.");
        return;
    }
    
    // Get time range
    int franjaInicio = ui->fromComboBox->currentData().toInt();
    int franjaFin = ui->toComboBox->currentData().toInt();
    
    if (franjaInicio > franjaFin) {
        QMessageBox::warning(this, "Error", "La hora de inicio debe ser menor o igual a la hora de fin.");
        return;
    }
    
    // Build availability schedule string
    // Format: (Lunes:HH:MM-HH:MM;Martes:HH:MM-HH:MM;...)
    QString horaInicio = QString::fromUtf8(horario_disponibilidad::getInicioFranja(franjaInicio));
    QString horaFin = QString::fromUtf8(horario_disponibilidad::getFinFranja(franjaFin));
    
    QString horarioStr = QString("(Lunes:%1-%2;Martes:%1-%2;Miercoles:%1-%2;Jueves:%1-%2;Viernes:%1-%2)")
        .arg(horaInicio).arg(horaFin);
    
    // Get color as RGB string
    QString colorStr = QString("%1,%2,%3")
        .arg(m_selectedColor.red())
        .arg(m_selectedColor.green())
        .arg(m_selectedColor.blue());
    
    if (m_currentId == -1) {
        // Create new maestro
        maestro* nuevoMaestro = new maestro();
        nuevoMaestro->setId(m_maestros->getCantidad());
        nuevoMaestro->setNombre(nombre.toUtf8().constData());
        nuevoMaestro->setHorario(horarioStr.toUtf8().constData());
        nuevoMaestro->setColor(colorStr.toUtf8().constData());
        
        // Add selected subjects
        for(int subjectId : m_selectedSubjects) {
            nuevoMaestro->addIdMateria(subjectId);
        }
        
        m_maestros->addMaestro(nuevoMaestro);
    } else {
        // Update existing maestro
        maestro* m = nullptr;
        for(int i = 0; i < m_maestros->getCantidad(); i++) {
            if(m_maestros->getMaestro(i)->getId() == m_currentId) {
                m = m_maestros->getMaestro(i);
                break;
            }
        }
        
        if (m) {
            m->setNombre(nombre.toUtf8().constData());
            m->setHorario(horarioStr.toUtf8().constData());
            m->setColor(colorStr.toUtf8().constData());
            
            // Update subjects
            m->clearMaterias();
            for(int subjectId : m_selectedSubjects) {
                m->addIdMateria(subjectId);
            }
        }
    }
    
    // Save to CSV
    m_maestros->guardarCSV(m_materias);
    
    emit applyClicked();
}

bool TeacherDetailsWidget::eventFilter(QObject* obj, QEvent* event)
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

void TeacherDetailsWidget::loadAvailableSubjects()
{
    if (!m_materias) return;
    
    m_availableList->clear();
    for(int i = 0; i < m_materias->getCantidad(); i++) {
        materia* mat = m_materias->getMateria(i);
        if (mat && !m_selectedSubjects.contains(mat->getId())) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromUtf8(mat->getNombre()));
            item->setData(Qt::UserRole, mat->getId());
            m_availableList->addItem(item);
        }
    }
}

void TeacherDetailsWidget::loadAssignedSubjects()
{
    if (!m_materias) return;
    
    m_assignedList->clear();
    for(int subjectId : m_selectedSubjects) {
        materia* mat = m_materias->getMateria(subjectId);
        if (mat) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromUtf8(mat->getNombre()));
            item->setData(Qt::UserRole, mat->getId());
            m_assignedList->addItem(item);
        }
    }
}

void TeacherDetailsWidget::onAddSubject()
{
    QListWidgetItem* item = m_availableList->currentItem();
    if (item) {
        int subjectId = item->data(Qt::UserRole).toInt();
        m_selectedSubjects.insert(subjectId);
        loadAvailableSubjects();
        loadAssignedSubjects();
    }
}

void TeacherDetailsWidget::onRemoveSubject()
{
    QListWidgetItem* item = m_assignedList->currentItem();
    if (item) {
        int subjectId = item->data(Qt::UserRole).toInt();
        m_selectedSubjects.remove(subjectId);
        loadAvailableSubjects();
        loadAssignedSubjects();
    }
}
