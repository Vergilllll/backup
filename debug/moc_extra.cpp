/****************************************************************************
** Meta object code from reading C++ file 'extra.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../extra.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'extra.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_extra_t {
    QByteArrayData data[14];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_extra_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_extra_t qt_meta_stringdata_extra = {
    {
QT_MOC_LITERAL(0, 0, 5), // "extra"
QT_MOC_LITERAL(1, 6, 10), // "backToMain"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 12), // "BrowseSource"
QT_MOC_LITERAL(4, 31, 15), // "BrowseDirectory"
QT_MOC_LITERAL(5, 47, 16), // "BrowseBackupPath"
QT_MOC_LITERAL(6, 64, 16), // "ConfirmSelection"
QT_MOC_LITERAL(7, 81, 20), // "startScheduledBackup"
QT_MOC_LITERAL(8, 102, 19), // "stopScheduledBackup"
QT_MOC_LITERAL(9, 122, 13), // "performBackup"
QT_MOC_LITERAL(10, 136, 14), // "showMainWindow"
QT_MOC_LITERAL(11, 151, 13), // "onWindowClose"
QT_MOC_LITERAL(12, 165, 16), // "closeApplication"
QT_MOC_LITERAL(13, 182, 11) // "SetPassWord"

    },
    "extra\0backToMain\0\0BrowseSource\0"
    "BrowseDirectory\0BrowseBackupPath\0"
    "ConfirmSelection\0startScheduledBackup\0"
    "stopScheduledBackup\0performBackup\0"
    "showMainWindow\0onWindowClose\0"
    "closeApplication\0SetPassWord"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_extra[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
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
    QMetaType::Void,

       0        // eod
};

void extra::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        extra *_t = static_cast<extra *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backToMain(); break;
        case 1: _t->BrowseSource(); break;
        case 2: _t->BrowseDirectory(); break;
        case 3: _t->BrowseBackupPath(); break;
        case 4: _t->ConfirmSelection(); break;
        case 5: _t->startScheduledBackup(); break;
        case 6: _t->stopScheduledBackup(); break;
        case 7: _t->performBackup(); break;
        case 8: _t->showMainWindow(); break;
        case 9: _t->onWindowClose(); break;
        case 10: _t->closeApplication(); break;
        case 11: _t->SetPassWord(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (extra::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&extra::backToMain)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject extra::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_extra.data,
      qt_meta_data_extra,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *extra::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *extra::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_extra.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int extra::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void extra::backToMain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
