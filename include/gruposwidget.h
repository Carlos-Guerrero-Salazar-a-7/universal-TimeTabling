#ifndef GRUPOSWIDGET_H
#define GRUPOSWIDGET_H

#include <QWidget>

namespace Ui {
class GruposWidget;
}
class grupos;
class materias;
class maestros;
class maestros;
class ConjuntoMaterias;
class Horario;
class GruposWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GruposWidget(QWidget *parent = nullptr);
    ~GruposWidget();
    void cargarGrupos();
    void setHorarios(class Horario* h);

protected:
    void showEvent(QShowEvent *event) override;

public:
    void setData(grupos* g, materias* m, maestros* ma, ConjuntoMaterias* c, Horario* h, int cantH);

private slots:
    void on_createGroupButton_clicked();
    void on_searchLineEdit_textChanged(const QString &arg1);
    void handleEditGroupClicked();
    void handleDeleteGroupClicked();
    void handleDetailsGroupClicked();

private:
    Ui::GruposWidget *ui;
    grupos* m_grupos = nullptr;
    materias* m_materias = nullptr;
    maestros* m_maestros = nullptr;
    ConjuntoMaterias* m_conjuntos = nullptr;
    class Horario* m_horarios = nullptr;
    int m_cantHorarios = 0;
    
    void limpiarLayout();
signals:
    void solicitarEdicionGrupo(int id_grupo);
    void solicitarNuevoGrupo();
    void solicitarDetallesGrupo(int id_grupo);
};

#endif // GRUPOSWIDGET_H
