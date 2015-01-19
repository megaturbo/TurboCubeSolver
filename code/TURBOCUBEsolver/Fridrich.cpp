#include "Fridrich.h"
#include <QString>
#include <QStringBuilder>
#include <cubie.h>
#include <qdebug.h>

QString Fridrich::solve(Cube *cube){
    QString step1 = cross(cube);
    QString step2 = F2L(cube);
    QString step3 = OLL2Look(cube);
    step3 += OLL2Look(cube); //2-look OLL
    QString step4 = PLL2Look(cube);
    step4 += PLL2Look(cube); //2-look PLL
    //positionning the solved YELLOW face
    step4 += cube->turnFace(YELLOW, RED - cube->locateCubie(RED, BLUE, YELLOW).at(0) / 3);
    qDebug() << "Cross: " << step1 << step1.count(' ') << " moves.";
    qDebug() << "F2L: " << step2 << step2.count(' ') << " moves.";
    qDebug() << "OLL: " << step3 << step3.count(' ') << " moves.";
    qDebug() << "PLL: " << step4 << step4.count(' ') << " moves.";
    qDebug() << "Total moves to solve: " << step1.count(' ') + step2.count(' ') + step3.count(' ') + step4.count(' ');
    return "[" + step1 + "][" + step2 + "][" + step3 + "][" + step4 + "]";
}

QString Fridrich::crossEdge(Cube *cube, int firstEdgeColor)
{
    QString sequenceToSolve = "";
    color edgeColor = (color) firstEdgeColor;
    QList<int> cubieIndices = cube->locateCubie(WHITE, edgeColor); //Locating the cubie
    color faceWhiteSticker = (color) (cubieIndices.at(0) / 3); //face on which the WHITE sticker is
    color faceColorSticker = (color) (cubieIndices.at(2) / 3); //face on which the col sticker is
    //while the cubie is not at its solved state
    while(faceWhiteSticker != WHITE || faceColorSticker != edgeColor){
        //Depending on where the WHITE sticker is:
        switch(faceWhiteSticker){
        case YELLOW: //if it's on the YELLOW face
            sequenceToSolve.append(cube->turnFace(YELLOW, edgeColor - faceColorSticker));
            sequenceToSolve.append(cube->turnFace(edgeColor, 2));
            //cubie solved
            break;
        case WHITE: //if the WHITE sticker is on the WHITE face but col is not on the right face
            //Turning this cubie on the yellow face to further solve it
            sequenceToSolve.append(cube->turnFace(faceColorSticker, 2));
            break;
        default: //if the WHITE sticker is not on the WHITE or YELLOW
            //if it's just on quarter turn away from being correctly placed
            if(edgeColor == faceColorSticker){
                //if it's on the right of the face
                if(cubieIndices.at(2) > faceColorSticker * 3 + 1){
                    sequenceToSolve.append(cube->turnFace(edgeColor, -1));
                } else {
                    sequenceToSolve.append(cube->turnFace(edgeColor, 1));
                }
            }
            //if it is on any of the 4 edges, we turn the face it's on so the white sticker is on the yellow face
            else if (cubieIndices.at(1) == 1){
                //if it's on the right of the face
                if(cubieIndices.at(2) > faceColorSticker * 3 + 1){
                    sequenceToSolve.append(cube->turnFace(faceColorSticker));
                    sequenceToSolve.append(cube->turnFace(YELLOW, edgeColor - faceColorSticker));
                    sequenceToSolve.append(cube->turnFace(faceColorSticker, -1));
                } else {
                    sequenceToSolve.append(cube->turnFace(faceColorSticker, -1));
                    sequenceToSolve.append(cube->turnFace(YELLOW, edgeColor - faceColorSticker));
                    sequenceToSolve.append(cube->turnFace(faceColorSticker));
                }
            }
            //if the col sticker is on WHITE
            else if (faceColorSticker == WHITE){
                //if the WHITE sticker is on col
                if(faceWhiteSticker == edgeColor){
                    //we do the corresponding algorithm
                    sequenceToSolve.append(cube->turnFace(faceWhiteSticker));
                    sequenceToSolve.append(cube->turnFace(WHITE, -1));
                    sequenceToSolve.append(cube->turnFace((faceWhiteSticker + 1) % 4, 1));
                    sequenceToSolve.append(cube->turnFace(WHITE));
                }
                else {
                    //we put the white sticker on yellow
                    sequenceToSolve.append(cube->turnFace(faceWhiteSticker, 1));
                    sequenceToSolve.append(cube->turnFace((faceWhiteSticker + 1) % 4, -1));
                    sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                    sequenceToSolve.append(cube->turnFace((faceWhiteSticker + 1) % 4, 1));
                }
            }
            //col sticker is on YELLOW
            else {
                sequenceToSolve.append(cube->turnFace(YELLOW, edgeColor - faceWhiteSticker + 1));
                sequenceToSolve.append(cube->turnFace((edgeColor + 1) % 4, 1));
                sequenceToSolve.append(cube->turnFace(edgeColor, -1));
                sequenceToSolve.append(cube->turnFace((edgeColor + 1) % 4, -1));
            }
            break;
        }
        cubieIndices = cube->locateCubie(WHITE, edgeColor);
        faceWhiteSticker = (color) (cubieIndices.at(0) / 3);
        faceColorSticker = (color) (cubieIndices.at(2) / 3);
    }
    return sequenceToSolve;
}

