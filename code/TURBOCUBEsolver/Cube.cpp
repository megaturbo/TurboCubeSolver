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
        qDebug() << "boucle";
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

QList<int> Cube::cubie(int i, int j) {
    //not on the cube
    if(i < 0 || i > 17 || j < 0 || j > 3) {
        QList<int> ret;
        return ret;
    } else {
        //indices on the face
        int x = i % 3;
        int y = j;
        //on this face
        color face = (color) (i /3);
        //we had the indices to this qlist and we will return it at the end of the method
        QList<int> ret;
        ret += i;
        ret += j;
        //if x = y = 1, it's a center
        if (x == 1 && y == 1) {
            return ret;
        }
        //if face is RED, BLUE, ORANGE OR GREEN
        else if (face < 4) {
            //if the sticker is adjacent to another RED, BLUE, ORANGE OR GREEN face
            //if the sticker is on the left of the face, return the sticker to the left of it
            if(x == 0){
                ret += (i + 11) % 12;
                ret += y;
            }
            //if the sticker is on the right of the face, return the sticker to the right of it
            if (x == 2) {
                ret += (i + 1) % 12;
                ret += y;
            }
            //if the sticker is adjacent to the white face
            if (y == 0){
                switch(face){
                case RED:
                    ret += WHITE * 3 + x;
                    ret += 2;
                    break;
                case BLUE:
                    ret += WHITE * 3 + 2;
                    ret += 2 - x;
                    break;
                case ORANGE:
                    ret += WHITE * 3 + 2 - x;
                    ret += 0;
                    break;
                case GREEN:
                    ret += WHITE * 3;
                    ret += x;
                    break;
                default:
                    //should not happen
                    break;
                }
            }
            //if the sticker is adjacent to the yellow face
            if (y == 2){
                switch(face){
                case RED:
                    ret += YELLOW * 3 + 2 - x;
                    ret += 2;
                    break;
                case BLUE:
                    ret += YELLOW * 3;
                    ret += 2 - x;
                    break;
                case ORANGE:
                    ret += YELLOW * 3 + x;
                    ret += 0;
                    break;
                case GREEN:
                    ret += YELLOW * 3 + 2;
                    ret += x;
                    break;
                default:
                    //should not happen
                    break;
                }
            }
        }
        //if face is WHITE
        else if (face == WHITE){
            //if the face is adjacent to RED
            if (y == 2) {
                ret += RED * 3 + x;
                ret += 0;
            }
            //if the face is adjacent to BLUE
            if (x == 2) {
                ret += BLUE * 3 + 2 - y;
                ret += 0;
            }
            //if the face is adjacent to ORANGE
            if (y == 0) {
                ret += ORANGE * 3 + 2 - x;
                ret += 0;
            }
            //if the face is adjacent to GREEN
            if (x == 0) {
                ret += GREEN * 3 + y;
                ret += 0;
            }
        }
        //else face is YELLOW
        else {
            //if the face is adjacent to RED
            if (y == 2) {
                ret += RED * 3 + 2 - x;
                ret += 2;
            }
            //if the face is adjacent to BLUE
            if (x == 0) {
                ret += BLUE * 3 + 2 - y;
                ret += 2;
            }
            //if the face is adjacent to ORANGE
            if (y == 0) {
                ret += ORANGE * 3 + x;
                ret += 2;
            }
            //if the face is adjacent to GREEN
            if (x == 2) {
                ret += GREEN * 3 + y;
                ret += 2;
            }
        }
        return ret;
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

