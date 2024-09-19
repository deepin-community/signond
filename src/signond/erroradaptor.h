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

#ifndef SIGNOND_ERROR_ADAPTOR_H
#define SIGNOND_ERROR_ADAPTOR_H

#include "error.h"

#include <QDBusMessage>

namespace SignonDaemonNS {

class ErrorAdaptor
{
public:
    explicit ErrorAdaptor(const Error &error);

    QString code() const { return m_code; }
    QString message() const { return m_message; }
    QDBusMessage createReply(const QDBusMessage &msg) const {
        return msg.createErrorReply(m_code, m_message);
    }

private:
    QString m_code;
    QString m_message;
};

} // namespace SignonDaemonNS

#endif // SIGNOND_ERROR_ADAPTOR_H
