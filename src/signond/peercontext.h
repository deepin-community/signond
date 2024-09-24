/* -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of signon
 *
 * Copyright (C) 2020 UBports Foundation
 *
 * Contact: Alberto Mardegan <mardy@users.sourceforge.net>
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

#ifndef SIGNOND_PEER_CONTEXT_H
#define SIGNOND_PEER_CONTEXT_H

#include <QDBusConnection>
#include <QDBusContext>
#include <QDBusMessage>

namespace SignonDaemonNS {

class AccessControlManagerHelper;

class PeerContext
{
public:
    PeerContext(const QDBusConnection &connection,
                const QDBusMessage &message):
        m_connection(connection),
        m_message(message)
    {
    }

    PeerContext(const QDBusContext &context):
        m_connection(context.connection()),
        m_message(context.message())
    {
    }

protected:
    /* Keeping the members protected ensures that we don't accidentally use
     * them to deliver replies.
     */
    const QDBusConnection &connection() const { return m_connection; }
    const QDBusMessage &message() const { return m_message; }

private:
    friend AccessControlManagerHelper;
    QDBusConnection m_connection;
    QDBusMessage m_message;
};

} // namespace SignonDaemonNS

#endif // SIGNOND_PEER_CONTEXT_H
