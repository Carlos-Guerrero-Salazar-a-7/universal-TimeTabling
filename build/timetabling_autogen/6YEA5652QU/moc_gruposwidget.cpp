/****************************************************************************
** Meta object code from reading C++ file 'gruposwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/gruposwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gruposwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GruposWidget_t {
    QByteArrayData data[12];
    char stringdata0[226];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GruposWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GruposWidget_t qt_meta_stringdata_GruposWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "GruposWidget"
QT_MOC_LITERAL(1, 13, 21), // "solicitarEdicionGrupo"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "id_grupo"
QT_MOC_LITERAL(4, 45, 19), // "solicitarNuevoGrupo"
QT_MOC_LITERAL(5, 65, 22), // "solicitarDetallesGrupo"
QT_MOC_LITERAL(6, 88, 28), // "on_createGroupButton_clicked"
QT_MOC_LITERAL(7, 117, 29), // "on_searchLineEdit_textChanged"
QT_MOC_LITERAL(8, 147, 4), // "arg1"
QT_MOC_LITERAL(9, 152, 22), // "handleEditGroupClicked"
QT_MOC_LITERAL(10, 175, 24), // "handleDeleteGroupClicked"
QT_MOC_LITERAL(11, 200, 25) // "handleDetailsGroupClicked"

    },
    "GruposWidget\0solicitarEdicionGrupo\0\0"
    "id_grupo\0solicitarNuevoGrupo\0"
    "solicitarDetallesGrupo\0"
    "on_createGroupButton_clicked\0"
    "on_searchLineEdit_textChanged\0arg1\0"
    "handleEditGroupClicked\0handleDeleteGroupClicked\0"
    "handleDetailsGroupClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GruposWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,
       5,    1,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   61,    2, 0x08 /* Private */,
       7,    1,   62,    2, 0x08 /* Private */,
       9,    0,   65,    2, 0x08 /* Private */,
      10,    0,   66,    2, 0x08 /* Private */,
      11,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GruposWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GruposWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->solicitarEdicionGrupo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->solicitarNuevoGrupo(); break;
        case 2: _t->solicitarDetallesGrupo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_createGroupButton_clicked(); break;
        case 4: _t->on_searchLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->handleEditGroupClicked(); break;
        case 6: _t->handleDeleteGroupClicked(); break;
        case 7: _t->handleDetailsGroupClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GruposWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GruposWidget::solicitarEdicionGrupo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GruposWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GruposWidget::solicitarNuevoGrupo)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GruposWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GruposWidget::solicitarDetallesGrupo)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GruposWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GruposWidget.data,
    qt_meta_data_GruposWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GruposWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GruposWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GruposWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GruposWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void GruposWidget::solicitarEdicionGrupo(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GruposWidget::solicitarNuevoGrupo()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GruposWidget::solicitarDetallesGrupo(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
