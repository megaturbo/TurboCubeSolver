#include "Cube.h"
#include <QString>
#include <iostream>
#include <qdebug.h>
#include <QList>
#include <qdebug.h>
#include <QGlobal.h>
#include <QTime>

Cube::~Cube(){

}

QString Cube::validateCube(){
    //Defining legal cubies and what the location is on the solved cube
    QList<QList<color> > cubies;
    QList<QList<int> > loc;

    //CORNERS
    cubies.append(QList<color>()<<WHITE<<RED<<BLUE);
    loc.append(QList<int>()<<14<<2<<2<<0<<3<<0);
    cubies.append(QList<color>()<<WHITE<<BLUE<<ORANGE);
    loc.append(QList<int>()<<14<<0<<5<<0<<6<<0);
    cubies.append(QList<color>()<<WHITE<<ORANGE<<GREEN);
    loc.append(QList<int>()<<12<<0<<8<<0<<9<<0);
    cubies.append(QList<color>()<<WHITE<<GREEN<<RED);
    loc.append(QList<int>()<<12<<2<<11<<0<<0<<0);

    cubies.append(QList<color>()<<YELLOW<<RED<<GREEN);
    loc.append(QList<int>()<<17<<2<<0<<2<<11<<2);
    cubies.append(QList<color>()<<YELLOW<<GREEN<<ORANGE);
    loc.append(QList<int>()<<17<<0<<9<<2<<8<<2);
    cubies.append(QList<color>()<<YELLOW<<ORANGE<<BLUE);
    loc.append(QList<int>()<<15<<0<<6<<2<<5<<2);
    cubies.append(QList<color>()<<YELLOW<<BLUE<<RED);
    loc.append(QList<int>()<<15<<2<<3<<2<<2<<2);

    //EDGES
    cubies.append(QList<color>()<<WHITE<<RED);
    loc.append(QList<int>()<<13<<2<<1<<0);
    cubies.append(QList<color>()<<WHITE<<BLUE);
    loc.append(QList<int>()<<14<<1<<4<<0);
    cubies.append(QList<color>()<<WHITE<<ORANGE);
    loc.append(QList<int>()<<13<<0<<7<<0);
    cubies.append(QList<color>()<<WHITE<<GREEN);
    loc.append(QList<int>()<<12<<1<<10<<0);

    cubies.append(QList<color>()<<YELLOW<<RED);
    loc.append(QList<int>()<<16<<2<<1<<2);
    cubies.append(QList<color>()<<YELLOW<<GREEN);
    loc.append(QList<int>()<<17<<1<<10<<2);
    cubies.append(QList<color>()<<YELLOW<<ORANGE);
    loc.append(QList<int>()<<16<<0<<7<<2);
    cubies.append(QList<color>()<<YELLOW<<BLUE);
    loc.append(QList<int>()<<15<<1<<4<<2);

    cubies.append(QList<color>()<<RED<<BLUE);
    loc.append(QList<int>()<<2<<1<<3<<1);
    cubies.append(QList<color>()<<BLUE<<ORANGE);
    loc.append(QList<int>()<<5<<1<<6<<1);
    cubies.append(QList<color>()<<ORANGE<<GREEN);
    loc.append(QList<int>()<<8<<1<<9<<1);
    cubies.append(QList<color>()<<GREEN<<RED);
    loc.append(QList<int>()<<11<<1<<0<<1);

    //copying the cube to not affect it by swapping cubies
    Cube copy(matCube);

    int nbSwaps = 0;

    //if any one of the legal cubies doesn't exist on the cube, then it is not valid
    //CORNERS
    for (int i = 0; i < 8; ++i) {
        //locating the cubie, if it does not exist, then the cube is impossible
        QList<int> indices = copy.locateCubie(cubies.at(i)[0], cubies.at(i)[1], cubies.at(i)[2]);
        if(indices.length() < 1){
            QString message = "The cubie " + toString(cubies.at(i)[0]) + ", " + toString(cubies.at(i)[1]) + ", " + toString(cubies.at(i)[2]) + " does not exist on the cube.";
            return message;
        }
        //Swapping corners to count parity if the cubie is not at its solved position
        if(!copy.cubieEqual(loc.at(i), cubies.at(i)[0], cubies.at(i)[1], cubies.at(i)[2])){
            nbSwaps++;
            for (int j = 0; j < 3; ++j) {
                color save = copy.matCube[loc.at(i)[2 * j]][loc.at(i)[2 * j + 1]];
                copy.matCube[loc.at(i)[2 * j]][loc.at(i)[2 * j + 1]] = copy.matCube[indices[2 * j]][indices[2 * j + 1]];
                copy.matCube[indices[2 * j]][indices[2 * j + 1]] = save;
            }
        }
    }

    //EDGES
    for (int i = 8; i < 20; ++i) {
        //locating the cubie, if it does not exist, then the cube is impossible
        QList<int> indices = copy.locateCubie(cubies.at(i)[0], cubies.at(i)[1]);
        if(indices.length() < 1){
            QString message = "The cubie " + toString(cubies.at(i)[0]) + ", " + toString(cubies.at(i)[1]) + " is missing.";
            return message;
        }
        //Swapping edges to count parity if the cubie is not at its solved position
        if(!copy.cubieEqual(loc.at(i), cubies.at(i)[0], cubies.at(i)[1])){
            nbSwaps++;
            for (int j = 0; j < 2; ++j) {
                color save = copy.matCube[loc.at(i)[2 * j]][loc.at(i)[2 * j + 1]];
                copy.matCube[loc.at(i)[2 * j]][loc.at(i)[2 * j + 1]] = copy.matCube[indices[2 * j]][indices[2 * j + 1]];
                copy.matCube[indices[2 * j]][indices[2 * j + 1]] = save;
            }
        }
    }

    //parity check
    if(nbSwaps % 2 == 1){
        return "The parity on the cube is wrong. The number of swaps on the cube cannot be odd.";
    }

    //rotating corners by pairs, if the last corner is not correctly oriented, then the cube isn't legal
    for (int i = 0; i < 7; ++i) {
        while(copy.matCube[loc.at(i)[0]][loc.at(i)[1]] != cubies.at(i)[0]){
            color save = copy.matCube[loc.at(i)[0]][loc.at(i)[1]];
            copy.matCube[loc.at(i)[0]][loc.at(i)[1]] = copy.matCube[loc.at(i)[2]][loc.at(i)[3]];
            copy.matCube[loc.at(i)[2]][loc.at(i)[3]] = copy.matCube[loc.at(i)[4]][loc.at(i)[5]];
            copy.matCube[loc.at(i)[4]][loc.at(i)[5]] = save;
            save = copy.matCube[loc.at(i + 1)[4]][loc.at(i + 1)[5]];
            copy.matCube[loc.at(i + 1)[4]][loc.at(i + 1)[5]] = copy.matCube[loc.at(i + 1)[2]][loc.at(i + 1)[3]];
            copy.matCube[loc.at(i + 1)[2]][loc.at(i + 1)[3]] = copy.matCube[loc.at(i + 1)[0]][loc.at(i + 1)[1]];
            copy.matCube[loc.at(i + 1)[0]][loc.at(i + 1)[1]] = save;
        }
    }

    //if the last corner is flipped
    if(copy.matCube[loc.at(7)[0]][loc.at(7)[1]] != YELLOW){
        return "The orientation of the corner cubies is wrong.";
    }

    //flipping the edges
    for (int i = 8; i < 19; ++i) {
        if(copy.matCube[loc.at(i)[0]][loc.at(i)[1]] != cubies.at(i)[0]){
            color save = copy.matCube[loc.at(i)[0]][loc.at(i)[1]];
            copy.matCube[loc.at(i)[0]][loc.at(i)[1]] = copy.matCube[loc.at(i)[2]][loc.at(i)[3]];
            copy.matCube[loc.at(i)[2]][loc.at(i)[3]] = save;
            save = copy.matCube[loc.at(i + 1)[2]][loc.at(i + 1)[3]];
            copy.matCube[loc.at(i + 1)[2]][loc.at(i + 1)[3]] = copy.matCube[loc.at(i + 1)[0]][loc.at(i + 1)[1]];
            copy.matCube[loc.at(i + 1)[0]][loc.at(i + 1)[1]] = save;
        }
    }

    //if the last edge is flipped
    if(copy.matCube[loc.at(19)[0]][loc.at(19)[1]] != GREEN){
        return "The orientation of the edge cubies is wrong.";
    }

    //checking the corners stickers
    for (int i = 0; i < 17; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(copy.matCube[i][j] != (color)(i / 3)){
                return "All cubies exist on the cube but one or more has its stickers inverted.";
            }
        }
    }

    return "true";
}

