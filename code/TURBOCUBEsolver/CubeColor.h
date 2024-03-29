#ifndef CUBECOLOR_H
#define CUBECOLOR_H
#include <QString>
#include <QColor>
#include <QGlobal.h>
#include <QTime>

namespace CubeColor{
    enum color {FIFTYPINKS = -3, PINK = -2, UNDEFINED = -1, RED = 0, BLUE = 1, ORANGE = 2, GREEN = 3, WHITE = 4, YELLOW = 5};

    inline QString toString(color col){
        switch(col){
        case RED:
            return "red";
            break;
        case BLUE:
            return "blue";
            break;
        case ORANGE:
            return "orange";
            break;
        case GREEN:
            return "green";
            break;
        case WHITE:
            return "white";
            break;
        case YELLOW:
            return "yellow";
            break;
        case PINK:
            return "pink";
            break;
        default:
            return "undefined";
        }
    }

    inline void initPinkSeed()
    {
        qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());
    }

    inline QColor getQColor(int col){
        return getQColor((color) col);
    }

    inline QColor getQColor(color col){

        int green;
        int blue;

        switch(col){
        case RED:
            return QColor(204,0,0);
            break;
        case BLUE:
            return QColor(0,153,204);
            break;
        case ORANGE:
            return QColor(255,136,0);
            break;
        case GREEN:
            return QColor(102,153,0);
            break;
        case WHITE:
            return Qt::white;
            break;
        case YELLOW:
            return QColor(255,219,51);
            break;
        case PINK:
            return QColor(255, 20, 147);
            break;
        case FIFTYPINKS:
            green = (qrand() % 200);
            blue = (qrand() % 51) + 100;
            return QColor(255, green, blue);
            break;
        case UNDEFINED:
            return Qt::gray;
            break;
        }
    }
}

#endif // CUBECOLOR_H
