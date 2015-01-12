#include "CubeInputWidget.h"

CubeInputWidget::CubeInputWidget(QWidget *parent) :
    QWidget(parent)
{
    //set window size
    this->setFixedSize(931,450);

    //Reset matrix
    setMatrix(cubeInputMatrix);

    //rectangle mold for button geometry
    QRect *rectMold = new QRect();
    QIcon *controlIcon = new QIcon("..\\..\\Pictures\\input\\arrow Up.PNG");

    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 3; x++)
        {
            pbGroup[x][y]=new QPushButton(this);
        }
    }

    //control
    QPushButton *pbUp = new QPushButton(this);
    QPushButton *pbDown = new QPushButton(this);
    QPushButton *pbRight = new QPushButton(this);
    QPushButton *pbLeft = new QPushButton(this);

    //-----------------------------------------------------------------------------------------//

    //set button grid
    for(int y = 0;y<3;y++){
        for(int x = 0;x<3;x++){
            pbGroup[x][y]->setGeometry(*rectMold);
            rectMold->setRect(83+x*76,110+y*76,75,75);}}

    //set button base colors
    for(int y = 0;y<3;y++){
        for(int x = 0;x<3;x++){
            pbGroup[x][y]->setStyleSheet("background-color: gray");}}

    //SIGNAL->SLOT for face buttons

    for(int y = 0;y<3;y++){
        for(int x = 0;x<3;x++){
            connect(pbGroup[x][y],SIGNAL(clicked()),this,SLOT(changeSquare()));}}

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

    //SIGNAL->SLOT for control buttons
    connect(pbUp,SIGNAL(clicked()),this,SLOT(changeFaceUp()));
    connect(pbDown,SIGNAL(clicked()),this,SLOT(changeFaceDown()));
    connect(pbRight,SIGNAL(clicked()),this,SLOT(changeFaceRight()));
    connect(pbLeft,SIGNAL(clicked()),this,SLOT(changeFaceLeft()));
}

void CubeInputWidget::setMatrix(color cubeInputMatrix[18][3])
{
    //set matrix
    for(int i = 0;i<18;i++)
    {
        for(int j = 0;j<3;j++)
        {
            cubeInputMatrix[i][j] = UNDEFINED;
        }
    }

    //set CubeMatrix center colors
    cubeInputMatrix[1][1] = RED;
    cubeInputMatrix[1][4] = BLUE;
    cubeInputMatrix[1][7] = ORANGE;
    cubeInputMatrix[1][10] = GREEN;
    cubeInputMatrix[1][13] = WHITE;
    cubeInputMatrix[1][16] = YELLOW;
}

void CubeInputWidget::changeSquare()
{
    QObject *sndr = sender();

}

void CubeInputWidget::changeFaceRight()
{

}

void CubeInputWidget::changeFaceLeft()
{

}

void CubeInputWidget::changeFaceUp()
{

}

void CubeInputWidget::changeFaceDown()
{

}

CubeInputWidget::~CubeInputWidget()
{

}