void Cube::qDebugDisplay() {
    QString s = "\n";
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 18; x++) {
            switch(matCube[x][y]) {
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
            case WHITE:
                s += "W ";
                break;
            case YELLOW:
                s += "Y ";
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

void Cube::setMatrix(color matrix[18][3])
{
    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            matCube[x][y] = matrix[x][y];
        }
    }
}

void Cube::setMatrix(int matrix[18][3])
{
    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            matCube[x][y] =(color) matrix[x][y];
        }
    }
}

void Cube::setSticker(int x, int y, int c)
{
    setSticker(x, y, (color)c);
}

void Cube::setSticker(int x, int y, color c)
{
    matCube[x][y] = c;
}

color** Cube::getFaceMatrix(QChar face) const{

    int firstID;
    color** faceMatrix = new color*[3];

    switch(face.toLatin1())
    {
        case 'F':
            firstID = 0;
            break;
        case 'R':
            firstID = 3;
            break;
        case 'B':
            firstID = 6;
            break;
        case 'L':
            firstID = 9;
            break;
        case 'U':
            firstID = 12;
            break;
        case 'D':
            firstID = 15;
            break;
    }

    for(int x = firstID; x < firstID + 3; x++)
    {
//        faceMatrix = new color[3];
        for(int y = 0; y < 3; y++)
        {
            faceMatrix[x][y] = matCube[x][y];
        }
    }

    return faceMatrix;

}

