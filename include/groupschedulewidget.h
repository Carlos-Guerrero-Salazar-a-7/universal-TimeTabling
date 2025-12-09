#ifndef GROUPSCHEDULEWIDGET_H
#define GROUPSCHEDULEWIDGET_H

#include <QWidget>

namespace Ui {
class GroupScheduleWidget;
}

class maestros;
class materias;
class grupos;
class salones;
class Horario;

class GroupScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupScheduleWidget(QWidget *parent = nullptr);
    ~GroupScheduleWidget();
    
    void setData(maestros* m, materias* mat, grupos* g, salones* s, Horario* h, int cantH);
    void loadSchedule(int id);

signals:
    void backClicked();

private slots:
    void on_backButton_clicked();
    void on_exportButton_clicked();

private:
    Ui::GroupScheduleWidget *ui;
    
    class maestros* m_maestros = nullptr;
    class materias* m_materias = nullptr;
    class grupos* m_grupos = nullptr;
    class salones* m_salones = nullptr;
    class Horario* m_horarios = nullptr;
    int m_cantHorarios = 0;
    int m_currentId = -1;
    
    void cargarTabla();
    void exportToCSV(class grupo* g);
};

#endif // GROUPSCHEDULEWIDGET_H
