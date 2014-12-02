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
        turbocubesolver.cpp \
    cube.cpp \
    fridrich.cpp \
    cubie.cpp

HEADERS  += turbocubesolver.h \
    cube.h \
    fridrich.h \
    CubeColor.h \
    cubie.h

FORMS    += turbocubesolver.ui