//don't forget to delete the matrix returned after use
color** Cube::getMatrix() const{
    color** mat = new color*[18];
    for (int i = 0; i < 18; ++i) {
        mat[i] = new color[3];
        for (int j = 0; j < 3; ++j) {
            mat[i][j] = matCube[i][j];
        }
    }
    return mat;
}

Cube::Cube(color matrix[18][3])
{
    setMatrix(matrix);
}

Cube::Cube(int matrix[18][3])
{
    setMatrix(matrix);
}

Cube::Cube(const Cube &c){
    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            matCube[x][y] = c.matCube[x][y];
        }
    }
}

//returns indices of the cubie's stickers
//ordered by colors
QList<int> Cube::locateCubie(color firstColor, color secondColor) {
    //storing the stickers indices on the matrix in this list
    QList<int> indices;
    //we're testing 3 edge cubies on 4 faces, it will cover the entire cube
    for (int face = 0; face < 4; ++face) {
        indices = linkedStickers(face * 3 + 1, 0);
        if (cubieEqual(indices, firstColor, secondColor)) {
            if (matCube[indices.at(0)][indices.at(1)] == firstColor) {
                return indices;
            } else {
                QList<int> sortedIndices;
                sortedIndices += indices.at(2);
                sortedIndices += indices.at(3);
                sortedIndices += indices.at(0);
                sortedIndices += indices.at(1);
                return sortedIndices;
            }
        }
        indices = linkedStickers(face * 3 + 1, 2);
        if (cubieEqual(indices, firstColor, secondColor)) {
            if (matCube[indices.at(0)][indices.at(1)] == firstColor) {
                return indices;
            } else {
                QList<int> sortedIndices;
                sortedIndices += indices.at(2);
                sortedIndices += indices.at(3);
                sortedIndices += indices.at(0);
                sortedIndices += indices.at(1);
                return sortedIndices;
            }
        }
        indices = linkedStickers(face * 3, 1);
        if (cubieEqual(indices, firstColor, secondColor)) {
            if (matCube[indices.at(0)][indices.at(1)] == firstColor) {
                return indices;
            } else {
                QList<int> sortedIndices;
                sortedIndices += indices.at(2);
                sortedIndices += indices.at(3);
                sortedIndices += indices.at(0);
                sortedIndices += indices.at(1);
                return sortedIndices;
            }
        }
    }
    //if we did not find the given cubie, we return an empty QList
    indices.clear();
    return indices;
}

//returns indices of the cubie's stickers
//ordered by colors
QList<int> Cube::locateCubie(color firstColor, color secondColor, color thirdColor) {
    QList<int> indices;
    //we're testing 2 corner cubies on 4 faces, it will cover the entire cube
    for (int face = 0; face < 4; ++face) {
        //checking first corner
        //getting the indices of this corner
        indices = linkedStickers(face * 3, 0);
        //if this corner is the one we are looking for, we return the indices of its stickers
        if(cubieEqual(indices, firstColor, secondColor, thirdColor)) {
            QList<int> sortedIndices;
            for (int i = 0; i < 6; i+=2) {
                if (matCube[indices.at(i)][indices.at(i + 1)] == firstColor) {
                    sortedIndices += indices.at(i);
                    sortedIndices += indices.at(i + 1);
                }
            }
            for (int i = 0; i < 6; i+=2) {
                if (matCube[indices.at(i)][indices.at(i + 1)] == secondColor) {
                    sortedIndices += indices.at(i);
                    sortedIndices += indices.at(i + 1);
                }
            }
            for (int i = 0; i < 6; i+=2) {
                if (matCube[indices.at(i)][indices.at(i + 1)] == thirdColor) {
                    sortedIndices += indices.at(i);
                    sortedIndices += indices.at(i + 1);
                }
            }
            return sortedIndices;
        }
        //checking second corner
        indices = linkedStickers(face * 3, 2);
        if(cubieEqual(indices, firstColor, secondColor, thirdColor)) {
            QList<int> sortedIndices;
            for (int i = 0; i < 6; i+=2) {
                if (matCube[indices.at(i)][indices.at(i + 1)] == firstColor) {
                    sortedIndices += indices.at(i);
                    sortedIndices += indices.at(i + 1);
                }
            }
            for (int i = 0; i < 6; i+=2) {
                if (matCube[indices.at(i)][indices.at(i + 1)] == secondColor) {
                    sortedIndices += indices.at(i);
                    sortedIndices += indices.at(i + 1);
                }
            }
            for (int i = 0; i < 6; i+=2) {
                if (matCube[indices.at(i)][indices.at(i + 1)] == thirdColor) {
                    sortedIndices += indices.at(i);
                    sortedIndices += indices.at(i + 1);
                }
            }
            return sortedIndices;
        }
    }
    //if we did not find the given cubie, we return an empty QList
    indices.clear();
    return indices;
}

