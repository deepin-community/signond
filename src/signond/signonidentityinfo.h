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
#ifndef SIGNONIDENTITYINFO_H
#define SIGNONIDENTITYINFO_H

#include <QStringList>
#include <QVariantMap>

#include "signond/signoncommon.h"
#include "signonsecuritycontext.h"

namespace SignonDaemonNS {

typedef QString MethodName;
typedef QStringList MechanismsList;
typedef QMap<MethodName, MechanismsList> MethodMap;
typedef QList<SignonSecurityContext> SignonSecurityContextList;

/*!
 * @struct SignonIdentityInfo
 * Daemon side representation of identity information.
 * @todo description.
 */
struct SignonIdentityInfo: protected QVariantMap
{
    SignonIdentityInfo();
    SignonIdentityInfo(const QVariantMap &info);

    const QVariantMap toMap() const;

    void update(const SignonIdentityInfo &info);

    void setNew() { setId(SIGNOND_NEW_IDENTITY); }
    bool isNew() const { return id() == SIGNOND_NEW_IDENTITY; }
    void setId(quint32 id) { insert(SIGNOND_IDENTITY_INFO_ID, id); }
    quint32 id() const { return value(SIGNOND_IDENTITY_INFO_ID, 0).toUInt(); }

    void setUserName(const QString &userName) {
        insert(SIGNOND_IDENTITY_INFO_USERNAME, userName);
    }

    QString userName() const {
        return value(SIGNOND_IDENTITY_INFO_USERNAME).toString();
    }

    void setUserNameSecret(bool secret) {
        insert(SIGNOND_IDENTITY_INFO_USERNAME_IS_SECRET, secret);
    }

    bool isUserNameSecret() const {
        return value(SIGNOND_IDENTITY_INFO_USERNAME_IS_SECRET).toBool();
    }

    void setPassword(const QString &password) {
        insert(SIGNOND_IDENTITY_INFO_SECRET, password);
    }

    QString password() const {
        return value(SIGNOND_IDENTITY_INFO_SECRET).toString();
    }

    void removeSecrets() {
        remove(SIGNOND_IDENTITY_INFO_SECRET);
        if (isUserNameSecret())
            remove(SIGNOND_IDENTITY_INFO_USERNAME);
    }

    bool hasSecrets() const {
        return contains(SIGNOND_IDENTITY_INFO_SECRET) ||
            (isUserNameSecret() && contains(SIGNOND_IDENTITY_INFO_USERNAME));
    }

    void setStorePassword(bool storePassword) {
        insert(SIGNOND_IDENTITY_INFO_STORESECRET, storePassword);
    }

    bool storePassword() const {
        return value(SIGNOND_IDENTITY_INFO_STORESECRET).toBool();
    }

    void setCaption(const QString &caption) {
        insert(SIGNOND_IDENTITY_INFO_CAPTION, caption);
    }

    QString caption() const {
        return value(SIGNOND_IDENTITY_INFO_CAPTION).toString();
    }

    void setRealms(const QStringList &realms) {
        insert(SIGNOND_IDENTITY_INFO_REALMS, realms);
    }

    QStringList realms() const {
        return value(SIGNOND_IDENTITY_INFO_REALMS).toStringList();
    }

    void setMethods(const MethodMap &methods) {
        insert(SIGNOND_IDENTITY_INFO_AUTHMETHODS, QVariant::fromValue(methods));
    }

    MethodMap methods() const {
        return value(SIGNOND_IDENTITY_INFO_AUTHMETHODS).value<MethodMap>();
    }

    void setAccessControlList(const SignonSecurityContextList &accessControlList) {
        insert(SIGNOND_IDENTITY_INFO_ACL, QVariant::fromValue(accessControlList));
    }

    void setAccessControlList(const QStringList &accessControlList) {
        SignonSecurityContextList list;
        for (const QString &sysCtx: accessControlList) {
            SignonSecurityContext securityContext = SignonSecurityContext(sysCtx, QLatin1String("*"));
            list.append(securityContext);
        }

        insert(SIGNOND_IDENTITY_INFO_ACL, QVariant::fromValue(list));
    }

    QStringList accessControlList() const {
        SignonSecurityContextList accessControlList = value(SIGNOND_IDENTITY_INFO_ACL).value<SignonSecurityContextList>();
        QStringList list;
        for (const SignonSecurityContext &securityContext: accessControlList) {
            list.append(securityContext.systemContext());
        }

        return list;
    }

    void setValidated(bool validated) {
        insert(SIGNOND_IDENTITY_INFO_VALIDATED, validated);
    }

    bool validated() const {
        return value(SIGNOND_IDENTITY_INFO_VALIDATED).toBool();
    }

    void setType(quint32 type) {
        insert(SIGNOND_IDENTITY_INFO_TYPE, type);
    }

    quint32 type() const {
        return value(SIGNOND_IDENTITY_INFO_TYPE).toUInt();
    }

    void setOwnerList(const QStringList &owners) {
        insert(SIGNOND_IDENTITY_INFO_OWNER, owners);
    }

    QStringList ownerList() const {
        return value(SIGNOND_IDENTITY_INFO_OWNER).toStringList();
    }

    void setRefCount(int refCount) {
        insert(SIGNOND_IDENTITY_INFO_REFCOUNT, refCount);
    }

    int refCount() const {
        return value(SIGNOND_IDENTITY_INFO_REFCOUNT).toInt();
    }

    bool checkMethodAndMechanism(const QString &method,
                                 const QString &mechanism,
                                 QString &allowedMechanism);
}; //struct SignonIdentityInfo

} //namespace SignonDaemonNS

Q_DECLARE_METATYPE(SignonDaemonNS::MethodMap)
Q_DECLARE_METATYPE(SignonDaemonNS::SignonSecurityContextList)

#endif // SIGNONIDENTITYINFO_H
