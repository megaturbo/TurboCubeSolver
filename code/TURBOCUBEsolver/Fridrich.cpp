#include "Fridrich.h"
#include <QString>
#include <QStringBuilder>
#include <cubie.h>
#include <qdebug.h>

QString Fridrich::solve(Cube *c){
    QString step1 = cross(c);
    c->displayCube();
    QString step2 = F2L(c);
    c->displayCube();
    QString step3 = OLL(c);
    c->displayCube();
    QString step4 = PLL(c);
    c->displayCube();
    qDebug() << "Cross: " << step1 << step1.count(' ') << " moves.";
    qDebug() << "F2L: " << step2 << step2.count(' ') << " moves.";
    qDebug() << "OLL: " << step3 << step3.count(' ') << " moves.";
    qDebug() << "PLL: " << step4 << step4.count(' ') << " moves.";
    qDebug() << "Total moves to solve: " << step1.count(' ') + step2.count(' ') + step3.count(' ') + step4.count(' ');
    return step1 + step2 + step3 + step4;
}

QString Fridrich::crossEdge(Cube *c, int co)
{
    QString facesTurned = "";
    color col = (color) co;
    QList<int> pos = c->locateCubie(WHITE, col); //Locating the cubie
    color faceWhite = (color) (pos.at(0) / 3); //face on which the WHITE sticker is
    color faceCol = (color) (pos.at(2) / 3); //face on which the col sticker is
    //while the cubie is not at its solved state
    while(faceWhite != WHITE || faceCol != col){
        //Depending on where the WHITE sticker is:
        switch(faceWhite){
        case YELLOW: //if it's on the YELLOW face
            facesTurned.append(c->turnFace(YELLOW, col - faceCol));
            facesTurned.append(c->turnFace(col, 2));
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
                    facesTurned.append(c->turnFace(col, -1));
                } else {
                    facesTurned.append(c->turnFace(col, 1));
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
                    facesTurned.append(c->turnFace(faceWhite));
                    facesTurned.append(c->turnFace(WHITE, -1));
                    facesTurned.append(c->turnFace((faceWhite + 1) % 4, 1));
                    facesTurned.append(c->turnFace(WHITE));
                }
                else {
                    //we put the white sticker on yellow
                    facesTurned.append(c->turnFace(faceWhite, 1));
                    facesTurned.append(c->turnFace((faceWhite + 1) % 4, -1));
                    facesTurned.append(c->turnFace(YELLOW, -1));
                    facesTurned.append(c->turnFace((faceWhite + 1) % 4, 1));
                }
            }
            //col sticker is on YELLOW
            else {
                facesTurned.append(c->turnFace(YELLOW, col - faceWhite + 1));
                facesTurned.append(c->turnFace((col + 1) % 4, 1));
                facesTurned.append(c->turnFace(col, -1));
                facesTurned.append(c->turnFace((col + 1) % 4, -1));
            }
            break;
        }
        pos = c->locateCubie(WHITE, col);
        faceWhite = (color) (pos.at(0) / 3);
        faceCol = (color) (pos.at(2) / 3);
    }
    return facesTurned;
}

