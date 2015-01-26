#ifndef CUBECOLOR_H
#define CUBECOLOR_H
#include <QString>

namespace CubeColor{
    enum color {UNDEFINED = -1, RED = 0, BLUE = 1, ORANGE = 2, GREEN = 3, WHITE = 4, YELLOW = 5};

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
        default:
            return "undefined";
        }
    }
}

#endif // CUBECOLOR_H
