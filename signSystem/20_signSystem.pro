#-------------------------------------------------
#
# Project created by QtCreator 2020-02-06T16:34:14
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 20_signSystem
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    person.cpp \
    login.cpp \
    register.cpp

HEADERS  += widget.h \
    person.h \
    login.h \
    register.h

FORMS    += widget.ui \
    person.ui \
    login.ui \
    register.ui

RESOURCES += \
    resource/bg.qrc
