#ifndef TEACHERDISPONIBILITYWIDGET_H
#define TEACHERDISPONIBILITYWIDGET_H

#include <QWidget>

namespace Ui {
class TeacherDisponibilityWidget;
}

class maestros;

class TeacherDisponibilityWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherDisponibilityWidget(QWidget *parent = nullptr);
    ~TeacherDisponibilityWidget();
    
    void setData(maestros* ma);
    void cargarMaestros();

private:
    Ui::TeacherDisponibilityWidget *ui;
    class maestros* m_maestros = nullptr;
    
    void limpiarLayout();

signals:
    void solicitarDetallesMaestro(int id);
    void solicitarEdicionMaestro(int id);
    void solicitarNuevoMaestro();

private slots:
    void on_addTeacherButton_clicked();
    void on_itemClicked(int id);
    void handleEditTeacher(int id);
};

#endif // TEACHERDISPONIBILITYWIDGET_H
