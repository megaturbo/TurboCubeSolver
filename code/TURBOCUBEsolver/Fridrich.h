#ifndef FRIDRICH_H
#define FRIDRICH_H

#include <CubeColor.h>
#include <QString>
#include <cube.h>

using namespace CubeColor;
class Fridrich
{
public:
    static QString solve(Cube *cube);
    static QString fastestFridrichSolve(Cube *cube);

private:
    //Secondary steps
    static QString crossEdge(Cube *cube, int firstEdgeColor, QList<color> *solved);
    static QString F2LPair(Cube *cube, int firstCornerColor);

    //Main steps
    static QString cross(Cube *cube);
    static QString F2L(Cube *cube);
    static QString PLL(Cube *cube);
    static QString OLL(Cube *cube); //NOT IMPLEMENTED

    static QString OLL2Look(Cube *cube);
    static QString PLL2Look(Cube *cube);

    //fast methods where we try each possible solution and keep the fastest one
    static QString fastestCross(Cube *cube);
    static QStringList fastestF2L(Cube *cube);

    static void cleanSequence(QStringList &sequence);
    static void clean2Sequences(QString &sequenceLeft, QString &sequenceRight);
};

#endif // FRIDRICH_H