QString Fridrich::F2LPair(Cube *c, int col)
{
    QString facesTurned;
    color col1 = (color) col;
    color col2 = (color)((col1 + 1) % 4);
    qDebug() << endl << endl << "For WHITE " << col1 << " " << col2 << "pair" << endl;
    QList<int> cornerPos = c->locateCubie(WHITE, col1, col2); //Locating the corner cubie
    QList<int> edgePos = c->locateCubie(col1, col2);
    color faceWhite = (color) (cornerPos.at(0) / 3); //face on which the WHITE sticker is
    color faceCornerCol1 = (color) (cornerPos.at(2) / 3); //face on which the col1 sticker is
    color faceCornerCol2 = (color) (cornerPos.at(4) / 3); //face on which the col2 sticker is
    color faceEdgeCol1 = (color) (edgePos.at(0) / 3);
    color faceEdgeCol2 = (color) (edgePos.at(2) / 3);
    //while the pair of cubies is not at its solved state. The loop is useful
    //because we can reduce complex cases to simpler ones and let the program solve them
    while((faceWhite != WHITE  || faceCornerCol1 != col1 || faceEdgeCol1!= col1 || faceEdgeCol2!= col2)){
        //edge cubie on the YELLOW face
        if(faceEdgeCol1 == YELLOW || faceEdgeCol2 == YELLOW){
            qDebug()<< "edge cubie on the YELLOW face";
            //corner cubie on the YELLOW face
            if(faceWhite == YELLOW || faceCornerCol1 == YELLOW || faceCornerCol2 == YELLOW){
                qDebug()<< "corner cubie on the YELLOW face";
                //Corner pointing outward
                if(faceWhite < 4 && faceWhite > -1){
                    qDebug()<< "Corner pointing outward";
                    //Basic case 1, corner and edge aligned
                    if(faceCornerCol1 == faceEdgeCol1 && faceCornerCol2 == faceEdgeCol2){
                        qDebug()<< "Basic case 1, corner and edge aligned";
                        //WHITE sticker points right
                        if(faceCornerCol1 == YELLOW){
                            qDebug()<< "WHITE sticker points right";
                            facesTurned.append(c->turnFace(YELLOW, col1 - faceEdgeCol2));
                            facesTurned.append(c->turnFace(col2, -1));
                            facesTurned.append(c->turnFace(YELLOW, 1));
                            facesTurned.append(c->turnFace(col2, 1));
                        } else {
                            facesTurned.append(c->turnFace(YELLOW, col2 - faceEdgeCol1));
                            facesTurned.append(c->turnFace(col1, 1));
                            facesTurned.append(c->turnFace(YELLOW, -1));
                            facesTurned.append(c->turnFace(col1, -1));
                        }
                    }
                    //Basic case 2, corner and edge cubie aligned after one R or L'
                    else if(((faceEdgeCol1 == (faceWhite + 3) % 4) || (faceEdgeCol2 == (faceWhite + 1) % 4))
                            && ((faceCornerCol1 == YELLOW && faceEdgeCol2 == YELLOW) || (faceCornerCol2 == YELLOW && faceEdgeCol1 == YELLOW))){
                        qDebug()<< "Basic case 2, corner and edge cubie aligned after one R or L'";
                        //WHITE sticker points right
                        if(faceCornerCol1 == YELLOW){
                            qDebug()<< "WHITE sticker points right";
                            facesTurned.append(c->turnFace(YELLOW, col2 - faceCornerCol2));
                            facesTurned.append(c->turnFace(col1, 1));
                            facesTurned.append(c->turnFace(YELLOW, 1));
                            facesTurned.append(c->turnFace(col1, -1));
                        } else {
                            facesTurned.append(c->turnFace(YELLOW, col1 - faceCornerCol1));
                            facesTurned.append(c->turnFace(col2, -1));
                            facesTurned.append(c->turnFace(YELLOW, -1));
                            facesTurned.append(c->turnFace(col2, 1));
                        }
                    }
                    //WHITE sticker and edge col1 sticker are on the same face
                    else if(faceWhite == faceEdgeCol1){
                        qDebug()<< "WHITE sticker and edge col1 sticker are on the same face";
                        //WHITE sticker points right
                        if(faceCornerCol1 == YELLOW){
                            qDebug()<< "WHITE sticker points right";
                            facesTurned.append(c->turnFace(YELLOW, col1 - faceCornerCol2));
                            facesTurned.append(c->turnFace(col1, 1));
                            facesTurned.append(c->turnFace(YELLOW, -1));
                            facesTurned.append(c->turnFace(col1, -1));
                        } else {
                            facesTurned.append(c->turnFace(YELLOW, col2 - faceCornerCol1));
                            facesTurned.append(c->turnFace(col2, -1));
                            facesTurned.append(c->turnFace(YELLOW, 1));
                            facesTurned.append(c->turnFace(col2, 1));
                        }
                    }
//                        //WHITE sticker and edge col1 sticker are on opposite faces
//                        else if((faceWhite == (faceEdgeCol1 + 2) % 4) && faceEdgeCol2 == YELLOW && faceCornerCol2 == YELLOW/* || (faceWhite == (faceEdgeCol2 + 2) % 4)*/){
//                            qDebug()<< "WHITE sticker and edge col1 sticker are on opposite faces";
//                            //WHITE sticker points right
//                            if(faceCornerCol1 == YELLOW){
//                                qDebug()<< "WHITE sticker points right";
//                                facesTurned.append(c->turnFace(YELLOW, col1 - faceCornerCol2));
//                                facesTurned.append(c->turnFace(col1, 1));
//                                facesTurned.append(c->turnFace(YELLOW, 1));
//                                facesTurned.append(c->turnFace(col1, -1));
//                            } else {
////                                facesTurned.append(c->turnFace(YELLOW, col2 - faceCornerCol1));
////                                facesTurned.append(c->turnFace(col2, -1));
////                                facesTurned.append(c->turnFace(YELLOW, -1));
////                                facesTurned.append(c->turnFace(col2, 1));
//                                facesTurned.append(c->turnFace(YELLOW, col1 - faceWhite));
//                                facesTurned.append(c->turnFace(col1, 1));
//                                facesTurned.append(c->turnFace(YELLOW, 1));
//                                facesTurned.append(c->turnFace(col1, -1));

//                            }
//                        }
//                        //corner and edge cubie are aligned but the colors aren't matching
//                        else if(faceEdgeCol1 == faceCornerCol2 && faceEdgeCol2 == faceCornerCol1){
//                            qDebug()<< "corner and edge cubie are aligned but the colors aren't matching";
//                            //WHITE sticker points right
//                            if(faceCornerCol1 == YELLOW){
//                                qDebug()<< "WHITE sticker points right";
//                                facesTurned.append(c->turnFace(YELLOW, col2 - faceWhite));
//                                facesTurned.append(c->turnFace(col2, -1));
//                                facesTurned.append(c->turnFace(YELLOW, 2));
//                                facesTurned.append(c->turnFace(col2, 1));
//                            } else {
//                                facesTurned.append(c->turnFace(YELLOW, col1 - faceWhite));
//                                facesTurned.append(c->turnFace(col1, 1));
//                                facesTurned.append(c->turnFace(YELLOW, 2));
//                                facesTurned.append(c->turnFace(col1, -1));
//                            }
//                        }
                    //WHITE sticker and edge col2 sticker are on the same face
                    else if(faceWhite == faceEdgeCol2){
                        qDebug()<< "WHITE sticker and edge col2 sticker are on the same face";
                        //WHITE sticker points right
                        if(faceCornerCol1 == YELLOW){
                            qDebug()<< "WHITE sticker points right";
                            facesTurned.append(c->turnFace(YELLOW, col1 - faceWhite));
                            facesTurned.append(c->turnFace(col1, 1));
                            facesTurned.append(c->turnFace(YELLOW, -1));
                            facesTurned.append(c->turnFace(col1, -1));
                        } else {
                            facesTurned.append(c->turnFace(YELLOW, col2 - faceWhite));
                            facesTurned.append(c->turnFace(col2, -1));
                            facesTurned.append(c->turnFace(YELLOW, 1));
                            facesTurned.append(c->turnFace(col2, 1));
                        }
                    }
                    //corner and edge aren't adjacent
                    else {
                        qDebug()<< "corner and edge aren't adjacent";
                        //WHITE sticker points right
                        if(faceCornerCol1 == YELLOW){
                            qDebug()<< "WHITE sticker points right";
                            facesTurned.append(c->turnFace(YELLOW, col2 - faceWhite));
//                                facesTurned.append(c->turnFace(YELLOW, col2 - faceEdgeCol2 + 1));
                            cornerPos = c->locateCubie(WHITE, col1, col2); //Locating the corner cubie
                            edgePos = c->locateCubie(col1, col2);
                            faceWhite = (color) (cornerPos.at(0) / 3); //face on which the WHITE sticker is
                            faceCornerCol1 = (color) (cornerPos.at(2) / 3); //face on which the col1 sticker is
                            faceCornerCol2 = (color) (cornerPos.at(4) / 3); //face on which the col2 sticker is
                            faceEdgeCol1 = (color) (edgePos.at(0) / 3);
                            faceEdgeCol2 = (color) (edgePos.at(2) / 3);
                            facesTurned.append(c->turnFace(col2, -1));
                            //edge and corner similarily aligned
                            if((faceCornerCol1 == YELLOW && faceEdgeCol1 == YELLOW) || (faceCornerCol2 == YELLOW && faceEdgeCol2 == YELLOW)){
                                qDebug() << "edge and corner similarily aligned";
                                facesTurned.append(c->turnFace(YELLOW, faceCornerCol2 - faceEdgeCol2));
                            } else {
                                facesTurned.append(c->turnFace(YELLOW, col1 - faceEdgeCol1));
                            }
                            facesTurned.append(c->turnFace(col2, 1));
                        } else {
                            facesTurned.append(c->turnFace(YELLOW, col1 - faceWhite));
//                                facesTurned.append(c->turnFace(YELLOW, col1 - faceEdgeCol1 +3));
                            cornerPos = c->locateCubie(WHITE, col1, col2); //Locating the corner cubie
                            edgePos = c->locateCubie(col1, col2);
                            faceWhite = (color) (cornerPos.at(0) / 3); //face on which the WHITE sticker is
                            faceCornerCol1 = (color) (cornerPos.at(2) / 3); //face on which the col1 sticker is
                            faceCornerCol2 = (color) (cornerPos.at(4) / 3); //face on which the col2 sticker is
                            faceEdgeCol1 = (color) (edgePos.at(0) / 3);
                            faceEdgeCol2 = (color) (edgePos.at(2) / 3);
                            facesTurned.append(c->turnFace(col1, 1));
                            //edge and corner similarily aligned
                            if((faceCornerCol1 == YELLOW && faceEdgeCol1 == YELLOW) || (faceCornerCol2 == YELLOW && faceEdgeCol2 == YELLOW)){
                                qDebug() << "edge and corner similarily aligned";
                                facesTurned.append(c->turnFace(YELLOW, faceCornerCol1 - faceEdgeCol1));
                            } else {
                                facesTurned.append(c->turnFace(YELLOW, col2 - faceEdgeCol2));
                            }
                            facesTurned.append(c->turnFace(col1, -1));
                        }
                    }
                }
                //WHITE sticker is on the YELLOW face
                else {
                    qDebug()<< "WHITE sticker is on the YELLOW face";
                    //Cubies are adjacent and the col1/col2 stickers from both edge and corner are on the same face
                    if(faceEdgeCol1 == faceCornerCol1 || faceEdgeCol2 == faceCornerCol2){
                        qDebug()<< "Cubies are adjacent and the col1/col2 stickers from both edge and corner are on the same face";
                        //edge corner has col1 on the YELLOW face
                        if(faceCornerCol1 == YELLOW) {
                            qDebug()<< "edge corner has col1 on the YELLOW face";
                            facesTurned.append(c->turnFace(YELLOW, col2 - faceCornerCol1));
                            facesTurned.append(c->turnFace(col2, -1));
                            facesTurned.append(c->turnFace(YELLOW, -1));
                            facesTurned.append(c->turnFace(col2, 1));
                        } else {
                            facesTurned.append(c->turnFace(YELLOW, col2 - faceCornerCol1));
                            facesTurned.append(c->turnFace(col1, 1));
                            facesTurned.append(c->turnFace(YELLOW, 1));
                            facesTurned.append(c->turnFace(col1, -1));
                        }
                    }
                    //Cubies are adjacent and the col1/col2 stickers are not matching
                    if(faceEdgeCol1 == faceCornerCol2 || faceEdgeCol2 == faceCornerCol1){
                        qDebug()<< "Cubies are adjacent and the col1/col2 stickers are not matching";
                        //edge corner has col1 on the YELLOW face
                        if(faceCornerCol1 == YELLOW) {
                            qDebug()<< "edge corner has col1 on the YELLOW face";
                            facesTurned.append(c->turnFace(YELLOW, col2 - faceCornerCol1));
                            facesTurned.append(c->turnFace(col2, -1));
                            facesTurned.append(c->turnFace(YELLOW, 2));
                            facesTurned.append(c->turnFace(col2, 1));
                        } else {
                            facesTurned.append(c->turnFace(YELLOW, col2 - faceCornerCol1));
                            facesTurned.append(c->turnFace(col1, 1));
                            facesTurned.append(c->turnFace(YELLOW, 2));
                            facesTurned.append(c->turnFace(col1, -1));
                        }
                    }
                    //cubies are not adjacent and col1 edge sticker is opposite to col1 corner sticker
                    else if (faceEdgeCol1 == (faceCornerCol1 + 2) % 4 || faceEdgeCol2 == (faceCornerCol2 + 2) % 4) {
                        qDebug()<< "cubies are not adjacent and col1 edge sticker is opposite to col1 corner sticker";
                        //edge corner has col1 on the YELLOW face
                        if(faceCornerCol1 == YELLOW) {
                            qDebug()<< "edge corner has col1 on the YELLOW face";
                            facesTurned.append(c->turnFace(YELLOW, col2 - faceEdgeCol2));
                            facesTurned.append(c->turnFace(col2, -1));
                            facesTurned.append(c->turnFace(YELLOW, 2));
                            facesTurned.append(c->turnFace(col2, 1));
                        } else {
                            facesTurned.append(c->turnFace(YELLOW, col1 - faceEdgeCol1));
                            facesTurned.append(c->turnFace(col1, 1));
                            facesTurned.append(c->turnFace(YELLOW, 2));
                            facesTurned.append(c->turnFace(col1, -1));
                        }
                    }
                    //Cubies are not adjacent and col1 is opposite to col2
                    else {
                        qDebug()<< "Cubies are not adjacent and col1 is opposite to col2";
                        //edge corner has col1 on the YELLOW face
                        if(faceCornerCol1 == YELLOW) {
                            qDebug()<< "edge corner has col1 on the YELLOW face";
                            facesTurned.append(c->turnFace(YELLOW, col2 - faceEdgeCol2));
                            facesTurned.append(c->turnFace(col2, -1));
                            facesTurned.append(c->turnFace(YELLOW, -1));
                            facesTurned.append(c->turnFace(col2, 1));
                        } else {
                            facesTurned.append(c->turnFace(YELLOW, col1 - faceEdgeCol1));
                            facesTurned.append(c->turnFace(col1, 1));
                            facesTurned.append(c->turnFace(YELLOW, 1));
                            facesTurned.append(c->turnFace(col1, -1));
                        }
                    }
                }
            }
            //Corner cubie on the WHITE face
            else {
                qDebug()<< "Corner cubie on the WHITE face";
                //WHITE sticker on WHITE face
                if(faceWhite == WHITE){
                    qDebug()<< "WHITE sticker on WHITE face";
                    //edge col1 sticker on YELLOW face
                    if(faceEdgeCol1 == YELLOW){
                        qDebug()<< "edge col1 sticker on YELLOW face";
                        facesTurned.append(c->turnFace(YELLOW, faceCornerCol2 - faceEdgeCol2 + 1));
                        facesTurned.append(c->turnFace(faceCornerCol1, 1));
                        facesTurned.append(c->turnFace(YELLOW, - 1));
                        facesTurned.append(c->turnFace(faceCornerCol1, -1));
                    } else {
                        facesTurned.append(c->turnFace(YELLOW, faceCornerCol1 - faceEdgeCol1 + 3));
                        facesTurned.append(c->turnFace(faceCornerCol2, -1));
                        facesTurned.append(c->turnFace(YELLOW, 1));
                        facesTurned.append(c->turnFace(faceCornerCol2, 1));
                    }
                }
                //corner col1 sticker on YELLOW face
                else if(faceCornerCol1 == WHITE){
                    qDebug()<< "corner col1 sticker on YELLOW face";
                    //edge col1 sticker on YELLOW face
                    if(faceEdgeCol1 == YELLOW){
                        qDebug()<< "edge col1 sticker on YELLOW face";
                        facesTurned.append(c->turnFace(YELLOW, faceWhite - faceEdgeCol2));
                        facesTurned.append(c->turnFace(faceWhite, -1));
                        facesTurned.append(c->turnFace(YELLOW, -1));
                        facesTurned.append(c->turnFace(faceWhite, 1));
                    } else {
                        facesTurned.append(c->turnFace(YELLOW, faceCornerCol2 - faceEdgeCol1));
                        facesTurned.append(c->turnFace(faceWhite, -1));
                        facesTurned.append(c->turnFace(YELLOW, -1));
                        facesTurned.append(c->turnFace(faceWhite, 1));
                    }
                }
                //corner col2 sticker on YELLOW face
                else {
                    qDebug()<< "corner col2 sticker on YELLOW face";
                    //edge col1 sticker on YELLOW face
                    if(faceEdgeCol1 == YELLOW){
                        qDebug()<< "edge col1 sticker on YELLOW face";
                        facesTurned.append(c->turnFace(YELLOW, faceCornerCol1 - faceEdgeCol2));
                        facesTurned.append(c->turnFace(faceWhite, 1));
                        facesTurned.append(c->turnFace(YELLOW, 1));
                        facesTurned.append(c->turnFace(faceWhite, -1));
                    } else {
                        facesTurned.append(c->turnFace(YELLOW, faceWhite - faceEdgeCol1));
                        facesTurned.append(c->turnFace(faceWhite, 1));
                        facesTurned.append(c->turnFace(YELLOW, 1));
                        facesTurned.append(c->turnFace(faceWhite, -1));
                    }
                }
            }
        }
        //edge cubie not on the YELLOW face
        else {
            qDebug()<< "edge cubie not on the YELLOW face";
            //corner cubie on the YELLOW face
            if(faceWhite == YELLOW || faceCornerCol1 == YELLOW || faceCornerCol2 == YELLOW){
                qDebug()<< "corner cubie on the YELLOW face";
                //WHITE sticker on the YELLOW face
                if(faceWhite == YELLOW){
                    qDebug()<< "WHITE sticker on the YELLOW face";
                    //edge correctly oriented
                    if(faceEdgeCol1 == (faceEdgeCol2 + 3) % 4){
                        qDebug()<< "edge correctly oriented";
                        facesTurned.append(c->turnFace(YELLOW, faceEdgeCol1 - faceCornerCol2));
                        facesTurned.append(c->turnFace(faceEdgeCol1, 1));
                        facesTurned.append(c->turnFace(YELLOW, 1));
                        facesTurned.append(c->turnFace(faceEdgeCol1, -1));
                        facesTurned.append(c->turnFace(YELLOW, -1));
                    } else {
                        facesTurned.append(c->turnFace(YELLOW, faceEdgeCol1 - faceCornerCol1));
                        facesTurned.append(c->turnFace(faceEdgeCol1, -1));
                        facesTurned.append(c->turnFace(YELLOW, 1));
                        facesTurned.append(c->turnFace(faceEdgeCol1, 1));
                    }
                }
                //corner col1 sticker on the YELLOW face
                else if(faceCornerCol1 == YELLOW){
                    qDebug()<< "corner col1 sticker on the YELLOW face";
                    //edge correctly oriented
                    if(faceEdgeCol1 == (faceEdgeCol2 + 3) % 4){
                        qDebug()<< "edge correctly oriented";
                        facesTurned.append(c->turnFace(YELLOW, faceEdgeCol2 - faceWhite));
                        facesTurned.append(c->turnFace(faceEdgeCol2, -1));
                        facesTurned.append(c->turnFace(YELLOW, 1));
                        facesTurned.append(c->turnFace(faceEdgeCol2, 1));
                    } else {
                        facesTurned.append(c->turnFace(YELLOW, faceEdgeCol1 - faceWhite));
                        facesTurned.append(c->turnFace(faceEdgeCol1, -1));
                        facesTurned.append(c->turnFace(YELLOW, -1));
                        facesTurned.append(c->turnFace(faceEdgeCol1, 1));
                    }
                }
                //corner col2 sticker on the YELLOW face
                else {
                    qDebug()<< "corner col2 sticker on the YELLOW face";
                    //edge correctly oriented
                    if(faceEdgeCol1 == (faceEdgeCol2 + 3) % 4){
                        qDebug()<< "edge correctly oriented";
                        facesTurned.append(c->turnFace(YELLOW, faceEdgeCol1 - faceWhite));
                        facesTurned.append(c->turnFace(faceEdgeCol1, 1));
                        facesTurned.append(c->turnFace(YELLOW, -1));
                        facesTurned.append(c->turnFace(faceEdgeCol1, -1));
                    } else {
                        facesTurned.append(c->turnFace(YELLOW, faceEdgeCol2 - faceWhite));
                        facesTurned.append(c->turnFace(faceEdgeCol2, 1));
                        facesTurned.append(c->turnFace(YELLOW, 1));
                        facesTurned.append(c->turnFace(faceEdgeCol2, -1));
                    }
                }
            }
            //corner cubie on the WHITE face
            else {
                //all cases identical except for one
                qDebug()<< "corner cubie on the WHITE face";
                //corner col2 is on the WHITE face and the edge is incorrectly oriented
//                    if((faceEdgeCol1 == faceWhite || faceEdgeCol1 == faceCornerCol1 || faceEdgeCol1 == faceCornerCol2) &&
//                            (faceCornerCol2 == WHITE) && (!(faceEdgeCol1 == (faceEdgeCol2 + 3) % 4))){
//                        qDebug()<< "corner col2 is on the WHITE face and the edge is incorrectly oriented";
//                        facesTurned.append(c->turnFace(faceEdgeCol1, 1));
//                        facesTurned.append(c->turnFace(YELLOW, 1));
//                        facesTurned.append(c->turnFace(faceEdgeCol1, -1));
//                    } else {
                    //edge correctly oriented
                    if(faceEdgeCol1 == (faceEdgeCol2 + 3) % 4){
                        qDebug()<< "edge correctly oriented";
                        facesTurned.append(c->turnFace(faceEdgeCol1, 1));
                        facesTurned.append(c->turnFace(YELLOW, -1));
                        facesTurned.append(c->turnFace(faceEdgeCol1, -1));
                    } else {
                        facesTurned.append(c->turnFace(faceEdgeCol1, -1));
                        facesTurned.append(c->turnFace(YELLOW, 1));
                        facesTurned.append(c->turnFace(faceEdgeCol1, 1));
                    }
//                    }
            }
        }
        cornerPos = c->locateCubie(WHITE, col1, col2); //Locating the corner cubie
        edgePos = c->locateCubie(col1, col2);
        faceWhite = (color) (cornerPos.at(0) / 3); //face on which the WHITE sticker is
        faceCornerCol1 = (color) (cornerPos.at(2) / 3); //face on which the col1 sticker is
        faceCornerCol2 = (color) (cornerPos.at(4) / 3); //face on which the col2 sticker is
        faceEdgeCol1 = (color) (edgePos.at(0) / 3);
        faceEdgeCol2 = (color) (edgePos.at(2) / 3);
    }
    return facesTurned;
}

