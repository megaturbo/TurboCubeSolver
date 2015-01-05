#include "Fridrich.h"
#include <QString>
#include <QStringBuilder>
#include <cubie.h>
#include <qdebug.h>

QString Fridrich::solve(Cube *c){
    QString facesTurned; //string containing the faces we turn to solve the given cube
    facesTurned = cross(c);
    facesTurned += F2L(c);
    facesTurned += OLL(c);
    facesTurned += PLL(c);
    return facesTurned;
}

QString Fridrich::cross(Cube *c){
    QString facesTurned = ""; //string containing the faces we turn to solve this step on the given cube
    for (int col = 0; col < 4; col++) { //Solving the 4 cubies {WHITE, RED}, {WHITE, ORANGE}, {WHITE, GREEN}, {WHITE, BLUE}
        QList<int> pos = c->locateCubie(WHITE, (color) col); //Locating the cubie
        color faceWhite = (color) (pos.at(0) / 3); //face on which the WHITE sticker is
        color faceCol = (color) (pos.at(2) / 3); //face on which the col sticker is
        //while the cubie is not at its solved state
        while(faceWhite != WHITE || faceCol != col){
            //Depending on where the WHITE sticker is:
            switch(faceWhite){
            case WHITE:
                //if the WHITE sticker is on the WHITE face but col is not on the right face
                //Turning this cubie on the yellow face to further solve it
                facesTurned.append(c->turnFace(faceCol, 2));
                break;
            case YELLOW:
                //if it's on the YELLOW face
                facesTurned.append(c->turnFace(YELLOW, col - faceCol));
                facesTurned.append(c->turnFace((color) col, 2));
                //cubie solved
                break;
            default:
                //if the WHITE sticker is not on the WHITE or YELLOW face
                if(col == faceCol){
                    //if it's just on quarter turn away from being correctly placed
                    if(pos.at(2) > faceCol * 3 + 1){
                        facesTurned.append(c->turnFace((color) col, -1));
                    } else {
                        facesTurned.append(c->turnFace((color) col, 1));
                    }
                } else if (pos.at(1) == 1){
                    //if it is on any of the 4 edges, we turn the face it's on so the white sticker is on the yellow face
                    if(pos.at(2) > faceCol * 3 + 1){
                        //if it's on the right of the face
                        facesTurned.append(c->turnFace(faceCol));
                        facesTurned.append(c->turnFace(YELLOW, col - faceCol));
                        facesTurned.append(c->turnFace(faceCol, -1));
                    } else {
                        facesTurned.append(c->turnFace(faceCol, -1));
                        facesTurned.append(c->turnFace(YELLOW, col - faceCol));
                        facesTurned.append(c->turnFace(faceCol));
                    }
                } else if (faceCol == WHITE){
                    //if the col sticker is on white
                    //we do the algorithm
                    facesTurned.append(c->turnFace((color)col));
                    facesTurned.append(c->turnFace(WHITE, -1));
                    pos = c->locateCubie(WHITE, (color) col);
                    faceWhite = (color) (pos.at(0) / 3);
                    faceCol = (color) (pos.at(2) / 3);
                    facesTurned.append(c->turnFace(faceCol));
                    facesTurned.append(c->turnFace(WHITE));
                } else if (faceWhite != col) {
                    //it's on the yellow face but not where we want it
                    facesTurned.append(c->turnFace(YELLOW));
                } else {
                    //we do the algorithm to solve the cubie
                    facesTurned.append(c->turnFace(YELLOW));
                    pos = c->locateCubie(WHITE, (color) col);
                    faceWhite = (color) (pos.at(0) / 3);
                    faceCol = (color) (pos.at(2) / 3);
                    facesTurned.append(c->turnFace(faceWhite));
                    facesTurned.append(c->turnFace((color) col, -1));
                    facesTurned.append(c->turnFace(faceWhite, -1));
                }
                break;
            }
            pos = c->locateCubie(WHITE, (color) col);
            faceWhite = (color) (pos.at(0) / 3);
            faceCol = (color) (pos.at(2) / 3);
        }
    }
    return facesTurned;
}

