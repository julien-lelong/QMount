#ifndef QMOUNT_H
#define QMOUNT_H

#include <QObject>

namespace QMount {

enum ErrorCode {
    NO_ERR, ALREADY_ASSIGNED, ACCESS_DENIED, BAD_DEV_TYPE, BAD_DEVICE, BAD_NET_NAME,
    BAD_PROFILE, BAD_PROVIDER, BAD_USERNAME, BUSY, CANCELLED, CANNOT_OPEN_PROFILE,
    DEVICE_ALREADY_REMEMBERED, EXTENDED_ERROR, INVALID_ADDRESS, INVALID_PARAMETER, INVALID_PASSWORD,
    LOGON_FAILURE, NO_NET_OR_BAD_PATH, NO_NETWORK, UNKNOWN
};

QMount::ErrorCode addConnection(const QString &remoteName, const QString &username, const QString &password);

class QMount : public QObject
{
    Q_OBJECT

public:
    explicit QMount(QObject *parent = 0);
    static ErrorCode addConnection(const QString &remoteName, const QString &username, const QString &password);
};


}

#endif // QMOUNT_H
