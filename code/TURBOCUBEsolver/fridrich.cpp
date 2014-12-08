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
QString Fridrich::cross(Cube *c, color col){
    QList<int> wrpos = c->locateCubie(WHITE, RED);
    QList<int> wbpos = c->locateCubie(WHITE, BLUE);
    QList<int> wopos = c->locateCubie(WHITE, ORANGE);
    QList<int> wgpos = c->locateCubie(WHITE, GREEN);
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
