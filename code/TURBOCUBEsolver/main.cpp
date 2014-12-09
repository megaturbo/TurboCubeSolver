#include "turbocubesolver.h"
#include <QApplication>
#include <qdebug.h>
#include <Cube.h>
#include <QList>

using namespace CubeColor;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TURBOCUBEsolver w;

    qDebug() << "Debug console test";
    w.show();

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

    QList<int> indices = cube.locateCubie(BLUE, YELLOW);

    QString s = "";
    for (int i = 0; i < indices.length(); i++) {
        s += QString::number(indices.at(i));
        s += " ";
        if(i % 2 == 1){
            s += "\n";
        }
    }
    qDebug() << s;

    return a.exec();
}
