#include "Fridrich.h"
#include <QString>
#include <qdebug.h>

QString Fridrich::solve(Cube *cube){
    QString step1 = cross(cube);
    QString step2 = F2L(cube);
    //    QString step3 = OLL2Look(cube);
    //    step3 += OLL2Look(cube); //2-look OLL
    //    QString step4 = PLL2Look(cube);
    //    step4 += PLL2Look(cube); //2-look PLL

    QString step3 = OLL(cube);
    QString step4 = PLL(cube);

    //positionning the solved YELLOW face
    step4 += cube->turnFace(YELLOW, RED - cube->locateCubie(RED, BLUE, YELLOW).at(0) / 3);
    step1.chop(1);
    step3.chop(1);
    step4.chop(1);
    //    qDebug() << "[" + step1 + "][" + step2 + "][" + step3 + "][" + step4 + "]";
    return "[" + step1 + "][" + step2 + "][" + step3 + "][" + step4 + "]";
}

void Fridrich::clean2Sequences(QString &sequenceLeft, QString &sequenceRight)
{
    if(!sequenceLeft.isEmpty() && !sequenceRight.isEmpty()){

        //        Cube::cleanSequence(sequenceLeft);
        //        Cube::cleanSequence(sequenceRight);

        //getting the moves
        QStringList movesLeft = sequenceLeft.split(' ');
        QStringList movesRight = sequenceRight.split(' ');
        //as each move is followed by a space, the movesLeft and right ends with an empty string. This doesn't matter for the right one but it does for the left one
        movesLeft.removeLast();
        //getting the needed moves
        QString left = movesLeft.last();
        QString right = movesRight.first();
        //if the last move of the left sequence and the first move of the right one are on the same face, we can simplify them into only one or zero move
        if(left.at(0) == right.at(0)){
            int nbQTurn = 2;
            if(right.length() > 1) {
                if(right[1]=='2') {
                    nbQTurn += 1;
                } else {
                    nbQTurn += 2;
                }
            }
            if (left.length() > 1) {
                if (left[1]=='2') {
                    nbQTurn += 1;
                } else {
                    nbQTurn += 2;
                }
            }
            nbQTurn %= 4;
            switch(nbQTurn){
            case 1:
                right = right[0];
                break;
            case 2:
                right = right[0] + "2";
                break;
            case 3:
                right = right[0] + "\'";
                break;
            default:
                right = "";
                break;
            }
            //removing the last left move because it will be merged into the right sequence
            movesLeft.removeLast();
            sequenceLeft = movesLeft.join(" ");
            sequenceLeft += " ";

            //if the new move is empty, we remove the old one, else we replace the old move with it
            if(right != ""){
                movesRight.replace(0, right);
            } else {
                movesRight.removeFirst();
            }
            sequenceRight = movesRight.join(" ");
        }
    }
}

void Fridrich::cleanSequence(QStringList &sequence){
    for(int i = 0; i < sequence.length() - 1; i++)
    {
        QString left = sequence.at(i);
        QString right;
        int j = 0;
        do{
            //if the sequence directly on the right of the left one is empty, we check the next one and so on
            right = sequence.at(i + ++j);
        }while(right.isEmpty() && i + j < sequence.length() - 1);

        //cleaning those sequences
        clean2Sequences(left, right);

        //and putting the new sequences into the stringlist
        sequence.replace(i, left);
        sequence.replace(i + j, right);
    }
}

QString Fridrich::fastestFridrichSolve(Cube *cube){
    //we only call the cross because it calls FOP
    QStringList CFOP = fastestCross(cube);

    cube->moveSequence(CFOP.join(""), RED, YELLOW);

    QString ret;
    for (int i = 0; i < 4; ++i) {
        qDebug() << QString::number(CFOP.at(i).count(' '));
        ret += QString::number(CFOP.at(i).count(' ')) + " ";
    }
    ret += CFOP.join("");
    qDebug() << ret;
    return ret;
}

