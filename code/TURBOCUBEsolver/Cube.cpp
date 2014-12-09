#include "Cube.h"
#include <QString>
#include <iostream>
#include <qdebug.h>
#include <QList>
#include <qdebug.h>

void Cube::displayCube() {
    QString s = "\n";
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 18; x++) {
            switch(matCube[x][y]) {
            case WHITE:
                s += "W ";
                break;
            case YELLOW:
                s += "Y ";
                break;
            case RED:
                s += "R ";
                break;
            case BLUE:
                s += "B ";
                break;
            case GREEN:
                s += "G ";
                break;
            case ORANGE:
                s += "O ";
                break;
            default:
                s += "? ";
                break;
            }
            if(x % 3 == 2) {
                s += " ";
            }
        }
        s += "\n";
    }
    qDebug() << s;
}

//Constructors
void Cube::setMatrix(color matrix[18][3])
{
    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            matCube[x][y] = matrix[x][y];
        }
    }
}

Cube::Cube(color matrix[18][3])
{
    setMatrix(matrix);
}

//Utility methods

//returns indices of the cubie's stickers
QList<int> Cube::locateCubie(color c1, color c2) {
    //we're testing 3 cubies on 4 faces, it will cover the entire cube
    QList<int> cubi;
    for (int face = 0; face < 4; ++face) {
        cubi = cubie(face * 3 + 1, 0);
        if(cubieEqual(cubi, c1, c2)) {
            return cubi;
        }
        cubi = cubie(face * 3 + 1, 2);
        if(cubieEqual(cubi, c1, c2)) {
            return cubi;
        }
        cubi = cubie(face * 3, 1);
        if(cubieEqual(cubi, c1, c2)) {
            return cubi;
        }
    }
}

//returns indices of the cubie's stickers
QList<int> Cube::locateCubie(color c1, color c2, color c3) {
    //we're testing 2 cubies on 4 faces, it will cover the entire cube
    QList<int> cubi;
    for (int face = 0; face < 4; ++face) {
        cubi = cubie(face * 3, 0);
        if(cubieEqual(cubi, c1, c2, c3)) {
            return cubi;
        }
        cubi = cubie(face * 3, 2);
        if(cubieEqual(cubi, c1, c2, c3)) {
            return cubi;
        }
    }
}

