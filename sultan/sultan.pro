QT       += core gui widgets sql websockets

contains(CONFIG, SINGLEBIN) {
    QT += concurrent printsupport
}

TARGET = Sultan
TEMPLATE = app

CONFIG += c++11

contains(CONFIG, SINGLEBIN) {
    include(../libglobal/libglobal_src.pri)
    include(../libprint/libprint_src.pri)
    include(../libdb/libdb_src.pri)
    include(../libserver/libserver_src.pri)
    include(../libgui/libgui_src.pri)
} else {
    include(../libglobal/libglobal.pri)
    include(../libprint/libprint.pri)
    include(../libdb/libdb.pri)
    include(../libserver/libserver.pri)
    include(../libgui/libgui.pri)
}

macx {
    QMAKE_LIBDIR += $$OUT_PWD/../bin/Sultan.app/Contents/Frameworks
    LIBS += -framework Foundation
    contains(CONFIG, SINGLEBIN) {
        LIBS += -lcups
    }
    DESTDIR = ../bin
    copymigration_sqlite.commands = $$quote(cp -R $${PWD}/../migration_sqlite $$OUT_PWD/../bin/Sultan.app/Contents/Resources)
    copymigration_mysql.commands = $$quote(cp -R $${PWD}/../migration_mysql $$OUT_PWD/../bin/Sultan.app/Contents/Resources)
    copytr.commands = $$quote(cp -R $${PWD}/translation/*.qm $${OUT_PWD}/../bin/)
} else:win32 {
    LIBS += -L$$OUT_PWD/../bin
    contains(CONFIG, SINGLEBIN) {
        LIBS += -lKernel32 -lwinspool
    }
    RC_FILE = sultan.rc
    DESTDIR = ../bin/
    PWD_WIN = $${PWD}
    DESTDIR_WIN = $$OUT_PWD/../bin/
    PWD_WIN ~= s,/,\\,g
    DESTDIR_WIN ~= s,/,\\,g
    copymigration_sqlite.commands = $$quote(cmd /c xcopy /S /I /Y $${PWD_WIN}\..\migration_sqlite $${DESTDIR_WIN}\migration_sqlite)
    copymigration_mysql.commands = $$quote(cmd /c xcopy /S /I /Y $${PWD_WIN}\..\migration_mysql $${DESTDIR_WIN}\migration_mysql)
    copytr.commands = $$quote(cmd /c xcopy /S /I /Y $${PWD_WIN}\..\translation\*.qm $${DESTDIR_WIN})
} else {
    QMAKE_LIBDIR = $$OUT_PWD/../bin $$QMAKE_LIBDIR
    LIBS += -L$$OUT_PWD/../bin
    contains(CONFIG, SINGLEBIN) {
        LIBS += -lcups
    }
    DESTDIR = ../bin
    copymigration_sqlite.commands = $$quote(cp -R $${PWD}/../migration_sqlite $${OUT_PWD}/../bin/)
    copymigration_mysql.commands = $$quote(cp -R $${PWD}/../migration_mysql $${OUT_PWD}/../bin/)
    copysh.commands = $$quote(cp -R $${PWD}/../script/Sultan.sh $${OUT_PWD}/../bin/)
    copytr.commands = $(COPY) $${PWD}/../translation/*.qm $${OUT_PWD}/../bin/
    QMAKE_EXTRA_TARGETS += copysh
    POST_TARGETDEPS += copysh
}


QMAKE_EXTRA_TARGETS += copymigration_sqlite copymigration_mysql copytr
POST_TARGETDEPS += copymigration_sqlite copymigration_mysql copytr

RESOURCES += sultan.qrc

TRANSLATIONS = ../translation/sultan_id.ts

SOURCES += main.cpp \
    core.cpp \
    gui/splash.cpp \
    gui/settingdialog.cpp \
    socket/socketmanager.cpp \
    socket/socketclient.cpp \
    socket/sockethandler.cpp \
    gui/logindialog.cpp \
    gui/restartconfirmationdialog.cpp \
    gui/datesettingdialog.cpp

HEADERS  += \
    core.h \
    gui/splash.h \
    gui/settingdialog.h \
    socket/socketmanager.h \
    socket/socketclient.h \
    socket/sockethandler.h \
    gui/logindialog.h \
    gui/restartconfirmationdialog.h \
    gui/datesettingdialog.h

FORMS += \
    gui/splash.ui \
    gui/settingdialog.ui \
    gui/logindialog.ui \
    gui/restartconfirmationdialog.ui \
    gui/datesettingdialog.ui
