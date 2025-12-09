#include "scheduleswidget.h"
#include "ui_scheduleswidget.h"
#include "../include/maestros.h"
#include "../include/grupos.h"
#include "../include/materias.h"
#include "../include/horario.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QSpacerItem>

// ClickableFrame for list items
class ScheduleClickableFrame : public QFrame {
    Q_OBJECT
public:
    explicit ScheduleClickableFrame(QWidget* parent = nullptr) : QFrame(parent) {}
    void setId(int id) { m_id = id; }
    int getId() const { return m_id; }
signals:
    void clicked(int id);
protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            emit clicked(m_id);
        }
        QFrame::mousePressEvent(event);
    }
private:
    int m_id = -1;
};

SchedulesWidget::SchedulesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchedulesWidget)
{
    ui->setupUi(this);
    
    // Hide template item
    ui->itemFrame->hide();
    
    // Connect search
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, [this](const QString &){
        cargarLista();
    });
    
    // Set initial state
    m_showingTeachers = true;
    ui->maestroButton->setStyleSheet("background-color: #2c3e50; color: white; border-radius: 5px; font-weight: bold;");
    ui->grupoButton->setStyleSheet("background-color: #5c7c9e; color: white; border-radius: 5px; font-weight: bold;");
}

SchedulesWidget::~SchedulesWidget()
{
    delete ui;
}

void SchedulesWidget::setData(maestros* m, grupos* g, materias* mat, Horario* hMaestros, int cantHMaestros, Horario* hGrupos, int cantHGrupos)
{
    m_maestros = m;
    m_grupos = g;
    m_materias = mat;
    m_horariosMaestros = hMaestros;
    m_cantHorariosMaestros = cantHMaestros;
    m_horariosGrupos = hGrupos;
    m_cantHorariosGrupos = cantHGrupos;
    
    cargarLista();
}

void SchedulesWidget::limpiarLayout()
{
    QLayoutItem* item;
    while ((item = ui->verticalLayout->takeAt(0)) != nullptr) {
        if (item->widget() && item->widget() != ui->itemFrame) {
            delete item->widget();
        }
        delete item;
    }
}

void SchedulesWidget::cargarLista()
{
    limpiarLayout();
    
    QString searchText = ui->searchLineEdit->text().toLower();
    
    if (m_showingTeachers) {
        if (!m_maestros) return;
        
        for(int i = 0; i < m_maestros->getCantidad(); i++) {
            maestro* m = m_maestros->getMaestro(i);
            if (!m) continue;
            
            QString nombre = QString::fromUtf8(m->getNombre());
            if (!searchText.isEmpty() && !nombre.toLower().contains(searchText)) {
                continue;
            }
            
            // Create widget
            ScheduleClickableFrame* item = new ScheduleClickableFrame(ui->scrollAreaWidgetContents);
            item->setId(m->getId());
            item->setMinimumSize(0, 60);
            item->setStyleSheet(ui->itemFrame->styleSheet());
            item->setCursor(Qt::PointingHandCursor);
            connect(item, &ScheduleClickableFrame::clicked, this, &SchedulesWidget::on_itemClicked);
            
            QHBoxLayout* layout = new QHBoxLayout(item);
            layout->setContentsMargins(20, 0, 20, 0);
            
            QLabel* nameLabel = new QLabel(nombre, item);
            nameLabel->setStyleSheet(ui->nameLabel->styleSheet());
            
            QFrame* line1 = new QFrame(item);
            line1->setFrameShape(QFrame::VLine);
            line1->setFrameShadow(QFrame::Sunken);
            
            QLabel* subjectsLabel = new QLabel(QString("%1 Materias").arg(m->getCantidadMaterias()), item);
            subjectsLabel->setStyleSheet(ui->subjectsLabel->styleSheet());
            
            QFrame* line2 = new QFrame(item);
            line2->setFrameShape(QFrame::VLine);
            line2->setFrameShadow(QFrame::Sunken);
            
            // Calculate total hours (approximate based on subjects)
            int totalHoras = 0;
            if (m_materias) {
                for(int j=0; j<m->getCantidadMaterias(); j++) {
                    materia* mat = m_materias->getMateria(m->getIdMateria(j));
                    if(mat) totalHoras += mat->getHorasNecesarias();
                }
            }
            
            QLabel* hoursLabel = new QLabel(QString("%1 Horas").arg(totalHoras), item);
            hoursLabel->setStyleSheet(ui->hoursLabel->styleSheet());
            
            layout->addWidget(nameLabel);
            layout->addWidget(line1);
            layout->addWidget(subjectsLabel);
            layout->addWidget(line2);
            layout->addWidget(hoursLabel);
            
            item->show();
            ui->verticalLayout->addWidget(item);
        }
    } else {
        // Show Groups
        if (!m_grupos) return;
        
        for(int i = 0; i < m_grupos->getCantidad(); i++) {
            grupo* g = m_grupos->getGrupo(i);
            if (!g) continue;
            
            QString nombre = QString::fromUtf8(g->getNombre());
            if (!searchText.isEmpty() && !nombre.toLower().contains(searchText)) {
                continue;
            }
            
            // Create widget
            ScheduleClickableFrame* item = new ScheduleClickableFrame(ui->scrollAreaWidgetContents);
            item->setId(g->getId());
            item->setMinimumSize(0, 60);
            item->setStyleSheet(ui->itemFrame->styleSheet());
            item->setCursor(Qt::PointingHandCursor);
            connect(item, &ScheduleClickableFrame::clicked, this, &SchedulesWidget::on_itemClicked);
            
            QHBoxLayout* layout = new QHBoxLayout(item);
            layout->setContentsMargins(20, 0, 20, 0);
            
            QLabel* nameLabel = new QLabel(nombre, item);
            nameLabel->setStyleSheet(ui->nameLabel->styleSheet());
            
            QFrame* line1 = new QFrame(item);
            line1->setFrameShape(QFrame::VLine);
            line1->setFrameShadow(QFrame::Sunken);
            
            // For groups, maybe show preferred schedule or something else
            QString horarioStr = QString("%1 - %2").arg(Horario::getInicioFranja(g->getFranjaInicio()))
                                                   .arg(Horario::getFinFranja(g->getFranjaFin()));
            
            QLabel* scheduleLabel = new QLabel(horarioStr, item);
            scheduleLabel->setStyleSheet(ui->subjectsLabel->styleSheet());
            
            layout->addWidget(nameLabel);
            layout->addWidget(line1);
            layout->addWidget(scheduleLabel);
            
            item->show();
            ui->verticalLayout->addWidget(item);
        }
    }
    
    ui->verticalLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void SchedulesWidget::on_maestroButton_clicked()
{
    m_showingTeachers = true;
    ui->maestroButton->setStyleSheet("background-color: #2c3e50; color: white; border-radius: 5px; font-weight: bold;");
    ui->grupoButton->setStyleSheet("background-color: #5c7c9e; color: white; border-radius: 5px; font-weight: bold;");
    cargarLista();
}

void SchedulesWidget::on_grupoButton_clicked()
{
    m_showingTeachers = false;
    ui->maestroButton->setStyleSheet("background-color: #5c7c9e; color: white; border-radius: 5px; font-weight: bold;");
    ui->grupoButton->setStyleSheet("background-color: #2c3e50; color: white; border-radius: 5px; font-weight: bold;");
    cargarLista();
}

void SchedulesWidget::on_itemClicked(int id)
{
    if (m_showingTeachers) {
        emit showTeacherSchedule(id);
    } else {
        emit showGroupSchedule(id);
    }
}

#include "scheduleswidget.moc"
