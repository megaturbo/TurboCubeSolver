#include "cube.h"
#include <QString>
#include <iostream>
#include <qdebug.h>
#include <QList>

//Public methods
//Constructors
Cube::Cube()
{
}

Cube::Cube(QList<Cubie> newCube){
    setCube(newCube);
}

Cube::Cube(QMap<Cubie, QList<color> > newCube){

}

//Utility methods

void Cube::setCube(QList<Cubie> newCube){

}

void Cube::setCube(QMap<Cubie, QList<color> > newCube){
        this->cube = newCube;
}

//returns faces the cubie's on
QList<color> Cube::locateCubie(Cubie c){
    return cube.find(c).value();
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
