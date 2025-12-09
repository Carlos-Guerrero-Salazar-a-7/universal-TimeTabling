cmake_minimum_required(VERSION 3.16)

project(timetabling VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(include)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        include/mainwindow.h
        forms/mainwindow.ui
        src/saloneswidget.cpp
        include/saloneswidget.h
        forms/saloneswidget.ui
        src/roomdetailswidget.cpp
        include/roomdetailswidget.h
        forms/roomdetailswidget.ui
        src/scheduleswidget.cpp
        include/scheduleswidget.h
        forms/scheduleswidget.ui
        src/teacherschedulewidget.cpp
        include/teacherschedulewidget.h
        forms/teacherschedulewidget.ui
        src/quarterswidget.cpp include/quarterswidget.h forms/quarterswidget.ui
        src/quarterdetailswidget.cpp include/quarterdetailswidget.h forms/quarterdetailswidget.ui
        src/gruposwidget.cpp include/gruposwidget.h forms/gruposwidget.ui
        src/groupdetailswidget.cpp include/groupdetailswidget.h forms/groupdetailswidget.ui
        src/teacherdisponibilitywidget.cpp include/teacherdisponibilitywidget.h forms/teacherdisponibilitywidget.ui
        src/teacherdetailswidget.cpp include/teacherdetailswidget.h forms/teacherdetailswidget.ui
        src/groupschedulewidget.cpp include/groupschedulewidget.h forms/groupschedulewidget.ui
        src/generationwidget.cpp
        include/generationwidget.h
        forms/generationwidget.ui
        src/materias.cpp
        src/salones.cpp
        src/grupos.cpp
        src/maestros.cpp
        src/conjunto_materias.cpp
        src/horario.cpp
        src/modificaciones_objetos.cpp
        src/horario_disponibilidad.cpp
        src/universal_time_tabling.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(timetabling
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET timetabling APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(timetabling SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(timetabling
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(timetabling PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.timetabling)
endif()
set_target_properties(timetabling PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms
)

include(GNUInstallDirs)
install(TARGETS timetabling
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(timetabling)
endif()
