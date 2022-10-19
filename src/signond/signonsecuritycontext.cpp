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

#include "signond-common.h"
#include "signonsecuritycontext.h"

#include <QDBusMetaType>
#include <QMetaType>
#include <QStringList>

namespace SignonDaemonNS {

SignonSecurityContext::SignonSecurityContext()
{
}

SignonSecurityContext::SignonSecurityContext(const QString &systemContext, const QString &applicationContext):
    m_systemContext(systemContext),
    m_applicationContext(applicationContext)
{
}

QDBusArgument &operator<<(QDBusArgument &argument, const SignonSecurityContext &securityContext)
{
    argument.beginStructure();
    argument << securityContext.systemContext() << securityContext.applicationContext();
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, SignonSecurityContext &securityContext)
{
    QString systemContext;
    QString applicationContext;

    argument.beginStructure();
    argument >> systemContext >> applicationContext;
    securityContext.setSystemContext(systemContext);
    securityContext.setApplicationContext(applicationContext);
    argument.endStructure();
    return argument;
}

void SignonSecurityContext::setSystemContext(const QString &systemContext)
{
    m_systemContext = systemContext;
}

QString SignonSecurityContext::systemContext() const
{
    return m_systemContext;
}

void SignonSecurityContext::setApplicationContext(const QString &applicationContext)
{
    m_applicationContext = applicationContext;
}

QString SignonSecurityContext::applicationContext() const
{
    return m_applicationContext;
}

} //namespace SignonDaemonNS