//return the indices of the stickers of the cubie containing the sticker at (i, j)
QList<int> Cube::linkedStickers(int i, int j) {
    //we add the indices to this qlist and we will return it at the end of the method
    QList<int> indices;
    //not on the cube
    if(i < 0 || i > 17 || j < 0 || j > 3) {
        return indices;
    } else {
        //indices on the face
        int x = i % 3;
        int y = j;
        //face on which the (i, j) sticker is
        color face = (color) (i /3);
        indices += i;
        indices += j;
        //if x = y = 1, it's a center
        if (x == 1 && y == 1) {
            return indices;
        }
        //if face is RED, BLUE, ORANGE OR GREEN
        else if (face < 4) {
            //if the sticker is adjacent to another RED, BLUE, ORANGE OR GREEN face
            //if the sticker is on the left of the face, return the sticker to the left of it
            if(x == 0){
                indices += (i + 11) % 12;
                indices += y;
            }
            //if the sticker is on the right of the face, return the sticker to the right of it
            if (x == 2) {
                indices += (i + 1) % 12;
                indices += y;
            }
            //if the sticker is adjacent to the WHITE face
            if (y == 0){
                switch(face){
                case RED:
                    indices += WHITE * 3 + x;
                    indices += 2;
                    break;
                case BLUE:
                    indices += WHITE * 3 + 2;
                    indices += 2 - x;
                    break;
                case ORANGE:
                    indices += WHITE * 3 + 2 - x;
                    indices += 0;
                    break;
                case GREEN:
                    indices += WHITE * 3;
                    indices += x;
                    break;
                default:
                    //should not happen
                    break;
                }
            }
            //if the sticker is adjacent to the YELLOW face
            if (y == 2){
                switch(face){
                case RED:
                    indices += YELLOW * 3 + 2 - x;
                    indices += 2;
                    break;
                case BLUE:
                    indices += YELLOW * 3;
                    indices += 2 - x;
                    break;
                case ORANGE:
                    indices += YELLOW * 3 + x;
                    indices += 0;
                    break;
                case GREEN:
                    indices += YELLOW * 3 + 2;
                    indices += x;
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
                indices += RED * 3 + x;
                indices += 0;
            }
            //if the face is adjacent to BLUE
            if (x == 2) {
                indices += BLUE * 3 + 2 - y;
                indices += 0;
            }
            //if the face is adjacent to ORANGE
            if (y == 0) {
                indices += ORANGE * 3 + 2 - x;
                indices += 0;
            }
            //if the face is adjacent to GREEN
            if (x == 0) {
                indices += GREEN * 3 + y;
                indices += 0;
            }
        }
        //else face is YELLOW
        else {
            //if the face is adjacent to RED
            if (y == 2) {
                indices += RED * 3 + 2 - x;
                indices += 2;
            }
            //if the face is adjacent to BLUE
            if (x == 0) {
                indices += BLUE * 3 + 2 - y;
                indices += 2;
            }
            //if the face is adjacent to ORANGE
            if (y == 0) {
                indices += ORANGE * 3 + x;
                indices += 2;
            }
            //if the face is adjacent to GREEN
            if (x == 2) {
                indices += GREEN * 3 + y;
                indices += 2;
            }
        }
        return indices;
    }
}

//Randomly scrambles the cube and returns the generated moves
QString Cube::scramble(int depth)
{
    QString scrambling;
    int firstLastMove = -1;
    int secondLastMove = -1;
    int nextMove;
    int nbQ;
    QString cMove;
    QString cQ;

//    qsrand(QDateTime::currentDateTime().toTime_t());
    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());

    for(int i = 0; i < depth; i++)
    {

        do{
            nextMove = qrand() % 6;
        }while(nextMove == firstLastMove || nextMove == secondLastMove);

        // Get move
        switch (nextMove) {
            case 0:
                cMove = 'U';
                break;
            case 1:
                cMove = 'D';
                break;
            case 2:
                cMove = 'L';
                break;
            case 3:
                cMove = 'R';
                break;
            case 4:
                cMove = 'F';
                break;
            case 5:
                cMove = 'B';
            break;
        }

        nbQ = qrand() % 3;

        // Get nb of quarter turn
        switch(nbQ){
            case 0:
                cQ = "";
                break;
            case 1:
                cQ = '2';
                break;
            case 2:
                cQ = '\'';
                break;
        }

        // add to scramble
        scrambling += cMove + cQ + ' ';

        secondLastMove = firstLastMove;
        firstLastMove = nextMove;
    }

//    qDebug() << scrambling;

    this->moveSequence(scrambling, RED, YELLOW);

    return scrambling;

}

