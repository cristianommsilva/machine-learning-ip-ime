/****************************************************************************
** Meta object code from reading C++ file 'paramcorpus.h'
**
** Created: Sat 25. Aug 20:04:49 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../InterfaceFAMA/paramcorpus.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paramcorpus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ParamCorpus[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   13,   12,   12, 0x0a,
      45,   43,   12,   12, 0x0a,
      70,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ParamCorpus[] = {
    "ParamCorpus\0\0state\0escolherAtributos(bool)\0"
    "i\0redimensionarTabela(int)\0accept()\0"
};

void ParamCorpus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ParamCorpus *_t = static_cast<ParamCorpus *>(_o);
        switch (_id) {
        case 0: _t->escolherAtributos((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->redimensionarTabela((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->accept(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ParamCorpus::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ParamCorpus::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ParamCorpus,
      qt_meta_data_ParamCorpus, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParamCorpus::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParamCorpus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParamCorpus::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParamCorpus))
        return static_cast<void*>(const_cast< ParamCorpus*>(this));
    return QDialog::qt_metacast(_clname);
}

int ParamCorpus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE