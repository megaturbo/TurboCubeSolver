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
    Cube ();
    Cube(QList<Cubie> newCube);
    Cube(QMap<Cubie, QList<color> > newCube);
    void setCube(QList<Cubie> newCube);
    void setCube(QMap<Cubie, QList<color> > newCube);
    //returns faces the cubie's on
    QList<color> locateCubie(Cubie c);
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

    //this one sucks, probably
    QList<Cubie> cubeZOR;
    //Cubies linked with the 2/3 faces on which they are
    QMap<Cubie, QList<color> > cube;
    //3d array for the cubies
    Cubie cube[3][3][3];
    //FUCKING MATRIX
    QMatrix matCube();
};
#endif // CUBE_H
