/****************************************************************************
** Meta object code from reading C++ file 'quarterswidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/quarterswidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quarterswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClickableFrame_t {
    QByteArrayData data[3];
    char stringdata0[24];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClickableFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClickableFrame_t qt_meta_stringdata_ClickableFrame = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ClickableFrame"
QT_MOC_LITERAL(1, 15, 7), // "clicked"
QT_MOC_LITERAL(2, 23, 0) // ""

    },
    "ClickableFrame\0clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClickableFrame[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void ClickableFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClickableFrame *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClickableFrame::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClickableFrame::clicked)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject ClickableFrame::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_ClickableFrame.data,
    qt_meta_data_ClickableFrame,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ClickableFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClickableFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClickableFrame.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ClickableFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ClickableFrame::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_QuartersWidget_t {
    QByteArrayData data[10];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QuartersWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QuartersWidget_t qt_meta_stringdata_QuartersWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QuartersWidget"
QT_MOC_LITERAL(1, 15, 29), // "solicitarDetallesCuatrimestre"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 2), // "id"
QT_MOC_LITERAL(4, 49, 28), // "solicitarEdicionCuatrimestre"
QT_MOC_LITERAL(5, 78, 26), // "solicitarNuevoCuatrimestre"
QT_MOC_LITERAL(6, 105, 17), // "on_quarterClicked"
QT_MOC_LITERAL(7, 123, 20), // "on_addButton_clicked"
QT_MOC_LITERAL(8, 144, 17), // "handleEditQuarter"
QT_MOC_LITERAL(9, 162, 19) // "handleDeleteQuarter"

    },
    "QuartersWidget\0solicitarDetallesCuatrimestre\0"
    "\0id\0solicitarEdicionCuatrimestre\0"
    "solicitarNuevoCuatrimestre\0on_quarterClicked\0"
    "on_addButton_clicked\0handleEditQuarter\0"
    "handleDeleteQuarter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QuartersWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       5,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   56,    2, 0x08 /* Private */,
       7,    0,   57,    2, 0x08 /* Private */,
       8,    1,   58,    2, 0x08 /* Private */,
       9,    1,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void QuartersWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QuartersWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->solicitarDetallesCuatrimestre((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->solicitarEdicionCuatrimestre((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->solicitarNuevoCuatrimestre(); break;
        case 3: _t->on_quarterClicked(); break;
        case 4: _t->on_addButton_clicked(); break;
        case 5: _t->handleEditQuarter((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->handleDeleteQuarter((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QuartersWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QuartersWidget::solicitarDetallesCuatrimestre)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QuartersWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QuartersWidget::solicitarEdicionCuatrimestre)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QuartersWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QuartersWidget::solicitarNuevoCuatrimestre)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QuartersWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_QuartersWidget.data,
    qt_meta_data_QuartersWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QuartersWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QuartersWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QuartersWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QuartersWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QuartersWidget::solicitarDetallesCuatrimestre(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QuartersWidget::solicitarEdicionCuatrimestre(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QuartersWidget::solicitarNuevoCuatrimestre()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
