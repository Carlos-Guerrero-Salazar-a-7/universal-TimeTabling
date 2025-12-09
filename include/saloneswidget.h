#ifndef SALONESWIDGET_H
#define SALONESWIDGET_H

#include <QWidget>

namespace Ui {
class SalonesWidget;
}

class salones;

class SalonesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SalonesWidget(QWidget *parent = nullptr);
    ~SalonesWidget();
    
    void setData(salones* s);
    void cargarSalones();

private:
    Ui::SalonesWidget *ui;
    class salones* m_salones = nullptr;
    
    void limpiarLayout();

signals:
    void solicitarDetallesSalon(int id);
    void solicitarNuevoSalon();
    
private slots:
    void on_itemClicked(int id);
    void on_addButton_clicked();
};

#endif // SALONESWIDGET_H
