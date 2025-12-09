#ifndef QUARTERDETAILSWIDGET_H
#define QUARTERDETAILSWIDGET_H

#include <QWidget>

namespace Ui {
class QuarterDetailsWidget;
}

class ConjuntoMaterias;
class materias;

class QuarterDetailsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuarterDetailsWidget(QWidget *parent = nullptr);
    ~QuarterDetailsWidget();

    void cargarDatos(int id);
    void prepararNuevo();

public:
    void setData(class ConjuntoMaterias* c, class materias* m);

signals:
    void backClicked();
    void applyClicked();

private slots:
    void on_backButton_clicked();
    void on_applyButton_clicked();
    void on_addSubjectButton_clicked();
    void on_removeSubjectButton_clicked();
    void on_editNameButton_clicked();

private:
    Ui::QuarterDetailsWidget *ui;
    class ConjuntoMaterias* m_conjuntos = nullptr;
    class materias* m_materias = nullptr;
    int m_currentId = -1;
    
    void cargarTabla();
};

#endif // QUARTERDETAILSWIDGET_H
