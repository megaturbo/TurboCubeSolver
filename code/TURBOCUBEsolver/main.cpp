#include "turbocubesolver.h"
#include <QApplication>
#include <qdebug.h>
#include <Cube.h>
#include <QList>
#include "IsometricCubeWidget.h"
#include <Fridrich.h>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QObject>
#include "MainWidget.h"

using namespace CubeColor;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget mainWidget;
    mainWidget.show();

    return a.exec();
}
