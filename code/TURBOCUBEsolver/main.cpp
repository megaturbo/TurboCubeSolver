#include "turbocubesolver.h"
#include <QApplication>
<<<<<<< HEAD
#include "CubeInput.h"
=======
#include <qdebug.h>
#include <Cube.h>
#include <QList>

using namespace CubeColor;
>>>>>>> 48a3c84d87bc4b76d7f6510f87d443f9b1394ec0

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TURBOCUBEsolver w;

    qDebug() << "Debug console test";
    w.show();

<<<<<<< HEAD
=======
    color solvedCube[18][3];

    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            solvedCube[x][y] = (color)(x / 3);
        }
    }
    Cube cube(solvedCube);
    for (int col = 0; col < 6; ++col) {
        qDebug() << "test " << col << " face";
        cube.turnFace((color)col);
        cube.displayCube();
    }

    QList<int> indices = cube.locateCubie(YELLOW, RED, BLUE);

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

    return a.exec();
}
