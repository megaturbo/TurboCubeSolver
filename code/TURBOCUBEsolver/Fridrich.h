#ifndef FRIDRICH_H
#define FRIDRICH_H

#include <CubeColor.h>
#include <QString>
#include <cube.h>

using namespace CubeColor;
class Fridrich
{
public:
    QString solve(Cube *c);

private:
    //int face is the face we begin with,
    //usually white so we set it at 0
    //by default
    QString cross(Cube *c);
    QString F2L(Cube *c);
    //as 2 layers are solved at this point,
    //we don't need to set a face to solve
    QString OLL(Cube *c);
    QString PLL(Cube *c);
};

#endif // FRIDRICH_H
