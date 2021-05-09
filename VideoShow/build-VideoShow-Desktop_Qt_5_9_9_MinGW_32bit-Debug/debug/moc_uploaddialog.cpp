/****************************************************************************
** Meta object code from reading C++ file 'uploaddialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VideoShow/uploaddialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uploaddialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UploadDialog_t {
    QByteArrayData data[27];
    char stringdata0[384];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UploadDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UploadDialog_t qt_meta_stringdata_UploadDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "UploadDialog"
QT_MOC_LITERAL(1, 13, 17), // "SIG_GetOnePicture"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "image"
QT_MOC_LITERAL(4, 38, 14), // "SIG_UploadFile"
QT_MOC_LITERAL(5, 53, 8), // "filePath"
QT_MOC_LITERAL(6, 62, 7), // "imgPath"
QT_MOC_LITERAL(7, 70, 5), // "Hobby"
QT_MOC_LITERAL(8, 76, 2), // "by"
QT_MOC_LITERAL(9, 79, 18), // "on_pb_view_clicked"
QT_MOC_LITERAL(10, 98, 25), // "on_pb_beginUpload_clicked"
QT_MOC_LITERAL(11, 124, 18), // "slot_updateProcess"
QT_MOC_LITERAL(12, 143, 3), // "cur"
QT_MOC_LITERAL(13, 147, 3), // "max"
QT_MOC_LITERAL(14, 151, 7), // "initDev"
QT_MOC_LITERAL(15, 159, 14), // "setVideoDevice"
QT_MOC_LITERAL(16, 174, 3), // "str"
QT_MOC_LITERAL(17, 178, 14), // "setAudioDevice"
QT_MOC_LITERAL(18, 193, 19), // "on_pb_page1_clicked"
QT_MOC_LITERAL(19, 213, 19), // "on_pb_page2_clicked"
QT_MOC_LITERAL(20, 233, 17), // "on_cb_cam_clicked"
QT_MOC_LITERAL(21, 251, 18), // "on_cb_desk_clicked"
QT_MOC_LITERAL(22, 270, 18), // "slot_updateRecTime"
QT_MOC_LITERAL(23, 289, 25), // "on_pb_recordBegin_clicked"
QT_MOC_LITERAL(24, 315, 23), // "on_pb_recordEnd_clicked"
QT_MOC_LITERAL(25, 339, 21), // "on_pb_rtmpUrl_clicked"
QT_MOC_LITERAL(26, 361, 22) // "on_pb_savePath_clicked"

    },
    "UploadDialog\0SIG_GetOnePicture\0\0image\0"
    "SIG_UploadFile\0filePath\0imgPath\0Hobby\0"
    "by\0on_pb_view_clicked\0on_pb_beginUpload_clicked\0"
    "slot_updateProcess\0cur\0max\0initDev\0"
    "setVideoDevice\0str\0setAudioDevice\0"
    "on_pb_page1_clicked\0on_pb_page2_clicked\0"
    "on_cb_cam_clicked\0on_cb_desk_clicked\0"
    "slot_updateRecTime\0on_pb_recordBegin_clicked\0"
    "on_pb_recordEnd_clicked\0on_pb_rtmpUrl_clicked\0"
    "on_pb_savePath_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UploadDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    3,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  109,    2, 0x0a /* Public */,
      10,    0,  110,    2, 0x0a /* Public */,
      11,    2,  111,    2, 0x0a /* Public */,
      14,    0,  116,    2, 0x0a /* Public */,
      15,    1,  117,    2, 0x0a /* Public */,
      17,    1,  120,    2, 0x0a /* Public */,
      18,    0,  123,    2, 0x08 /* Private */,
      19,    0,  124,    2, 0x08 /* Private */,
      20,    0,  125,    2, 0x08 /* Private */,
      21,    0,  126,    2, 0x08 /* Private */,
      22,    0,  127,    2, 0x08 /* Private */,
      23,    0,  128,    2, 0x08 /* Private */,
      24,    0,  129,    2, 0x08 /* Private */,
      25,    0,  130,    2, 0x08 /* Private */,
      26,    0,  131,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 7,    5,    6,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
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

void UploadDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UploadDialog *_t = static_cast<UploadDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_GetOnePicture((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->SIG_UploadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< Hobby(*)>(_a[3]))); break;
        case 2: _t->on_pb_view_clicked(); break;
        case 3: _t->on_pb_beginUpload_clicked(); break;
        case 4: _t->slot_updateProcess((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 5: _t->initDev(); break;
        case 6: _t->setVideoDevice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setAudioDevice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->on_pb_page1_clicked(); break;
        case 9: _t->on_pb_page2_clicked(); break;
        case 10: _t->on_cb_cam_clicked(); break;
        case 11: _t->on_cb_desk_clicked(); break;
        case 12: _t->slot_updateRecTime(); break;
        case 13: _t->on_pb_recordBegin_clicked(); break;
        case 14: _t->on_pb_recordEnd_clicked(); break;
        case 15: _t->on_pb_rtmpUrl_clicked(); break;
        case 16: _t->on_pb_savePath_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (UploadDialog::*_t)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UploadDialog::SIG_GetOnePicture)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (UploadDialog::*_t)(QString , QString , Hobby );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UploadDialog::SIG_UploadFile)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject UploadDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UploadDialog.data,
      qt_meta_data_UploadDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *UploadDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UploadDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UploadDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int UploadDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void UploadDialog::SIG_GetOnePicture(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UploadDialog::SIG_UploadFile(QString _t1, QString _t2, Hobby _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
