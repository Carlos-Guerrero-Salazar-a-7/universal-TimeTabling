#ifndef ROOMDETAILSWIDGET_H
#define ROOMDETAILSWIDGET_H

#include <QWidget>

namespace Ui {
class RoomDetailsWidget;
}

class salones;

class RoomDetailsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomDetailsWidget(QWidget *parent = nullptr);
    ~RoomDetailsWidget();
    
    void setData(salones* s);
    void cargarDatos(int id);
    void prepararNuevoSalon();

private:
    Ui::RoomDetailsWidget *ui;
    class salones* m_salones = nullptr;
    int m_currentId = -1;

signals:
    void backClicked();
    void applyClicked();
    
private slots:
    void on_backButton_clicked();
    void on_createButton_clicked();
};

#endif // ROOMDETAILSWIDGET_H
