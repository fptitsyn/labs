QT       += core gui sql axcontainer printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adddatadialog.cpp \
    connectiondialog.cpp \
    main.cpp \
    mainwindow.cpp \
    modifydialog.cpp \
    printdialog.cpp

HEADERS += \
    adddatadialog.h \
    connectiondialog.h \
    mainwindow.h \
    modifydialog.h \
    printdialog.h

FORMS += \
    adddatadialog.ui \
    connectiondialog.ui \
    mainwindow.ui \
    modifydialog.ui \
    printdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