//Returns the sequence nullifying the sequence in parameter. E.g, U' R2 is reverse for R2 U
QString Cube::reverseSequence(QString sequence)
{
    QStringList moves = sequence.split(' ');
    QString reversed = "";
    QString tmp;

    for(int i = 0; i < moves.length(); i++)
    {
        tmp = moves.at(moves.length()-i-1);
        if(tmp.length()==1)
        {
            tmp+="'";
        }else if(tmp.length()==2)
        {
            if(tmp.at(1)== '\'')
            {
                tmp = tmp.at(0);
            }
        }
        if(tmp.length()>0)
        {
            reversed += tmp + " ";
        }
    }

    return reversed;
}

//This method merges consecutive moves on the same face in one move. For example, U2 U' = U.
//It returns the cleaned sequence
void Cube::cleanSequence(QString &sequence){
    QStringList moves = sequence.split(' ');
    QString cleanedSequence = "";
    QString tmp;
    QString lastMove = "k";

    for (int i = 0; i < moves.length(); i++) {
        tmp = moves.at(i);
        if (tmp.at(0) == lastMove.at(0)) {
            int nbQTurn = 2;
            if(tmp.length() > 1) {
                if(tmp[1]=='2') {
                    nbQTurn += 1;
                } else {
                    nbQTurn += 2;
                }
            }
            if (lastMove.length() > 1) {
                if (lastMove[1]=='2') {
                    nbQTurn += 1;
                } else {
                    nbQTurn += 2;
                }
            }
            nbQTurn %= 4;
            switch(nbQTurn){
            case 1:
                tmp = tmp[0];
                break;
            case 2:
                tmp = tmp[0] + "2";
                break;
            case 3:
                tmp = tmp[0] + "\'";
                break;
            default:
                tmp = "";
                break;
            }
            lastMove = "k";
        }
        if (lastMove != "k") {
            cleanedSequence += lastMove + " ";
        }
        lastMove = tmp;
    }
    cleanedSequence += tmp;
    sequence = cleanedSequence;
}


/**
 * @brief Cube::moveSequence Move a sequence depending of the cube orientation
 * @param sequence The sequence to do
 * @param colorF The color on the Front
 * @param colorU The color on the Up
 * @return The actual sequence did
 */
QString Cube::moveSequence(QString sequence, color colorFront, color colorUp) {

    QStringList moves = sequence.split(' ');

    QChar theMove;
    int nbQTurn;

    QString facesTurned = "";

    foreach (QString move, moves)
    {
        theMove = move[0];

        if(move.length()>1)
        {
            if(move[1]=='2')
            {
                nbQTurn = 2;
            }else{
                nbQTurn = 3;
            }
        }else{
            nbQTurn = 1;
        }

        switch (theMove.toLatin1()) {
        case 'F':
            facesTurned += F(nbQTurn, colorFront, colorUp);
            break;
        case 'B':
            facesTurned += B(nbQTurn, colorFront, colorUp);
            break;
        case 'L':
            facesTurned += L(nbQTurn, colorFront, colorUp);
            break;
        case 'R':
            facesTurned += R(nbQTurn, colorFront, colorUp);
            break;
        case 'U':
            facesTurned += U(nbQTurn, colorFront, colorUp);
            break;
        case 'D':
            facesTurned += D(nbQTurn, colorFront, colorUp);
            break;
        }
    }
    return facesTurned;
}

//matrix rotations
QString Cube::U(int nbQuarterTurn, color colorFront, color colorUp) {
    Q_UNUSED(colorFront);
    return turnFace(colorUp, nbQuarterTurn);
}

QString Cube::D(int nbQuarterTurn, color colorFront, color colorUp) {
    Q_UNUSED(colorFront);
    //Defining the face we'll spin relatively to which face are up and front
    color face;
    switch(colorUp){
    case YELLOW:
        face = WHITE;
        break;
    case WHITE:
        face = YELLOW;
        break;
    default:
        face = (color) ((colorUp + 2) % 4);
        break;
    }
    return turnFace(face, nbQuarterTurn);
}

