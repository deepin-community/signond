include( ../../common-project-config.pri )
include( ../../common-vars.pri )
TEMPLATE = lib

TARGET = signon-qt5

# Input
public_headers += \
    sessiondata.h \
    identityinfo.h \
    authservice.h \
    identity.h \
    authsession.h \
    libsignoncommon.h \
    securitycontext.h \
    signon.h \
    signonerror.h

private_headers = authserviceimpl.h \
    async-dbus-proxy.h \
    authsessionimpl.h \
    connection-manager.h \
    dbusinterface.h \
    debug.h \
    identityimpl.h \
    identityinfoimpl.h \
    securitycontextpriv.h

HEADERS = $$public_headers \
    $$private_headers

INCLUDEPATH += . \
    .. \
    $$TOP_SRC_DIR/include

SOURCES += identityinfo.cpp \
    async-dbus-proxy.cpp \
    authservice.cpp \
    authserviceimpl.cpp \
    authsession.cpp \
    authsessionimpl.cpp \
    connection-manager.cpp \
    dbusinterface.cpp \
    debug.cpp \
    identity.cpp \
    identityimpl.cpp \
    identityinfoimpl.cpp \
    securitycontext.cpp

QT += core \
    dbus

CONFIG += \
    build_all \
    link_pkgconfig
    
DEFINES += \
    QT_NO_CAST_TO_ASCII \
    QT_NO_CAST_FROM_ASCII

include( $$TOP_SRC_DIR/common-installs-config.pri )

headers.files = $$public_headers \
    AuthService \
    AuthSession \
    Error \
    Identity \
    IdentityInfo \
    SecurityContext \
    SessionData
headers.path = $${INSTALL_PREFIX}/include/$${TARGET}/SignOn
INSTALLS += headers

pkgconfig.files = lib$${TARGET}.pc
include($${TOP_SRC_DIR}/common-pkgconfig.pri)
INSTALLS += pkgconfig

QMAKE_SUBSTITUTES += $${CMAKE_BASENAME}Config.cmake.in \
    $${CMAKE_BASENAME}ConfigVersion.cmake.in
cmake_modules.files = $${CMAKE_BASENAME}Config.cmake \
    $${CMAKE_BASENAME}ConfigVersion.cmake
cmake_modules.path = $${CMAKE_CONFIG_PATH}

INSTALLS += cmake_modules
