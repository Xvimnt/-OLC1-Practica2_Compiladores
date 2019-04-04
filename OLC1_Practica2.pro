#-------------------------------------------------
#
# Project created by QtCreator 2019-03-30T16:41:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OLC1_Practica2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        secondpractice.cpp \
    ../../../Downloads/Ejemplo/node.cpp \
    ../../../Downloads/Ejemplo/plotter.cpp

HEADERS += \
        secondpractice.h \
    ../../../Downloads/Ejemplo/lexico.l \
    ../../../Downloads/Ejemplo/node.h \
    ../../../Downloads/Ejemplo/plotter.h \
    ../../../Downloads/Ejemplo/sintactico.y

FORMS += \
        secondpractice.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    scanner.l \
    parser.y \
    ../../../Downloads/Ejemplo/generador.bat
