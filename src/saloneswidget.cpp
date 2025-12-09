#include "saloneswidget.h"
#include "ui_saloneswidget.h"
#include "../include/salones.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QSpacerItem>

// ClickableFrame for list items
class SalonClickableFrame : public QFrame {
    Q_OBJECT
public:
    explicit SalonClickableFrame(QWidget* parent = nullptr) : QFrame(parent) {}
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

SalonesWidget::SalonesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SalonesWidget)
{
    ui->setupUi(this);
    
    // Hide template item if it exists, or just ensure layout is ready
    // Assuming UI has a scrollAreaWidgetContents with a vertical layout
}

SalonesWidget::~SalonesWidget()
{
    delete ui;
}

void SalonesWidget::setData(salones* s)
{
    m_salones = s;
    cargarSalones();
}

void SalonesWidget::limpiarLayout()
{
    if (!ui->scrollAreaWidgetContents->layout()) return;
    
    QLayoutItem* item;
    while ((item = ui->scrollAreaWidgetContents->layout()->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void SalonesWidget::cargarSalones()
{
    limpiarLayout();
    if (!m_salones) return;
    
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    if (!layout) {
        layout = new QVBoxLayout(ui->scrollAreaWidgetContents);
        ui->scrollAreaWidgetContents->setLayout(layout);
    }
    
    for(int i = 0; i < m_salones->getCantidad(); i++) {
        salon* s = m_salones->getSalon(i);
        if (!s) continue;
        
        SalonClickableFrame* item = new SalonClickableFrame(ui->scrollAreaWidgetContents);
        item->setId(s->getId());
        item->setMinimumSize(0, 60);
        item->setStyleSheet("background-color: #5c7c9e; border-radius: 5px; margin-bottom: 5px;");
        item->setCursor(Qt::PointingHandCursor);
        connect(item, &SalonClickableFrame::clicked, this, &SalonesWidget::on_itemClicked);
        
        QHBoxLayout* itemLayout = new QHBoxLayout(item);
        
        QLabel* nameLabel = new QLabel(QString::fromUtf8(s->getNombre()), item);
        nameLabel->setStyleSheet("color: white; font-weight: bold; font-size: 16px;");
        
        QLabel* typeLabel = new QLabel(QString::fromUtf8(s->getTipo()), item);
        typeLabel->setStyleSheet("color: white; font-style: italic;");
        
        itemLayout->addWidget(nameLabel);
        itemLayout->addStretch();
        itemLayout->addWidget(typeLabel);
        
        layout->addWidget(item);
    }
    
    layout->addStretch();
}

void SalonesWidget::on_itemClicked(int id)
{
    emit solicitarDetallesSalon(id);
}

void SalonesWidget::on_addButton_clicked()
{
    emit solicitarNuevoSalon();
}

#include "saloneswidget.moc"
