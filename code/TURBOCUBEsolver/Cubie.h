#ifndef CUBIE_H
#define CUBIE_H

#include <QList>
#include <QVector>
#include <CubeColor.h>

using namespace CubeColor;
class Cubie
{
public:
    Cubie(color* colors);
    bool operator==(const Cubie c) const;
    bool operator<(const Cubie c) const ;
private:
    QList<color> colors;
    int id;
};

#endif // CUBIE_H
