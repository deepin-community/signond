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

#ifndef SIGNOND_ERROR_H
#define SIGNOND_ERROR_H

#include <QString>

namespace SignonDaemonNS {

class Error
{
public:
    enum Code {
        NoError = 0,
        UnknownError,
        InternalServer,
        InternalCommunication,
        PermissionDenied,
        MethodOrMechanismNotAllowed,
        EncryptionFailed,
        MethodNotKnown,
        ServiceNotAvailable,
        InvalidQuery,
        MethodNotAvailable,
        IdentityNotFound,
        StoreFailed,
        RemoveFailed,
        SignoutFailed,
        OperationCanceled,
        CredentialsNotAvailable,
        ReferenceNotFound,
        MechanismNotAvailable,
        MissingData,
        InvalidCredentials,
        NotAuthorized,
        WrongState,
        OperationNotSupported,
        NoConnection,
        NetworkError,
        SslError,
        RuntimeError,
        SessionCanceled,
        TimedOut,
        UserInteraction,
        OperationFailed,
        TOSNotAccepted,
        ForgotPassword,
        IncorrectDate,
        UserDefinedError,
    };

    Error(Code code = NoError, const QString &message = QString()):
        m_code(code),
        m_message(message)
    {
    }

    static Error none() { return Error(NoError); }

    operator bool() const { return isError(); }
    bool isError() const { return m_code != Code::NoError; }

    Code code() const { return m_code; }
    QString message() const { return m_message; }

private:
    Code m_code;
    QString m_message;
};

} // namespace SignonDaemonNS

#endif // SIGNOND_ERROR_H
