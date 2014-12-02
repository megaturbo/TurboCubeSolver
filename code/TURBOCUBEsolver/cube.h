#ifndef CUBE_H
#define CUBE_H

#include <QMap>
#include <QVector>
#include <QList>
#include <CubeColor.h>

using namespace CubeColor;
class Cube{
  public:
    Cube ();
    Cube(QList<QMap<color, color> > newCube);
    void setCube(QList<QMap<color, color> > newCube);
    //returns faces the cubie's on
    int* locateCubie(color c1, color c2, color c3 = UNDEFINED);
  private:
    //actually moves the faces
    void moveSequence(QString sequence);

    //matrix rotation per face
    void U(int nbQuarterTurn);
    void D(int nbQuarterTurn);
    void B(int nbQuarterTurn);
    void F(int nbQuarterTurn);
    void R(int nbQuarterTurn);
    void L(int nbQuarterTurn);

    QList<QMap<color, color> > cube;
};
#endif // CUBE_H
