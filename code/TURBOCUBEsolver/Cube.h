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
class Cube {
  public:
    Cube(color matrix[18][3]);
    Cube(const Cube &c);
    ~Cube();
    //returns faces the cubie's on
    QList<int> locateCubie(color c1, color c2);
    QList<int> locateCubie(color c1, color c2, color c3);
    //returns the 2 or 3 colors of the cubie linked to the sticker at (i, j) on matCube
    QList<int> cubie(int i, int j);

    QString scramble();
    static QString reverseSequence(QString sequence);

    QString moveSequence(QString sequence, color col1, color col2);
    QString turnFace(int face, int number = 1);

    void displayCube();

    void setMatrix(color matrix[18][3]);
    color** getMatrix() const;

public slots:

private:
    //utility
    bool cubieEqual(QList<int> cubi, color c1, color c2);
    bool cubieEqual(QList<int> cubi, color c1, color c2, color c3);

    //matrix rotation per face
    QString U(int nbQuarterTurn, color col1, color col2);
    QString D(int nbQuarterTurn, color col1, color col2);
    QString B(int nbQuarterTurn, color col1, color col2);
    QString F(int nbQuarterTurn, color col1, color col2);
    QString R(int nbQuarterTurn, color col1, color col2);
    QString L(int nbQuarterTurn, color col1, color col2);

    color matCube[18][3];
};
#endif // CUBE_H
