/****************************************************************************
** Meta object code from reading C++ file 'dishlist.h'
**
** Created: Fri Jun 15 16:30:24 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dishlist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dishlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dishlist[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      27,    9,    9,    9, 0x08,
      42,   38,    9,    9, 0x08,
      59,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_dishlist[] = {
    "dishlist\0\0on_add_clicked()\0push_but()\0"
    "now\0dish_change(int)\0on_pushButton_2_clicked()\0"
};

void dishlist::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        dishlist *_t = static_cast<dishlist *>(_o);
        switch (_id) {
        case 0: _t->on_add_clicked(); break;
        case 1: _t->push_but(); break;
        case 2: _t->dish_change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_2_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData dishlist::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject dishlist::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dishlist,
      qt_meta_data_dishlist, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &dishlist::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *dishlist::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *dishlist::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dishlist))
        return static_cast<void*>(const_cast< dishlist*>(this));
    return QDialog::qt_metacast(_clname);
}

int dishlist::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
