#include "gruposwidget.h"
#include "ui_gruposwidget.h"
#include "../include/grupos.h"
#include "../include/materias.h"
#include "../include/maestros.h"
#include "../include/conjunto_materias.h"
#include "../include/horario.h"
#include <QMessageBox>
#include <QDebug>
#include <QShowEvent>

GruposWidget::GruposWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GruposWidget)
{
    ui->setupUi(this);
    
    // Ocultar el widget de ejemplo
    ui->groupItem->setVisible(false);
}

GruposWidget::~GruposWidget()
{
    delete ui;
}

void GruposWidget::setData(grupos* g, materias* m, maestros* ma, ConjuntoMaterias* c, Horario* h, int cantH)
{
    m_grupos = g;
    m_materias = m;
    m_maestros = ma;
    m_conjuntos = c;
    m_horarios = h;
    m_cantHorarios = cantH;
    cargarGrupos();
}

void GruposWidget::cargarGrupos()
{
    limpiarLayout();
    
    if (!m_grupos) return;
    
    QString searchText = ui->searchLineEdit->text().toLower();
    
    for(int i = 0; i < m_grupos->getCantidad(); i++) {
        grupo* g = m_grupos->getGrupo(i);
        if (!g) continue;
        
        QString nombre = QString::fromUtf8(g->getNombre());
        if (!searchText.isEmpty() && !nombre.toLower().contains(searchText)) {
            continue;
        }
        
        // Clonar el widget de ejemplo
        QFrame* item = new QFrame(ui->scrollAreaWidgetContents);
        item->setMinimumSize(0, 200);
        item->setStyleSheet(ui->groupItem->styleSheet());
        item->show();
        
        // Configurar nombre
        QLabel* nameLabel = new QLabel(item);
        nameLabel->setGeometry(ui->groupNameLabel->geometry());
        nameLabel->setStyleSheet(ui->groupNameLabel->styleSheet());
        nameLabel->setText(nombre);
        nameLabel->show();
        
        // Configurar botones
        QPushButton* deleteBtn = new QPushButton(item);
        deleteBtn->setGeometry(ui->deleteButton->geometry());
        deleteBtn->setStyleSheet(ui->deleteButton->styleSheet());
        deleteBtn->setText("Eliminar");
        deleteBtn->setProperty("groupId", i); // Guardar ID
        connect(deleteBtn, &QPushButton::clicked, this, &GruposWidget::handleDeleteGroupClicked);
        deleteBtn->show();
        
        QPushButton* editBtn = new QPushButton(item);
        editBtn->setGeometry(ui->editButton->geometry());
        editBtn->setStyleSheet(ui->editButton->styleSheet());
        editBtn->setText("Editar");
        editBtn->setProperty("groupId", i); // Guardar ID
        connect(editBtn, &QPushButton::clicked, this, &GruposWidget::handleEditGroupClicked);
        editBtn->show();
        
        // Add Details Button (reuse geometry or adjust)
        QPushButton* detailsBtn = new QPushButton(item);
        // Adjust geometry to be next to edit
        QRect editGeo = ui->editButton->geometry();
        detailsBtn->setGeometry(editGeo.x() - 110, editGeo.y(), 100, editGeo.height());
        detailsBtn->setStyleSheet(ui->editButton->styleSheet()); // Reuse style
        detailsBtn->setText("Detalles");
        detailsBtn->setProperty("groupId", i);
        connect(detailsBtn, &QPushButton::clicked, this, &GruposWidget::handleDetailsGroupClicked);
        detailsBtn->show();
        
        // Configurar tabla
        QTableWidget* table = new QTableWidget(item);
        table->setGeometry(ui->groupTable->geometry());
        table->setStyleSheet(ui->groupTable->styleSheet());
        table->setColumnCount(3);
        table->setHorizontalHeaderLabels({"Materia", "Horas", "Maestro"});
        table->verticalHeader()->setVisible(false);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        
        // Llenar tabla con materias del conjunto
        if (m_conjuntos && m_materias) {
            int setId = g->getConjuntoDeMaterias();
            Set* s = m_conjuntos->getSet(setId);
            if (s) {
                table->setRowCount(s->cant_materias);
                for(int j=0; j<s->cant_materias; j++) {
                    int matId = s->materia_ids[j];
                    materia* mat = m_materias->getMateria(matId);
                    if (mat) {
                        table->setItem(j, 0, new QTableWidgetItem(QString::fromUtf8(mat->getNombre())));
                        table->setItem(j, 1, new QTableWidgetItem(QString::number(mat->getHorasNecesarias())));
                        
                        // Buscar maestro asignado en el horario generado
                        QString nombreMaestro = "Pendiente";
                        if (m_horarios && i < m_cantHorarios) {
                            Horario* h = &m_horarios[i]; 
                            bool encontrado = false;
                            for(int d=0; d<Horario::getNumDias(); d++) {
                                for(int f=0; f<Horario::getNumFranjas(); f++) {
                                    CeldaHorario* celda = h->getCelda(d, f);
                                    if (celda && celda->id_materia == matId) {
                                        if (celda->id_maestro != -1 && m_maestros) {
                                            maestro* ma = m_maestros->getMaestro(celda->id_maestro);
                                            // Wait, id_maestro is ID, getMaestro takes index.
                                            // Need to find by ID.
                                            for(int k=0; k<m_maestros->getCantidad(); k++) {
                                                if(m_maestros->getMaestro(k)->getId() == celda->id_maestro) {
                                                    nombreMaestro = QString::fromUtf8(m_maestros->getMaestro(k)->getNombre());
                                                    encontrado = true;
                                                    break;
                                                }
                                            }
                                        }
                                        if (encontrado) break;
                                    }
                                }
                                if (encontrado) break;
                            }
                        }
                        
                        table->setItem(j, 2, new QTableWidgetItem(nombreMaestro));
                    }
                }
            }
        }
        
        // Make table compact
        table->setMaximumHeight(150); // Limit table height
        table->setMinimumHeight(100);
        table->verticalHeader()->setDefaultSectionSize(25); // Compact row height
        table->horizontalHeader()->setStretchLastSection(true);
        table->setStyleSheet("QTableWidget { border: 1px solid #ddd; border-radius: 5px; }"
                            "QHeaderView::section { background-color: #5c7c9e; color: white; padding: 4px; }"
                            "QTableWidget::item { padding: 2px; }");
        
        table->show();
        
        ui->verticalLayout->addWidget(item);
    }
    
    // Spacer al final
    ui->verticalLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void GruposWidget::limpiarLayout()
{
    QLayoutItem* item;
    while ((item = ui->verticalLayout->takeAt(0)) != nullptr) {
        if (item->widget() && item->widget() != ui->groupItem) {
            delete item->widget();
        }
        delete item;
    }
    // Re-agregar el widget base oculto si fue removido (aunque takeAt lo remueve del layout, no lo borra si no llamamos delete widget)
    // Pero como groupItem es hijo de scrollAreaWidgetContents, no se borra automáticamente al quitar del layout si no le hacemos delete.
    // Mejor estrategia: borrar todo EXCEPTO groupItem.
    
    // Como groupItem está en el layout, al hacer takeAt(0) lo sacamos.
    // Vamos a asegurarnos de que groupItem vuelva a estar o no borrarlo.
    // Simplificación: iterar y borrar solo si no es groupItem.
}

void GruposWidget::on_createGroupButton_clicked()
{
    emit solicitarNuevoGrupo();
}

void GruposWidget::on_searchLineEdit_textChanged(const QString &arg1)
{
    cargarGrupos();
}

void GruposWidget::handleEditGroupClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        int id = btn->property("groupId").toInt();
        emit solicitarEdicionGrupo(id);
    }
}

void GruposWidget::handleDeleteGroupClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        int id = btn->property("groupId").toInt();
        
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Eliminar Grupo", "¿Estás seguro de eliminar este grupo?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // Implementar eliminación en backend
            // m_grupos->eliminar(id); // Necesitamos implementar esto en grupos.cpp
            // Por ahora solo recargamos
            qDebug() << "Eliminar grupo " << id;
            cargarGrupos();
        }
    }
}

void GruposWidget::handleDetailsGroupClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        int id = btn->property("groupId").toInt();
        emit solicitarDetallesGrupo(id);
    }
}

void GruposWidget::setHorarios(Horario* h)
{
    m_horarios = h;
    cargarGrupos();
}

void GruposWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    cargarGrupos();
}
