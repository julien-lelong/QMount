#include "qmount.h"

#ifdef Q_OS_WIN32
#include "qmountwin.h"
#endif

namespace QMount {

ErrorCode addConnection(const QString &remoteName, const QString &username, const QString &password)
{
    return QMount::QMount::addConnection(remoteName, username, password);
}

QMount::QMount(QObject *parent) : QObject(parent)
{

}

ErrorCode QMount::QMount::addConnection(const QString &remoteName, const QString &username, const QString &password)
{
#ifdef Q_OS_WIN32
    return QMountWin::addConnection(remoteName, username, password);
#endif
}

}
