TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
    tst_access_control_manager_helper.pro \
    tst_timeouts.pro \
    tst_pluginproxy.pro \
    tst_database.pro \
    access-control.pro \

system($$pkgConfigExecutable() --exists libqtdbusmock-1) {
    SUBDIRS += \
        session_tool.pro \
        tst_signond.pro
    tst_signond.depends += session_tool
}

# Disabled until fixed
#SUBDIRS += tst_backup.pro
