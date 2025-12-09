#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "generationwidget.h"
#include "saloneswidget.h"
#include "roomdetailswidget.h"
#include "scheduleswidget.h"
#include "teacherschedulewidget.h"
#include "quarterswidget.h"
#include "quarterdetailswidget.h"
#include "gruposwidget.h"
#include "groupdetailswidget.h"
#include "teacherdisponibilitywidget.h"
#include "teacherdetailswidget.h"
#include "groupschedulewidget.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class materias;
class salones;
class grupos;
class maestros;

class Horario;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setData(materias* m, salones* s, grupos* g, maestros* ma, ConjuntoMaterias* c, Horario* hGrupos, int cantHGrupos, Horario* hMaestros, int cantHMaestros);

private slots:
    void on_generationButton_clicked();
    void on_teacherDisponibilityButton_clicked();
    void on_schedulesButton_clicked();
    void on_cuatrimestresButton_clicked();
    void on_groupButton_clicked();
    void on_salonesButton_clicked();

private:
    Ui::MainWindow *ui;
    GenerationWidget *generationWidget;
    SalonesWidget *salonesWidget;
    RoomDetailsWidget *roomDetailsWidget;
    SchedulesWidget *schedulesWidget;
    TeacherScheduleWidget *teacherScheduleWidget;
    QuartersWidget *quartersWidget;
    QuarterDetailsWidget *quarterDetailsWidget;
    GruposWidget *gruposWidget;
    GroupDetailsWidget *groupDetailsWidget;
    TeacherDisponibilityWidget *teacherDisponibilityWidget;
    TeacherDetailsWidget *teacherDetailsWidget;
    GroupScheduleWidget *groupScheduleWidget;

    // Data pointers
    materias* m_materias = nullptr;
    salones* m_salones = nullptr;
    grupos* m_grupos = nullptr;
    maestros* m_maestros = nullptr;
    ConjuntoMaterias* m_conjuntos = nullptr;
};
#endif // MAINWINDOW_H
