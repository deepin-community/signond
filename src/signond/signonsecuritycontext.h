/*
 * This file is part of signon
 *
 * Copyright (C) 2018 elementary, Inc
 *
 * Contact: Corentin Noël <corentin@elementary.io>
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

#ifndef SIGNONSECURITYCONTEXT_H
#define SIGNONSECURITYCONTEXT_H

#include <QDBusMetaType>
#include <QStringList>
#include <QVariantMap>

#include "signond/signoncommon.h"

namespace SignonDaemonNS {

/*!
 * @struct SignonSecurityContext
 * Daemon side representation of security context information.
 */
struct SignonSecurityContext
{
public:
    SignonSecurityContext();
    SignonSecurityContext(const QString &systemContext, const QString &applicationContext);

    void setSystemContext(const QString &systemContext);
    QString systemContext() const;

    void setApplicationContext(const QString &applicationContext);
    QString applicationContext() const;

private:
    QString m_systemContext;
    QString m_applicationContext;
};

typedef QList<SignonSecurityContext> SignonSecurityContextList;

QDBusArgument &operator<<(QDBusArgument &argument, const SignonSecurityContext &securityContext);
const QDBusArgument &operator>>(const QDBusArgument &argument, SignonSecurityContext &securityContext);

} //namespace SignonDaemonNS

Q_DECLARE_METATYPE(SignonDaemonNS::SignonSecurityContext)

#endif // SIGNONSECURITYCONTEXT_H
