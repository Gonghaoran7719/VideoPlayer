/****************************************************************************
** Meta object code from reading C++ file 'videoshow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VideoShow/videoshow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoshow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VideoShow_t {
    QByteArrayData data[19];
    char stringdata0[268];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoShow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoShow_t qt_meta_stringdata_VideoShow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "VideoShow"
QT_MOC_LITERAL(1, 10, 18), // "on_pb_play_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 18), // "on_pb_open_clicked"
QT_MOC_LITERAL(4, 49, 19), // "on_pb_pause_clicked"
QT_MOC_LITERAL(5, 69, 18), // "on_pb_stop_clicked"
QT_MOC_LITERAL(6, 88, 23), // "slot_PlayerStateChanged"
QT_MOC_LITERAL(7, 112, 5), // "state"
QT_MOC_LITERAL(8, 118, 17), // "slot_getTotalTime"
QT_MOC_LITERAL(9, 136, 4), // "uSec"
QT_MOC_LITERAL(10, 141, 17), // "slot_TimerTimeOut"
QT_MOC_LITERAL(11, 159, 28), // "slot_videoSliderValueChanged"
QT_MOC_LITERAL(12, 188, 5), // "value"
QT_MOC_LITERAL(13, 194, 20), // "on_pb_online_clicked"
QT_MOC_LITERAL(14, 215, 11), // "slot_PlayTV"
QT_MOC_LITERAL(15, 227, 20), // "OnlineDialog::TVList"
QT_MOC_LITERAL(16, 248, 2), // "tv"
QT_MOC_LITERAL(17, 251, 12), // "slot_PlayUrl"
QT_MOC_LITERAL(18, 264, 3) // "url"

    },
    "VideoShow\0on_pb_play_clicked\0\0"
    "on_pb_open_clicked\0on_pb_pause_clicked\0"
    "on_pb_stop_clicked\0slot_PlayerStateChanged\0"
    "state\0slot_getTotalTime\0uSec\0"
    "slot_TimerTimeOut\0slot_videoSliderValueChanged\0"
    "value\0on_pb_online_clicked\0slot_PlayTV\0"
    "OnlineDialog::TVList\0tv\0slot_PlayUrl\0"
    "url"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoShow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    1,   73,    2, 0x08 /* Private */,
       8,    1,   76,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    1,   80,    2, 0x08 /* Private */,
      13,    0,   83,    2, 0x08 /* Private */,
      14,    1,   84,    2, 0x08 /* Private */,
      17,    1,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::LongLong,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::QString,   18,

       0        // eod
};

void VideoShow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoShow *_t = static_cast<VideoShow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pb_play_clicked(); break;
        case 1: _t->on_pb_open_clicked(); break;
        case 2: _t->on_pb_pause_clicked(); break;
        case 3: _t->on_pb_stop_clicked(); break;
        case 4: _t->slot_PlayerStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_getTotalTime((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 6: _t->slot_TimerTimeOut(); break;
        case 7: _t->slot_videoSliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_pb_online_clicked(); break;
        case 9: _t->slot_PlayTV((*reinterpret_cast< OnlineDialog::TVList(*)>(_a[1]))); break;
        case 10: _t->slot_PlayUrl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject VideoShow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VideoShow.data,
      qt_meta_data_VideoShow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VideoShow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoShow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoShow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VideoShow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
