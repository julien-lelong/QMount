#include "qmountwin.h"

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <Winnetwk.h>

namespace QMount {

QMountWin::QMountWin(QObject *parent) : QObject(parent)
{

}

ErrorCode QMountWin::addConnection(const QString &remoteName, const QString &username, const QString &password)
{
    HANDLE hToken;
    LogonUser(L"NETWORK SERVICE",
              L"NT AUTHORITY",
              NULL,
              LOGON32_LOGON_NEW_CREDENTIALS,
              LOGON32_PROVIDER_WINNT50, &hToken);

    ImpersonateLoggedOnUser(hToken);

    NETRESOURCE resource;
    // Zero out the NETRESOURCE struct
    memset(&resource, 0, sizeof (NETRESOURCE));
    resource.dwScope        = RESOURCE_GLOBALNET;
    resource.dwType         = RESOURCETYPE_DISK;
    resource.lpLocalName    = NULL;
    resource.lpRemoteName   = (LPWSTR) remoteName.utf16();
    resource.lpProvider     = NULL;

    DWORD result(WNetAddConnection2(&resource,
                                    (LPWSTR) password.utf16(),
                                    (LPWSTR) username.utf16(),
                                    CONNECT_TEMPORARY));

    if (result == NO_ERROR) {
        return ErrorCode::NO_ERR;
    } else if (result == ERROR_ALREADY_ASSIGNED) {
        return ErrorCode::ALREADY_ASSIGNED;
    } else if (result == ERROR_ACCESS_DENIED) {
        return ErrorCode::ACCESS_DENIED;
    } else if (result == ERROR_BAD_DEV_TYPE) {
        return ErrorCode::BAD_DEV_TYPE;
    } else if (result == ERROR_BAD_DEVICE) {
        return ErrorCode::BAD_DEVICE;
    } else if (result == ERROR_BAD_NET_NAME) {
        return ErrorCode::BAD_NET_NAME;
    } else if (result == ERROR_BAD_PROFILE) {
        return ErrorCode::BAD_PROFILE;
    } else if (result == ERROR_BAD_PROVIDER) {
        return ErrorCode::BAD_PROVIDER;
    } else if (result == ERROR_BAD_USERNAME) {
        return ErrorCode::BAD_USERNAME;
    } else if (result == ERROR_BUSY) {
        return ErrorCode::BUSY;
    } else if (result == ERROR_CANCELLED) {
        return ErrorCode::CANCELLED;
    } else if (result == ERROR_CANNOT_OPEN_PROFILE) {
        return ErrorCode::CANNOT_OPEN_PROFILE;
    } else if (result == ERROR_DEVICE_ALREADY_REMEMBERED) {
        return ErrorCode::DEVICE_ALREADY_REMEMBERED;
    } else if (result == ERROR_EXTENDED_ERROR) {
        return ErrorCode::EXTENDED_ERROR;
    } else if (result == ERROR_INVALID_ADDRESS) {
        return ErrorCode::INVALID_ADDRESS;
    } else if (result == ERROR_INVALID_PARAMETER) {
        return ErrorCode::INVALID_PARAMETER;
    } else if (result == ERROR_INVALID_PASSWORD) {
        return ErrorCode::INVALID_PASSWORD;
    } else if (result == ERROR_LOGON_FAILURE) {
        return ErrorCode::LOGON_FAILURE;
    } else if (result == ERROR_NO_NET_OR_BAD_PATH) {
        return ErrorCode::NO_NET_OR_BAD_PATH;
    } else if (result == ERROR_NO_NETWORK) {
        return ErrorCode::NO_NETWORK;
    }

    return ErrorCode::UNKNOWN;
}

}
