/****************************************************************************
** Meta object code from reading C++ file 'widget2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../untitled3/widget2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget2_t {
    QByteArrayData data[16];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget2_t qt_meta_stringdata_Widget2 = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Widget2"
QT_MOC_LITERAL(1, 8, 7), // "Timeout"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 8), // "Timeout2"
QT_MOC_LITERAL(4, 26, 12), // "SetDirection"
QT_MOC_LITERAL(5, 39, 1), // "n"
QT_MOC_LITERAL(6, 41, 13), // "CheckGameOver"
QT_MOC_LITERAL(7, 55, 9), // "StartPush"
QT_MOC_LITERAL(8, 65, 9), // "PausePush"
QT_MOC_LITERAL(9, 75, 8), // "QuitPush"
QT_MOC_LITERAL(10, 84, 7), // "setFood"
QT_MOC_LITERAL(11, 92, 7), // "settime"
QT_MOC_LITERAL(12, 100, 7), // "setWall"
QT_MOC_LITERAL(13, 108, 7), // "AISnake"
QT_MOC_LITERAL(14, 116, 9), // "AITimeout"
QT_MOC_LITERAL(15, 126, 9) // "clearCore"

    },
    "Widget2\0Timeout\0\0Timeout2\0SetDirection\0"
    "n\0CheckGameOver\0StartPush\0PausePush\0"
    "QuitPush\0setFood\0settime\0setWall\0"
    "AISnake\0AITimeout\0clearCore"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget2[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    1,   81,    2, 0x0a /* Public */,
       6,    0,   84,    2, 0x0a /* Public */,
       7,    0,   85,    2, 0x0a /* Public */,
       8,    0,   86,    2, 0x0a /* Public */,
       9,    0,   87,    2, 0x0a /* Public */,
      10,    0,   88,    2, 0x0a /* Public */,
      11,    0,   89,    2, 0x0a /* Public */,
      12,    0,   90,    2, 0x0a /* Public */,
      13,    0,   91,    2, 0x0a /* Public */,
      14,    0,   92,    2, 0x0a /* Public */,
      15,    0,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Timeout(); break;
        case 1: _t->Timeout2(); break;
        case 2: _t->SetDirection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->CheckGameOver(); break;
        case 4: _t->StartPush(); break;
        case 5: _t->PausePush(); break;
        case 6: _t->QuitPush(); break;
        case 7: _t->setFood(); break;
        case 8: _t->settime(); break;
        case 9: _t->setWall(); break;
        case 10: _t->AISnake(); break;
        case 11: _t->AITimeout(); break;
        case 12: _t->clearCore(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget2::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Widget2.data,
    qt_meta_data_Widget2,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget2.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