QStringList Fridrich::fastestCross(Cube *cube){
    QStringList fewestMovesCFOPSequence;
    for (int i = 0; i < 100; ++i) {
        fewestMovesCFOPSequence += "U ";
    }
    //Solving the 4 cubies {WHITE, RED}, {WHITE, ORANGE}, {WHITE, GREEN}, {WHITE, BLUE} in every possible order
    for (int color1 = 0; color1 < 4; color1++) {
        for (int color2 = 0; color2 < 4; ++color2) {
            if(color2 != color1){
                for (int color3 = 0; color3 < 4; ++color3){
                    if(color3 != color2 && color3 != color1){
                        for (int color4 = 0; color4 < 4; ++color4) {
                            if(color4 != color3 && color4 != color2 && color4 != color1){
                                Cube *tempCube = new Cube(*cube);
                                QList<color> *solved = new QList<color>();
                                QString sequence = "";
                                sequence += crossEdge(tempCube, color1, solved);
                                sequence += crossEdge(tempCube, color2, solved);
                                sequence += crossEdge(tempCube, color3, solved);
                                sequence += crossEdge(tempCube, color4, solved);
                                sequence += tempCube->turnFace(WHITE, tempCube->locateCubie(WHITE, RED).at(2) / 3 - RED);
                                //For each possibility of doing the cross, we do FOP and then keep as a definitive sequence the fastest way of solving the cube
                                QStringList CFOP;
                                CFOP.append(sequence);
                                CFOP.append(fastestF2L(tempCube));
                                cleanSequence(CFOP);
                                if(CFOP.join("").count(' ') < fewestMovesCFOPSequence.join("").count(' ')){
                                    fewestMovesCFOPSequence = CFOP;
                                }
                                delete solved;
                                delete tempCube;
                                tempCube = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return fewestMovesCFOPSequence;
}

QStringList Fridrich::fastestF2L(Cube *cube){
    QStringList fewestMovesFOPSequence;
    for (int i = 0; i < 50; ++i) {
        fewestMovesFOPSequence += "F2 L ";
    }
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
                                QStringList FOPsequence;
                                QString F2Lsequence;
                                F2Lsequence += F2LPair(tempCube, color1);
                                F2Lsequence += F2LPair(tempCube, color2);
                                F2Lsequence += F2LPair(tempCube, color3);
                                F2Lsequence += F2LPair(tempCube, color4);
                                FOPsequence += F2Lsequence;
                                FOPsequence += OLL(tempCube);
                                QString PLLSequence = PLL(tempCube);
                                PLLSequence += tempCube->turnFace(YELLOW, RED - tempCube->locateCubie(RED, BLUE, YELLOW).at(0) / 3);
                                FOPsequence += PLLSequence;
                                //clean sequence
                                cleanSequence(FOPsequence);
                                if(FOPsequence.join("").count(' ') < fewestMovesFOPSequence.join("").count(' ')){
                                    fewestMovesFOPSequence = FOPsequence;
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
    return fewestMovesFOPSequence;
}

QString Fridrich::crossEdge(Cube *cube, int firstEdgeColor, QList<color> *solved)
{
    QString sequenceToSolve = "";
    color edgeColor = (color) firstEdgeColor;
    QList<int> cubieIndices = cube->locateCubie(WHITE, edgeColor); //Locating the cubie
    color faceWhiteSticker = (color) (cubieIndices.at(0) / 3); //face on which the WHITE sticker is
    color faceColorSticker = (color) (cubieIndices.at(2) / 3); //face on which the col sticker is

    //Depending on where the WHITE sticker is:
    switch(faceWhiteSticker){
    case YELLOW: //if it's on the YELLOW face
        if(solved->length() != 0){
            sequenceToSolve.append(cube->turnFace(YELLOW, ((edgeColor - solved->at(0)) + (cube->locateCubie(WHITE, solved->at(0)).at(2) / 3) - faceColorSticker)));
        }
        sequenceToSolve.append(cube->turnFace(cube->locateCubie(WHITE, edgeColor).at(2) / 3, 2));
        break;
    case WHITE: //if the WHITE sticker is on the WHITE face but col is not on the right face
        //if none on the white face are solved
        if(solved->length() == 0){
        }
        //if the cubie is correct relatively to the other edges we are trying to solve
        else if ((solved->at(0) - edgeColor + 4) % 4 == (cube->locateCubie(WHITE, solved->at(0)).at(2) / 3 - faceColorSticker + 4) % 4){
        } else {
            sequenceToSolve.append(cube->turnFace(faceColorSticker, 2));
            sequenceToSolve.append(cube->turnFace(YELLOW, ((edgeColor - solved->at(0)) + (cube->locateCubie(WHITE, solved->at(0)).at(2) / 3) - faceColorSticker)));
            sequenceToSolve.append(cube->turnFace(cube->locateCubie(WHITE, edgeColor).at(2) / 3, 2));
        }
        break;
    default: //if the WHITE sticker is not on the WHITE or YELLOW
        //the edge is on the middle layer
        if(faceColorSticker < 4){
            if(solved->length() != 0){
                sequenceToSolve.append(cube->turnFace(WHITE, ((edgeColor - solved->at(0)) + (cube->locateCubie(WHITE, solved->at(0)).at(2) / 3)) - faceColorSticker));
            }
            //if it's on the right of the face
            if(cubieIndices.at(2) > faceColorSticker * 3 + 1){
                sequenceToSolve.append(cube->turnFace(cube->locateCubie(WHITE, edgeColor).at(2) / 3, -1));
            } else {
                sequenceToSolve.append(cube->turnFace(cube->locateCubie(WHITE, edgeColor).at(2) / 3, 1));
            }
        }
        //the edge is on WHITE
        else if (faceColorSticker == WHITE){
            sequenceToSolve.append(cube->turnFace(faceWhiteSticker, 1));
            if(solved->length() != 0){
                sequenceToSolve.append(cube->turnFace(WHITE, ((edgeColor - solved->at(0)) + (cube->locateCubie(WHITE, solved->at(0)).at(2) / 3)) - cube->locateCubie(WHITE, edgeColor).at(2) / 3));
            }
            sequenceToSolve.append(cube->turnFace((faceWhiteSticker + 1) % 4, 1));
        }
        //the edge is on YELLOW
        else {
            if(solved->length() != 0){
                sequenceToSolve.append(cube->turnFace(YELLOW, ((edgeColor - solved->at(0)) + (cube->locateCubie(WHITE, solved->at(0)).at(2) / 3) - faceWhiteSticker)));
            }
            sequenceToSolve.append(cube->turnFace(cube->locateCubie(WHITE, edgeColor).at(0) / 3, -1));
            if(solved->length() != 0){
                sequenceToSolve.append(cube->turnFace(WHITE, ((edgeColor - solved->at(0)) + (cube->locateCubie(WHITE, solved->at(0)).at(2) / 3)) - cube->locateCubie(WHITE, edgeColor).at(2) / 3));
            }
            sequenceToSolve.append(cube->turnFace(cube->locateCubie(WHITE, edgeColor).at(2) / 3, 1));
        }
        break;
    }
    solved->append(edgeColor);

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
    while(faceWhiteSticker != WHITE  || faceFirstCorner != firstEdgeColor || faceFirstEdge!= firstEdgeColor || faceSecondEdge!= secondEdgeColor){
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
                                QList<color> *solved = new QList<color>();
                                QString sequence = "";
                                sequence += crossEdge(tempCube, color1, solved);
                                sequence += crossEdge(tempCube, color2, solved);
                                sequence += crossEdge(tempCube, color3, solved);
                                sequence += crossEdge(tempCube, color4, solved);
                                sequence += tempCube->turnFace(WHITE, tempCube->locateCubie(WHITE, RED).at(2) / 3 - RED);
                                if(sequence.count(' ') < fewestMovesSequence.count(' ')){
                                    fewestMovesSequence = sequence;
                                }
                                delete solved;
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
    for (int i = 0; i < fewestMovesSequence.length(); ++i) {
        fewestMovesSequence[i].chop(1);
    }
    return fewestMovesSequence.join("|");
}


QString Fridrich::PLL2Look(Cube *c){
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
                    return c->moveSequence("R' U' R2 U R U R' U' R U R U' R U' R'", face, YELLOW);
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

QString Fridrich::PLL(Cube *c){
    color cubeMatrix[18][3];
    //this boolean checks if this step is already solved
    bool solved = true;
    color** tempMatrix = c->getMatrix();
    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            cubeMatrix[x][y] = tempMatrix[x][y];
            //if the adjacent faces don't all have the same color, this step isn't solved yet
            if(x < 12 && x % 3 == 0 && y == 2 && (tempMatrix[x][y] != tempMatrix[x + 1][y] || tempMatrix[x][y] != tempMatrix[x + 2][y])){
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
                //the edge on the evaluated face is solved respectively to its adjacent corners
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
                    return c->moveSequence("R' U' R2 U R U R' U' R U R U' R U' R'", face, YELLOW);
                }
            }
            //2 corners are inverted
            else if ((int)cubeMatrix[((face + 2) % 4) * 3][2] == (cubeMatrix[((face + 2) % 4) * 3 + 2][2] + 2) % 4) {
                //edge from evaluated face on the opposite face
                if(cubeMatrix[face * 3][2] == cubeMatrix[((face + 2) % 4) * 3 + 1][2]){
                    //edge from opposite face on this face
                    if(cubeMatrix[face * 3 + 1][2] == cubeMatrix[((face + 1) % 4) * 3 + 2][2]){
                        return c->moveSequence("R U R' U' R' F R2 U' R' U' R U R' F'", (color)((face + 3) % 4), YELLOW);
                    }
                    //edge from opposite face on the left face
                    else if(cubeMatrix[((face + 1) % 4) * 3 + 1][2] == cubeMatrix[((face + 1) % 4) * 3 + 2][2]){
                        return c->moveSequence("B2 D' R U' R U R' D B2 L U' L'", face, YELLOW);
                    }
                    //edge from opposite face on the right face
                    else if(cubeMatrix[((face + 3) % 4) * 3 + 1][2] == cubeMatrix[((face + 3) % 4) * 3][2]){
                        return c->moveSequence("B2 D L' U L' U' L D' B2 R' U R", face, YELLOW);
                    }

                }
                //edge from evaluated face on the right
                else if(cubeMatrix[face * 3][2] == cubeMatrix[((face + 3) % 4) * 3  + 1][2]){
                    //edge from left on the evaluated face
                    if(cubeMatrix[face * 3 + 1][2] == cubeMatrix[((face + 1) % 4) * 3][2]){
                        return c->moveSequence("F2 R2 F L F' R2 F L' F", face, YELLOW);
                    }
                    //edge from opposite face on evaluated face
                    else if(cubeMatrix[face * 3 + 1][2] == cubeMatrix[((face + 1) % 4) * 3 + 2][2]){
                        return c->moveSequence("L U L' B2 D' R U' R' U R' D B2", (color)((face + 1) % 4), YELLOW);
                    }
                    //edge from right face on evaluated face
                    else if(cubeMatrix[face * 3 + 1][2] == cubeMatrix[((face + 3) % 4) * 3 + 2][2]){
                        return c->moveSequence("R' U2 R U2 R' F R U R' U' R' F' R2", face, YELLOW);
                    }
                }
                //edge from evaluated face on the left
                else if(cubeMatrix[face * 3][2] == cubeMatrix[((face + 1) % 4) * 3 + 1][2]){
                    //edge from left on the evaluated face
                    if(cubeMatrix[face * 3 + 1][2] == cubeMatrix[((face + 1) % 4) * 3][2]){
                        return c->moveSequence("L U2 L' U2 L F' L' U' L U L F L2", face, YELLOW);
                    }
                    //edge from opposite face on evaluated face
                    else if(cubeMatrix[face * 3 + 1][2] == cubeMatrix[((face + 1) % 4) * 3 + 2][2]){
                        return c->moveSequence("R' U' R B2 D L' U L U' L D' B2", (color)((face + 3) % 4), YELLOW);
                    }
                    //edge from right face on evaluated face
                    else if(cubeMatrix[face * 3 + 1][2] == cubeMatrix[((face + 3) % 4) * 3 + 2][2]){
                        return c->moveSequence("F2 L2 F' R' F L2 F' R F'", face, YELLOW);
                    }
                }
                //edge from evaluated face on the evaluated face
                else if(cubeMatrix[face * 3][2] == cubeMatrix[face * 3 + 1][2]){
                    //edge from opposite face on opposite face
                    if(cubeMatrix[((face + 2) % 4) * 3 + 1][2] == cubeMatrix[((face + 1) % 4) * 3 + 2][2]){
                        return c->moveSequence("U' R' U R U' R2 F' U' F U R F R' F' R2", (color)((face + 3) % 4), YELLOW);
                    }
                    //edge from opposite face on right face
                    else if(cubeMatrix[((face + 3) % 4) * 3 + 1][2] == cubeMatrix[((face + 3) % 4) * 3][2]){
                        return c->moveSequence("R U R' F' R U R' U' R' F R2 U' R'", (color)((face + 3) % 4), YELLOW);
                    }
                    //edge from opposite face on left face
                    else if(cubeMatrix[((face + 1) % 4) * 3 + 1][2] == cubeMatrix[((face + 1) % 4) * 3 + 2][2]){
                        return c->moveSequence("L' U' L F L' U' L U L F' L2 U L", (color)((face + 1) % 4), YELLOW);
                    }
                }
            }
        }
        //no corners correct relatively
        else if ((int)cubeMatrix[face * 3][2] == (cubeMatrix[face * 3 + 2][2] + 2) % 4 && (int)cubeMatrix[((face + 1) % 4) * 3][2] == (cubeMatrix[((face + 1) % 4) * 3 + 2][2] + 2) % 4) {
            //todo
            //edges from opposite faces are on opposite faces (e.g. RED and ORANGE opposite)
            if((int)cubeMatrix[face * 3 + 1][2] == (cubeMatrix[((face + 2) % 4) * 3 + 1][2] + 2) % 4
                    && (int)cubeMatrix[((face + 1) % 4) * 3 + 1][2] == (cubeMatrix[((face + 3) % 4) * 3 + 1][2] + 2) % 4){
                //the corners on evaluated face belong to it and same for opposite face
                if(cubeMatrix[((face + 1) % 4) * 3][2] == cubeMatrix[face * 3 + 1][2] && cubeMatrix[((face + 3) % 4) * 3 + 2][2] == cubeMatrix[face * 3 + 1][2]
                        && cubeMatrix[((face + 1) % 4) * 3 + 2][2] == cubeMatrix[((face + 2) % 4) * 3 + 1][2] && cubeMatrix[((face + 3) % 4) * 3][2] == cubeMatrix[((face + 2) % 4) * 3 + 1][2]){
                    return c->moveSequence("R' F' L' F R F' L F R' F' L F R F' L' F", face, YELLOW);
                }
                //edge and left corner from evaluated face identical
                else if(cubeMatrix[face * 3 + 1][2] == cubeMatrix[face * 3 + 2][2]){
                    return c->moveSequence("R' U R U' R' F' U' F R U R' F R' F' R U' R", face, YELLOW);
                }
                //edge and right corner from evaluated face identical
                else if(cubeMatrix[face * 3 + 1][2] == cubeMatrix[face * 3][2]){
                    return c->moveSequence("R U' R' U R B U B' R' U' R B' R B R' U R'", face, YELLOW);
                }
            }
            //evaluated face has left corner and edge similar
            else if(cubeMatrix[face * 3 + 1][2] == cubeMatrix[face * 3 + 2][2]){
                //edge from opposite face on right face
                if(cubeMatrix[((face + 3) % 4) * 3 + 1][2] == cubeMatrix[face * 3][2]){
                    return c->moveSequence("R' U R' U' B' D B' D' B2 R' B' R B R", face, YELLOW);
                }
                //edge from opposite face on left face
                else if(cubeMatrix[((face + 1) % 4) * 3 + 1][2] == cubeMatrix[face * 3][2]){
                    return c->moveSequence("F R U' R' U' R U R' F' R U R' U' R' F R F'", face, YELLOW);
                }
            }
        }
    }
    return "";
}

QString Fridrich::OLL(Cube *cube){
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
    //the different cases can be seen from all four faces, so the program has to check them four
    for (int col = 0; col < 4; ++col) {
        //Face from which the cube is seen
        color face = (color) col;
        //The four YELLOW corners, seen from the face we are now evaluating (they aren't all used in the 2-look OLL)
        bool topRight;
        bool topLeft;
        bool botRight;
        bool botLeft;
        //The four YELLOW edges
        bool top;
        bool bot;
        bool left;
        bool right;
        bool adjFront[3];
        bool adjRight[3];
        bool adjLeft[3];
        bool adjBack[3];
        for (int i = 0; i < 3; ++i) {
            adjFront[i] = cubeMatrix[face * 3 + 2 - i][2] == YELLOW;
            adjRight[i] = cubeMatrix[((face + 3) % 4) * 3 + 2 - i][2] == YELLOW;
            adjLeft[i] = cubeMatrix[((face + 1) % 4) * 3 + 2 - i][2] == YELLOW;
            adjBack[i] = cubeMatrix[((face + 2) % 4) * 3 + 2 - i][2] == YELLOW;
        }
        switch(face){
        case RED:
            topLeft = cubeMatrix[YELLOW * 3][0] == YELLOW;
            topRight = cubeMatrix[YELLOW * 3 + 2][0] == YELLOW;
            botLeft = cubeMatrix[YELLOW * 3][2] == YELLOW;
            botRight = cubeMatrix[YELLOW * 3 + 2][2] == YELLOW;
            top = cubeMatrix[YELLOW * 3 + 1][0] == YELLOW;
            bot = cubeMatrix[YELLOW * 3 + 1][2] == YELLOW;
            left = cubeMatrix[YELLOW * 3][1] == YELLOW;
            right = cubeMatrix[YELLOW * 3 + 2][1] == YELLOW;
            break;
        case BLUE:
            topLeft = cubeMatrix[YELLOW * 3 + 2][0] == YELLOW;
            topRight = cubeMatrix[YELLOW * 3 + 2][2] == YELLOW;
            botLeft = cubeMatrix[YELLOW * 3][0] == YELLOW;
            botRight = cubeMatrix[YELLOW * 3][2] == YELLOW;
            top = cubeMatrix[YELLOW * 3 + 2][1] == YELLOW;
            bot = cubeMatrix[YELLOW * 3][1] == YELLOW;
            left = cubeMatrix[YELLOW * 3 + 1][0] == YELLOW;
            right = cubeMatrix[YELLOW * 3 + 1][2] == YELLOW;
            break;
        case ORANGE:
            topLeft = cubeMatrix[YELLOW * 3 + 2][2] == YELLOW;
            topRight = cubeMatrix[YELLOW * 3][2] == YELLOW;
            botLeft = cubeMatrix[YELLOW * 3 + 2][0] == YELLOW;
            botRight = cubeMatrix[YELLOW * 3][0] == YELLOW;
            top = cubeMatrix[YELLOW * 3 + 1][2] == YELLOW;
            bot = cubeMatrix[YELLOW * 3 + 1][0] == YELLOW;
            left = cubeMatrix[YELLOW * 3 + 2][1] == YELLOW;
            right = cubeMatrix[YELLOW * 3][1] == YELLOW;
            break;
        case GREEN:
            topRight = cubeMatrix[YELLOW * 3][0] == YELLOW;
            topLeft = cubeMatrix[YELLOW * 3][2] == YELLOW;
            botRight = cubeMatrix[YELLOW * 3 + 2][0] == YELLOW;
            botLeft = cubeMatrix[YELLOW * 3 + 2][2] == YELLOW;
            top = cubeMatrix[YELLOW * 3][1] == YELLOW;
            bot = cubeMatrix[YELLOW * 3 + 2][1] == YELLOW;
            left = cubeMatrix[YELLOW * 3 + 1][2] == YELLOW;
            right = cubeMatrix[YELLOW * 3 + 1][0] == YELLOW;
            break;
        default:
            break;
        }
        //counting the number of solved corners to check the state of the cube
        int nbCorner = (topRight) + (topLeft) + (botRight) + (botLeft);
        int nbEdge = (top) + (bot) + (left) + (right);
        //The YELLOW face edges are all solved and form a cross
        if (nbEdge == 4) {
            //No corner solved yet
            if(nbCorner == 0) {
                //The YELLOW stickers on the corners are parallel
                if(adjFront[0] && adjFront[2] && adjBack[0] && adjBack[2]) {
                    return cube->moveSequence("R U2 R' U' R U R' U' R U' R'", face, YELLOW);
                }
                //The YELLOW stickers on the corners are not parallel
                else if (adjFront[0] && adjBack[2] && adjRight[0] && adjRight[2]) {
                    return cube->moveSequence("L U' R' U L' U R U R' U R", face, YELLOW);
                }
            }
            //One corner solved
            else if (nbCorner == 1){
                //the bottom left corner on the YELLOW face points outwards
                if(botRight && adjFront[0]) {
                    return cube->moveSequence("L' U R U' L U R'", face, YELLOW);
                }
                //the bottom left corner on the YELLOW face points the evaluated face
                else if (botRight && adjLeft[2]) {
                    return cube->moveSequence("R' U2 R U R' U R", face, YELLOW);
                }
            }
            //Two corners solved and diagonal
            else if((botLeft && topRight) || (botRight && topLeft)){
                if(adjLeft[2]) {
                    return cube->moveSequence("R' F' L' F R F' L F", face, YELLOW);
                }
            }
            //Two corners solved not diagonal
            else if(nbCorner == 2) {
                //YELLOW stickers are on the evaluated face
                if (adjFront[0] && adjFront[2]) {
                    return cube->moveSequence("R2 D R' U2 R D' R' U2 R'", face, YELLOW);
                }
                //one YELLOW sticker is on the evaluated face, and the other one is opposite to it
                else if (adjFront[2]) {
                    return cube->moveSequence("R' F' L F R F' L' F", face, YELLOW);
                }
            }
        }
        //Dots
        else if (nbEdge == 0) {
            switch(nbCorner){
            case 0:
                if(adjLeft[0] && adjLeft[2] && adjRight[0] && adjRight[2]){
                    return cube->moveSequence("R U B' R B R2 U' R' F R F'", face, YELLOW);
                } else if (adjFront[0] && adjFront[2] && adjLeft[0] && adjRight[2]){
                    return cube->moveSequence("R' F R F' U2 R' F R F2 U2 F", face, YELLOW);
                }
                break;
            case 1:
                if(botRight){
                    if(adjFront[0]){
                        QString s = cube->moveSequence("R' U2", (color)((face + 1) % 4), YELLOW); //R' U2 x R' U R U' y R' U' R' U R' F
                        s += cube->moveSequence("R' U R U'", WHITE, (color)((face + 1) % 4));
                        s += cube->moveSequence("R' U' R' U R' F", face, (color)((face + 1) % 4));
                        return s;
                    }else if(adjLeft[2]){
                        return cube->moveSequence("F' B2 L B' L F U2 F' L B' F", face, YELLOW); //y L' R2 B R' B L U2' L' B M'
                    }
                }
                break;
            case 2:
                if(botLeft && botRight && adjBack[0] && adjBack[2]){
                    QString s = cube->moveSequence("F R U R' U", face, YELLOW);
                    s += cube->moveSequence("R' U2 R' F R F'", (color)((face + 1) % 4), YELLOW);
                    return s;
                } else if(topLeft && topRight && adjLeft[2] && adjRight[0]){
                    QString s = cube->moveSequence("R' U2 F R U R' U'", face, YELLOW); //R' U2 F R U R' U' y' R2 U2 x' R U
                    s += cube->moveSequence("R2 U2", (color)((face + 1) % 4), YELLOW);
                    s += cube->moveSequence("R U", YELLOW, (color)((face + 3) % 4));
                    return s;
                } else if(topLeft && botRight && adjLeft[2]){
                    return cube->moveSequence("R U R' U R' F R F' U2 R' F R F'", face, YELLOW);
                }
                break;
            case 4:
                return cube->moveSequence("R2 U2 R' F2 U2 R2 F' R2 U2 F2 R U2 R2 U'", face, YELLOW);
                break;
            }
        }
        //all corners
        else if (nbCorner == 4){
            if(left && right){
                return cube->moveSequence("L' R U R' U' L R' F R F'", face, YELLOW);
            }
            if(left && bot){
                return cube->moveSequence("L' U2 L U F R U2 R' U' F'", face, YELLOW);
            }
        }
        //the edge stickers form a YELLOW line on the YELLOW face
        else if ((left && right) || (top && bot)) {
            //lines
            if(nbCorner == 0){
                //vertical
                if(top && adjRight[0] && adjRight[2]){
                    if(adjLeft[0] && adjLeft[2]){
                        QString s = cube->moveSequence("R U'", face, YELLOW); //R U' y R2 D R' U2 R D' R2 d R'
                        s += cube->moveSequence("R2 D R' U2 R D' R2 U F'", (color)((face + 3) % 4), YELLOW);
                        return s;
                    } else if(adjFront[0] && adjBack[2]){
                        return cube->moveSequence("R' U' F' U F' L F L' F R", face, YELLOW);
                    }
                } else if(left && adjRight[0] && adjRight[2]){
                    if(adjLeft[0] && adjLeft[2]){
                        return cube->moveSequence("L' B' L U' R' U R U' R' U R L' B L", face, YELLOW);
                    } else if(adjFront[0] && adjBack[2]){
                        return cube->moveSequence("F U R U' R' U R U' R' F'", face, YELLOW);
                    }
                }
            }
            //Big Ls
            if(nbCorner == 1 && left){
                if(botRight){
                    if(adjFront[0]){
                        return cube->moveSequence("R' F R U R' F' R F U' F'", face, YELLOW);
                    }
                    if(adjLeft[2]){
                        return cube->moveSequence("L' B' L R' U' R U L' B L", face, YELLOW);
                    }
                } else if(botLeft){
                    if(adjRight[0]){
                        return cube->moveSequence("R B R' L U L' U' R B' R'", face, YELLOW);
                    }
                    if(adjFront[2]){
                        return cube->moveSequence("L F' L' U' L F L' F' U F", face, YELLOW);
                    }
                }
            }
            //Ts
            if(left && botRight && topRight){
                if(adjLeft[0] && adjLeft[2]){
                    return cube->moveSequence("F R U R' U' F'", face, YELLOW);
                } else if(adjFront[0] && adjBack[2]){
                    return cube->moveSequence("R U R' U' R' F R F'", face, YELLOW);
                }
            }
            //Zs
            if((botRight && topLeft) || (botLeft && topRight)){
                if(left && topLeft && adjLeft[2] && adjBack[0]){
                    return cube->moveSequence("R' F R U R' U' F' U R", face, YELLOW);
                } else if(left && botLeft && adjRight[0] && adjBack[2]){
                    return cube->moveSequence("L F' L' U' L U F U' L'", face, YELLOW);
                }
            }
            //Cs
            if((topLeft && botLeft) || (botLeft && botRight)){
                if (bot && topLeft && botLeft && adjRight[0] && adjRight[2]){
                    QString s = cube->moveSequence("R U", face, YELLOW); //R U x' R U' R' U x U' R'
                    s += cube->moveSequence("R U' R' U", YELLOW, (color)((face + 2) % 4));
                    s += cube->moveSequence("U' R'", face, YELLOW);
                    return s;
                } else if (left && botLeft && botRight && adjRight[2] && adjLeft[0]){
                    QString s = cube->moveSequence("R U R' U'", face, YELLOW); //R U R' U' x D' R' U R E'
                    s += cube->moveSequence("D' R' U R D U'", WHITE, face);
                    return s;
                }
            }
        }
        //little Ls
        else if ((top && left) || (top && right) || (bot && left) || (bot && right)){
            if(nbCorner == 0){
                if(left && top){
                    //2 cases
                    if(adjLeft[0] && adjLeft[2] && adjBack[0] && adjFront[2]){
                        return cube->moveSequence("F R U R' U' R U R' U' F'", face, YELLOW);
                    } else if (adjFront[0] && adjFront[2] && adjBack[0] && adjBack[2]){
                        return cube->moveSequence("L F' L' F U2 L2 B L B' L", face, YELLOW);
                    }
                }
                if(top && right){
                    //3 cases
                    if(adjRight[0] && adjRight[2] && adjBack[2] && adjFront[0]){
                        return cube->moveSequence("F' L' U' L U L' U' L U F", face, YELLOW);
                    }
                    if(adjLeft[0] && adjLeft[2] && adjFront[2] && adjBack[0]){
                        return cube->moveSequence("R' F R' F' R2 U2 B' R B R'", face, YELLOW);
                    }
                    if(adjFront[0] && adjFront[2] && adjBack[0] && adjBack[2]){
                        return cube->moveSequence("R' F R F' U2 R2 B' R' B R'", face, YELLOW);
                    }
                }
                if(bot && right){
                    //1 case
                    if(adjLeft[0] && adjLeft[2] && adjFront[2] && adjBack[0]){
                        QString s = cube->moveSequence("L U'", face, YELLOW); //L U' y' R' U2' R' U R U' R U2 R d' L'
                        s += cube->moveSequence("R' U2 R' U R U' R U2 R U' F'", (color)((face + 1) % 4), YELLOW);
                        return s;
                    }
                }
            } else {
                if(left){
                    //8 cases + Ps/Ws
                    if(top){
                        //4 cases + Ps
                        if(botLeft && adjFront[2] && adjRight[2] && adjBack[2]){
                            return cube->moveSequence("L F R' F R F2 L'", face, YELLOW);
                        }
                        if(botLeft && botRight && adjBack[0] && adjBack[2]){
                            return cube->moveSequence("U' R U2 R' U' R U' R2 F' U' F U R", face, YELLOW);
                        }
                        if(botRight && adjBack[0] && adjLeft[0] && adjFront[0]){
                            QString s = cube->moveSequence("R' U' R", face, YELLOW); //R' U' R y' x' R U' R' F R U R'
                            s += cube->moveSequence("R U' R' F R U R'", YELLOW, (color)((face + 3) % 4));
                            return s;
                        }
                        if(botRight && topLeft && adjFront[0] && adjRight[2]){
                            return cube->moveSequence("F R' F' R U R U' R'", face, YELLOW);
                        }
                        //Ps
                        if(topLeft && botLeft && adjFront[2] && adjBack[0]){
                            return cube->moveSequence("L U F' U' L' U L F L'", face, YELLOW);
                        }
                        if(topLeft && botLeft && adjRight[0] && adjRight[2]){
                            return cube->moveSequence("F U R U' R' F'", face, YELLOW);
                        }
                    }
                    if(bot){
                        //4 cases + Ws
                        if(topLeft && topRight && adjLeft[2] && adjRight[0]){
                            QString s = cube->moveSequence("U' R U' R2 F", YELLOW, (color)((face + 2) % 4)); //x' U' R U' R2' F x R U R' U' R B2
                            s += cube->moveSequence("R U R' U' R B2", face, YELLOW);
                            return s;
                        }
                        if(botRight && adjBack[0] && adjLeft[0] && adjBack[0]){
                            QString s = cube->moveSequence("U2 L", face, YELLOW); //U2 r R2' U' R U' R' U2 R U' M
                            s += cube->moveSequence("R2 U' R U' R' U2 R U' L' R", WHITE, face);
                            return s;
                        }
                        if(topRight && adjLeft[2] && adjBack[2] && adjFront[2]){
                            QString s = cube->moveSequence("R U R'", face, YELLOW); //R U R' y R' F R U' R' F' R
                            s += cube->moveSequence("R' F R U' R' F' R", (color)((face + 3) % 4), YELLOW);
                            return s;
                        }
                        if(topLeft && adjFront[0] && adjBack[0] && adjRight[0]){
                            return cube->moveSequence("L' B' L U' R' U R L' B L", face, YELLOW);
                        }
                        //Ws
                        if(topLeft && botRight && adjFront[0] && adjRight[2]){
                            return cube->moveSequence("R' U' R U' R' U R U R B' R' B", face, YELLOW);
                        }
                    }
                }
                if(right){
                    //6 cases + Ps/Ws
                    if(top){
                        //3 cases + Ps
                        if(botLeft && botRight && adjBack[0] && adjBack[2]){
                            return cube->moveSequence("U' R' U2 R U R' U R2 B U B' U' R'", face, YELLOW);
                        }
                        if(botLeft && topRight && adjRight[0] && adjBack[2]){
                            QString s = cube->moveSequence("R' U2 R", face, YELLOW); //R' U2 l R U' R' U l' U2 R
                            s += cube->moveSequence("R U' R' U R'", YELLOW, (color)((face + 2) % 4));
                            s += cube->moveSequence("U2 R", face, YELLOW);
                            return s;
                        }
                        if(topRight && adjFront[0] && adjRight[0] && adjLeft[0]){
                            return cube->moveSequence("L U2 R' U' R U' L'", WHITE, face);
                        }
                        //Ps
                        if(topRight && botRight && adjFront[0] && adjBack[2]){
                            return cube->moveSequence("R' U' F U R U' R' F' R", face, YELLOW);
                        }
                        if(topRight && botRight && adjLeft[0] && adjLeft[2]){
                            return cube->moveSequence("F' U' L' U L F", face, YELLOW);
                        }
                    }
                    if(bot){
                        //3 cases + Ws
                        if(botLeft && adjFront[2] && adjBack[2] && adjRight[2]){
                            QString s = cube->moveSequence("U2 R'", face, YELLOW); //U2 l' L2 U L' U L U2 L' U M
                            s += cube->moveSequence("L2 U L' U L U2 L' U L' R", WHITE, face);
                            return s;
                        }
                        if(topRight && topLeft && adjLeft[2] && adjRight[0]){
                            return cube->moveSequence("R2 U R' B' R U' R2 U R B R'", face, YELLOW); //R2' U R' B R U' R2' U l U l'
                        }
                        if(botRight && adjLeft[2] && adjBack[2] && adjRight[2]){
                            return cube->moveSequence("L' U2 R U R' U L", YELLOW, (color)((face + 2) % 4));
                        }
                        //Ws
                        if(botLeft && topRight && adjFront[2] && adjLeft[0]){
                            return cube->moveSequence("L U L' U L U' L' U' L' B L B'", face, YELLOW);
                        }
                    }
                }

            }
        }
    }
    return "";
}
