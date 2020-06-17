/****************************************************************************
** Meta object code from reading C++ file 'sniffer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../snifferQt/sniffer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sniffer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sniffer_t {
    QByteArrayData data[12];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sniffer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sniffer_t qt_meta_stringdata_sniffer = {
    {
QT_MOC_LITERAL(0, 0, 7), // "sniffer"
QT_MOC_LITERAL(1, 8, 20), // "on_selectBtn_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "checked"
QT_MOC_LITERAL(4, 38, 31), // "on_adapters_currentIndexChanged"
QT_MOC_LITERAL(5, 70, 5), // "index"
QT_MOC_LITERAL(6, 76, 23), // "on_PCITable_cellChanged"
QT_MOC_LITERAL(7, 100, 3), // "row"
QT_MOC_LITERAL(8, 104, 6), // "column"
QT_MOC_LITERAL(9, 111, 26), // "on_captimeText_textChanged"
QT_MOC_LITERAL(10, 138, 4), // "arg1"
QT_MOC_LITERAL(11, 143, 23) // "on_PCITable_cellClicked"

    },
    "sniffer\0on_selectBtn_clicked\0\0checked\0"
    "on_adapters_currentIndexChanged\0index\0"
    "on_PCITable_cellChanged\0row\0column\0"
    "on_captimeText_textChanged\0arg1\0"
    "on_PCITable_cellClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sniffer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       4,    1,   42,    2, 0x08 /* Private */,
       6,    2,   45,    2, 0x08 /* Private */,
       9,    1,   50,    2, 0x08 /* Private */,
      11,    2,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,

       0        // eod
};

void sniffer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<sniffer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_selectBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_adapters_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_PCITable_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->on_captimeText_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_PCITable_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject sniffer::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_sniffer.data,
    qt_meta_data_sniffer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *sniffer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sniffer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sniffer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int sniffer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
