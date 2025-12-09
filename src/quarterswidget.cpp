#include "quarterswidget.h"
#include "ui_quarterswidget.h"
#include "../include/conjunto_materias.h"
#include "../include/materias.h"
#include <QDebug>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QSpacerItem>
#include <QPushButton>
#include <QMessageBox>



QuartersWidget::QuartersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuartersWidget)
{
    ui->setupUi(this);
    ui->itemFrame->setVisible(false); // Hide template
}

QuartersWidget::~QuartersWidget()
{
    delete ui;
}

void QuartersWidget::setData(ConjuntoMaterias* c, materias* m)
{
    m_conjuntos = c;
    m_materias = m;
    cargarCuatrimestres();
}

void QuartersWidget::cargarCuatrimestres()
{
    limpiarLayout();
    
    if (!m_conjuntos || !m_materias) return;
    
    QString searchText = ui->searchLineEdit->text().toLower();
    
    for(int i = 0; i < m_conjuntos->getCantidad(); i++) {
        Set* s = m_conjuntos->getSet(i);
        if (!s) continue;
        
        QString nombre = QString::fromUtf8(s->nombre.c_str());
        if (!searchText.isEmpty() && !nombre.toLower().contains(searchText)) {
            continue;
        }
        
        // Calcular horas totales
        int totalHoras = 0;
        for(int j = 0; j < s->cant_materias; j++) {
            materia* m = m_materias->getMateria(s->materia_ids[j]);
            if (m) {
                totalHoras += m->getHorasNecesarias();
            }
        }
        
        // Crear widget
        ClickableFrame* item = new ClickableFrame(ui->scrollAreaWidgetContents);
        item->setQuarterId(i);
        item->setMinimumSize(0, 80);
        item->setStyleSheet(ui->itemFrame->styleSheet());
        item->setCursor(Qt::PointingHandCursor);
        connect(item, &ClickableFrame::clicked, this, &QuartersWidget::on_quarterClicked);
        
        QHBoxLayout* layout = new QHBoxLayout(item);
        layout->setContentsMargins(20, 0, 20, 0);
        
        QLabel* nameLabel = new QLabel(nombre, item);
        nameLabel->setStyleSheet(ui->quarterNameLabel->styleSheet());
        
        QFrame* line1 = new QFrame(item);
        line1->setFrameShape(QFrame::VLine);
        line1->setFrameShadow(QFrame::Sunken);
        
        QLabel* subjectsLabel = new QLabel(QString("%1 Materias").arg(s->cant_materias), item);
        subjectsLabel->setStyleSheet(ui->subjectsCountLabel->styleSheet());
        
        QFrame* line2 = new QFrame(item);
        line2->setFrameShape(QFrame::VLine);
        line2->setFrameShadow(QFrame::Sunken);
        
        QLabel* hoursLabel = new QLabel(QString("%1 Horas").arg(totalHoras), item);
        hoursLabel->setStyleSheet(ui->hoursCountLabel->styleSheet());
        
        // Add spacer
        QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        
        // Edit button
        QPushButton* editBtn = new QPushButton("Editar", item);
        editBtn->setStyleSheet("background-color: #3498db; color: white; border-radius: 5px; padding: 5px 15px; font-weight: bold;");
        editBtn->setCursor(Qt::PointingHandCursor);
        editBtn->setProperty("quarterId", i);
        connect(editBtn, &QPushButton::clicked, this, [this, id = i]() {
            handleEditQuarter(id);
        });
        
        // Delete button
        QPushButton* deleteBtn = new QPushButton("Eliminar", item);
        deleteBtn->setStyleSheet("background-color: #e74c3c; color: white; border-radius: 5px; padding: 5px 15px; font-weight: bold;");
        deleteBtn->setCursor(Qt::PointingHandCursor);
        deleteBtn->setProperty("quarterId", i);
        connect(deleteBtn, &QPushButton::clicked, this, [this, id = i]() {
            handleDeleteQuarter(id);
        });
        
        layout->addWidget(nameLabel);
        layout->addWidget(line1);
        layout->addWidget(subjectsLabel);
        layout->addWidget(line2);
        layout->addWidget(hoursLabel);
        layout->addItem(spacer);
        layout->addWidget(editBtn);
        layout->addWidget(deleteBtn);
        
        item->show();
        ui->verticalLayout->addWidget(item);
    }
    
    ui->verticalLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void QuartersWidget::limpiarLayout()
{
    QLayoutItem* item;
    while ((item = ui->verticalLayout->takeAt(0)) != nullptr) {
        if (item->widget() && item->widget() != ui->itemFrame) {
            delete item->widget();
        }
        delete item;
    }
}

void QuartersWidget::on_quarterClicked()
{
    ClickableFrame* frame = qobject_cast<ClickableFrame*>(sender());
    if (frame) {
        emit solicitarDetallesCuatrimestre(frame->getQuarterId());
    }
}

void QuartersWidget::on_addButton_clicked()
{
    emit solicitarNuevoCuatrimestre();
}

void QuartersWidget::handleEditQuarter(int id)
{
    emit solicitarEdicionCuatrimestre(id);
}

void QuartersWidget::handleDeleteQuarter(int id)
{
    if (!m_conjuntos) return;
    
    Set* s = m_conjuntos->getSet(id);
    if (!s) return;
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Eliminar Cuatrimestre",
        QString("¿Estás seguro de eliminar el cuatrimestre '%1'?\nEsto no se puede deshacer.")
            .arg(QString::fromStdString(s->nombre)),
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        // TODO: Implement delete in ConjuntoMaterias class
        QMessageBox::information(this, "Información", "Funcionalidad de eliminación pendiente de implementar en la clase ConjuntoMaterias.");
        // After implementation: m_conjuntos->eliminar(id); cargarCuatrimestres();
    }
}
