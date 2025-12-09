#ifndef TEACHERSCHEDULEWIDGET_H
#define TEACHERSCHEDULEWIDGET_H

#include <QWidget>

namespace Ui {
class TeacherScheduleWidget;
}

class maestros;
class materias;
class grupos;
class salones;
class Horario;

class TeacherScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherScheduleWidget(QWidget *parent = nullptr);
    ~TeacherScheduleWidget();
    
    void setData(maestros* m, materias* mat, grupos* g, salones* s, Horario* h, int cantH);
    void loadSchedule(int id);

private:
    Ui::TeacherScheduleWidget *ui;
    
    class maestros* m_maestros = nullptr;
    class materias* m_materias = nullptr;
    class grupos* m_grupos = nullptr;
    class salones* m_salones = nullptr;
    class Horario* m_horarios = nullptr;
    int m_cantHorarios = 0;
    int m_currentTeacherId = -1;
    
    void cargarTabla();
    void exportToCSV(class maestro* m);

signals:
    void backClicked();

private slots:
    void on_backButton_clicked();
    void on_exportButton_clicked();
};

#endif // TEACHERSCHEDULEWIDGET_H
