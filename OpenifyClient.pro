QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    audiometadata.cpp \
    editeduser.cpp \
    file.cpp \
    folder.cpp \
    logindialog.cpp \
    logininformation.cpp \
    main.cpp \
    mainwindow.cpp \
    serverconnector.cpp \
    userinfo.cpp \
    usermanagerdialog.cpp

HEADERS += \
    audiometadata.h \
    editeduser.h \
    file.h \
    folder.h \
    logindialog.h \
    logininformation.h \
    mainwindow.h \
    serverconnector.h \
    userinfo.h \
    usermanagerdialog.h

FORMS += \
    logindialog.ui \
    mainwindow.ui \
    usermanagerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

macx {
    QMAKE_INFO_PLIST += $${TARGET}/data/default.plist
    QMAKE_POST_LINK += sed -i -e "s/@VERSION@/$$VERSION/g" "./$${TARGET}.app/Contents/Info.plist";
}
