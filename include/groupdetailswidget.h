#ifndef GROUPDETAILSWIDGET_H
#define GROUPDETAILSWIDGET_H

#include <QWidget>
#include <QColor>
#include <QEvent>

namespace Ui {
class GroupDetailsWidget;
}
class grupos;
class materias;
class maestros;
class ConjuntoMaterias;
class GroupDetailsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupDetailsWidget(QWidget *parent = nullptr);
    ~GroupDetailsWidget();

public:
    void setData(grupos* g, materias* m, maestros* ma, ConjuntoMaterias* c);
    void cargarGrupoForEdit(int id);
    void prepararNuevoGrupo();
    void cargarDatos(int id);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void on_createButton_clicked();
    void on_backButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::GroupDetailsWidget *ui;
    grupos* m_grupos = nullptr;
    materias* m_materias = nullptr;
    maestros* m_maestros = nullptr;
    ConjuntoMaterias* m_conjuntos = nullptr;
    
    int m_currentGroupId = -1; // -1 para nuevo grupo
    QColor m_selectedColor;
    
signals:
    void backClicked();
    void applyClicked();
    void finalizado(); // Keep for compatibility if needed, or remove
};

#endif // GROUPDETAILSWIDGET_H
