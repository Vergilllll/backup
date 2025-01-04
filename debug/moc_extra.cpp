/****************************************************************************
** Meta object code from reading C++ file 'extra.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../extra.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'extra.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_extra_t {
    QByteArrayData data[20];
    char stringdata0[295];
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
QT_MOC_LITERAL(6, 64, 22), // "ConfirmScheduledBackup"
QT_MOC_LITERAL(7, 87, 21), // "ConfirmRealTimeBackup"
QT_MOC_LITERAL(8, 109, 20), // "startScheduledBackup"
QT_MOC_LITERAL(9, 130, 19), // "stopScheduledBackup"
QT_MOC_LITERAL(10, 150, 19), // "startRealTimeBackup"
QT_MOC_LITERAL(11, 170, 18), // "stopRealTimeBackup"
QT_MOC_LITERAL(12, 189, 9), // "onTimeout"
QT_MOC_LITERAL(13, 199, 14), // "showMainWindow"
QT_MOC_LITERAL(14, 214, 13), // "onWindowClose"
QT_MOC_LITERAL(15, 228, 16), // "closeApplication"
QT_MOC_LITERAL(16, 245, 11), // "SetPassWord"
QT_MOC_LITERAL(17, 257, 13), // "onFileChanged"
QT_MOC_LITERAL(18, 271, 4), // "path"
QT_MOC_LITERAL(19, 276, 18) // "onDirectoryChanged"

    },
    "extra\0backToMain\0\0BrowseSource\0"
    "BrowseDirectory\0BrowseBackupPath\0"
    "ConfirmScheduledBackup\0ConfirmRealTimeBackup\0"
    "startScheduledBackup\0stopScheduledBackup\0"
    "startRealTimeBackup\0stopRealTimeBackup\0"
    "onTimeout\0showMainWindow\0onWindowClose\0"
    "closeApplication\0SetPassWord\0onFileChanged\0"
    "path\0onDirectoryChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_extra[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    0,  112,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    1,  114,    2, 0x08 /* Private */,
      19,    1,  117,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString,   18,

       0        // eod
};

void extra::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<extra *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backToMain(); break;
        case 1: _t->BrowseSource(); break;
        case 2: _t->BrowseDirectory(); break;
        case 3: _t->BrowseBackupPath(); break;
        case 4: _t->ConfirmScheduledBackup(); break;
        case 5: _t->ConfirmRealTimeBackup(); break;
        case 6: _t->startScheduledBackup(); break;
        case 7: _t->stopScheduledBackup(); break;
        case 8: _t->startRealTimeBackup(); break;
        case 9: _t->stopRealTimeBackup(); break;
        case 10: _t->onTimeout(); break;
        case 11: _t->showMainWindow(); break;
        case 12: _t->onWindowClose(); break;
        case 13: _t->closeApplication(); break;
        case 14: _t->SetPassWord(); break;
        case 15: _t->onFileChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->onDirectoryChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (extra::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&extra::backToMain)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject extra::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_extra.data,
    qt_meta_data_extra,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
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
