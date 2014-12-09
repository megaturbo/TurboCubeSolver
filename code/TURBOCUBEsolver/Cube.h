#ifndef CUBE_H
#define CUBE_H

#include <QMap>
#include <QVector>
#include <QList>
#include <CubeColor.h>
#include <cubie.h>
#include <QMatrix>

using namespace CubeColor;
class Cube{
  public:
    Cube(color matrix[18][3]);
    //returns faces the cubie's on
    QList<int> locateCubie(color c1, color c2);
    QList<int> locateCubie(color c1, color c2, color c3);
    //returns the 2 or 3 colors of the cubie linked to the sticker at (i, j) on matCube
    QList<int> cubie(int i, int j);

    void moveSequence(QString sequence);

    //matrix rotation per face
    void U(int nbQuarterTurn);
    void D(int nbQuarterTurn);
    void B(int nbQuarterTurn);
    void F(int nbQuarterTurn);
    void R(int nbQuarterTurn);
    void L(int nbQuarterTurn);
    void turnRed(int nbQuarterTurn);
    void turnBlue(int nbQuarterTurn);
    void turnOrange(int nbQuarterTurn);
    void turnGreen(int nbQuarterTurn);
    void turnWhite(int nbQuarterTurn);
    void turnYellow(int nbQuarterTurn);

    void turnFace(color face);

    void displayCube();

    void setMatrix(color matrix[18][3]);
private:
    //utility
    bool cubieEqual(QList<int> cubi, color c1, color c2);
    bool cubieEqual(QList<int> cubi, color c1, color c2, color c3);


    color matCube[18][3];
};
#endif // CUBE_H