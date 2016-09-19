#ifndef QMOUNTWIN_H
#define QMOUNTWIN_H

#include <QObject>

#include "qmount.h"

namespace QMount {

class QMountWin : public QObject
{
    Q_OBJECT
public:
    explicit QMountWin(QObject *parent = 0);
    static ErrorCode addConnection(const QString &remoteName, const QString &username, const QString &password);
};

}

#endif // QMOUNTWIN_H
