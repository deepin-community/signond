include( ../../common-project-config.pri )
include( ../../common-vars.pri )
TEMPLATE = app
TARGET = signond
QT += core \
    sql \
    xml \
    network \
    dbus

#generate adaptor for backup
DBUS_ADAPTORS += \
    ../../lib/signond/com.nokia.SingleSignOn.Backup.xml

HEADERS += \
    accesscontrolmanagerhelper.h \
    credentialsaccessmanager.h \
    credentialsdb.h \
    credentialsdb_p.h \
    default-crypto-manager.h \
    default-key-authorizer.h \
    default-secrets-storage.h \
    error.h \
    erroradapter.h \
    peercontext.h \
    signonsessioncore.h \
    signonauthsessionadaptor.h \
    signonauthsession.h \
    signonidentity.h \
    signond-common.h \
    signondaemonadaptor.h \
    signondaemon.h \
    signondisposable.h \
    signontrace.h \
    pluginproxy.h \
    signonidentityinfo.h \
    signonui_interface.h \
    signonidentityadaptor.h \
    signonsecuritycontext.h \
    signonsessioncoretools.h
SOURCES += \
    accesscontrolmanagerhelper.cpp \
    credentialsaccessmanager.cpp \
    credentialsdb.cpp \
    default-crypto-manager.cpp \
    default-key-authorizer.cpp \
    default-secrets-storage.cpp \
    erroradaptor.cpp \
    signonsessioncore.cpp \
    signonauthsessionadaptor.cpp \
    signonauthsession.cpp \
    signonidentity.cpp \
    signondaemonadaptor.cpp \
    signondisposable.cpp \
    signonui_interface.cpp \
    pluginproxy.cpp \
    main.cpp \
    signondaemon.cpp \
    signonidentityinfo.cpp \
    signonidentityadaptor.cpp \
    signonsecuritycontext.cpp \
    signonsessioncoretools.cpp
INCLUDEPATH += . \
    $${TOP_SRC_DIR}/lib/plugins \
    $${TOP_SRC_DIR}/lib/plugins/signon-plugins-common \
    $${TOP_SRC_DIR}/lib/signond \
    $${TOP_SRC_DIR}/lib/sim-dlc \
    $${TOP_SRC_DIR}/lib

CONFIG += build_all \
    link_pkgconfig

QMAKE_LIBDIR += \
    $${TOP_BUILD_DIR}/lib/plugins/signon-plugins-common \
    $${TOP_BUILD_DIR}/lib/signond/SignOn

CONFIG(enable-p2p) {
    DEFINES += ENABLE_P2P
    PKGCONFIG += dbus-1
}

CONFIG(enable-backup) {
    DEFINES += ENABLE_BACKUP
    SOURCES += \
        backup.cpp
    HEADERS += \
        backup.h
}

DEFINES += QT_NO_CAST_TO_ASCII \
    QT_NO_CAST_FROM_ASCII
DEFINES += "SIGNOND_PLUGINS_DIR=$${SIGNOND_PLUGINS_DIR_QUOTED}"
DEFINES += "SIGNOND_EXTENSIONS_DIR=$${SIGNOND_EXTENSIONS_DIR_QUOTED}"

#Trace defines can be overruled by signond's configuration file `LoggingLevel`
DEFINES += SIGNOND_TRACE
LIBS += \
    -lrt \
    -lsignon-plugins-common \
    -lsignon-extension

headers.files = $$HEADERS
include( ../../common-installs-config.pri )

OTHER_FILES += \
    signond.conf \
    setupstorage.sh

conf_file.files = $$OTHER_FILES
conf_file.path = /etc/

INSTALLS += conf_file
