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
    IsometricCubeWidget.cpp \
    MainWidget.cpp \
    ResolutionWidget.cpp \
    TurboSplashScreen.cpp

HEADERS  += \
    CubeColor.h \
    Cube.h \
    Fridrich.h \
    IsometricCubeWidget.h \
    MainWidget.h \
    ResolutionWidget.h \
    TurboSplashScreen.h


RC_FILE = myapp.rc

RESOURCES += \
    font_resources.qrc \
    picture_resources.qrc
