/****************************************************************************
** Meta object code from reading C++ file 'ClientWorker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../client/ClientWorker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientWorker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ClientWorker_t {
    QByteArrayData data[33];
    char stringdata[512];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientWorker_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientWorker_t qt_meta_stringdata_ClientWorker = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 13),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 10),
QT_MOC_LITERAL(4, 39, 17),
QT_MOC_LITERAL(5, 57, 16),
QT_MOC_LITERAL(6, 74, 18),
QT_MOC_LITERAL(7, 93, 13),
QT_MOC_LITERAL(8, 107, 11),
QT_MOC_LITERAL(9, 119, 22),
QT_MOC_LITERAL(10, 142, 11),
QT_MOC_LITERAL(11, 154, 9),
QT_MOC_LITERAL(12, 164, 8),
QT_MOC_LITERAL(13, 173, 8),
QT_MOC_LITERAL(14, 182, 11),
QT_MOC_LITERAL(15, 194, 9),
QT_MOC_LITERAL(16, 204, 15),
QT_MOC_LITERAL(17, 220, 15),
QT_MOC_LITERAL(18, 236, 15),
QT_MOC_LITERAL(19, 252, 19),
QT_MOC_LITERAL(20, 272, 14),
QT_MOC_LITERAL(21, 287, 13),
QT_MOC_LITERAL(22, 301, 28),
QT_MOC_LITERAL(23, 330, 16),
QT_MOC_LITERAL(24, 347, 19),
QT_MOC_LITERAL(25, 367, 23),
QT_MOC_LITERAL(26, 391, 17),
QT_MOC_LITERAL(27, 409, 16),
QT_MOC_LITERAL(28, 426, 8),
QT_MOC_LITERAL(29, 435, 10),
QT_MOC_LITERAL(30, 446, 28),
QT_MOC_LITERAL(31, 475, 22),
QT_MOC_LITERAL(32, 498, 13)
    },
    "ClientWorker\0commandFailed\0\0eErrorCode\0"
    "connectedToServer\0connectionFailed\0"
    "friendStatusUpdate\0friendRequest\0"
    "callRequest\0std::list<std::string>\0"
    "callDropped\0addInCall\0leftCall\0sendText\0"
    "enterInCall\0leaveCall\0onReadSomething\0"
    "onSignInRequest\0onSignUpRequest\0"
    "onConnectionSuccess\0onDisconnected\0"
    "onSocketError\0QAbstractSocket::SocketError\0"
    "addFriendRequest\0deleteFriendRequest\0"
    "friendValidationRequest\0answerCallRequest\0"
    "addToCallRequest\0onHangUp\0onSendText\0"
    "onClientDisconnectedFromCall\0"
    "onClientKickedFromCall\0logoutRequest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  154,    2, 0x06 /* Public */,
       4,    0,  157,    2, 0x06 /* Public */,
       5,    0,  158,    2, 0x06 /* Public */,
       6,    0,  159,    2, 0x06 /* Public */,
       7,    1,  160,    2, 0x06 /* Public */,
       8,    2,  163,    2, 0x06 /* Public */,
      10,    1,  168,    2, 0x06 /* Public */,
      11,    1,  171,    2, 0x06 /* Public */,
      12,    1,  174,    2, 0x06 /* Public */,
      13,    2,  177,    2, 0x06 /* Public */,
      14,    0,  182,    2, 0x06 /* Public */,
      15,    0,  183,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,  184,    2, 0x0a /* Public */,
      17,    0,  185,    2, 0x0a /* Public */,
      18,    0,  186,    2, 0x0a /* Public */,
      19,    0,  187,    2, 0x0a /* Public */,
      20,    0,  188,    2, 0x0a /* Public */,
      21,    1,  189,    2, 0x0a /* Public */,
      23,    1,  192,    2, 0x0a /* Public */,
      24,    1,  195,    2, 0x0a /* Public */,
      25,    2,  198,    2, 0x0a /* Public */,
      26,    2,  203,    2, 0x0a /* Public */,
      27,    1,  208,    2, 0x0a /* Public */,
      28,    0,  211,    2, 0x0a /* Public */,
      29,    1,  212,    2, 0x0a /* Public */,
      30,    0,  215,    2, 0x0a /* Public */,
      31,    0,  216,    2, 0x0a /* Public */,
      32,    0,  217,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 9,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ClientWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientWorker *_t = static_cast<ClientWorker *>(_o);
        switch (_id) {
        case 0: _t->commandFailed((*reinterpret_cast< eErrorCode(*)>(_a[1]))); break;
        case 1: _t->connectedToServer(); break;
        case 2: _t->connectionFailed(); break;
        case 3: _t->friendStatusUpdate(); break;
        case 4: _t->friendRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->callRequest((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< std::list<std::string>(*)>(_a[2]))); break;
        case 6: _t->callDropped((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->addInCall((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->leftCall((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->sendText((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->enterInCall(); break;
        case 11: _t->leaveCall(); break;
        case 12: _t->onReadSomething(); break;
        case 13: _t->onSignInRequest(); break;
        case 14: _t->onSignUpRequest(); break;
        case 15: _t->onConnectionSuccess(); break;
        case 16: _t->onDisconnected(); break;
        case 17: _t->onSocketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 18: _t->addFriendRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: _t->deleteFriendRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->friendValidationRequest((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 21: _t->answerCallRequest((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 22: _t->addToCallRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: _t->onHangUp(); break;
        case 24: _t->onSendText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 25: _t->onClientDisconnectedFromCall(); break;
        case 26: _t->onClientKickedFromCall(); break;
        case 27: _t->logoutRequest(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ClientWorker::*_t)(eErrorCode );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientWorker::commandFailed)) {
                *result = 0;
            }
        }
        {
            typedef void (ClientWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientWorker::connectedToServer)) {
                *result = 1;
            }
        }
        {
            typedef void (ClientWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientWorker::connectionFailed)) {
                *result = 2;
            }
        }
        {
            typedef void (ClientWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientWorker::friendStatusUpdate)) {
                *result = 3;
            }
        }
        {
            typedef void (ClientWorker::*_t)(QString const & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientWorker::friendRequest)) {
                *result = 4;
            }
        }
        {
            typedef void (ClientWorker::*_t)(QString const & , std::list<std::string> const & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientWorker::callRequest)) {
                *result = 5;
            }
        }
        {
            typedef void (ClientWorker::*_t)(QString const & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientWorker::callDropped)) {
                *result = 6;
            }
        }
        {
            typedef void (ClientWorker::*_t)(QString const & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientWorker::addInCall)) {
                *result = 7;
            }
        }
        {
            typedef void (ClientWorker::*_t)(QString const & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientWorker::leftCall)) {
                *result = 8;
            }
        }
        {
            typedef void (ClientWorker::*_t)(QString const & , QString const & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientWorker::sendText)) {
                *result = 9;
            }
        }
        {
            typedef void (ClientWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientWorker::enterInCall)) {
                *result = 10;
            }
        }
        {
            typedef void (ClientWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientWorker::leaveCall)) {
                *result = 11;
            }
        }
    }
}

const QMetaObject ClientWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClientWorker.data,
      qt_meta_data_ClientWorker,  qt_static_metacall, 0, 0}
};


const QMetaObject *ClientWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClientWorker.stringdata))
        return static_cast<void*>(const_cast< ClientWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int ClientWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void ClientWorker::commandFailed(eErrorCode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientWorker::connectedToServer()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ClientWorker::connectionFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ClientWorker::friendStatusUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ClientWorker::friendRequest(QString const & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ClientWorker::callRequest(QString const & _t1, std::list<std::string> const & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ClientWorker::callDropped(QString const & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ClientWorker::addInCall(QString const & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ClientWorker::leftCall(QString const & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ClientWorker::sendText(QString const & _t1, QString const & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ClientWorker::enterInCall()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void ClientWorker::leaveCall()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}
QT_END_MOC_NAMESPACE
