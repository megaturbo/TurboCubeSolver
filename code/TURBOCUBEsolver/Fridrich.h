#ifndef FRIDRICH_H
#define FRIDRICH_H

#include <CubeColor.h>
#include <QString>
#include <cube.h>

using namespace CubeColor;
class Fridrich
{
public:
    static QString solve(Cube *c);

private:
    //Secondary steps
    static QString crossEdge(Cube *c, int co);
    static QString F2LPair(Cube *c, int col);
    //Main steps
    static QString cross(Cube *c);
    static QString F2L(Cube *c);
    static QString OLL(Cube *c);
    static QString PLL(Cube *c);
};

#endif // FRIDRICH_H
