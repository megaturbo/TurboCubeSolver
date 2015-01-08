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

    static QString crossEdge(Cube *c, int co);
    static QString F2LPair(Cube *c, int col);
private:
    //int face is the face we begin with,
    //usually white so we set it at 0
    //by default
    static QString cross(Cube *c);
    static QString F2L(Cube *c);
    //as 2 layers are solved at this point,
    //we don't need to set a face to solve
    static QString OLL(Cube *c);
    static QString PLL(Cube *c);
};

#endif // FRIDRICH_H
