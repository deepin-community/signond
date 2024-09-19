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

#include "erroradaptor.h"

#include "signond-common.h"

using namespace SignonDaemonNS;

#define DECLARE_ERROR(s) \
    { SIGNOND_##s##_ERR_NAME, SIGNOND_##s##_ERR_STR }

static struct ErrorStrings {
    QString code;
    QString defaultMessage;
} s_errorStrings[] = {
    // These must be kept in sync with the Error::Code from the header file
    { QStringLiteral(), QStringLiteral() },
    DECLARE_ERROR(UNKNOWN),
    DECLARE_ERROR(INTERNAL_SERVER),
    DECLARE_ERROR(INTERNAL_COMMUNICATION),
    DECLARE_ERROR(PERMISSION_DENIED),
    DECLARE_ERROR(METHOD_OR_MECHANISM_NOT_ALLOWED),
    DECLARE_ERROR(ENCRYPTION_FAILED),
    DECLARE_ERROR(METHOD_NOT_KNOWN),
    DECLARE_ERROR(SERVICE_NOT_AVAILABLE),
    DECLARE_ERROR(INVALID_QUERY),
    DECLARE_ERROR(METHOD_NOT_AVAILABLE),
    DECLARE_ERROR(IDENTITY_NOT_FOUND),
    DECLARE_ERROR(STORE_FAILED),
    DECLARE_ERROR(REMOVE_FAILED),
    DECLARE_ERROR(SIGNOUT_FAILED),
    DECLARE_ERROR(IDENTITY_OPERATION_CANCELED),
    DECLARE_ERROR(CREDENTIALS_NOT_AVAILABLE),
    DECLARE_ERROR(REFERENCE_NOT_FOUND),
    DECLARE_ERROR(MECHANISM_NOT_AVAILABLE),
    DECLARE_ERROR(MISSING_DATA),
    DECLARE_ERROR(INVALID_CREDENTIALS),
    DECLARE_ERROR(NOT_AUTHORIZED),
    DECLARE_ERROR(WRONG_STATE),
    DECLARE_ERROR(OPERATION_NOT_SUPPORTED),
    DECLARE_ERROR(NO_CONNECTION),
    DECLARE_ERROR(NETWORK),
    DECLARE_ERROR(SSL),
    DECLARE_ERROR(RUNTIME),
    DECLARE_ERROR(SESSION_CANCELED),
    DECLARE_ERROR(TIMED_OUT),
    DECLARE_ERROR(USER_INTERACTION),
    DECLARE_ERROR(OPERATION_FAILED),
    DECLARE_ERROR(TOS_NOT_ACCEPTED),
    DECLARE_ERROR(FORGOT_PASSWORD),
    DECLARE_ERROR(INCORRECT_DATE),
    { SIGNOND_USER_ERROR_ERR_NAME, QString() }, // plugin-defined errors
};

ErrorAdaptor::ErrorAdaptor(const Error &error)
{
    static constexpr size_t numErrors = sizeof(s_errorStrings) / sizeof(ErrorStrings);

    Error::Code errorCode = error.code();
    QString errorMessage = error.message();

    if (errorCode > Error::NoError && errorCode < numErrors) {
        m_code = s_errorStrings[errorCode].code;
        m_message = errorMessage.isEmpty() ?
            s_errorStrings[errorCode].defaultMessage : errorMessage;
    } else {
        BLAME() << "Unhandled error code:" << errorCode;
    }
}
