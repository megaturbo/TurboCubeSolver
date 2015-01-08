#include "turbocubesolver.h"
#include <QApplication>
#include "CubeInput.h"
#include <qdebug.h>
#include <Cube.h>
#include <QList>
#include <IsometricCubeWidget.h>
#include <Fridrich.h>

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

    // DISPLAY ISOMETRIC CUBE

    // get color matrix

    // create the isometric widget
    Cube *solvedCube = new Cube(solvedMatrix);

    QString scrambling = solvedCube->scramble();

//    solvedCube->moveSequence("R F D' U' R L' F' L U2 R B2 F2 B' D' U R D F2 B' R'");

//    qDebug() << "SCRAMBLE: " << scrambling;
//    qDebug() << "UNSCRAMBLE: " << Cube::reverseSequence(scrambling);

    IsometricCubeWidget w(*solvedCube);

    QString solv = Fridrich::solve(solvedCube);

    w.setCube(*solvedCube);

    qDebug() << solv;

    qDebug() << "SCRAMBLE: " << scrambling;

    w.show();

    //testCube->turnFace(WHITE,1);
    //w.setCube(*testCube);

    return a.exec();
}