QString Fridrich::F2LPair(Cube *cube, int firstCornerColor)
{
    QString sequenceToSolve;
    color firstEdgeColor = (color) firstCornerColor;
    color secondEdgeColor = (color)((firstEdgeColor + 1) % 4);
    QList<int> cornerIndices = cube->locateCubie(WHITE, firstEdgeColor, secondEdgeColor); //Locating the corner cubie
    QList<int> edgeIndices = cube->locateCubie(firstEdgeColor, secondEdgeColor);
    color faceWhiteSticker = (color) (cornerIndices.at(0) / 3); //face on which the WHITE sticker is
    color faceFirstCorner= (color) (cornerIndices.at(2) / 3); //face on which the col1 sticker is
    color faceSecondCorner = (color) (cornerIndices.at(4) / 3); //face on which the col2 sticker is
    color faceFirstEdge = (color) (edgeIndices.at(0) / 3);
    color faceSecondEdge = (color) (edgeIndices.at(2) / 3);
    //while the pair of cubies is not at its solved state. The loop is useful
    //because we can reduce complex cases to simpler ones and let the program solve them
    int loopCounter = 0;
    while((faceWhiteSticker != WHITE  || faceFirstCorner != firstEdgeColor || faceFirstEdge!= firstEdgeColor || faceSecondEdge!= secondEdgeColor) && loopCounter++ < 50){
        //edge cubie on the YELLOW face
        if(faceFirstEdge == YELLOW || faceSecondEdge == YELLOW){
            //corner cubie on the YELLOW face
            if(faceWhiteSticker == YELLOW || faceFirstCorner == YELLOW || faceSecondCorner == YELLOW){
                //Corner pointing outward
                if(faceWhiteSticker < 4 && faceWhiteSticker > -1){
                    //Basic case 1, corner and edge aligned
                    if(faceFirstCorner == faceFirstEdge && faceSecondCorner == faceSecondEdge){
                        //WHITE sticker points right
                        if(faceFirstCorner == YELLOW){
                            sequenceToSolve.append(cube->turnFace(YELLOW, firstEdgeColor - faceSecondEdge));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, -1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, 1));
                        } else {
                            sequenceToSolve.append(cube->turnFace(YELLOW, secondEdgeColor - faceFirstEdge));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, 1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, -1));
                        }
                    }
                    //Basic case 2, corner and edge cubie aligned after one R or L'
                    else if(((faceFirstEdge == (faceWhiteSticker + 3) % 4) || (faceSecondEdge == (faceWhiteSticker + 1) % 4))
                            && ((faceFirstCorner == YELLOW && faceSecondEdge == YELLOW) || (faceSecondCorner == YELLOW && faceFirstEdge == YELLOW))){
                        //WHITE sticker points right
                        if(faceFirstCorner == YELLOW){
                            sequenceToSolve.append(cube->turnFace(YELLOW, secondEdgeColor - faceSecondCorner));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, 1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, -1));
                        } else {
                            sequenceToSolve.append(cube->turnFace(YELLOW, firstEdgeColor - faceFirstCorner));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, -1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, 1));
                        }
                    }
                    //WHITE sticker and edge col1 sticker are on the same face
                    else if(faceWhiteSticker == faceFirstEdge){
                        //WHITE sticker points right
                        if(faceFirstCorner == YELLOW){
                            sequenceToSolve.append(cube->turnFace(YELLOW, firstEdgeColor - faceSecondCorner));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, 1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, -1));
                        } else {
                            sequenceToSolve.append(cube->turnFace(YELLOW, secondEdgeColor - faceFirstCorner));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, -1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, 1));
                        }
                    }
                    //WHITE sticker and edge col2 sticker are on the same face
                    else if(faceWhiteSticker == faceSecondEdge){
                        //WHITE sticker points right
                        if(faceFirstCorner == YELLOW){
                            sequenceToSolve.append(cube->turnFace(YELLOW, firstEdgeColor - faceWhiteSticker));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, 1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, -1));
                        } else {
                            sequenceToSolve.append(cube->turnFace(YELLOW, secondEdgeColor - faceWhiteSticker));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, -1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, 1));
                        }
                    }
                    //corner and edge aren't adjacent
                    else {
                        //WHITE sticker points right
                        if(faceFirstCorner == YELLOW){
                            sequenceToSolve.append(cube->turnFace(YELLOW, secondEdgeColor - faceWhiteSticker));
                            cornerIndices = cube->locateCubie(WHITE, firstEdgeColor, secondEdgeColor); //Locating the corner cubie
                            edgeIndices = cube->locateCubie(firstEdgeColor, secondEdgeColor);
                            faceWhiteSticker = (color) (cornerIndices.at(0) / 3); //face on which the WHITE sticker is
                            faceFirstCorner = (color) (cornerIndices.at(2) / 3); //face on which the col1 sticker is
                            faceSecondCorner = (color) (cornerIndices.at(4) / 3); //face on which the col2 sticker is
                            faceFirstEdge = (color) (edgeIndices.at(0) / 3);
                            faceSecondEdge = (color) (edgeIndices.at(2) / 3);
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, -1));
                            //edge and corner similarily aligned
                            if((faceFirstCorner == YELLOW && faceFirstEdge == YELLOW) || (faceSecondCorner == YELLOW && faceSecondEdge == YELLOW)){
                                sequenceToSolve.append(cube->turnFace(YELLOW, faceSecondCorner - faceSecondEdge));
                            } else {
                                sequenceToSolve.append(cube->turnFace(YELLOW, firstEdgeColor - faceFirstEdge));
                            }
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, 1));
                        } else {
                            sequenceToSolve.append(cube->turnFace(YELLOW, firstEdgeColor - faceWhiteSticker));
                            cornerIndices = cube->locateCubie(WHITE, firstEdgeColor, secondEdgeColor); //Locating the corner cubie
                            edgeIndices = cube->locateCubie(firstEdgeColor, secondEdgeColor);
                            faceWhiteSticker = (color) (cornerIndices.at(0) / 3); //face on which the WHITE sticker is
                            faceFirstCorner = (color) (cornerIndices.at(2) / 3); //face on which the col1 sticker is
                            faceSecondCorner = (color) (cornerIndices.at(4) / 3); //face on which the col2 sticker is
                            faceFirstEdge = (color) (edgeIndices.at(0) / 3);
                            faceSecondEdge = (color) (edgeIndices.at(2) / 3);
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, 1));
                            //edge and corner similarily aligned
                            if((faceFirstCorner == YELLOW && faceFirstEdge == YELLOW) || (faceSecondCorner == YELLOW && faceSecondEdge == YELLOW)){
                                sequenceToSolve.append(cube->turnFace(YELLOW, faceFirstCorner - faceFirstEdge));
                            } else {
                                sequenceToSolve.append(cube->turnFace(YELLOW, secondEdgeColor - faceSecondEdge));
                            }
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, -1));
                        }
                    }
                }
                //WHITE sticker is on the YELLOW face
                else {
                    //Cubies are adjacent and the col1/col2 stickers from both edge and corner are on the same face
                    if(faceFirstEdge == faceFirstCorner || faceSecondEdge == faceSecondCorner){
                        //edge corner has col1 on the YELLOW face
                        if(faceFirstCorner == YELLOW) {
                            sequenceToSolve.append(cube->turnFace(YELLOW, secondEdgeColor - faceFirstCorner));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, -1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, 1));
                        } else {
                            sequenceToSolve.append(cube->turnFace(YELLOW, secondEdgeColor - faceFirstCorner));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, 1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, -1));
                        }
                    }
                    //Cubies are adjacent and the col1/col2 stickers are not matching
                    if(faceFirstEdge == faceSecondCorner || faceSecondEdge == faceFirstCorner){
                        //edge corner has col1 on the YELLOW face
                        if(faceFirstCorner == YELLOW) {
                            sequenceToSolve.append(cube->turnFace(YELLOW, secondEdgeColor - faceFirstCorner));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, -1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, 2));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, 1));
                        } else {
                            sequenceToSolve.append(cube->turnFace(YELLOW, secondEdgeColor - faceFirstCorner));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, 1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, 2));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, -1));
                        }
                    }
                    //cubies are not adjacent and col1 edge sticker is opposite to col1 corner sticker
                    else if (faceFirstEdge == (faceFirstCorner + 2) % 4 || faceSecondEdge == (faceSecondCorner + 2) % 4) {
                        //edge corner has col1 on the YELLOW face
                        if(faceFirstCorner == YELLOW) {
                            sequenceToSolve.append(cube->turnFace(YELLOW, secondEdgeColor - faceSecondEdge));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, -1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, 2));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, 1));
                        } else {
                            sequenceToSolve.append(cube->turnFace(YELLOW, firstEdgeColor - faceFirstEdge));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, 1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, 2));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, -1));
                        }
                    }
                    //Cubies are not adjacent and col1 is opposite to col2
                    else {
                        //edge corner has col1 on the YELLOW face
                        if(faceFirstCorner == YELLOW) {
                            sequenceToSolve.append(cube->turnFace(YELLOW, secondEdgeColor - faceSecondEdge));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, -1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                            sequenceToSolve.append(cube->turnFace(secondEdgeColor, 1));
                        } else {
                            sequenceToSolve.append(cube->turnFace(YELLOW, firstEdgeColor - faceFirstEdge));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, 1));
                            sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                            sequenceToSolve.append(cube->turnFace(firstEdgeColor, -1));
                        }
                    }
                }
            }
            //Corner cubie on the WHITE face
            else {
                //WHITE sticker on WHITE face
                if(faceWhiteSticker == WHITE){
                    //edge col1 sticker on YELLOW face
                    if(faceFirstEdge == YELLOW){
                        sequenceToSolve.append(cube->turnFace(YELLOW, faceSecondCorner - faceSecondEdge + 1));
                        sequenceToSolve.append(cube->turnFace(faceFirstCorner, 1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, - 1));
                        sequenceToSolve.append(cube->turnFace(faceFirstCorner, -1));
                    } else {
                        sequenceToSolve.append(cube->turnFace(YELLOW, faceFirstCorner - faceFirstEdge + 3));
                        sequenceToSolve.append(cube->turnFace(faceSecondCorner, -1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                        sequenceToSolve.append(cube->turnFace(faceSecondCorner, 1));
                    }
                }
                //corner col1 sticker on YELLOW face
                else if(faceFirstCorner == WHITE){
                    //edge col1 sticker on YELLOW face
                    if(faceFirstEdge == YELLOW){
                        sequenceToSolve.append(cube->turnFace(YELLOW, faceWhiteSticker - faceSecondEdge));
                        sequenceToSolve.append(cube->turnFace(faceWhiteSticker, -1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                        sequenceToSolve.append(cube->turnFace(faceWhiteSticker, 1));
                    } else {
                        sequenceToSolve.append(cube->turnFace(YELLOW, faceSecondCorner - faceFirstEdge));
                        sequenceToSolve.append(cube->turnFace(faceWhiteSticker, -1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                        sequenceToSolve.append(cube->turnFace(faceWhiteSticker, 1));
                    }
                }
                //corner col2 sticker on YELLOW face
                else {
                    //edge col1 sticker on YELLOW face
                    if(faceFirstEdge == YELLOW){
                        sequenceToSolve.append(cube->turnFace(YELLOW, faceFirstCorner - faceSecondEdge));
                        sequenceToSolve.append(cube->turnFace(faceWhiteSticker, 1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                        sequenceToSolve.append(cube->turnFace(faceWhiteSticker, -1));
                    } else {
                        sequenceToSolve.append(cube->turnFace(YELLOW, faceWhiteSticker - faceFirstEdge));
                        sequenceToSolve.append(cube->turnFace(faceWhiteSticker, 1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                        sequenceToSolve.append(cube->turnFace(faceWhiteSticker, -1));
                    }
                }
            }
        }
        //edge cubie not on the YELLOW face
        else {
            //corner cubie on the YELLOW face
            if(faceWhiteSticker == YELLOW || faceFirstCorner == YELLOW || faceSecondCorner == YELLOW){
                //WHITE sticker on the YELLOW face
                if(faceWhiteSticker == YELLOW){
                    //edge correctly oriented
                    if(faceFirstEdge == (faceSecondEdge + 3) % 4){
                        sequenceToSolve.append(cube->turnFace(YELLOW, faceFirstEdge - faceSecondCorner));
                        sequenceToSolve.append(cube->turnFace(faceFirstEdge, 1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                        sequenceToSolve.append(cube->turnFace(faceFirstEdge, -1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                    } else {
                        sequenceToSolve.append(cube->turnFace(YELLOW, faceFirstEdge - faceFirstCorner));
                        sequenceToSolve.append(cube->turnFace(faceFirstEdge, -1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                        sequenceToSolve.append(cube->turnFace(faceFirstEdge, 1));
                    }
                }
                //corner col1 sticker on the YELLOW face
                else if(faceFirstCorner == YELLOW){
                    //edge correctly oriented
                    if(faceFirstEdge == (faceSecondEdge + 3) % 4){
                        sequenceToSolve.append(cube->turnFace(YELLOW, faceSecondEdge - faceWhiteSticker));
                        sequenceToSolve.append(cube->turnFace(faceSecondEdge, -1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                        sequenceToSolve.append(cube->turnFace(faceSecondEdge, 1));
                    } else {
                        sequenceToSolve.append(cube->turnFace(YELLOW, faceFirstEdge - faceWhiteSticker));
                        sequenceToSolve.append(cube->turnFace(faceFirstEdge, -1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                        sequenceToSolve.append(cube->turnFace(faceFirstEdge, 1));
                    }
                }
                //corner col2 sticker on the YELLOW face
                else {
                    //edge correctly oriented
                    if(faceFirstEdge == (faceSecondEdge + 3) % 4){
                        sequenceToSolve.append(cube->turnFace(YELLOW, faceFirstEdge - faceWhiteSticker));
                        sequenceToSolve.append(cube->turnFace(faceFirstEdge, 1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                        sequenceToSolve.append(cube->turnFace(faceFirstEdge, -1));
                    } else {
                        sequenceToSolve.append(cube->turnFace(YELLOW, faceSecondEdge - faceWhiteSticker));
                        sequenceToSolve.append(cube->turnFace(faceSecondEdge, 1));
                        sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                        sequenceToSolve.append(cube->turnFace(faceSecondEdge, -1));
                    }
                }
            }
            //corner cubie on the WHITE face
            else {
                //edge correctly oriented
                if(faceFirstEdge == (faceSecondEdge + 3) % 4){
                    sequenceToSolve.append(cube->turnFace(faceFirstEdge, 1));
                    sequenceToSolve.append(cube->turnFace(YELLOW, -1));
                    sequenceToSolve.append(cube->turnFace(faceFirstEdge, -1));
                } else {
                    sequenceToSolve.append(cube->turnFace(faceFirstEdge, -1));
                    sequenceToSolve.append(cube->turnFace(YELLOW, 1));
                    sequenceToSolve.append(cube->turnFace(faceFirstEdge, 1));
                }
            }
        }
        cornerIndices = cube->locateCubie(WHITE, firstEdgeColor, secondEdgeColor); //Locating the corner cubie
        edgeIndices = cube->locateCubie(firstEdgeColor, secondEdgeColor);
        faceWhiteSticker = (color) (cornerIndices.at(0) / 3); //face on which the WHITE sticker is
        faceFirstCorner = (color) (cornerIndices.at(2) / 3); //face on which the col1 sticker is
        faceSecondCorner = (color) (cornerIndices.at(4) / 3); //face on which the col2 sticker is
        faceFirstEdge = (color) (edgeIndices.at(0) / 3);
        faceSecondEdge = (color) (edgeIndices.at(2) / 3);
    }
    if (loopCounter > 50){
        qDebug() << "Failure for pair " << firstEdgeColor << secondEdgeColor;
    }
    return sequenceToSolve;
}

QString Fridrich::cross(Cube *cube){
    QString fewestMovesSequence = "U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U U ";
    //Solving the 4 cubies {WHITE, RED}, {WHITE, ORANGE}, {WHITE, GREEN}, {WHITE, BLUE} in every possible order
    for (int color1 = 0; color1 < 4; color1++) {
        for (int color2 = 0; color2 < 4; ++color2) {
            if(color2 != color1){
                for (int color3 = 0; color3 < 4; ++color3){
                    if(color3 != color2 && color3 != color1){
                        for (int color4 = 0; color4 < 4; ++color4) {
                            if(color4 != color3 && color4 != color2 && color4 != color1){
                                Cube *tempCube = new Cube(*cube);
                                QString sequence = "";
                                sequence += crossEdge(tempCube, color1);
                                sequence += crossEdge(tempCube, color2);
                                sequence += crossEdge(tempCube, color3);
                                sequence += crossEdge(tempCube, color4);
                                if(sequence.count(' ') < fewestMovesSequence.count(' ')){
                                    fewestMovesSequence = sequence;
                                }
                                delete tempCube;
                                tempCube = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    cube->moveSequence(fewestMovesSequence, RED, YELLOW);
    return fewestMovesSequence;
}

QString Fridrich::F2L(Cube *cube){
    QStringList fewestMovesSequence;
    fewestMovesSequence.append("F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L F2 L ");
    for (int color1 = 0; color1 < 4; color1++) { //Solving the 4 pairs of cubies {{WHITE, RED, BLUE}, {RED BLUE}},
        //{{WHITE, BLUE, ORANGE}, {BLUE, ORANGE}}, {{WHITE, ORANGE, GREEN}, {ORANGE, GREEN}},
        //{{WHITE, GREEN, RED}, {GREEN, RED}}
        for (int color2 = 0; color2 < 4; ++color2) {
            if(color2 != color1){
                for (int color3 = 0; color3 < 4; ++color3){
                    if(color3 != color2 && color3 != color1){
                        for (int color4 = 0; color4 < 4; ++color4) {
                            if(color4 != color3 && color4 != color2 && color4 != color1){
                                Cube *tempCube = new Cube(*cube);
                                QStringList sequence;
                                sequence += F2LPair(tempCube, color1);
                                sequence += F2LPair(tempCube, color2);
                                sequence += F2LPair(tempCube, color3);
                                sequence += F2LPair(tempCube, color4);
                                if(sequence.join("").count(' ') < fewestMovesSequence.join("").count(' ')){
                                    fewestMovesSequence = sequence;
                                }
                                delete tempCube;
                                tempCube = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    cube->moveSequence(fewestMovesSequence.join(""), RED, YELLOW);
    return fewestMovesSequence.join("| ");
}

QString Fridrich::OLL2Look(Cube *cube){
    //copying the matrix
    color cubeMatrix[18][3];
    //this boolean checks if this step is already solved
    bool solved = true;
    color** tempMatrix = cube->getMatrix();
    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            cubeMatrix[x][y] = tempMatrix[x][y];
            //if x and y are on the YELLOW face and are not YELLOW, this step isn't solved yet
            if(x >= YELLOW * 3 && cubeMatrix[x][y] != YELLOW){
                solved = false;
            }
        }
        delete [] tempMatrix[x];
    }
    delete [] tempMatrix;
    //is it solved yet?
    if(solved){
        return "";
    }
    //counting the number of solved corners to check the state of the cube
    int nBCorner = (cubeMatrix[YELLOW * 3 + 0][0] == YELLOW) + (cubeMatrix[YELLOW * 3 + 2][2] == YELLOW) + (cubeMatrix[YELLOW * 3 + 0][2] == YELLOW) + (cubeMatrix[YELLOW * 3 + 2][0] == YELLOW);
    //the different cases can be seen from all four faces, so the program has to check them four
    for (int col = 0; col < 4; ++col) {
        //Face from which the cube is seen
        color face = (color) col;
        //The four YELLOW corners, seen from the face we are now evaluating (they aren't all used in the 2-look OLL)
        color topRight;
        color topLeft;
        color botRight;
        color botLeft;
        switch(face){
        case RED:
            topRight = cubeMatrix[YELLOW * 3][0];
            topLeft = cubeMatrix[YELLOW * 3 + 2][0];
            botRight = cubeMatrix[YELLOW * 3][2];
            botLeft = cubeMatrix[YELLOW * 3 + 2][2];
            break;
        case BLUE:
            topRight = cubeMatrix[YELLOW * 3 + 2][0];
            topLeft = cubeMatrix[YELLOW * 3 + 2][2];
            botRight = cubeMatrix[YELLOW * 3][0];
            botLeft = cubeMatrix[YELLOW * 3][2];
            break;
        case ORANGE:
            topRight = cubeMatrix[YELLOW * 3 + 2][2];
            topLeft = cubeMatrix[YELLOW * 3][2];
            botRight = cubeMatrix[YELLOW * 3 + 2][0];
            botLeft = cubeMatrix[YELLOW * 3][0];
            break;
        case GREEN:
            topRight = cubeMatrix[YELLOW * 3][2];
            topLeft = cubeMatrix[YELLOW * 3][0];
            botRight = cubeMatrix[YELLOW * 3 + 2][2];
            botLeft = cubeMatrix[YELLOW * 3 + 2][0];
            break;
        default:
            break;
        }
        //The YELLOW face edges are all solved and form a cross
        if (cubeMatrix[YELLOW * 3 + 1][0] == YELLOW && cubeMatrix[YELLOW * 3 + 1][2] == YELLOW && cubeMatrix[YELLOW * 3][1] == YELLOW && cubeMatrix[YELLOW * 3 + 2][1] == YELLOW) {
            //No corner solved yet
            if(nBCorner == 0) {
                //The YELLOW stickers on the corners are parallel
                if(cubeMatrix[face * 3 + 0][2] == YELLOW && cubeMatrix[face * 3 + 2][2] == YELLOW && cubeMatrix[((face + 2) % 4) * 3][2] == YELLOW && cubeMatrix[((face + 2) % 4) * 3 + 2][2] == YELLOW) {
                    return cube->moveSequence("R U2 R' U' R U R' U' R U' R'", face, YELLOW);
                }
                //The YELLOW stickers on the corners are not parallel
                else if (cubeMatrix[face * 3 + 2][2] == YELLOW && cubeMatrix[((face + 2) % 4) * 3][2] == YELLOW && cubeMatrix[((face + 3) % 4) * 3][2] == YELLOW && cubeMatrix[((face + 3) % 4) * 3 + 2][2] == YELLOW) {
                    return cube->moveSequence("L U' R' U L' U R U R' U R", face, YELLOW);
                }
            }
            //One corner solved
            else if (nBCorner == 1){
                //the bottom left corner on the YELLOW face points right
                if(botLeft == YELLOW && cubeMatrix[face * 3 + 2][2] != YELLOW) {
                    return cube->moveSequence("R' U2 R U R' U R", face, YELLOW);
                }
                //the bottom left corner on the YELLOW face points the evaluated face
                else if (botLeft == YELLOW && cubeMatrix[face * 3 + 2][2] == YELLOW) {
                    return cube->moveSequence("L' U R U' L U R'", face, YELLOW);
                }
            }
            //Two corners solved and diagonal
            else if((cubeMatrix[YELLOW * 3 + 0][0] == YELLOW && cubeMatrix[YELLOW * 3 + 2][2] == YELLOW) || (cubeMatrix[YELLOW * 3 + 2][0] == YELLOW && cubeMatrix[YELLOW * 3 + 0][2] == YELLOW)){
                if(cubeMatrix[((face + 1) % 4) * 3][2] == YELLOW) {
                    return cube->moveSequence("R' F' L' F R F' L F", face, YELLOW);
                }
            }
            //Two corners solved not diagonal
            else if(nBCorner == 2) {
                //YELLOW stickers are on the evaluated face
                if (cubeMatrix[face * 3][2] == YELLOW && cubeMatrix[face * 3 + 2][2] == YELLOW) {
                    return cube->moveSequence("R2 D R' U2 R D' R' U2 R'", face, YELLOW);
                }
                //one YELLOW sticker is on the evaluated face, and the other one is opposite to it
                else if (cubeMatrix[face * 3][2] == YELLOW) {
                    return cube->moveSequence("R' F' L F R F' L' F", face, YELLOW);
                }
            }
        }
        //No YELLOW sticker on the YELLOW face
        else if (cubeMatrix[YELLOW * 3 + 1][0] != YELLOW && cubeMatrix[YELLOW * 3 + 1][2] != YELLOW && cubeMatrix[YELLOW * 3 + 0][1] != YELLOW && cubeMatrix[YELLOW * 3 + 2][1] != YELLOW) {
            return cube->moveSequence("R U R' U R' F R F' U2 R' F R F'", face, YELLOW);
        }
        //the edge stickers form a YELLOW line on the YELLOW face
        else if ((cubeMatrix[YELLOW * 3 + 1][0] == YELLOW && cubeMatrix[YELLOW * 3 + 1][2] == YELLOW) || (cubeMatrix[YELLOW * 3 + 0][1] == YELLOW && cubeMatrix[YELLOW * 3 + 2][1] == YELLOW)) {
            //horizontal line
            if(cubeMatrix[face * 3 + 1][2] == YELLOW){
                return cube->moveSequence("L' B' L U' R' U R U' R' U R L' B L", face, YELLOW);
            }
        }
        //other cases
        else {
            //little L yellow left and up
            if (cubeMatrix[face * 3 + 1][2] == YELLOW && cubeMatrix[((face + 1) % 4) * 3 + 1][2] != YELLOW){
                return cube->moveSequence("F R U R' U' R U R' U' F'", face, YELLOW);
            }
        }
    }
    return "";
}

QString Fridrich::PLL2Look(Cube *c){
    //copying the matrix
    color cubeMatrix[18][3];
    //this boolean checks if this step is already solved
    bool solved = true;
    color** tempMatrix = c->getMatrix();
    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            cubeMatrix[x][y] = tempMatrix[x][y];
            //if the adjacent faces don't all have the same color, this step isn't solved yet
            if(x < 12 && x % 3 == 0 && y == 2 && (cubeMatrix[x][y] != cubeMatrix[x + 1][y] || cubeMatrix[x][y] != cubeMatrix[x + 2][y])){
                solved = false;
            }
        }
        delete [] tempMatrix[x];
    }
    delete [] tempMatrix;
    tempMatrix = 0;
    //is it solved yet?
    if (solved) {
        return "";
    }
    //Again, the different cases here can be seen from 4 different angles
    for (int col = 0; col < 4; ++col) {
        color face = (color) col;
        //2 corners are the same color on the evaluated face
        if (cubeMatrix[face * 3][2] == cubeMatrix[face * 3 + 2][2]) {
            //the 4 corners are solved relatively to each others
            if (cubeMatrix[((face + 2) % 4) * 3][2] == cubeMatrix[((face + 2) % 4) * 3 + 2][2]) {
                //1 edge is solved respectively to its adjacent corners
                if (cubeMatrix[face * 3 + 1][2] == cubeMatrix[face * 3][2]) {
                    //the edge on the right and YELLOW face must go on the left face
                    if (cubeMatrix[((face + 2) % 4) * 3][2] == cubeMatrix[((face + 1) % 4) * 3 + 1][2]) {
                        return c->moveSequence("R' U R' U' R' U' R' U R U R2", face, YELLOW);
                    }
                    //the edge on the left and YELLOW face must go on the right face
                    else if (cubeMatrix[((face + 2) % 4) * 3][2] == cubeMatrix[((face + 3) % 4) * 3 + 1][2]) {
                        return c->moveSequence("R2 U' R' U' R U R U R U' R", face, YELLOW);
                    }
                }
                //the 4 edges are on the face opposite to the one they belong to
                else if (cubeMatrix[face * 3 + 1][2] == cubeMatrix[((face + 2) % 4) * 3][2] && cubeMatrix[face * 3][2] == cubeMatrix[((face + 2) % 4) * 3  + 1][2]) {
                    return c->moveSequence("R2 L2 D R2 L2 U2 R2 L2 D R2 L2", face, YELLOW);
                }
                //the 4 edges are diagonally swapped
                else if (cubeMatrix[((face + 3) % 4) * 3 + 1][2] == cubeMatrix[face* 3][2] && cubeMatrix[((face + 3) % 4) * 3][2] == cubeMatrix[face * 3 + 1][2]) {
                    return c->moveSequence("R' U' R2 U R U R' U' R U R U' R U' R' U2", face, YELLOW);
                }
            }
            //2 corners are inverted
            else if ((int)cubeMatrix[((face + 2) % 4) * 3][2] == (cubeMatrix[((face + 2) % 4) * 3 + 2][2] + 2) % 4) {
                return c->moveSequence("R U R' U' R' F R2 U' R' U' R U R' F'", (color)((face + 3) % 4), YELLOW);
            }
        }
        //no corners correct
        else if ((int)cubeMatrix[face * 3][2] == (cubeMatrix[face * 3 + 2][2] + 2) % 4 && (int)cubeMatrix[((face + 1) % 4) * 3][2] == (cubeMatrix[((face + 1) % 4) * 3 + 2][2] + 2) % 4) {
            return c->moveSequence("R' U R' U' B' D B' D' B2 R' B' R B R", face, YELLOW);
        }
    }
    return "";
}
