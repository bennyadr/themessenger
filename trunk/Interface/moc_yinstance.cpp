/****************************************************************************
** Meta object code from reading C++ file 'yinstance.h'
**
** Created: Sun Nov 2 23:55:07 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "yinstance.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'yinstance.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_c_YInstance[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      23,   13,   12,   12, 0x05,
      50,   13,   12,   12, 0x05,
      81,   12,   12,   12, 0x05,
      95,   12,   12,   12, 0x05,
     117,  109,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_c_YInstance[] = {
    "c_YInstance\0\0buddylist\0"
    "SetBuddyList(c_BuddyList*)\0"
    "SetOnlineBuddies(c_BuddyList*)\0"
    "BuddyQuited()\0BuddyJoined()\0message\0"
    "NewMessage(string)\0"
};

const QMetaObject c_YInstance::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_c_YInstance,
      qt_meta_data_c_YInstance, 0 }
};

const QMetaObject *c_YInstance::metaObject() const
{
    return &staticMetaObject;
}

void *c_YInstance::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_c_YInstance))
	return static_cast<void*>(const_cast< c_YInstance*>(this));
    return QThread::qt_metacast(_clname);
}

int c_YInstance::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SetBuddyList((*reinterpret_cast< c_BuddyList*(*)>(_a[1]))); break;
        case 1: SetOnlineBuddies((*reinterpret_cast< c_BuddyList*(*)>(_a[1]))); break;
        case 2: BuddyQuited(); break;
        case 3: BuddyJoined(); break;
        case 4: NewMessage((*reinterpret_cast< string(*)>(_a[1]))); break;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void c_YInstance::SetBuddyList(c_BuddyList * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void c_YInstance::SetOnlineBuddies(c_BuddyList * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void c_YInstance::BuddyQuited()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void c_YInstance::BuddyJoined()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void c_YInstance::NewMessage(string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
