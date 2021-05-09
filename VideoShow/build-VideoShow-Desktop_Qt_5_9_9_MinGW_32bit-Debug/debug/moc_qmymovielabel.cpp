/****************************************************************************
** Meta object code from reading C++ file 'qmymovielabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VideoShow/qmymovielabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmymovielabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QMyMovieLabel_t {
    QByteArrayData data[14];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QMyMovieLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QMyMovieLabel_t qt_meta_stringdata_QMyMovieLabel = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QMyMovieLabel"
QT_MOC_LITERAL(1, 14, 16), // "SIG_labelClicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 8), // "setMovie"
QT_MOC_LITERAL(4, 41, 7), // "QMovie*"
QT_MOC_LITERAL(5, 49, 5), // "movie"
QT_MOC_LITERAL(6, 55, 10), // "enterEvent"
QT_MOC_LITERAL(7, 66, 7), // "QEvent*"
QT_MOC_LITERAL(8, 74, 5), // "event"
QT_MOC_LITERAL(9, 80, 10), // "leaveEvent"
QT_MOC_LITERAL(10, 91, 10), // "setRtmpUrl"
QT_MOC_LITERAL(11, 102, 3), // "url"
QT_MOC_LITERAL(12, 106, 11), // "eventFilter"
QT_MOC_LITERAL(13, 118, 7) // "watched"

    },
    "QMyMovieLabel\0SIG_labelClicked\0\0"
    "setMovie\0QMovie*\0movie\0enterEvent\0"
    "QEvent*\0event\0leaveEvent\0setRtmpUrl\0"
    "url\0eventFilter\0watched"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMyMovieLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   45,    2, 0x0a /* Public */,
       6,    1,   48,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x0a /* Public */,
      10,    1,   54,    2, 0x0a /* Public */,
      12,    2,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 7,   13,    8,

       0        // eod
};

void QMyMovieLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QMyMovieLabel *_t = static_cast<QMyMovieLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_labelClicked(); break;
        case 1: _t->setMovie((*reinterpret_cast< QMovie*(*)>(_a[1]))); break;
        case 2: _t->enterEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 3: _t->leaveEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 4: _t->setRtmpUrl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMovie* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QMyMovieLabel::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMyMovieLabel::SIG_labelClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject QMyMovieLabel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QMyMovieLabel.data,
      qt_meta_data_QMyMovieLabel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QMyMovieLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMyMovieLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QMyMovieLabel.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QMyMovieLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QMyMovieLabel::SIG_labelClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
