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
            case YELLOW: //if it's on the YELLOW face
                facesTurned.append(c->turnFace(YELLOW, col - faceCol));
                facesTurned.append(c->turnFace((color) col, 2));
                //cubie solved
                break;
            case WHITE: //if the WHITE sticker is on the WHITE face but col is not on the right face
                //Turning this cubie on the yellow face to further solve it
                facesTurned.append(c->turnFace(faceCol, 2));
                break;
            default: //if the WHITE sticker is not on the WHITE or YELLOW
                //if it's just on quarter turn away from being correctly placed
                if(col == faceCol){
                    //if it's on the right of the face
                    if(pos.at(2) > faceCol * 3 + 1){
                        facesTurned.append(c->turnFace((color) col, -1));
                    } else {
                        facesTurned.append(c->turnFace((color) col, 1));
                    }
                }
                //if it is on any of the 4 edges, we turn the face it's on so the white sticker is on the yellow face
                else if (pos.at(1) == 1){
                    //if it's on the right of the face
                    if(pos.at(2) > faceCol * 3 + 1){
                        facesTurned.append(c->turnFace(faceCol));
                        facesTurned.append(c->turnFace(YELLOW, col - faceCol));
                        facesTurned.append(c->turnFace(faceCol, -1));
                    } else {
                        facesTurned.append(c->turnFace(faceCol, -1));
                        facesTurned.append(c->turnFace(YELLOW, col - faceCol));
                        facesTurned.append(c->turnFace(faceCol));
                    }
                }
                //if the col sticker is on WHITE
                else if (faceCol == WHITE){
                    //if the WHITE sticker is on col
                    if(faceWhite == col){
                        //we do the corresponding algorithm
                        facesTurned.append(c->turnFace((color)faceWhite));
                        facesTurned.append(c->turnFace(WHITE, -1));
                        facesTurned.append(c->turnFace((color)((faceWhite + 1) % 4), 1));
                        facesTurned.append(c->turnFace(WHITE));
                    }
                    else {
                        //we put the white sticker on yellow
                        facesTurned.append(c->turnFace(faceWhite, 1));
                        facesTurned.append(c->turnFace((color)((faceWhite + 1) % 4), -1));
                        facesTurned.append(c->turnFace(YELLOW, -1));
                        facesTurned.append(c->turnFace((color)((faceWhite + 1) % 4), 1));
                    }
                }
                //col sticker is on YELLOW
                else {
                    facesTurned.append(c->turnFace(YELLOW, ((col - faceWhite + 1) % 4)));
                    facesTurned.append(c->turnFace((color)((col + 1) % 4), 1));
                    facesTurned.append(c->turnFace((color) col, -1));
                    facesTurned.append(c->turnFace((color)((col + 1) % 4), -1));
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
        while(faceWhite != WHITE || faceEdgeCol1!= col1 || faceEdgeCol1 != col1 || faceCornerCol1 != col1){
            //corner cubie on the YELLOW face
            if(faceWhite == YELLOW || faceCornerCol1 == YELLOW || faceCornerCol2 == YELLOW){
                //edge cubie on the YELLOW face
                if(faceEdgeCol1 == YELLOW || faceEdgeCol2 == YELLOW){
                    //Corner pointing outward
                    if(faceWhite < 4 && faceWhite > -1){
                        //Basic case 1, corner and edge aligned
                        if(faceCornerCol1 == faceEdgeCol1 && faceCornerCol2 == faceEdgeCol2){
                            //if the WHITE sticker points right
                            if(faceCornerCol1 == YELLOW){
                                facesTurned.append(c->turnFace(YELLOW, col1 - faceEdgeCol2));
                                facesTurned.append(c->turnFace((color)col2, -1));
                                facesTurned.append(c->turnFace(YELLOW, 1));
                                facesTurned.append(c->turnFace((color)col2, 1));
                            } else {
                                facesTurned.append(c->turnFace(YELLOW, col2 - faceEdgeCol1));
                                facesTurned.append(c->turnFace((color)col1, 1));
                                facesTurned.append(c->turnFace(YELLOW, -1));
                                facesTurned.append(c->turnFace((color)col1, -1));
                            }
                        }
                        //Basic case 2, corner and edge cubie aligned after one R or L'
                        else if((faceCornerCol1 == (faceEdgeCol2 + 2) % 4) || (faceCornerCol2 == (faceEdgeCol1 + 2) % 4)){
                            //if the WHITE sticker points right
                            if(faceEdgeCol1 == YELLOW){
                                facesTurned.append(c->turnFace(YELLOW, col2 - faceCornerCol2));
                                facesTurned.append(c->turnFace((color)col1, 1));
                                facesTurned.append(c->turnFace(YELLOW, 1));
                                facesTurned.append(c->turnFace((color)col1, -1));
                            } else {
                                facesTurned.append(c->turnFace(YELLOW, col1 - faceCornerCol1));
                                facesTurned.append(c->turnFace((color)col2, -1));
                                facesTurned.append(c->turnFace(YELLOW, -1));
                                facesTurned.append(c->turnFace((color)col2, 1));
                            }
                        }
                        //if the WHITE sticker and the edge col1 sticker are on the same face
                        else if(faceWhite == faceEdgeCol1){
                            //if the WHITE sticker points right
                            if(faceCornerCol1 == YELLOW){
                                facesTurned.append(c->turnFace(YELLOW, col1 - faceCornerCol2));
                                facesTurned.append(c->turnFace((color) col1, 1));
                                facesTurned.append(c->turnFace(YELLOW, -1));
                                facesTurned.append(c->turnFace((color) col1, -1));
                            } else {
                                facesTurned.append(c->turnFace(YELLOW, col2 - faceCornerCol1);
                                facesTurned.append(c->turnFace((color) col2, -1));
                                facesTurned.append(c->turnFace(YELLOW, 1));
                                facesTurned.append(c->turnFace((color) col2, 1));
                            }
                        }
                        //if the WHITE sticker and edge col1 sticker are on opposite faces
                        else if(faceWhite == (faceEdgeCol1 + 2) % 4){
                            //if the WHITE sticker points right
                            if(faceCornerCol1 == YELLOW){
                                facesTurned.append(c->turnFace(YELLOW, col1 - faceCornerCol2));
                                facesTurned.append(c->turnFace((color) col1, 1));
                                facesTurned.append(c->turnFace(YELLOW, 1));
                                facesTurned.append(c->turnFace((color) col1, -1));
                            } else {
                                facesTurned.append(c->turnFace(YELLOW, col2 - faceCornerCol1));
                                facesTurned.append(c->turnFace((color) col2, -1));
                                facesTurned.append(c->turnFace(YELLOW, -1));
                                facesTurned.append(c->turnFace((color) col2, 1));
                            }
                        }
                        //if the corner and edge cubie are aligned but the colors aren't matching
                        else if(faceEdgeCol1 == faceCornerCol2 && faceEdgeCol2 == faceCornerCol1){
                            //if the WHITE sticker points right
                            if(faceCornerCol1 == YELLOW){
                                facesTurned.append(c->turnFace(YELLOW, col2 - faceWhite));
                                facesTurned.append(c->turnFace((color) col2, -1));
                                facesTurned.append(c->turnFace(YELLOW, 2));
                                facesTurned.append(c->turnFace((color) col2, 1));
                            } else {
                                facesTurned.append(c->turnFace(YELLOW, col1 - faceWhite));
                                facesTurned.append(c->turnFace((color) col1, 1));
                                facesTurned.append(c->turnFace(YELLOW, 2));
                                facesTurned.append(c->turnFace((color) col1, -1));
                            }
                        }
                        //if the WHITE sticker and edge col2 sticker are on the same face
                        else if(faceWhite == faceEdgeCol2){
                            //if the WHITE sticker points right
                            if(faceCornerCol1 == YELLOW){
                                facesTurned.append(c->turnFace(YELLOW, col1 - faceWhite));
                                facesTurned.append(c->turnFace(col1, 1));
                                facesTurned.append(c->turnFace(YELLOW, -1));
                                facesTurned.append(c->turnFace(col1, -1);
                            } else {
                                facesTurned.append(c->turnFace(YELLOW, col2 - faceWhite));
                                facesTurned.append(c->turnFace(col2, -1));
                                facesTurned.append(c->turnFace(YELLOW, 1));
                                facesTurned.append(c->turnFace(col2, 1));
                            }
                        }
                        //we can solve the 2 last cases
                        else {
                            //if the WHITE sticker points right
                            if(faceCornerCol1 == YELLOW){
                                facesTurned.append(c->turnFace(YELLOW, col2 - faceWhite));
                                facesTurned.append(c->turnFace(col2, -1));
                                facesTurned.append(c->turnFace(YELLOW, col2 - faceEdgeCol2 + 1));
                                facesTurned.append(c->turnFace(col2, 1));
                            } else {
                                facesTurned.append(c->turnFace(YELLOW, col1 - faceWhite));
                                facesTurned.append(c->turnFace(col1, 1));
                                facesTurned.append(c->turnFace(YELLOW, col2 - faceEdgeCol1 +31));
                                facesTurned.append(c->turnFace(col1, -1));
                            }
                        }
                    }
                }
            }


            qDebug() << "break;";
            //break;
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
