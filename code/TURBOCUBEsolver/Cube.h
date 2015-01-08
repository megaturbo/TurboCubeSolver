#ifndef CUBE_H
#define CUBE_H

#include <QMap>
#include <QVector>
#include <Cube.h>
#include <QList>
#include <CubeColor.h>
#include <cubie.h>
#include <QMatrix>

using namespace CubeColor;
class Cube{
  public:
    Cube(color matrix[18][3]);
    Cube(const Cube &c);
    //returns faces the cubie's on
    QList<int> locateCubie(color c1, color c2);
    QList<int> locateCubie(color c1, color c2, color c3);
    //returns the 2 or 3 colors of the cubie linked to the sticker at (i, j) on matCube
    QList<int> cubie(int i, int j);

    void moveSequence(QString sequence);
    QString scramble();
    static QString reverseSequence(QString sequence);

    //matrix rotation per face
    void U(int nbQuarterTurn);
    void D(int nbQuarterTurn);
    void B(int nbQuarterTurn);
    void F(int nbQuarterTurn);
    void R(int nbQuarterTurn);
    void L(int nbQuarterTurn);

    QString turnFace(int face, int number = 1);

    void displayCube();

    color colorAt(int i, int j);
    void setMatrix(color matrix[18][3]);
    color** getMatrix() const;
private:
    //utility
    bool cubieEqual(QList<int> cubi, color c1, color c2);
    bool cubieEqual(QList<int> cubi, color c1, color c2, color c3);


    color matCube[18][3];
};
#endif // CUBE_H
