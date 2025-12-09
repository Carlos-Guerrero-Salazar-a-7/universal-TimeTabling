#ifndef TEACHERDETAILSWIDGET_H
#define TEACHERDETAILSWIDGET_H

#include <QWidget>
#include <QColor>
#include <QSet>
#include <QEvent>

namespace Ui {
class TeacherDetailsWidget;
}

class maestros;
class materias;

class TeacherDetailsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherDetailsWidget(QWidget *parent = nullptr);
    ~TeacherDetailsWidget();
    
    void setData(maestros* ma, materias* m);
    void cargarDatos(int id);
    void prepararNuevoMaestro();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    Ui::TeacherDetailsWidget *ui;
    class maestros* m_maestros = nullptr;
    class materias* m_materias = nullptr;
    int m_currentId = -1;
    QColor m_selectedColor;
    QSet<int> m_selectedSubjects;
    
    class QListWidget* m_availableList = nullptr;
    class QListWidget* m_assignedList = nullptr;
    
    void createSubjectLists();
    void loadAvailableSubjects();
    void loadAssignedSubjects();
    void onAddSubject();
    void onRemoveSubject();

signals:
    void backClicked();
    void applyClicked();
    
private slots:
    void on_backButton_clicked();
    void on_createButton_clicked();
};

#endif // TEACHERDETAILSWIDGET_H
