/****************************************************************************
** Meta object code from reading C++ file 'rygl.h'
**
** Created: Fri Jun 15 16:30:23 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../rygl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rygl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_rygl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x08,
      26,    5,    5,    5, 0x08,
      48,    5,    5,    5, 0x08,
      68,    5,    5,    5, 0x08,
      87,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_rygl[] = {
    "rygl\0\0on_pbback_clicked()\0"
    "on_pbdelete_clicked()\0on_pbsave_clicked()\0"
    "on_pbadd_clicked()\0on_pbfind_clicked()\0"
};

void rygl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        rygl *_t = static_cast<rygl *>(_o);
        switch (_id) {
        case 0: _t->on_pbback_clicked(); break;
        case 1: _t->on_pbdelete_clicked(); break;
        case 2: _t->on_pbsave_clicked(); break;
        case 3: _t->on_pbadd_clicked(); break;
        case 4: _t->on_pbfind_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData rygl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject rygl::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_rygl,
      qt_meta_data_rygl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &rygl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *rygl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *rygl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_rygl))
        return static_cast<void*>(const_cast< rygl*>(this));
    return QDialog::qt_metacast(_clname);
}

int rygl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
