#include "turbocubesolver.h"
#include <QApplication>
#include <qdebug.h>
#include <Cube.h>
#include <QList>
#include <Fridrich.h>

using namespace CubeColor;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TURBOCUBEsolver w;

    qDebug() << "Debug console test";
    w.show();

    color matCube[18][3];
    for (int x = 0; x < 18; x++) {
        for (int y = 0; y < 3; y++) {
            matCube[x][y] = (color)(x / 3);
        }
    }
    Cube *testCube = new Cube(matCube);
    testCube->displayCube();
    for (int col = 5; col > -1; --col) {
        testCube->turnFace((color)col, -1);
        testCube->displayCube();
    }


    QString s = Fridrich::solve(testCube);

    testCube->displayCube();




    return a.exec();
}
