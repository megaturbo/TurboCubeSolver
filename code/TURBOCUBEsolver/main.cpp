#include "turbocubesolver.h"
#include <QApplication>
#include "CubeInput.h"
#include <qdebug.h>
#include <Cube.h>
#include <QList>
#include <Fridrich.h>

using namespace CubeColor;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TURBOCUBEsolver w;

    CubeInput u;
    u.show();

    return a.exec();
    /*qDebug() << "Debug console test";
    w.show();

    color solvedCube[18][3];

    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            solvedCube[x][y] = (color)(x / 3);
    color matCube[18][3];
    for (int x = 0; x < 18; x++) {
        for (int y = 0; y < 3; y++) {
            matCube[x][y] = (color)(x / 3);
        }
    }
    Cube *testCube = new Cube(matCube);
    testCube->displayCube();
//    for (int col = 5; col > -1; --col) {
//        testCube->turnFace((color)col, -1);
//        testCube->displayCube();
//    }
    testCube->turnFace(BLUE, 1);
    testCube->turnFace(YELLOW, 1);
    testCube->displayCube();


    QString s = "";
    for (int i = 0; i < indices.length(); i++) {
        s += QString::number(indices.at(i));
        s += " ";
        if(i % 2 == 1){
            s += "\n";
        }
    }
    qDebug() << s;
    QString s = Fridrich::solve(testCube);

    testCube->displayCube();




    return a.exec();*/
}
