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
	CubeInput.cpp \
    Cube.cpp \
    Cubie.cpp \
    Fridrich.cpp \
    NotationDecoder.cpp \
    TurboCubeSolver.cpp

HEADERS  += \
    CubeColor.h \
    Cube.h \
    Fridrich.h \
    Cubie.h \
    NotationDecoder.h \
    TurboCubeSolver.h
	CubeInput.h

FORMS    +=\
	CubeInput.ui \
    TurboCubeSolver.ui
