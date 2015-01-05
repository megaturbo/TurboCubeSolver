#include "CubeInput.h"

CubeInput::CubeInput(QWidget *parent) :
    QWidget(parent)
{

    this->setFixedSize(931,450);


    //rectangle mold for button geometry
    QRect *rectMold = new QRect();
    QIcon *controlIcon = new QIcon("..\\..\\Pictures\\input\\arrow Up.PNG");

    //topline
    QPushButton *pbTop0 = new QPushButton(this);
    QPushButton *pbTop1 = new QPushButton(this);
    QPushButton *pbTop2 = new QPushButton(this);

    //central
    QPushButton *pbMid0 = new QPushButton(this);
    QPushButton *pbMid1 = new QPushButton(this);
    QPushButton *pbMid2 = new QPushButton(this);

    //bottom
    QPushButton *pbBot0 = new QPushButton(this);
    QPushButton *pbBot1 = new QPushButton(this);
    QPushButton *pbBot2 = new QPushButton(this);

    //control
    QPushButton *pbUp = new QPushButton(this);
    QPushButton *pbDown = new QPushButton(this);
    QPushButton *pbRight = new QPushButton(this);
    QPushButton *pbLeft = new QPushButton(this);

    //-----------------------------------------------------------------------------------------//

    //set button grid
    rectMold->setRect(931/4-150,450/2-115,75,75);

    pbTop0->setGeometry(*rectMold);
    rectMold->translate(76,0);
    pbTop1->setGeometry(*rectMold);
    rectMold->translate(76,0);
    pbTop2->setGeometry(*rectMold);

    rectMold->translate(-152,76);
    pbMid0->setGeometry(*rectMold);
    rectMold->translate(76,0);
    pbMid1->setGeometry(*rectMold);
    rectMold->translate(76,0);
    pbMid2->setGeometry(*rectMold);

    rectMold->translate(-152,76);
    pbBot0->setGeometry(*rectMold);
    rectMold->translate(76,0);
    pbBot1->setGeometry(*rectMold);
    rectMold->translate(76,0);
    pbBot2->setGeometry(*rectMold);

    //set button base colors
    pbTop0->setStyleSheet("background-color: gray");
    pbTop1->setStyleSheet("background-color: gray");
    pbTop2->setStyleSheet("background-color: gray");

    pbMid0->setStyleSheet("background-color: gray");
    pbMid1->setStyleSheet("background-color: gray");
    pbMid2->setStyleSheet("background-color: gray");

    pbBot0->setStyleSheet("background-color: gray");
    pbBot1->setStyleSheet("background-color: gray");
    pbBot2->setStyleSheet("background-color: gray");


    //set control buttons
    rectMold->setRect(164, 43,64,64);
    pbUp->setGeometry(*rectMold);

    rectMold->setRect(164, 340,64,64);
    pbDown->setGeometry(*rectMold);

    rectMold->setRect(311, 192,64,64);
    pbRight->setGeometry(*rectMold);

    rectMold->setRect(15, 192,64,64);
    pbLeft->setGeometry(*rectMold);

    //set control button icons

    pbUp->setIconSize(QSize(64,64));
    pbDown->setIconSize(QSize(64,64));
    pbRight->setIconSize(QSize(64,64));
    pbLeft->setIconSize(QSize(64,64));

    pbUp->setIcon(*controlIcon);
    controlIcon->addFile("..\\..\\Pictures\\input\\arrow down.PNG");
    pbDown->setIcon(*controlIcon);
    controlIcon->addFile("..\\..\\Pictures\\input\\arrow right.PNG");
    pbRight->setIcon(*controlIcon);
    controlIcon->addFile("..\\..\\Pictures\\input\\arrow left.PNG");
    pbLeft->setIcon(*controlIcon);
}

CubeInput::~CubeInput()
{

}
