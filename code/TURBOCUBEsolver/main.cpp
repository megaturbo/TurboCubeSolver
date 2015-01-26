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
#include "TurboSplashScreen.h"

using namespace CubeColor;

int main(int argc, char *argv[])
{
    QString s = "B' U B' U' U B' U' B' U B U B2 U2 ";
    Cube::cleanSequence(s);

    QApplication a(argc, argv);

    int splashDisplayTime = 5000;

    MainWidget mainWidget;
    TurboSplashScreen *splashScreen = new TurboSplashScreen(splashDisplayTime);

    splashScreen->show();

    QTimer::singleShot(splashDisplayTime, splashScreen, SLOT(close()));

    //When splash screen is terminated, show the mainwidget.
    //  You can destroy the splash by clicking on it
    QObject::connect(splashScreen, SIGNAL(splashTerminated()), &mainWidget, SLOT(show()));

    return a.exec();
}
