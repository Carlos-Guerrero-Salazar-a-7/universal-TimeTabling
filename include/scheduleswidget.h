#ifndef SCHEDULESWIDGET_H

#define SCHEDULESWIDGET_H

#include <QWidget>

namespace Ui {
class SchedulesWidget;
}

class maestros;
class grupos;
class materias;
class Horario;

class SchedulesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SchedulesWidget(QWidget *parent = nullptr);
    ~SchedulesWidget();
    
    void setData(maestros* m, grupos* g, materias* mat, Horario* hMaestros, int cantHMaestros, Horario* hGrupos, int cantHGrupos);

private:
    Ui::SchedulesWidget *ui;
    
    // Data pointers
    class maestros* m_maestros = nullptr;
    class grupos* m_grupos = nullptr;
    class materias* m_materias = nullptr;
    class Horario* m_horariosMaestros = nullptr;
    class Horario* m_horariosGrupos = nullptr;
    int m_cantHorariosMaestros = 0;
    int m_cantHorariosGrupos = 0;
    
    bool m_showingTeachers = true; // true = Teachers, false = Groups
    
    void limpiarLayout();
    void cargarLista();

signals:
    void showTeacherSchedule(int id);
    void showGroupSchedule(int id);

private slots:
    void on_maestroButton_clicked();
    void on_grupoButton_clicked();
    void on_itemClicked(int id);
};

#endif // SCHEDULESWIDGET_H
