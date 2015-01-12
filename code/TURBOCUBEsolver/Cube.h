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
    Cube(int matrix[18][3]);
    Cube(const Cube &c);
    ~Cube();
    //returns faces the cubie's on
    QList<int> locateCubie(color firstColor, color secondColor);
    QList<int> locateCubie(color firstColor, color secondColor, color thirdColor);
    //returns the 2 or 3 colors of the cubie linked to the sticker at (i, j) on matCube
    QList<int> linkedStickers(int i, int j);

    QString scramble(int depth = 25);
    static QString reverseSequence(QString sequence);

    QString moveSequence(QString sequence, color colorFront, color colorUp);
    QString turnFace(int faceToTurn, int nbQuarterTurns = 1);

    void qDebugDisplay();

    void setMatrix(color matrix[18][3]);
    void setMatrix(int matrix[18][3]);
    color** getMatrix() const;
    color** getFaceMatrix(QChar face) const;

public slots:

private:
    //utility
    bool cubieEqual(QList<int> indices, color firstColor, color secondColor);
    bool cubieEqual(QList<int> indices, color firstColor, color secondColor, color thirdColor);

    //matrix rotation per face
    QString U(int nbQuarterTurn, color colorFront, color colorUp);
    QString D(int nbQuarterTurn, color colorFront, color colorUp);
    QString B(int nbQuarterTurn, color colorFront, color colorUp);
    QString F(int nbQuarterTurn, color colorFront, color colorUp);
    QString R(int nbQuarterTurn, color colorFront, color colorUp);
    QString L(int nbQuarterTurn, color colorFront, color colorUp);

    color matCube[18][3];
};
#endif // CUBE_H
