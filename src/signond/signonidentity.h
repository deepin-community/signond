/*
 * This file is part of signon
 *
 * Copyright (C) 2009-2010 Nokia Corporation.
 * Copyright (C) 2012-2016 Canonical Ltd.
 *
 * Contact: Alberto Mardegan <alberto.mardegan@canonical.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#ifndef SIGNONIDENTITY_H_
#define SIGNONIDENTITY_H_

#include <QtCore>

#include "pluginproxy.h"

#include "error.h"
#include "signond-common.h"
#include "signondaemon.h"
#include "signondisposable.h"
#include "signonidentityinfo.h"
#include "credentialsaccessmanager.h"

#include "signonui_interface.h"

#include <functional>

namespace SignonDaemonNS {

class SignonIdentityAdaptor;

/*!
 * @class SignonIdentity
 * Daemon side representation of identity.
 * @todo description.
 */
class SignonIdentity: public SignonDisposable
{
    Q_OBJECT

    friend class SignonIdentityAdaptor;

    virtual ~SignonIdentity();

public:
    typedef SignonIdentityAdaptor Adaptor;

    void destroy();
    static SignonIdentity *createIdentity(quint32 id, SignonDaemon *parent);
    quint32 id() const { return m_id; }

    SignonIdentityInfo queryInfo(bool &ok, bool queryPassword = true);
    quint32 storeCredentials(const SignonIdentityInfo &info);

    typedef std::function<void(bool verified, const Error &error)> VerifyUserCb;
    typedef std::function<void(quint32 id, const Error &error)> CredentialsUpdateCb;
    typedef std::function<void(const Error &error)> RemoveCb;
    typedef std::function<void(bool signedOut, const Error &error)> SignOutCb;

public Q_SLOTS:
    void requestCredentialsUpdate(const QString &message,
                                  const CredentialsUpdateCb &callback);
    Error getInfo(SignonIdentityInfo *info);
    Error addReference(const QString &reference, const QString &appId);
    Error removeReference(const QString &reference, const QString &appId);

    void verifyUser(const QVariantMap &params, const VerifyUserCb &callback);

    Error verifySecret(const QString &secret, bool *verified);
    void remove(const RemoveCb &callback);
    void signOut(const SignOutCb &callback);
    Error store(const QVariantMap &info, const QString &appId, quint32 *id);
    void queryUiSlot(QDBusPendingCallWatcher *call,
                     const CredentialsUpdateCb &callback);
    void verifyUiSlot(QDBusPendingCallWatcher *call,
                      const VerifyUserCb &callback);

Q_SIGNALS:
    void unregistered();
    //TODO - split this into the 3 separate signals(updated, removed, signed out)
    void infoUpdated(int);
    void stored(SignonIdentity *identity);

private Q_SLOTS:
    void removeCompleted(QDBusPendingCallWatcher *call,
                         const RemoveCb &callback);
    void signOutCompleted(QDBusPendingCallWatcher *call,
                          const SignOutCb &callback);
    void onCredentialsUpdated(quint32 id);

private:
    SignonIdentity(quint32 id, int timeout, SignonDaemon *parent);
    void queryUserPassword(const QVariantMap &params,
                           const VerifyUserCb &callback);

private:
    quint32 m_id;
    SignonUiAdaptor *m_signonui;
    SignonIdentityInfo *m_pInfo;
    bool m_destroyed;
}; //class SignonDaemon

} //namespace SignonDaemonNS

#endif /* SIGNONIDENTITY_H_ */
