#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "materias.h"
#include "salones.h"
#include "grupos.h"
#include "maestros.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize widgets
    salonesWidget = new SalonesWidget(this);
    roomDetailsWidget = new RoomDetailsWidget(this);
    schedulesWidget = new SchedulesWidget(this);
    teacherScheduleWidget = new TeacherScheduleWidget(this);
    quartersWidget = new QuartersWidget(this);
    generationWidget = new GenerationWidget(this);
    quarterDetailsWidget = new QuarterDetailsWidget(this);
    gruposWidget = new GruposWidget(this);
    groupDetailsWidget = new GroupDetailsWidget(this);
    teacherDisponibilityWidget = new TeacherDisponibilityWidget(this);
    teacherDetailsWidget = new TeacherDetailsWidget(this);
    groupScheduleWidget = new GroupScheduleWidget(this);

    // Add widgets to stacked widget
    ui->stackedWidget->addWidget(salonesWidget);          // Index 0
    ui->stackedWidget->addWidget(roomDetailsWidget);      // Index 1
    ui->stackedWidget->addWidget(schedulesWidget);        // Index 2
    ui->stackedWidget->addWidget(teacherScheduleWidget);  // Index 3
    ui->stackedWidget->addWidget(quartersWidget);         // Index 4
    ui->stackedWidget->addWidget(generationWidget);       // Index 5
    ui->stackedWidget->addWidget(quarterDetailsWidget);   // Index 6
    ui->stackedWidget->addWidget(gruposWidget);           // Index 7
    ui->stackedWidget->addWidget(groupDetailsWidget);     // Index 8
    ui->stackedWidget->addWidget(teacherDisponibilityWidget); // Index 9
    ui->stackedWidget->addWidget(teacherDetailsWidget);   // Index 10
    ui->stackedWidget->addWidget(groupScheduleWidget);    // Index 11

    // Set default view
    ui->stackedWidget->setCurrentIndex(0);
    
    // Connect signals
    // Salones
    connect(salonesWidget, &SalonesWidget::solicitarDetallesSalon, this, [this](int id){
        roomDetailsWidget->cargarDatos(id);
        ui->stackedWidget->setCurrentWidget(roomDetailsWidget);
        ui->sectionTitle->setText("Detalles del Salon");
    });
    
    connect(salonesWidget, &SalonesWidget::solicitarNuevoSalon, this, [this](){
        roomDetailsWidget->prepararNuevoSalon();
        ui->stackedWidget->setCurrentWidget(roomDetailsWidget);
        ui->sectionTitle->setText("Crear Salon");
    });

    connect(roomDetailsWidget, &RoomDetailsWidget::backClicked, this, [this](){
        salonesWidget->cargarSalones(); // Recargar por si hubo cambios
        ui->stackedWidget->setCurrentWidget(salonesWidget);
        ui->sectionTitle->setText("Salones");
    });
    
    connect(roomDetailsWidget, &RoomDetailsWidget::applyClicked, this, [this](){
        salonesWidget->cargarSalones();
        ui->stackedWidget->setCurrentWidget(salonesWidget);
        ui->sectionTitle->setText("Salones");
    });
    
    // Quarters
    connect(quartersWidget, &QuartersWidget::solicitarDetallesCuatrimestre, this, [this](int id){
        quarterDetailsWidget->cargarDatos(id);
        ui->stackedWidget->setCurrentWidget(quarterDetailsWidget);
        ui->sectionTitle->setText("Detalles del Cuatrimestre");
    });
    
    connect(quartersWidget, &QuartersWidget::solicitarEdicionCuatrimestre, this, [this](int id){
        quarterDetailsWidget->cargarDatos(id);
        ui->stackedWidget->setCurrentWidget(quarterDetailsWidget);
        ui->sectionTitle->setText("Editar Cuatrimestre");
    });
    
    connect(quartersWidget, &QuartersWidget::solicitarNuevoCuatrimestre, this, [this](){
        quarterDetailsWidget->prepararNuevo();
        ui->stackedWidget->setCurrentWidget(quarterDetailsWidget);
        ui->sectionTitle->setText("Nuevo Cuatrimestre");
    });
    
    connect(quarterDetailsWidget, &QuarterDetailsWidget::backClicked, this, [this](){
        quartersWidget->cargarCuatrimestres(); // Recargar por si hubo cambios
        ui->stackedWidget->setCurrentWidget(quartersWidget);
        ui->sectionTitle->setText("Cuatrimestres");
    });
    
    connect(quarterDetailsWidget, &QuarterDetailsWidget::applyClicked, this, [this](){
        quartersWidget->cargarCuatrimestres();
        ui->stackedWidget->setCurrentWidget(quartersWidget);
        ui->sectionTitle->setText("Cuatrimestres");
    });
    
    // Groups
    connect(gruposWidget, &GruposWidget::solicitarDetallesGrupo, this, [this](int id){
        groupDetailsWidget->cargarDatos(id);
        ui->stackedWidget->setCurrentWidget(groupDetailsWidget);
        ui->sectionTitle->setText("Detalles del Grupo");
    });
    
    connect(gruposWidget, &GruposWidget::solicitarNuevoGrupo, this, [this](){
        groupDetailsWidget->prepararNuevoGrupo();
        ui->stackedWidget->setCurrentWidget(groupDetailsWidget);
        ui->sectionTitle->setText("Crear Grupo");
    });
    
    connect(gruposWidget, &GruposWidget::solicitarEdicionGrupo, this, [this](int id){
        groupDetailsWidget->cargarGrupoForEdit(id);
        ui->stackedWidget->setCurrentWidget(groupDetailsWidget);
        ui->sectionTitle->setText("Editar Grupo");
    });
    
    connect(groupDetailsWidget, &GroupDetailsWidget::finalizado, this, [this](){
        gruposWidget->cargarGrupos(); // Recargar lista
        ui->stackedWidget->setCurrentWidget(gruposWidget);
        ui->sectionTitle->setText("Grupos");
    });
    
    connect(groupDetailsWidget, &GroupDetailsWidget::backClicked, this, [this](){
        gruposWidget->cargarGrupos();
        ui->stackedWidget->setCurrentWidget(gruposWidget);
        ui->sectionTitle->setText("Grupos");
    });
    
    connect(groupDetailsWidget, &GroupDetailsWidget::applyClicked, this, [this](){
        gruposWidget->cargarGrupos();
        ui->stackedWidget->setCurrentWidget(gruposWidget);
        ui->sectionTitle->setText("Grupos");
    });
    
    // Teachers
    connect(teacherDisponibilityWidget, &TeacherDisponibilityWidget::solicitarDetallesMaestro, this, [this](int id){
        teacherDetailsWidget->cargarDatos(id);
        ui->stackedWidget->setCurrentWidget(teacherDetailsWidget);
        ui->sectionTitle->setText("Detalles del Maestro");
    });
    
    connect(teacherDisponibilityWidget, &TeacherDisponibilityWidget::solicitarEdicionMaestro, this, [this](int id){
        teacherDetailsWidget->cargarDatos(id);
        ui->stackedWidget->setCurrentWidget(teacherDetailsWidget);
        ui->sectionTitle->setText("Editar Maestro");
    });
    
    connect(teacherDisponibilityWidget, &TeacherDisponibilityWidget::solicitarNuevoMaestro, this, [this](){
        teacherDetailsWidget->prepararNuevoMaestro();
        ui->stackedWidget->setCurrentWidget(teacherDetailsWidget);
        ui->sectionTitle->setText("Crear Maestro");
    });
    
    connect(teacherDetailsWidget, &TeacherDetailsWidget::backClicked, this, [this](){
        teacherDisponibilityWidget->cargarMaestros();
        ui->stackedWidget->setCurrentWidget(teacherDisponibilityWidget);
        ui->sectionTitle->setText("Disponibilidad de Maestros");
    });
    
    connect(teacherDetailsWidget, &TeacherDetailsWidget::applyClicked, this, [this](){
        teacherDisponibilityWidget->cargarMaestros();
        ui->stackedWidget->setCurrentWidget(teacherDisponibilityWidget);
        ui->sectionTitle->setText("Disponibilidad de Maestros");
    });
    
    // Schedules Navigation
    connect(schedulesWidget, &SchedulesWidget::showTeacherSchedule, this, [this](int id){
        teacherScheduleWidget->loadSchedule(id);
        ui->stackedWidget->setCurrentWidget(teacherScheduleWidget);
        ui->sectionTitle->setText("Horario del Maestro");
    });
    
    connect(schedulesWidget, &SchedulesWidget::showGroupSchedule, this, [this](int id){
        groupScheduleWidget->loadSchedule(id);
        ui->stackedWidget->setCurrentWidget(groupScheduleWidget);
        ui->sectionTitle->setText("Horario del Grupo");
    });
    
    connect(teacherScheduleWidget, &TeacherScheduleWidget::backClicked, this, [this](){
        ui->stackedWidget->setCurrentWidget(schedulesWidget);
        ui->sectionTitle->setText("Horarios");
    });
    
    connect(groupScheduleWidget, &GroupScheduleWidget::backClicked, this, [this](){
        ui->stackedWidget->setCurrentWidget(schedulesWidget);
        ui->sectionTitle->setText("Horarios");
    });
    
    // Conectar actualización de horarios
    connect(generationWidget, &GenerationWidget::schedulesUpdated, this, [this](){
        if (generationWidget) {
            Horario* hGrupos = generationWidget->getHorariosGrupos();
            Horario* hMaestros = generationWidget->getHorariosMaestros();
            // Horario* hSalones = generationWidget->getHorariosSalones(); // Not used in widgets yet but available
            
            int cantHGrupos = (m_grupos) ? m_grupos->getCantidad() : 0;
            int cantHMaestros = (m_maestros) ? m_maestros->getCantidad() : 0;

            if (gruposWidget) {
                gruposWidget->setHorarios(hGrupos);
            }
            
            if (schedulesWidget) {
                schedulesWidget->setData(m_maestros, m_grupos, m_materias, hMaestros, cantHMaestros, hGrupos, cantHGrupos);
            }
            
            if (teacherScheduleWidget) {
                teacherScheduleWidget->setData(m_maestros, m_materias, m_grupos, m_salones, hMaestros, cantHMaestros);
            }
            
            if (groupScheduleWidget) {
                groupScheduleWidget->setData(m_maestros, m_materias, m_grupos, m_salones, hGrupos, cantHGrupos);
            }
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setData(materias* m, salones* s, grupos* g, maestros* ma, ConjuntoMaterias* c, Horario* hGrupos, int cantHGrupos, Horario* hMaestros, int cantHMaestros)
{
    // Store pointers
    m_materias = m;
    m_salones = s;
    m_grupos = g;
    m_maestros = ma;
    m_conjuntos = c;

    // Pass data to widgets
    if (generationWidget) {
        generationWidget->setData(m, s, g, ma, c);
    }
    
    if (salonesWidget) {
        salonesWidget->setData(s);
    }
    
    if (roomDetailsWidget) {
        roomDetailsWidget->setData(s);
    }
    
    if (quartersWidget) {
        quartersWidget->setData(c, m);
    }
    
    if (quarterDetailsWidget) {
        quarterDetailsWidget->setData(c, m);
    }
    
    if (gruposWidget) {
        gruposWidget->setData(g, m, ma, c, hGrupos, cantHGrupos);
    }
    
    if (groupDetailsWidget) {
        groupDetailsWidget->setData(g, m, ma, c);
    }
    
    if (teacherDisponibilityWidget) {
        teacherDisponibilityWidget->setData(ma);
    }
    
    if (teacherDetailsWidget) {
        teacherDetailsWidget->setData(ma, m);
    }
    
    if (schedulesWidget) {
        schedulesWidget->setData(ma, g, m, hMaestros, cantHMaestros, hGrupos, cantHGrupos);
    }
    
    if (teacherScheduleWidget) {
        teacherScheduleWidget->setData(ma, m, g, s, hMaestros, cantHMaestros);
    }
    
    if (groupScheduleWidget) {
        groupScheduleWidget->setData(ma, m, g, s, hGrupos, cantHGrupos);
    }
}

void MainWindow::on_generationButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(generationWidget);
    ui->sectionTitle->setText("Generacion");
}

void MainWindow::on_teacherDisponibilityButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(teacherDisponibilityWidget);
    ui->sectionTitle->setText("Disponibilidad Maestros");
}

void MainWindow::on_schedulesButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(schedulesWidget);
    ui->sectionTitle->setText("Horarios");
}

void MainWindow::on_cuatrimestresButton_clicked()
{
    if (quartersWidget) {
        quartersWidget->cargarCuatrimestres();
    }
    ui->stackedWidget->setCurrentWidget(quartersWidget);
    ui->sectionTitle->setText("Cuatrimestres");
}

void MainWindow::on_groupButton_clicked()
{
    if (gruposWidget && generationWidget) {
        gruposWidget->setHorarios(generationWidget->getHorariosGrupos());
    }
    ui->stackedWidget->setCurrentWidget(gruposWidget);
    ui->sectionTitle->setText("Grupos");
}

void MainWindow::on_salonesButton_clicked()
{
    if (salonesWidget) {
        salonesWidget->cargarSalones();
    }
    ui->stackedWidget->setCurrentWidget(salonesWidget);
    ui->sectionTitle->setText("Salones");
}
