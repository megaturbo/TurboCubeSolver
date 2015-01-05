#include "turbocubesolver.h"
#include <QApplication>
<<<<<<< HEAD
#include "CubeInput.h"
=======
#include <qdebug.h>
#include <Cube.h>
#include <QList>
#include <Fridrich.h>

using namespace CubeColor;
>>>>>>> 48a3c84d87bc4b76d7f6510f87d443f9b1394ec0

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TURBOCUBEsolver w;

    qDebug() << "Debug console test";
    w.show();

<<<<<<< HEAD
<<<<<<< HEAD
=======
    color solvedCube[18][3];

    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            solvedCube[x][y] = (color)(x / 3);
=======
    color matCube[18][3];
    for (int x = 0; x < 18; x++) {
        for (int y = 0; y < 3; y++) {
            matCube[x][y] = (color)(x / 3);
>>>>>>> e32f5c2fd61a43310da2e0b8eff80e4eda74d151
        }
    }
    Cube *testCube = new Cube(matCube);
    testCube->displayCube();
    for (int col = 5; col > -1; --col) {
        testCube->turnFace((color)col, 1);
        testCube->displayCube();
    }


<<<<<<< HEAD
    QString s = "";
    for (int i = 0; i < indices.length(); i++) {
        s += QString::number(indices.at(i));
        s += " ";
        if(i % 2 == 1){
            s += "\n";
        }
    }
    qDebug() << s;
>>>>>>> 48a3c84d87bc4b76d7f6510f87d443f9b1394ec0
=======
    QString s = Fridrich::solve(testCube);

    testCube->displayCube();
>>>>>>> e32f5c2fd61a43310da2e0b8eff80e4eda74d151

    return a.exec();
}
