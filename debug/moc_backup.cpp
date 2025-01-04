/****************************************************************************
** Meta object code from reading C++ file 'backup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../backup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_backup_t {
    QByteArrayData data[14];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_backup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_backup_t qt_meta_stringdata_backup = {
    {
QT_MOC_LITERAL(0, 0, 6), // "backup"
QT_MOC_LITERAL(1, 7, 14), // "return_to_main"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 8), // "sendPath"
QT_MOC_LITERAL(4, 32, 12), // "BrowseSource"
QT_MOC_LITERAL(5, 45, 15), // "BrowseDirectory"
QT_MOC_LITERAL(6, 61, 12), // "BrowseBackup"
QT_MOC_LITERAL(7, 74, 15), // "BackupResources"
QT_MOC_LITERAL(8, 90, 12), // "return_click"
QT_MOC_LITERAL(9, 103, 11), // "extra_click"
QT_MOC_LITERAL(10, 115, 11), // "SetPassWord"
QT_MOC_LITERAL(11, 127, 12), // "filter_click"
QT_MOC_LITERAL(12, 140, 10), // "showBackup"
QT_MOC_LITERAL(13, 151, 10) // "changePath"

    },
    "backup\0return_to_main\0\0sendPath\0"
    "BrowseSource\0BrowseDirectory\0BrowseBackup\0"
    "BackupResources\0return_click\0extra_click\0"
    "SetPassWord\0filter_click\0showBackup\0"
    "changePath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_backup[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   78,    2, 0x08 /* Private */,
       5,    0,   79,    2, 0x08 /* Private */,
       6,    0,   80,    2, 0x08 /* Private */,
       7,    0,   81,    2, 0x08 /* Private */,
       8,    0,   82,    2, 0x08 /* Private */,
       9,    0,   83,    2, 0x08 /* Private */,
      10,    0,   84,    2, 0x08 /* Private */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    1,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

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
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void backup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<backup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->return_to_main(); break;
        case 1: _t->sendPath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->BrowseSource(); break;
        case 3: _t->BrowseDirectory(); break;
        case 4: _t->BrowseBackup(); break;
        case 5: _t->BackupResources(); break;
        case 6: _t->return_click(); break;
        case 7: _t->extra_click(); break;
        case 8: _t->SetPassWord(); break;
        case 9: _t->filter_click(); break;
        case 10: _t->showBackup(); break;
        case 11: _t->changePath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (backup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&backup::return_to_main)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (backup::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&backup::sendPath)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject backup::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_backup.data,
    qt_meta_data_backup,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *backup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *backup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_backup.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int backup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void backup::return_to_main()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void backup::sendPath(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