//returns the indices of the stickers on the cubie linked to the sticker at (i, j) on matCube
QList<int> Cube::cubie(int i, int j) {
    //if the index isn't on the cube, why bother ?
    if(i < 0 || i > 17 || j < 0 || j > 3) {
        QList<int> ret;
        return ret;
    } else {
        //indices of the sticker on the face
        int x = i % 3;
        int y = j;
        //if center
        if (x == 1 && y == 1) {
            //cubie with one sticker (i, j)
            QList<int> ret;
            ret += i;
            ret += j;
            return ret;
        }
        //else, if edge
        else if (x % 2 != y % 2) {
            int adjacentx = 0;
            int adjacenty = 0;
            //going manual mode here
            color face = (color)(i / 6);
            switch (face) {
            case WHITE:
                adjacenty = 0;
                if (y == 0) {
                    adjacentx = ORANGE * 3 + 1;
                } else if (y == 2) {
                    adjacentx = RED * 3 + 1;
                } else if (x == 0) {
                    adjacentx = GREEN * 3 + 1;
                } else {
                    adjacentx = BLUE * 3 + 1;
                }
                break;
            case YELLOW:
                adjacenty = 2;
                if(y == 0) {
                    adjacentx = ORANGE * 3 + 1;
                } else if(y == 2) {
                    adjacentx = RED * 3 + 1;
                } else if(x == 0) {
                    adjacentx = BLUE * 3 + 1;
                } else {
                    adjacentx = GREEN * 3 + 1;
                }
                break;
            default:
                switch(y) {
                case 0:
                    switch(face) {
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
                    switch(face) {
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
                    if(x == 2) {
                        adjacentx = (i + 1) % 12;
                    } else {
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
        else {
            int* adjacentx = new int[2]{0, 0};
            int* adjacenty = new int[2]{0, 0};
            //going manual mode here
            color face = (color)(i / 6);
            switch (face) {
            case WHITE:
                adjacenty[0] = 0;
                adjacenty[1] = 0;
                if (y == 0 && x == 0) {
                    adjacentx[0] = ORANGE * 3 + 2;
                    adjacentx[1] = GREEN * 3;
                } else if(y == 0 && x == 2) {
                    adjacentx[0] = BLUE * 3 + 2;
                    adjacentx[1] = ORANGE * 3;
                } else if(y == 2 && x == 0) {
                    adjacentx[0] = GREEN * 3 + 2;
                    adjacentx[1] = RED * 3;
                } else {
                    adjacentx[0] = RED * 3 + 2;
                    adjacentx[1] = BLUE * 3;
                }
                break;
            case YELLOW:
                adjacenty[0] = 2;
                adjacenty[1] = 2;
                if (y == 0 && x == 0) {
                    adjacentx[0] = BLUE * 3 + 2;
                    adjacentx[1] = ORANGE * 3;
                } else if(y == 0 && x == 2) {
                    adjacentx[0] = ORANGE * 3 + 2;
                    adjacentx[1] = GREEN * 3;
                } else if(y == 2 && x == 0) {
                    adjacentx[0] = RED * 3 + 2;
                    adjacentx[1] = BLUE * 3;
                } else {
                    adjacentx[0] = GREEN * 3 + 2;
                    adjacentx[1] = RED * 3;
                }
                break;
            default:
                //sticker adjacent on RED/BLUE/ORANGE/GREEN face
                if (x == 0) {
                    adjacentx[0] = (i + 1) % 12;
                } else {
                    adjacentx[0] = (i - 1) % 12;
                }
                adjacenty[0] = y;
                //sticker on WHITE/YELLOW face
                if (y == 0) {
                    switch(face) {
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
                } else {
                    switch(face) {
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

void Cube::moveSequence(QString sequence) {

}

//matrix rotation per face
void Cube::U(int nbQuarterTurn) {

}

void Cube::D(int nbQuarterTurn) {

}

void Cube::B(int nbQuarterTurn) {

}

void Cube::F(int nbQuarterTurn) {

}

void Cube::R(int nbQuarterTurn) {

}

void Cube::L(int nbQuarterTurn) {

}

void Cube::turnFace(color face) {
    //rotates the stickers on the face
    color saveF[2];
    saveF[0] = matCube[face * 3][0];
    saveF[1] = matCube[face * 3 + 1][0];
    matCube[face * 3][0] = matCube[face * 3][2];
    matCube[face * 3 + 1][0] = matCube[face * 3][1];
    matCube[face * 3][2] = matCube[face * 3 + 2][2];
    matCube[face * 3][1] = matCube[face * 3 + 1][2];
    matCube[face * 3 + 2][2] = matCube[face * 3 + 2][0];
    matCube[face * 3 + 1][2] = matCube[face * 3 + 2][1];
    matCube[face * 3 + 2][0] = saveF[0];
    matCube[face * 3 + 2][1] = saveF[1];

    //rotates the stickers on the stickers adjacent to the face
    int* indicesx;
    int* indicesy;
    switch(face) {
    case RED:
        //{WHITE, BLUE, YELLOW, GREEN};
        indicesx = new int[12]{WHITE * 3 + 2, WHITE * 3 + 1, WHITE * 3,
                                BLUE * 3, BLUE * 3, BLUE * 3,
                                YELLOW * 3, YELLOW * 3 + 1, YELLOW * 3 + 2,
                                GREEN * 3 + 2, GREEN * 3 + 2, GREEN * 3 + 2};
        indicesy = new int[12]{2, 2, 2,
                                0, 1, 2,
                                2, 2, 2,
                                2, 1, 0};
        break;
    case BLUE:
        //{WHITE, ORANGE, YELLOW, RED};
        indicesx = new int[12]{WHITE * 3 + 2, WHITE * 3 + 2, WHITE * 3 + 2,
                                ORANGE * 3, ORANGE * 3, ORANGE * 3,
                                YELLOW * 3, YELLOW * 3, YELLOW * 3,
                                RED * 3 + 2, RED * 3 + 2, RED * 3 + 2};
        indicesy = new int[12]{2, 1, 0,
                                0, 1, 2,
                                0, 1, 2,
                                2, 1, 0};
        break;
    case ORANGE:
        //{WHITE, GREEN, YELLOW, BLUE};
        indicesx = new int[12]{WHITE * 3 + 2, WHITE * 3 + 1, WHITE * 3,
                                GREEN * 3, GREEN * 3, GREEN * 3,
                                YELLOW * 3 + 2, YELLOW * 3 + 1, YELLOW * 3,
                                BLUE * 3 + 2, BLUE * 3 + 2, BLUE * 3 + 2};
        indicesy = new int[12]{0, 0, 0,
                                0, 1, 2,
                                0, 0 ,0,
                                2, 1, 0};
        break;
    case GREEN:
        //{WHITE, RED, YELLOW, ORANGE};
        indicesx = new int[12]{WHITE * 3, WHITE * 3, WHITE * 3,
                                RED * 3, RED * 3, RED * 3,
                                YELLOW * 3 + 2, YELLOW * 3 + 2, YELLOW * 3 + 2,
                                ORANGE * 3 + 2, ORANGE * 3 + 2, ORANGE * 3 + 2};
        indicesy = new int[12]{0, 1, 2,
                                0, 1, 2,
                                2, 1, 0,
                                2, 1, 0};
        break;
    case WHITE:
        //{RED, GREEN, ORANGE, BLUE};
        indicesx = new int[12]{RED * 3, RED * 3 + 1, RED * 3 + 2,
                                GREEN * 3, GREEN * 3 + 1, GREEN * 3 + 2,
                                ORANGE * 3, ORANGE * 3 + 1, ORANGE * 3 + 2,
                                BLUE * 3, BLUE * 3 + 1, BLUE * 3 + 2};
        indicesy = new int[12]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        break;
    case YELLOW:
        //{RED, BLUE, ORANGE, GREEN};
        indicesx = new int[12]{RED * 3, RED * 3 + 1, RED * 3 + 2,
                                BLUE * 3, BLUE * 3 + 1, BLUE * 3 + 2,
                                ORANGE * 3, ORANGE * 3 + 1, ORANGE * 3 + 2,
                                GREEN * 3, GREEN * 3 + 1, GREEN * 3 + 2};
        indicesy = new int[12]{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
        break;
    default:
        break;
    }
    color save[3];
    for (int i = 0; i < 3; ++i) {
        save[i] = matCube[indicesx[i + 9]][indicesy[i + 9]];
    }
    for (int i = 11; i > 3; i-=3) {
        matCube[indicesx[i]][indicesy[i]] = matCube[indicesx[i - 3]][indicesy[i - 3]];
        matCube[indicesx[i - 1]][indicesy[i - 1]] = matCube[indicesx[i - 4]][indicesy[i - 4]];
        matCube[indicesx[i - 2]][indicesy[i - 2]] = matCube[indicesx[i - 5]][indicesy[i - 5]];
    }
    matCube[indicesx[0]][indicesy[0]] = save[0];
    matCube[indicesx[1]][indicesy[1]] = save[1];
    matCube[indicesx[2]][indicesy[2]] = save[2];
}

void Cube::turnRed(int nbQuarterTurn) {
    for (int i = 0; i < nbQuarterTurn % 4; ++i) {
        qDebug() << "turnRed!";
        turnFace(RED);
    }
}

void Cube::turnBlue(int nbQuarterTurn) {
    for (int i = 0; i < nbQuarterTurn % 4; ++i) {
        qDebug() << "turnBlue!";
        turnFace(BLUE);
    }
}

void Cube::turnOrange(int nbQuarterTurn) {
    for (int i = 0; i < nbQuarterTurn % 4; ++i) {
        qDebug() << "turnOrange!";
        turnFace(ORANGE);
    }
}

void Cube::turnGreen(int nbQuarterTurn){
    for (int i = 0; i < nbQuarterTurn % 4; ++i) {
        qDebug() << "turnGreen!";
        turnFace(GREEN);
    }
}

void Cube::turnWhite(int nbQuarterTurn) {
    for (int i = 0; i < nbQuarterTurn % 4; ++i) {
        qDebug() << "turnWhite!";
        turnFace(WHITE);
    }
}

void Cube::turnYellow(int nbQuarterTurn) {
    for (int i = 0; i < nbQuarterTurn % 4; ++i) {
        qDebug() << "turnYellow!";
        turnFace(YELLOW);
    }
}

//Private methods

bool Cube::cubieEqual(QList<int> cubi, color c1, color c2) {
    return ((matCube[cubi.at(0)][cubi.at(1)] == c1 && matCube[cubi.at(2)][cubi.at(3)] == c2)
         || (matCube[cubi.at(0)][cubi.at(1)] == c2 && matCube[cubi.at(2)][cubi.at(3)] == c1));

}

bool Cube::cubieEqual(QList<int> cubi, color c1, color c2, color c3) {
    return((matCube[cubi.at(4)][cubi.at(5)] == c1 && cubieEqual(cubi, c2, c3))
        || (matCube[cubi.at(4)][cubi.at(5)] == c2 && cubieEqual(cubi, c1, c3))
        || (matCube[cubi.at(4)][cubi.at(5)] == c3 && cubieEqual(cubi, c1, c2)));
}