QString Fridrich::F2L(Cube *c){
    QString facesTurned = ""; //string containing the faces we turn to solve this step on the given cube
    for (int col1 = 0; col1 < 4; col1++) { //Solving the 4 pairs of cubies {{WHITE, RED, BLUE}, {RED BLUE}},
                                        //{{WHITE, BLUE, ORANGE}, {BLUE, ORANGE}}, {{WHITE, ORANGE, GREEN}, {ORANGE, GREEN}},
                                        //{{WHITE, GREEN, RED}, {GREEN, RED}}
        int col2 = (col1 + 1) % 4;
        QList<int> cornerPos = c->locateCubie(WHITE, (color) col1, (color) col2); //Locating the corner cubie
        QList<int> edgePos = c->locateCubie((color) col1, (color) col2);
        color faceWhite = (color) (cornerPos.at(0) / 3); //face on which the WHITE sticker is
        color faceCornerCol1 = (color) (cornerPos.at(2) / 3); //face on which the col1 sticker is
        color faceCornerCol2 = (color) (cornerPos.at(4) / 3); //face on which the col2 sticker is
        color faceEdgeCol1 = (color) (edgePos.at(0) / 3);
        color faceEdgeCol2 = (color) (edgePos.at(2) / 3);
        //while the pair of cubies is not at its solved state
        while(faceWhite != WHITE || faceEdgeCol1 != col1 || faceCornerCol1 != col1){
            //Basic cases
            if((faceWhite < 4 && faceWhite > -1) && (faceCornerCol1 == faceEdgeCol1) && (faceCornerCol2 == faceEdgeCol2)){
                qDebug() << col1 << " " << faceEdgeCol1;
                if(faceEdgeCol2 == YELLOW){
                    //if col1 is on YELLOW, then cubie is on the left of the corner, with the YELLOW face up
                    facesTurned.append(c->turnFace(YELLOW, col2 - faceEdgeCol2 + 1));
                    //then R U' R'
                    facesTurned.append(c->turnFace((color)col2, 1));
                    facesTurned.append(c->turnFace(YELLOW, -1));
                    facesTurned.append(c->turnFace((color)col2, -1));
                } else {
                    facesTurned.append(c->turnFace(YELLOW, (col2 - faceEdgeCol2 + 3) % 4));
                    //then L' U L
                    facesTurned.append(c->turnFace((color)col2, -1));
                    facesTurned.append(c->turnFace(YELLOW, 1));
                    facesTurned.append(c->turnFace((color)col2, 1));
                }
            }
            if((faceWhite < 4 && faceWhite > -1) && (faceCornerCol1 == (faceEdgeCol2 + 2) % 4 )){

            }
            qDebug() << "brweak;";
            break;
            cornerPos = c->locateCubie(WHITE, (color) col1, (color) col2); //Locating the corner cubie
            edgePos = c->locateCubie((color) col1, (color) col2);
            faceWhite = (color) (cornerPos.at(0) / 3); //face on which the WHITE sticker is
            faceCornerCol1 = (color) (cornerPos.at(2) / 3); //face on which the col1 sticker is
            faceCornerCol2 = (color) (cornerPos.at(4) / 3); //face on which the col2 sticker is
            faceEdgeCol1 = (color) (edgePos.at(0) / 3);
            faceEdgeCol2 = (color) (edgePos.at(2) / 3);
        }
    }
    return facesTurned;
}

QString Fridrich::OLL(Cube *c){
    QString facesTurned = ""; //string containing the faces we turn to solve this step on the given cube

    return facesTurned;
}

QString Fridrich::PLL(Cube *c){
    QString facesTurned = ""; //string containing the faces we turn to solve this step on the given cube

    return facesTurned;
}
