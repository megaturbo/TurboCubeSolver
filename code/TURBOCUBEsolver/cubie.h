#ifndef CUBIE_H
#define CUBIE_H

#include <QList>
#include <QVector>
#include <CubeColor.h>

using namespace CubeColor;
class Cubie
{
public:
    Cubie();
    QList<color> colors;
    QList<color> faces;
    int pos[3];
};

#endif // CUBIE_H
