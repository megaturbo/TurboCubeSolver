#include "turbocubesolver.h"
#include <QApplication>
#include "CubeInput.h"
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

    /*CubeInput u;
    u.show();*/

    /*FRIDRICH TESTING*/

    qDebug() << "Fridrich testing, please do not comment or remove this section";
    color solvedMatrix[18][3];

    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            solvedMatrix[x][y] = (color)(x / 3);
        }
    }
    Cube *testCube = new Cube(solvedMatrix);



    testCube->displayCube();
    for (int col = 5; col > -1; --col) {
        testCube->turnFace((color)col, -1);
        testCube->displayCube();
    }

    testCube->displayCube();

    QString s = Fridrich::solve(testCube);

    testCube->displayCube();

    qDebug() << s;

    MainWidget mainWidget;
    mainWidget.show();

    return a.exec();
}
