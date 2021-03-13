#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T11:40:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = contnet
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    dockInt.cpp \
    manager.cpp \
    managed.cpp \
    qcontainerwidget.cpp \
    dialognewcont.cpp \
    qcontainerwidgetexam.cpp \
    qcontconnectednetwidget.cpp \
    qnetworkwidget.cpp \
    dialognewnet.cpp \
    dialogaddnet.cpp

HEADERS  += mainwindow.h \
    dockInt.h \
    managed.h \
    manager.h \
    qcontainerwidget.h \
    dialognewcont.h \
    qcontainerwidgetexam.h \
    qcontconnectednetwidget.h \
    qnetworkwidget.h \
    dialognewnet.h \
    dialogaddnet.h

FORMS    += mainwindow.ui \
    qcontainerwidget.ui \
    dialognewcont.ui \
    qcontainerwidgetexam.ui \
    qcontconnectednetwidget.ui \
    qnetworkwidget.ui \
    dialognewnet.ui \
    dialogaddnet.ui

DISTFILES +=

RESOURCES += resources.qrc
