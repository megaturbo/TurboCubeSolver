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

private:
    //Secondary steps
    static QString crossEdge(Cube *cube, int firstEdgeColor);
    static QString F2LPair(Cube *cube, int firstCornerColor);
    //Main steps
    static QString cross(Cube *cube);
    static QString F2L(Cube *cube);
    static QString PLL(Cube *cube);
    static QString OLL(Cube *cube);

    static QString OLL2Look(Cube *cube);
    static QString PLL2Look(Cube *cube);
};

#endif // FRIDRICH_H