QString Cube::B(int nbQuarterTurn, color colorFront, color colorUp) {
    Q_UNUSED(colorUp);
    //Defining the face we'll spin relatively to which face are up and front
    color face;
    switch(colorFront){
    case YELLOW:
        face = WHITE;
        break;
    case WHITE:
        face = YELLOW;
        break;
    default:
        face = (color) ((colorFront + 2) % 4);
        break;
    }
    return turnFace(face, nbQuarterTurn);
}

QString Cube::F(int nbQuarterTurn, color colorFront, color colorUp) {
    Q_UNUSED(colorUp);
    return turnFace(colorFront, nbQuarterTurn);
}

QString Cube::R(int nbQuarterTurn, color colorFront, color colorUp) {
    //Defining the face we'll spin relatively to which face are up and front
    color face;
    switch(colorFront){
    case YELLOW:
        face = (color) ((colorUp + 1) % 4);
        break;
    case WHITE:
        face = (color) ((colorUp + 3) % 4);
        break;
    default:
        if(colorUp == YELLOW){
            face = (color) ((colorFront + 3) % 4);
        } else if(colorUp == WHITE){
            face = (color) ((colorFront + 1) % 4);
        }else{
            if(colorUp > colorFront)
            {
                face = YELLOW;
                if(colorUp == GREEN && colorFront == RED)
                {
                    face = WHITE;
                }
            }else {
                face = WHITE;
                if(colorUp == RED && colorFront == GREEN)
                {
                    face = YELLOW;
                }
            }
        }
        break;
    }
    return turnFace(face, nbQuarterTurn);
}

QString Cube::L(int nbQuarterTurn, color colorFront, color colorUp) {
    //Defining the face we'll spin relatively to which face are up and front
    color face;
    switch(colorFront){
    case YELLOW:
        face = (color) ((colorUp + 3) % 4);
        break;
    case WHITE:
        face = (color) ((colorUp + 1) % 4);
        break;
    default:
        if(colorUp == YELLOW){
            face = (color) ((colorFront + 1) % 4);
        } else if(colorUp == WHITE){
            face = (color) ((colorFront + 3) % 4);
        } else {
            if(colorUp > colorFront)
            {
                face = WHITE;
                if(colorUp == GREEN && colorFront == RED)
                {
                    face = YELLOW;
                }
            } else {
                face = YELLOW;
                if(colorUp == RED && colorFront == GREEN)
                {
                    face = WHITE;
                }
            }
        }
        break;
    }
    return turnFace(face, nbQuarterTurn);
}

