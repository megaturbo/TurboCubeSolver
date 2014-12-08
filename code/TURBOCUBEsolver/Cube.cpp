#include "Cube.h"
#include <QString>
#include <iostream>
#include <qdebug.h>
#include <QList>

//Public methods
//Constructors
Cube::Cube()
{
}

//Utility methods

//returns indices of the cubie's stickers
QList<int> Cube::locateCubie(color c1, color c2){
    //we're testing 3 cubies on 4 faces, it will cover the entire cube
    for (int face = 0; face < 4; ++face) {

    }
}

QList<int> Cube::locateCubie(color c1, color c2, color c3){
    for (int face = 0; face < 6; ++face) {
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                if(x == 2 && y == 2){
                    //center
                }
                else if(matCube[x + face * 3][y] == c1){
                    QList<int> c = cubie(x, y);
                    int y = c.length();
                }
            }
        }
    }
}

//returns the indices of the stickers on the cubie linked to the sticker at (i, j) on matCube
QList<int> Cube::cubie(int i, int j){
    //if the index isn't on the cube, why bother ?
    if(i < 0 || i > 17 || j < 0 || j > 3){
        QList<int> ret;
        return ret;
    }else{
        //indices of the sticker on the face
        int x = i % 3;
        int y = j;
        //if center
        if (x == 1 && y == 1){
            //cubie with one sticker (i, j)
            QList<int> ret;
            ret += i;
            ret +=j;
            return ret;
        }
        //else, if edge
        else if(x % 2 != y % 2){
            int adjacentx = 0;
            int adjacenty = 0;
            //going manual mode here
            color face = (color)(i / 6);
            switch (face){
            case WHITE:
                adjacenty = 0;
                if(y == 0){
                    adjacentx = ORANGE * 3 + 1;
                }else if(y == 2){
                    adjacentx = RED * 3 + 1;
                }
                else if(x == 0){
                    adjacentx = GREEN * 3 + 1;
                }
                else{
                    adjacentx = BLUE * 3 + 1;
                }
                break;
            case YELLOW:
                adjacenty = 2;
                if(y == 0){
                    adjacentx = ORANGE * 3 + 1;
                }else if(y == 2){
                    adjacentx = RED * 3 + 1;
                }
                else if(x == 0){
                    adjacentx = BLUE * 3 + 1;
                }
                else{
                    adjacentx = GREEN * 3 + 1;
                }
                break;
            default:
                switch(y){
                case 0:
                    switch(face){
                    case RED:
                        adjacentx = WHITE * 3 + 1;
                        adjacenty = 2;
                        break;
                    case BLUE:
                        adjacentx = WHITE * 3 + 2;
                        adjacenty = 1;
                        break;
                    case ORANGE:
                        adjacentx = WHITE * 3 + 1;
                        adjacenty = 0;
                        break;
                    case GREEN:
                        adjacentx = WHITE * 3;
                        adjacenty = 1;
                        break;
                    default:
                        //should not happen
                        break;
                    }
                    break;
                case 2:
                    switch(face){
                    case RED:
                        adjacentx = YELLOW * 3 + 1;
                        adjacenty = 2;
                        break;
                    case BLUE:
                        adjacentx = YELLOW * 3;
                        adjacenty = 1;
                        break;
                    case ORANGE:
                        adjacentx = YELLOW * 3 + 1;
                        adjacenty = 0;
                        break;
                    case GREEN:
                        adjacentx = YELLOW * 3 + 2;
                        adjacenty = 1;
                        break;
                    default:
                        //should not happen
                        break;
                    }
                    break;
                default:
                    if(x == 0){
                        adjacentx = (i + 1) % 12;
                    }else{
                        adjacentx = (i - 1) % 12;
                    }
                    adjacenty = 1;
                    break;
                }
                break;
            }
            QList<int> ret;
            ret += i;
            ret += j;
            ret += adjacentx;
            ret += adjacenty;
            return ret;
        }
        //else, corner
        else{
            int* adjacentx = new int[2]{0, 0};
            int* adjacenty = new int[2]{0, 0};
            //going manual mode here
            color face =(color)(i / 6);
            switch (face){
            case WHITE:
                adjacenty[0] = 0;
                adjacenty[1] = 0;
                if(y == 0 && x == 0){
                    adjacentx[0] = ORANGE * 3 + 2;
                    adjacentx[1] = GREEN * 3;
                }else if(y == 0 && x == 2){
                    adjacentx[0] = BLUE * 3 + 2;
                    adjacentx[1] = ORANGE * 3;
                }
                else if(y == 2 && x == 0){
                    adjacentx[0] = GREEN * 3 + 2;
                    adjacentx[1] = RED * 3;
                }
                else{
                    adjacentx[0] = RED * 3 + 2;
                    adjacentx[1] = BLUE * 3;
                }
                break;
            case YELLOW:
                adjacenty[0] = 2;
                adjacenty[1] = 2;
                if(y == 0 && x == 0){
                    adjacentx[0] = BLUE * 3 + 2;
                    adjacentx[1] = ORANGE * 3;
                }else if(y == 0 && x == 2){
                    adjacentx[0] = ORANGE * 3 + 2;
                    adjacentx[1] = GREEN * 3;
                }
                else if(y == 2 && x == 0){
                    adjacentx[0] = RED * 3 + 2;
                    adjacentx[1] = BLUE * 3;
                }
                else{
                    adjacentx[0] = GREEN * 3 + 2;
                    adjacentx[1] = RED * 3;
                }
                break;
            default:
                //sticker adjacent on RED/BLUE/ORANGE/GREEN face
                if(x == 0){
                    adjacentx[0] = (i + 1) % 12;
                }else{
                    adjacentx[0] = (i - 1) % 12;
                }
                adjacenty[0] = y;
                //sticker on WHITE/YELLOW face
                if(y == 0){
                    switch(face){
                    case RED:
                        adjacentx[1] = WHITE * 3 + x;
                        adjacenty[1] = 2;
                        break;
                    case BLUE:
                        adjacentx[1] = WHITE * 3 + 2;
                        adjacenty[1] = 2 - x;
                        break;
                    case ORANGE:
                        adjacentx[1] = WHITE * 3 + 2 - x;
                        adjacenty[1] = 0;
                        break;
                    case GREEN:
                        adjacentx[1] = WHITE * 3;
                        adjacenty[1] = x;
                        break;
                    default:
                        //should not happen
                        break;
                    }
                }else{
                    switch(face){
                    case RED:
                        adjacentx[1] = YELLOW * 3 + 2 - x;
                        adjacenty[1] = 2;
                        break;
                    case BLUE:
                        adjacentx[1] = YELLOW * 3;
                        adjacenty[1] = 2 - x;
                        break;
                    case ORANGE:
                        adjacentx[1] = YELLOW * 3 + x;
                        adjacenty[1] = 0;
                        break;
                    case GREEN:
                        adjacentx[1] = YELLOW * 3 + 2;
                        adjacenty[1] = x;
                        break;
                    default:
                        //should not happen
                        break;
                    }
                }
                break;
            }
            QList<int> ret;
            ret += i;
            ret += j;
            ret += adjacentx[0];
            ret += adjacenty[0];
            ret += adjacentx[1];
            ret += adjacenty[1];
            return ret;
        }
    }
}

//Private methods

//actually moves the faces
void Cube::moveSequence(QString sequence){

}

//matrix rotation per face
void Cube::U(int nbQuarterTurn){

}

void Cube::D(int nbQuarterTurn){

}

void Cube::B(int nbQuarterTurn){

}

void Cube::F(int nbQuarterTurn){

}

void Cube::R(int nbQuarterTurn){

}

void Cube::L(int nbQuarterTurn){

}
