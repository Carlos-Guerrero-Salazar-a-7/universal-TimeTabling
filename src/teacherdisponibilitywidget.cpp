#include "teacherdisponibilitywidget.h"
#include "ui_teacherdisponibilitywidget.h"
#include "../include/maestros.h"
#include "../include/horario_disponibilidad.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QSpacerItem>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QDebug>

// ClickableFrame for list items
class TeacherClickableFrame : public QFrame {
    Q_OBJECT
public:
    explicit TeacherClickableFrame(QWidget* parent = nullptr) : QFrame(parent) {}
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

TeacherDisponibilityWidget::TeacherDisponibilityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherDisponibilityWidget)
{
    ui->setupUi(this);
    
    // Hide the template card
    ui->teacherCard->setVisible(false);
}

TeacherDisponibilityWidget::~TeacherDisponibilityWidget()
{
    delete ui;
}

void TeacherDisponibilityWidget::setData(maestros* ma)
{
    m_maestros = ma;
    cargarMaestros();
}

void TeacherDisponibilityWidget::limpiarLayout()
{
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->scrollAreaWidgetContents->layout());
    if (!gridLayout) return;
    
    QLayoutItem* item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        if (item->widget() && item->widget() != ui->teacherCard) {
            delete item->widget();
        }
        delete item;
    }
}

void TeacherDisponibilityWidget::cargarMaestros()
{
    limpiarLayout();
    if (!m_maestros) return;
    
    // Get or create grid layout
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui->scrollAreaWidgetContents->layout());
    if (!gridLayout) {
        // Delete any existing layout first
        if (ui->scrollAreaWidgetContents->layout()) {
            QLayout* oldLayout = ui->scrollAreaWidgetContents->layout();
            QLayoutItem* item;
            while ((item = oldLayout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
            delete oldLayout;
        }
        gridLayout = new QGridLayout(ui->scrollAreaWidgetContents);
        ui->scrollAreaWidgetContents->setLayout(gridLayout);
    }
    
    int row = 0;
    int col = 0;
    const int maxCols = 2; // 2 cards per row
    
    for(int i = 0; i < m_maestros->getCantidad(); i++) {
        maestro* m = m_maestros->getMaestro(i);
        if (!m) continue;
        
        // Create teacher card
        QFrame* card = new QFrame(ui->scrollAreaWidgetContents);
        card->setMinimumSize(550, 300);
        card->setStyleSheet("background-color: #f9f9f9; border-radius: 5px;");
        
        // Teacher name label
        QLabel* nameLabel = new QLabel(QString::fromUtf8(m->getNombre()), card);
        nameLabel->setGeometry(10, 10, 301, 31);
        nameLabel->setStyleSheet("font-size: 18px; color: black; font-weight: bold;");
        
        // Edit button
        QPushButton* editBtn = new QPushButton("Editar", card);
        editBtn->setGeometry(440, 10, 91, 31);
        editBtn->setStyleSheet("background-color: #333333; color: white; border-radius: 5px; font-weight: bold;");
        editBtn->setCursor(Qt::PointingHandCursor);
        editBtn->setProperty("teacherId", m->getId());
        connect(editBtn, &QPushButton::clicked, this, [this, id = m->getId()]() {
            handleEditTeacher(id);
        });
        
        // Schedule table
        QTableWidget* table = new QTableWidget(card);
        table->setGeometry(10, 50, 621, 301);
        table->setRowCount(horario_disponibilidad::getNumFranjas());
        table->setColumnCount(horario_disponibilidad::getNumDias() + 1); // +1 for time column
        
        // Set headers
        QStringList headers;
        headers << "";
        for(int d = 0; d < horario_disponibilidad::getNumDias(); d++) {
            headers << QString::fromUtf8(horario_disponibilidad::getNombreDia(d)).left(1); // L, M, M, J, V
        }
        table->setHorizontalHeaderLabels(headers);
        table->verticalHeader()->setVisible(false);
        
        // Style header only
        table->horizontalHeader()->setStyleSheet(
            "QHeaderView::section {"
            "    background-color: #4a5c8c;"
            "    color: white;"
            "    font-weight: bold;"
            "    border: 1px solid #fff;"
            "    font-size: 10px;"
            "}"
        );
        
        // Set grid line color
        table->setShowGrid(true);
        table->setGridStyle(Qt::SolidLine);
        
        // Get teacher's availability
        const horario_disponibilidad& horario = m->getHorarioDisponibilidad();
        
        // Fill table
        for(int f = 0; f < horario_disponibilidad::getNumFranjas(); f++) {
            // Time column
            QString timeRange = QString("%1 - %2")
                .arg(horario_disponibilidad::getInicioFranja(f))
                .arg(horario_disponibilidad::getFinFranja(f));
            QTableWidgetItem* timeItem = new QTableWidgetItem(timeRange);
            timeItem->setTextAlignment(Qt::AlignCenter);
            timeItem->setFlags(timeItem->flags() & ~Qt::ItemIsEditable);
            table->setItem(f, 0, timeItem);
            
            // Day columns
            for(int d = 0; d < horario_disponibilidad::getNumDias(); d++) {
                CeldaDisponibilidad* celda = const_cast<horario_disponibilidad&>(horario).getCelda(d, f);
                QTableWidgetItem* item = new QTableWidgetItem("");
                item->setTextAlignment(Qt::AlignCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                
                if (celda) {
                    QColor bgColor;
                    if (celda->isDisponible()) {
                        // Green for available
                        bgColor = QColor("#2ecc71");
                    } else if (celda->isOcupado()) {
                        // Gray for occupied
                        bgColor = QColor("#95a5a6");
                    } else {
                        // Red for not available (INDEFINIDO)
                        bgColor = QColor("#e74c3c");
                    }
                    
                    // Set both background and data role to ensure color shows
                    item->setBackground(QBrush(bgColor));
                    item->setData(Qt::BackgroundRole, bgColor);
                }
                
                table->setItem(f, d + 1, item);
            }
        }
        
        // Resize columns to fit
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        
        // Add card to grid
        gridLayout->addWidget(card, row, col);
        
        col++;
        if (col >= maxCols) {
            col = 0;
            row++;
        }
    }
    
    // Add stretch at the end
    gridLayout->setRowStretch(row + 1, 1);
}

void TeacherDisponibilityWidget::on_itemClicked(int id)
{
    emit solicitarDetallesMaestro(id);
}

void TeacherDisponibilityWidget::on_addTeacherButton_clicked()
{
    emit solicitarNuevoMaestro();
}

void TeacherDisponibilityWidget::handleEditTeacher(int id)
{
    emit solicitarEdicionMaestro(id);
}

#include "teacherdisponibilitywidget.moc"
