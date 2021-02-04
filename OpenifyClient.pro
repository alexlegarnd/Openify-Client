QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

macx {
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE += -O3
    ICON = mac_icon.icns
}

win32 {
    # remove possible other optimization flags
    QMAKE_CXXFLAGS_RELEASE -= -O
    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE += -O2

    # add the desired -O3 if not present, MinGW only
    # QMAKE_CXXFLAGS_RELEASE *= -O3

    RC_ICONS = win_icon.ico
}

VERSION = 1.0.1.0

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/aboutdialog.cpp \
    src/aboutinfo.cpp \
    src/audiometadata.cpp \
    src/editeduser.cpp \
    src/file.cpp \
    src/folder.cpp \
    src/logindialog.cpp \
    src/logininformation.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/serverconnector.cpp \
    src/userinfo.cpp \
    src/usermanagerdialog.cpp

HEADERS += \
    src/aboutdialog.h \
    src/aboutinfo.h \
    src/audiometadata.h \
    src/editeduser.h \
    src/file.h \
    src/folder.h \
    src/logindialog.h \
    src/logininformation.h \
    src/mainwindow.h \
    src/serverconnector.h \
    src/userinfo.h \
    src/usermanagerdialog.h

FORMS += \
    ui/aboutdialog.ui \
    ui/logindialog.ui \
    ui/mainwindow.ui \
    ui/usermanagerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

