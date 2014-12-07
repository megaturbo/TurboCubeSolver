#include "fridrich.h"
#include <QString>
#include <QStringBuilder>
#include <cubie.h>

QString Fridrich::solve(Cube *c){
    QString s;
    s = cross(c);
    s += F2L(c);
    s += OLL(c);
    s += PLL(c);
    return s;
}

//For now, it's only solving for the white face
QString Fridrich::cross(Cube *c, color color){
    Cubie wr(WHITE, RED);
    Cubie wg(WHITE, GREEN);
    Cubie wb(WHITE, BLUE);
    Cubie wo(WHITE, ORANGE);
    QList<color> wrpos = c->locateCubie(wr);
    QList<color> wgpos = c->locateCubie(wr);
    QList<color> wbpos = c->locateCubie(wr);
    QList<color> wopos = c->locateCubie(wr);
    return "";
}

//For now, it's only solving for the white face
QString Fridrich::F2L(Cube *c, color color){
    return "";
}
//as 2 layers are solved at this point,
//we don't need to set a face to solve
QString Fridrich::OLL(Cube *c){
    return "";
}

QString Fridrich::PLL(Cube *c){
    return "";
}