QString Cube::turnFace(int faceToTurn, int nbQuarterTurns) {
    color face = (color) faceToTurn;
    //The string s contains the move done with the YELLOW face up and RIGHT face front
    QString s = "";
    //reducing nbQuarterTurns to 0, 1, 2 or 3. If 0, we don't do anything and just return an empty string
    nbQuarterTurns = (nbQuarterTurns + 8) % 4;
    if(nbQuarterTurns == 0){
        return "";
    }
    //defining the indices of the stickers on the face
    //those will get spinned
    QList<int> indicesFaceX = QList<int>() << face * 3 + 2 <<  face * 3 + 2 <<
                            face * 3 + 1 <<  face * 3 + 2 <<
                            face * 3 <<  face * 3 <<
                            face * 3 + 1 <<  face * 3;
    QList<int> indicesFaceY = QList<int>() << 1 <<  0 <<
                            2 <<  2 <<
                            1 <<  2 <<
                            0 <<  0;
    //defining the indices of the stickers adjacent to the face
    //those too will get spinned
    QList<int> indicesX;
    QList<int> indicesY;
    switch(face) {
    case RED:
        s = "F";
        //if the RED face gets turned, then:
        //{WHITE, BLUE, YELLOW, GREEN} are adjacent, in this order;
        indicesX = QList<int>() <<WHITE * 3 <<  WHITE * 3 + 1 <<  WHITE * 3 + 2 <<
                                BLUE * 3 <<  BLUE * 3 <<  BLUE * 3 <<
                                YELLOW * 3 <<  YELLOW * 3 + 1 <<  YELLOW * 3 + 2 <<
                                GREEN * 3 + 2 <<  GREEN * 3 + 2 <<  GREEN * 3 + 2;
        indicesY = QList<int>() <<2 <<  2 <<  2 <<
                                0 <<  1 <<  2 <<
                                2 <<  2 <<  2 <<
                                2 <<  1 <<  0;
        break;
    case BLUE:
        s = "L";
        //if the BLUE face gets turned <<  then:
        //{WHITE <<  ORANGE <<  YELLOW <<  RED are adjacent <<  in this order;
        indicesX = QList<int>() <<WHITE * 3 + 2 <<  WHITE * 3 + 2 <<  WHITE * 3 + 2 <<
                                ORANGE * 3 <<  ORANGE * 3 <<  ORANGE * 3 <<
                                YELLOW * 3 <<  YELLOW * 3 <<  YELLOW * 3 <<
                                RED * 3 + 2 <<  RED * 3 + 2 <<  RED * 3 + 2;
        indicesY = QList<int>() <<2 <<  1 <<  0 <<
                                0 <<  1 <<  2 <<
                                0 <<  1 <<  2 <<
                                2 <<  1 <<  0;
        break;
    case ORANGE:
        s = "B";
        //if the ORANGE face gets turned <<  then:
        //{WHITE <<  GREEN <<  YELLOW <<  BLUE are adjacent <<  in this order;
        indicesX = QList<int>() <<WHITE * 3 + 2 <<  WHITE * 3 + 1 <<  WHITE * 3 <<
                                GREEN * 3 <<  GREEN * 3 <<  GREEN * 3 <<
                                YELLOW * 3 + 2 <<  YELLOW * 3 + 1 <<  YELLOW * 3 <<
                                BLUE * 3 + 2 <<  BLUE * 3 + 2 <<  BLUE * 3 + 2;
        indicesY = QList<int>() <<0 <<  0 <<  0 <<
                                0 <<  1 <<  2 <<
                                0 <<  0  << 0 <<
                                2 <<  1 <<  0;
        break;
    case GREEN:
        s = "R";
        //if the GREEN face gets turned <<  then:
        //{WHITE <<  RED <<  YELLOW <<  ORANGE are adjacent <<  in this order;
        indicesX = QList<int>() <<WHITE * 3 <<  WHITE * 3 <<  WHITE * 3 <<
                                RED * 3 <<  RED * 3 <<  RED * 3 <<
                                YELLOW * 3 + 2 <<  YELLOW * 3 + 2 <<  YELLOW * 3 + 2 <<
                                ORANGE * 3 + 2 <<  ORANGE * 3 + 2 <<  ORANGE * 3 + 2;
        indicesY = QList<int>() <<0 <<  1 <<  2 <<
                                0 <<  1 <<  2 <<
                                2 <<  1 <<  0 <<
                                2 <<  1 <<  0;
        break;
    case WHITE:
        s = "D";
        //if the WHITE face gets turned <<  then:
        //{RED <<  GREEN <<  ORANGE <<  BLUE are adjacent <<  in this order;
        indicesX = QList<int>() <<RED * 3 <<  RED * 3 + 1 <<  RED * 3 + 2 <<
                                GREEN * 3 <<  GREEN * 3 + 1 <<  GREEN * 3 + 2 <<
                                ORANGE * 3 <<  ORANGE * 3 + 1 <<  ORANGE * 3 + 2 <<
                                BLUE * 3 <<  BLUE * 3 + 1 <<  BLUE * 3 + 2;
        indicesY = QList<int>() <<0 <<  0 <<  0 <<  0 <<  0 <<  0 <<  0 <<  0 <<  0 <<  0 <<  0 <<  0;
        break;
    case YELLOW:
        s = "U";
        //if the YELLOW face gets turned <<  then:
        //{RED <<  BLUE <<  ORANGE <<  GREEN are adjacent <<  in this order;
        indicesX = QList<int>() <<RED * 3 <<  RED * 3 + 1 <<  RED * 3 + 2 <<
                                BLUE * 3 <<  BLUE * 3 + 1 <<  BLUE * 3 + 2 <<
                                ORANGE * 3 <<  ORANGE * 3 + 1 <<  ORANGE * 3 + 2 <<
                                GREEN * 3 <<  GREEN * 3 + 1 <<  GREEN * 3 + 2;
        indicesY = QList<int>() <<2 <<  2 <<  2 <<  2 <<  2 <<  2 <<  2 <<  2 <<  2 <<  2 <<  2 <<  2;
        break;
    default:
        return "should not happen";
        break;
    }

    color saveFace[4];
    color saveAdjacent[6];
    //Rotating the face -1, 1 or 2 quarter turns clock wise
    switch(nbQuarterTurns){
    case 1:
        //turning the face
        saveFace[0] = matCube[indicesFaceX[6]][indicesFaceY[6]];
        saveFace[1] = matCube[indicesFaceX[7]][indicesFaceY[7]];
        for (int i = 7; i > 1; i -= 2) {
            matCube[indicesFaceX[i]][indicesFaceY[i]] = matCube[indicesFaceX[i - 2]][indicesFaceY[i - 2]];
            matCube[indicesFaceX[i - 1]][indicesFaceY[i - 1]] = matCube[indicesFaceX[i - 3]][indicesFaceY[i - 3]];
        }
        matCube[indicesFaceX[0]][indicesFaceY[0]] = saveFace[0];
        matCube[indicesFaceX[1]][indicesFaceY[1]] = saveFace[1];
        //rotates the stickers on the adjacent faces
        for (int i = 0; i < 3; ++i) {
            saveAdjacent[i] = matCube[indicesX[i + 9]][indicesY[i + 9]];
        }
        for (int i = 11; i > 3; i-=3) {
            matCube[indicesX[i]][indicesY[i]] = matCube[indicesX[i - 3]][indicesY[i - 3]];
            matCube[indicesX[i - 1]][indicesY[i - 1]] = matCube[indicesX[i - 4]][indicesY[i - 4]];
            matCube[indicesX[i - 2]][indicesY[i - 2]] = matCube[indicesX[i - 5]][indicesY[i - 5]];
        }
        matCube[indicesX[0]][indicesY[0]] = saveAdjacent[0];
        matCube[indicesX[1]][indicesY[1]] = saveAdjacent[1];
        matCube[indicesX[2]][indicesY[2]] = saveAdjacent[2];
        break;
    case 2:
        s += "2";
        //turning the face
        for (int i = 0; i < 4; ++i) {
            saveFace[i] = matCube[indicesFaceX[i]][indicesFaceY[i]];
        }
        for (int i = 0; i < 4; i += 2) {
            matCube[indicesFaceX[i]][indicesFaceY[i]] = matCube[indicesFaceX[i + 4]][indicesFaceY[i + 4]];
            matCube[indicesFaceX[i + 1]][indicesFaceY[i + 1]] = matCube[indicesFaceX[i + 5]][indicesFaceY[i + 5]];
        }
        for (int i = 0; i < 4; ++i) {
            matCube[indicesFaceX[i + 4]][indicesFaceY[i + 4]] = saveFace[i];
        }
        //rotates the stickers on the adjacent faces
        for (int i = 0; i < 6; ++i) {
            saveAdjacent[i] = matCube[indicesX[i]][indicesY[i]];
        }
        for (int i = 0; i < 6; ++i) {
            matCube[indicesX[i]][indicesY[i]] = matCube[indicesX[i + 6]][indicesY[i + 6]];
        }
        for (int i = 0; i < 6; ++i) {
            matCube[indicesX[i + 6]][indicesY[i + 6]] = saveAdjacent[i];
        }
        break;
    case 3:
        s += "'";
        //turning the face
        saveFace[0] = matCube[indicesFaceX[0]][indicesFaceY[0]];
        saveFace[1] = matCube[indicesFaceX[1]][indicesFaceY[1]];
        for (int i = 0; i < 6; i += 2) {
            matCube[indicesFaceX[i]][indicesFaceY[i]] = matCube[indicesFaceX[i + 2]][indicesFaceY[i + 2]];
            matCube[indicesFaceX[i + 1]][indicesFaceY[i + 1]] = matCube[indicesFaceX[i + 3]][indicesFaceY[i + 3]];
        }
        matCube[indicesFaceX[6]][indicesFaceY[6]] = saveFace[0];
        matCube[indicesFaceX[7]][indicesFaceY[7]] = saveFace[1];
        //rotates the stickers on the adjacent faces
        for (int i = 0; i < 3; ++i) {
            saveAdjacent[i] = matCube[indicesX[i]][indicesY[i]];
        }
        for (int i = 0; i < 9; i += 3) {
            matCube[indicesX[i]][indicesY[i]] = matCube[indicesX[i + 3]][indicesY[i + 3]];
            matCube[indicesX[i + 1]][indicesY[i + 1]] = matCube[indicesX[i + 4]][indicesY[i + 4]];
            matCube[indicesX[i + 2]][indicesY[i + 2]] = matCube[indicesX[i + 5]][indicesY[i + 5]];
        }
        matCube[indicesX[9]][indicesY[9]] = saveAdjacent[0];
        matCube[indicesX[10]][indicesY[10]] = saveAdjacent[1];
        matCube[indicesX[11]][indicesY[11]] = saveAdjacent[2];
        break;
    default:
        return "";
        break;
    }
    s += " ";
    return s;
}

//returns true if the cubie at the stickers defined by the indices is these colors
bool Cube::cubieEqual(QList<int> indices, color firstColor, color secondColor) {
    return ((matCube[indices.at(0)][indices.at(1)] == firstColor && matCube[indices.at(2)][indices.at(3)] == secondColor)
         || (matCube[indices.at(0)][indices.at(1)] == secondColor && matCube[indices.at(2)][indices.at(3)] == firstColor));

}

bool Cube::cubieEqual(QList<int> indices, color firstColor, color secondColor, color thirdColor) {
    return((matCube[indices.at(4)][indices.at(5)] == firstColor && cubieEqual(indices, secondColor, thirdColor))
        || (matCube[indices.at(4)][indices.at(5)] == secondColor && cubieEqual(indices, firstColor, thirdColor))
        || (matCube[indices.at(4)][indices.at(5)] == thirdColor && cubieEqual(indices, firstColor, secondColor)));
}

