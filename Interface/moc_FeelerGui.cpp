/****************************************************************************
** Meta object code from reading C++ file 'FeelerGui.h'
**
** Created: Mon Nov 24 22:23:05 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "FeelerGui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FeelerGui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FeelerGui[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   10,   10,   10, 0x08,
      43,   10,   10,   10, 0x08,
      55,   10,   10,   10, 0x08,
      74,   70,   10,   10, 0x08,
      94,   10,   10,   10, 0x08,
     108,  103,   10,   10, 0x0a,
     146,  136,   10,   10, 0x0a,
     176,  136,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FeelerGui[] = {
    "FeelerGui\0\0PrintText(QString)\0"
    "showBudies()\0CloseTalk()\0SendMessages()\0"
    "mes\0SendNotify(QString)\0Logout()\0Item\0"
    "StartTalk(QListWidgetItem*)\0from,text\0"
    "SendMessages(QString,QString)\0"
    "RecvMessage(QString,QString)\0"
};

const QMetaObject FeelerGui::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FeelerGui,
      qt_meta_data_FeelerGui, 0 }
};

const QMetaObject *FeelerGui::metaObject() const
{
    return &staticMetaObject;
}

void *FeelerGui::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FeelerGui))
        return static_cast<void*>(const_cast< FeelerGui*>(this));
    return QDialog::qt_metacast(_clname);
}

int FeelerGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: PrintText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: showBudies(); break;
        case 2: CloseTalk(); break;
        case 3: SendMessages(); break;
        case 4: SendNotify((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: Logout(); break;
        case 6: StartTalk((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: SendMessages((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: RecvMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void FeelerGui::PrintText(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
