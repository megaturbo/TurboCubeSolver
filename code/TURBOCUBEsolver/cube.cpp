#include "cube.h"
#include <QString>
#include <iostream>
#include <qdebug.h>
#include <QMap>
#include <QList>

//Public methods
//Constructors
Cube::Cube()
{
}

Cube::Cube(QList<QMap<color, color> > newCube){
    setCube(newCube);
}

//Utility methods
void Cube::setCube(QList<QMap<color, color> > newCube){
    for(int i = 0; i < newCube.size(); i++){

    }
}

//returns faces the cubie's on
int* Cube::locateCubie(color c1, color c2, color c3){
    if (c3 == UNDEFINED){
        //Then edge
    }
    else{
        //Then corner
    }
}

//Private methods

//actually moves the faces
void Cube::moveSequence(QString sequence){

}

//matrix rotation per face
void Cube::U(int nbQuarterTurn){

}

void Cube::D(int nbQuarterTurn){

}

void Cube::B(int nbQuarterTurn){

}

void Cube::F(int nbQuarterTurn){

}

void Cube::R(int nbQuarterTurn){

}

void Cube::L(int nbQuarterTurn){

}
