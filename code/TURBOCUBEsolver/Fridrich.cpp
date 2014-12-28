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
    for (int col = 0; col < 4; col++) { //Solving the 4 cubies {WHITE, RED}, {WHITE, ORANGE}, {WHITE, GREEN}, {WHITE, BLUE}
        QList<int> pos = c->locateCubie(WHITE, (color) col); //Locating the cubie
        color faceWhite = (color) (pos.at(0) / 3); //face on which the WHITE sticker is
        color faceCol = (color) (pos.at(2) / 3); //face on which the col sticker is
        //while the cubie is not at its solved state
        while(faceWhite != WHITE || faceCol != col){
            pos = c->locateCubie(WHITE, (color) col); //Locating the cubie
            faceWhite = (color) (pos.at(0) / 3);
            faceCol = (color) (pos.at(2) / 3);
            //Depending on where the WHITE sticker is:
            switch(faceWhite){
            case WHITE:
                //if the WHITE sticker is on the WHITE face but col is not on the right face
                //Turning this cubie on the yellow face to further solve it
                c->turnFace(faceCol, 2);
                break;
            case YELLOW:
                //if it's on the YELLOW face
                if(faceCol == col){
                    //if col is on the right face
                    c->turnFace((color) col, 2);
                    //cubie solved
                } else {
                    //if it's not, we turn the face until it is
                    if(pos.at(2) > faceCol * 3 + 1){
                        c->turnFace(YELLOW);
                    } else {
                        c->turnFace(YELLOW, -1);
                    }
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
                        //if it's on the right of the face
                        c->turnFace(faceCol);
                        c->turnFace(YELLOW, 2);
                        c->turnFace(faceCol, -1);
                    } else {
                        c->turnFace(faceCol, -1);
                        c->turnFace(YELLOW, 2);
                        c->turnFace(faceCol);
                    }
                } else if (faceCol == WHITE){
                    //if the col sticker is on white
                    //we do the algorithm
                    c->turnFace((color)col);
                    c->turnFace(WHITE, -1);
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
                    c->turnFace(YELLOW);
                    pos = c->locateCubie(WHITE, (color) col);
                    faceWhite = (color) (pos.at(0) / 3);
                    faceCol = (color) (pos.at(2) / 3);
                    c->turnFace(faceWhite);
                    c->turnFace((color) col, -1);
                    c->turnFace(faceWhite, -1);
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
