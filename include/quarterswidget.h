#ifndef QUARTERSWIDGET_H
#define QUARTERSWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QMouseEvent>

namespace Ui {
class QuartersWidget;
}

class ConjuntoMaterias;
class materias;

class materias;

// Custom Frame to handle click events
class ClickableFrame : public QFrame {
    Q_OBJECT
public:
    explicit ClickableFrame(QWidget* parent = nullptr) : QFrame(parent) {}
    void setQuarterId(int id) { m_id = id; }
    int getQuarterId() const { return m_id; }
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            emit clicked();
        }
        QFrame::mousePressEvent(event);
    }
private:
    int m_id = -1;
};

class QuartersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuartersWidget(QWidget *parent = nullptr);
    ~QuartersWidget();

    void cargarCuatrimestres();

public:
    void setData(class ConjuntoMaterias* c, class materias* m);

signals:
    void solicitarDetallesCuatrimestre(int id);
    void solicitarEdicionCuatrimestre(int id);
    void solicitarNuevoCuatrimestre();

private slots:
    void on_quarterClicked();
    void on_addButton_clicked();
    void handleEditQuarter(int id);
    void handleDeleteQuarter(int id);

private:
    Ui::QuartersWidget *ui;
    class ConjuntoMaterias* m_conjuntos = nullptr;
    class materias* m_materias = nullptr;
    
    void limpiarLayout();
};

#endif // QUARTERSWIDGET_H
