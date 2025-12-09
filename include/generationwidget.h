#ifndef GENERATIONWIDGET_H
#define GENERATIONWIDGET_H

#include <QWidget>

namespace Ui {
class GenerationWidget;
}

class materias;
class salones;
class grupos;
class grupos;
class maestros;
class ConjuntoMaterias;
class Horario;

class GenerationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GenerationWidget(QWidget *parent = nullptr);
    ~GenerationWidget();

    void setData(materias* m, salones* s, grupos* g, maestros* ma, ConjuntoMaterias* c);
    Horario* getHorariosGrupos() const { return m_horarios_grupos; }
    Horario* getHorariosMaestros() const { return m_horarios_maestros; }
    Horario* getHorariosSalones() const { return m_horarios_salones; }

signals:
    void schedulesUpdated();

private slots:
    void on_deleteSchedule_clicked();
    void on_continueSchedule_clicked();
    void on_createSchedule_clicked();

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::GenerationWidget *ui;
    materias* m_materias = nullptr;
    salones* m_salones = nullptr;
    grupos* m_grupos = nullptr;
    maestros* m_maestros = nullptr;
    ConjuntoMaterias* m_conjuntos = nullptr;
    
    // Arrays de horarios
    class Horario* m_horarios_grupos = nullptr;
    class Horario* m_horarios_maestros = nullptr;
    class Horario* m_horarios_salones = nullptr;
};

#endif // GENERATIONWIDGET_H
