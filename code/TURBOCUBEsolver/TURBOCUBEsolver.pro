#-------------------------------------------------
#
# Project created by QtCreator 2014-11-24T17:20:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TURBOCUBEsolver
TEMPLATE = app


SOURCES += main.cpp\
    Cube.cpp \
    Fridrich.cpp \
    TurboCubeSolver.cpp \
    IsometricCubeWidget.cpp \
    MainWidget.cpp \
    CubeInputWidget.cpp

HEADERS  += \
    CubeColor.h \
    Cube.h \
    Fridrich.h \
    TurboCubeSolver.h \
    IsometricCubeWidget.h \
    MainWidget.h \
    CubeInputWidget.h

FORMS    +=\
    TurboCubeSolver.ui

RESOURCES += \
    resources.qrc
