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

    CubeInput u;
    u.show();

    return a.exec();
    /*qDebug() << "Debug console test";
    w.show();

    color solvedCube[18][3];

    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            solvedCube[x][y] = (color)(x / 3);
=======
    qDebug() << "Debug console test";

>>>>>>> 9a431c6829f629646d9e49024ddfc0113077c5d4
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
    testCube->turnFace(GREEN, 1);
    testCube->turnFace(YELLOW, 1);
    testCube->turnFace(GREEN, -1);
    testCube->turnFace(ORANGE, -1);
    testCube->turnFace(YELLOW, -1);
    testCube->turnFace(ORANGE, 1);
    testCube->turnFace(RED, 1);
    testCube->turnFace(YELLOW, -1);



    testCube->displayCube();


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
=======
>>>>>>> 9a431c6829f629646d9e49024ddfc0113077c5d4
    QString s = Fridrich::solve(testCube);

    testCube->displayCube();


    // DISPLAY ISOMETRIC CUBE

    // get color matrix
    color** matrix = testCube->getMatrix();

    // put it into a 18x3 int array
    int displayableCube[18][3];

    for(int x = 0; x < 18; x++)
    {
        for(int y = 0; y < 3; y++)
        {
            displayableCube[x][y] = matrix[x][y];
        }
    }

    // create the isometric widget
    IsometricCubeWidget w(displayableCube);
    w.show();

    return a.exec();*/
}
