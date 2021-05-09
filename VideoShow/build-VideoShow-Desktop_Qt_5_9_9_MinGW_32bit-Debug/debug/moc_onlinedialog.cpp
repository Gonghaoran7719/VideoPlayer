/****************************************************************************
** Meta object code from reading C++ file 'onlinedialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VideoShow/onlinedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'onlinedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UploadWorker_t {
    QByteArrayData data[7];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UploadWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UploadWorker_t qt_meta_stringdata_UploadWorker = {
    {
QT_MOC_LITERAL(0, 0, 12), // "UploadWorker"
QT_MOC_LITERAL(1, 13, 15), // "slot_UploadFile"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 8), // "filePath"
QT_MOC_LITERAL(4, 39, 7), // "imgPath"
QT_MOC_LITERAL(5, 47, 5), // "Hobby"
QT_MOC_LITERAL(6, 53, 2) // "hy"

    },
    "UploadWorker\0slot_UploadFile\0\0filePath\0"
    "imgPath\0Hobby\0hy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UploadWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 5,    3,    4,    6,

       0        // eod
};

void UploadWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UploadWorker *_t = static_cast<UploadWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_UploadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< Hobby(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject UploadWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UploadWorker.data,
      qt_meta_data_UploadWorker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *UploadWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UploadWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UploadWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UploadWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_OnlineDialog_t {
    QByteArrayData data[35];
    char stringdata0[436];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OnlineDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OnlineDialog_t qt_meta_stringdata_OnlineDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OnlineDialog"
QT_MOC_LITERAL(1, 13, 10), // "SIG_PlayTV"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 20), // "OnlineDialog::TVList"
QT_MOC_LITERAL(4, 46, 2), // "tv"
QT_MOC_LITERAL(5, 49, 17), // "SIG_updateProcess"
QT_MOC_LITERAL(6, 67, 11), // "SIG_PlayUrl"
QT_MOC_LITERAL(7, 79, 3), // "url"
QT_MOC_LITERAL(8, 83, 19), // "on_pb_login_clicked"
QT_MOC_LITERAL(9, 103, 15), // "slot_btnClicked"
QT_MOC_LITERAL(10, 119, 16), // "slot_loginCommit"
QT_MOC_LITERAL(11, 136, 4), // "name"
QT_MOC_LITERAL(12, 141, 8), // "password"
QT_MOC_LITERAL(13, 150, 19), // "slot_registerCommit"
QT_MOC_LITERAL(14, 170, 5), // "Hobby"
QT_MOC_LITERAL(15, 176, 2), // "hy"
QT_MOC_LITERAL(16, 179, 14), // "slot_ReadyData"
QT_MOC_LITERAL(17, 194, 5), // "char*"
QT_MOC_LITERAL(18, 200, 3), // "buf"
QT_MOC_LITERAL(19, 204, 4), // "nlen"
QT_MOC_LITERAL(20, 209, 12), // "slot_loginRs"
QT_MOC_LITERAL(21, 222, 15), // "slot_registerRs"
QT_MOC_LITERAL(22, 238, 13), // "slot_uploadRs"
QT_MOC_LITERAL(23, 252, 15), // "slot_downloadRs"
QT_MOC_LITERAL(24, 268, 16), // "slot_fileBlockRq"
QT_MOC_LITERAL(25, 285, 16), // "slot_PlayClicked"
QT_MOC_LITERAL(26, 302, 15), // "slot_UploadFile"
QT_MOC_LITERAL(27, 318, 8), // "filePath"
QT_MOC_LITERAL(28, 327, 7), // "imgPath"
QT_MOC_LITERAL(29, 335, 10), // "UploadFile"
QT_MOC_LITERAL(30, 346, 7), // "gifName"
QT_MOC_LITERAL(31, 354, 20), // "on_pb_upload_clicked"
QT_MOC_LITERAL(32, 375, 20), // "on_pb_tvShow_clicked"
QT_MOC_LITERAL(33, 396, 19), // "on_pb_video_clicked"
QT_MOC_LITERAL(34, 416, 19) // "on_pb_fresh_clicked"

    },
    "OnlineDialog\0SIG_PlayTV\0\0OnlineDialog::TVList\0"
    "tv\0SIG_updateProcess\0SIG_PlayUrl\0url\0"
    "on_pb_login_clicked\0slot_btnClicked\0"
    "slot_loginCommit\0name\0password\0"
    "slot_registerCommit\0Hobby\0hy\0"
    "slot_ReadyData\0char*\0buf\0nlen\0"
    "slot_loginRs\0slot_registerRs\0slot_uploadRs\0"
    "slot_downloadRs\0slot_fileBlockRq\0"
    "slot_PlayClicked\0slot_UploadFile\0"
    "filePath\0imgPath\0UploadFile\0gifName\0"
    "on_pb_upload_clicked\0on_pb_tvShow_clicked\0"
    "on_pb_video_clicked\0on_pb_fresh_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OnlineDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  119,    2, 0x06 /* Public */,
       5,    2,  122,    2, 0x06 /* Public */,
       6,    1,  127,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  130,    2, 0x0a /* Public */,
       9,    0,  131,    2, 0x0a /* Public */,
      10,    2,  132,    2, 0x0a /* Public */,
      13,    3,  137,    2, 0x0a /* Public */,
      16,    2,  144,    2, 0x0a /* Public */,
      20,    2,  149,    2, 0x0a /* Public */,
      21,    2,  154,    2, 0x0a /* Public */,
      22,    2,  159,    2, 0x0a /* Public */,
      23,    2,  164,    2, 0x0a /* Public */,
      24,    2,  169,    2, 0x0a /* Public */,
      25,    0,  174,    2, 0x0a /* Public */,
      26,    3,  175,    2, 0x0a /* Public */,
      29,    3,  182,    2, 0x0a /* Public */,
      29,    2,  189,    2, 0x2a /* Public | MethodCloned */,
      31,    0,  194,    2, 0x0a /* Public */,
      32,    0,  195,    2, 0x08 /* Private */,
      33,    0,  196,    2, 0x08 /* Private */,
      34,    0,  197,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 14,   11,   12,   15,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Int,   18,   19,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Int,   18,   19,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Int,   18,   19,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Int,   18,   19,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Int,   18,   19,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Int,   18,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 14,   27,   28,   15,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 14, QMetaType::QString,   27,   15,   30,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 14,   27,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OnlineDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OnlineDialog *_t = static_cast<OnlineDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_PlayTV((*reinterpret_cast< OnlineDialog::TVList(*)>(_a[1]))); break;
        case 1: _t->SIG_updateProcess((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 2: _t->SIG_PlayUrl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->on_pb_login_clicked(); break;
        case 4: _t->slot_btnClicked(); break;
        case 5: _t->slot_loginCommit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->slot_registerCommit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< Hobby(*)>(_a[3]))); break;
        case 7: _t->slot_ReadyData((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->slot_loginRs((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->slot_registerRs((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->slot_uploadRs((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->slot_downloadRs((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->slot_fileBlockRq((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->slot_PlayClicked(); break;
        case 14: _t->slot_UploadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< Hobby(*)>(_a[3]))); break;
        case 15: _t->UploadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< Hobby(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 16: _t->UploadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< Hobby(*)>(_a[2]))); break;
        case 17: _t->on_pb_upload_clicked(); break;
        case 18: _t->on_pb_tvShow_clicked(); break;
        case 19: _t->on_pb_video_clicked(); break;
        case 20: _t->on_pb_fresh_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (OnlineDialog::*_t)(OnlineDialog::TVList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OnlineDialog::SIG_PlayTV)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (OnlineDialog::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OnlineDialog::SIG_updateProcess)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (OnlineDialog::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OnlineDialog::SIG_PlayUrl)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject OnlineDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_OnlineDialog.data,
      qt_meta_data_OnlineDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *OnlineDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OnlineDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OnlineDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int OnlineDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void OnlineDialog::SIG_PlayTV(OnlineDialog::TVList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OnlineDialog::SIG_updateProcess(qint64 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OnlineDialog::SIG_PlayUrl(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