QString Fridrich::cross(Cube *c){
    QString facesTurnedMin = "U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U ";
    for (int col1 = 0; col1 < 4; col1++) { //Solving the 4 cubies {WHITE, RED}, {WHITE, ORANGE}, {WHITE, GREEN}, {WHITE, BLUE}
        for (int col2 = 0; col2 < 4; ++col2) {
            if(col2 != col1){
                for (int col3 = 0; col3 < 4; ++col3){
                    if(col3 != col2 && col3 != col1){
                        for (int col4 = 0; col4 < 4; ++col4) {
                            if(col4 != col3 && col4 != col2 && col4 != col1){
                                Cube *testCube = new Cube(*c);
                                QString facesTurned = "";
                                facesTurned += crossEdge(testCube, col1);
                                facesTurned += crossEdge(testCube, col2);
                                facesTurned += crossEdge(testCube, col3);
                                facesTurned += crossEdge(testCube, col4);
                                if(facesTurned.count(' ') < facesTurnedMin.count(' ')){
                                    facesTurnedMin = facesTurned;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    c->moveSequence(facesTurnedMin);
    return facesTurnedMin;
}


QString Fridrich::F2L(Cube *c){
    QString facesTurnedMin = "F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L F 2 L ";
    for (int col1 = 0; col1 < 4; col1++) { //Solving the 4 pairs of cubies {{WHITE, RED, BLUE}, {RED BLUE}},
        //{{WHITE, BLUE, ORANGE}, {BLUE, ORANGE}}, {{WHITE, ORANGE, GREEN}, {ORANGE, GREEN}},
        //{{WHITE, GREEN, RED}, {GREEN, RED}}
        for (int col2 = 0; col2 < 4; ++col2) {
            if(col2 != col1){
                for (int col3 = 0; col3 < 4; ++col3){
                    if(col3 != col2 && col3 != col1){
                        for (int col4 = 0; col4 < 4; ++col4) {
                            if(col4 != col3 && col4 != col2 && col4 != col1){
                                Cube *testCube = new Cube(*c);
                                QString facesTurned = "";
                                facesTurned += F2LPair(testCube, col1);
                                facesTurned += F2LPair(testCube, col2);
                                facesTurned += F2LPair(testCube, col3);
                                facesTurned += F2LPair(testCube, col4);
                                if(facesTurned.count(' ') < facesTurnedMin.count(' ')){
                                    facesTurnedMin = facesTurned;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    c->moveSequence(facesTurnedMin);
    return facesTurnedMin;
}

QString Fridrich::OLL(Cube *c){
    QString facesTurned = ""; //string containing the faces we turn to solve this step on the given cube

    c->getMatrix(); //REMOVING WARNINGS LOL))

    return facesTurned;
}

QString Fridrich::PLL(Cube *c){
    QString facesTurned = ""; //string containing the faces we turn to solve this step on the given cube

    c->getMatrix(); //REMOVING WARNINGS LOL))

    return facesTurned;
}
