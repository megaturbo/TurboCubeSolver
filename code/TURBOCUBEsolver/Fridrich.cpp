#include "Fridrich.h"
#include <QString>
#include <QStringBuilder>
#include <cubie.h>
#include <qdebug.h>

QString Fridrich::solve(Cube *c){
//    color solvedMatrix[18][3];

//    for (int x = 0; x < 18; ++x) {
//        for (int y = 0; y < 3; ++y) {
//            solvedMatrix[x][y] = (color)(x / 3);
//        }
//    }
//    Cube solvedCube(solvedMatrix);
    QString s;
    s = cross(c);
    s += F2L(c);
    s += OLL(c);
    s += PLL(c);
    return s;
}

//For now, it's only solving for the white face
//can be optimized
QString Fridrich::cross(Cube *c){
    QString s; //string return
    for (int col = 0; col < 4; col++) {
        QList<int> pos = c->locateCubie(WHITE, (color) col);
        color faceWhite = (color) (pos.at(0) / 3);
        color faceCol = (color) (pos.at(2) / 3);
        //while the cubie is not at its solved state
        while(faceWhite != WHITE || faceCol != col){
            pos = c->locateCubie(WHITE, (color) col);
            faceWhite = (color) (pos.at(0) / 3);
            faceCol = (color) (pos.at(2) / 3);
            switch(faceWhite){
            case WHITE:
                //if the cubie is on the white face but not at its correct place
                c->turnFace(faceCol);
                c->turnFace(faceCol);
                break;
            case YELLOW:
                //if it's on the yellow face
                if(faceCol == col){
                    //if it's on the correct face
                    c->turnFace((color) col);
                    c->turnFace((color) col);
                } else {
                    //if its not, we turn the face until it isc
                    c->turnFace(YELLOW);
                }
                break;
            default:
                //if the white sticker is not on the white or yellow face
                if(col == faceCol){
                    //if it's just on quarter turn away from being correctly placed
                    c->turnFace((color) col);
                } else if (pos.at(1) == 1){
                    //if it is on any of the 4 edges, we turn the face it's on so the white sticker is on the yellow face
                    if(pos.at(2) > faceCol * 3 + 1){
                        c->turnFace((faceCol));
                        c->turnFace(YELLOW);
                        c->turnFace(YELLOW);
                        c->turnFace((faceCol));
                        c->turnFace((faceCol));
                        c->turnFace((faceCol));
                    } else {
                        c->turnFace((faceCol));
                        c->turnFace((faceCol));
                        c->turnFace((faceCol));
                        c->turnFace(YELLOW);
                        c->turnFace(YELLOW);
                        c->turnFace((faceCol));
                    }
                } else if (faceCol == WHITE){
                    //if the col sticker is on white
                    //we do the algorithm
                    c->turnFace((color)col);
                    c->turnFace(WHITE);
                    c->turnFace(WHITE);
                    c->turnFace(WHITE);
                    pos = c->locateCubie(WHITE, (color) col);
                    faceWhite = (color) (pos.at(0) / 3);
                    faceCol = (color) (pos.at(2) / 3);
                    c->turnFace(faceCol);
                    c->turnFace(WHITE);
                } else if (faceWhite != col) {
                    //it's on the yellow face but not where we want it
                    c->turnFace(YELLOW);
                } else {
                    //we do the algorithm to solve the cubie
                    c->turnYellow(1);
                    pos = c->locateCubie(WHITE, (color) col);
                    faceWhite = (color) (pos.at(0) / 3);
                    faceCol = (color) (pos.at(2) / 3);
                    c->turnFace(faceWhite);
                    c->turnFace((color) col);
                    c->turnFace((color) col);
                    c->turnFace((color) col);
                    c->turnFace(faceWhite);
                    c->turnFace(faceWhite);
                    c->turnFace(faceWhite);
                }
                break;
            }
            pos = c->locateCubie(WHITE, (color) col);
            faceWhite = (color) (pos.at(0) / 3);
            faceCol = (color) (pos.at(2) / 3);
        }
    }
    return s;
}

//For now, it's only solving for the white face
QString Fridrich::F2L(Cube *c){
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
