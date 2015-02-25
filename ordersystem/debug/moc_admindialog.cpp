/****************************************************************************
** Meta object code from reading C++ file 'admindialog.h'
**
** Created: Fri Jun 15 16:30:21 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../admindialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'admindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_adminDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      32,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_adminDialog[] = {
    "adminDialog\0\0on_pbcp_released()\0"
    "on_pbry_released()\0"
};

void adminDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        adminDialog *_t = static_cast<adminDialog *>(_o);
        switch (_id) {
        case 0: _t->on_pbcp_released(); break;
        case 1: _t->on_pbry_released(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData adminDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject adminDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_adminDialog,
      qt_meta_data_adminDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &adminDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *adminDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *adminDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_adminDialog))
        return static_cast<void*>(const_cast< adminDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int adminDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
