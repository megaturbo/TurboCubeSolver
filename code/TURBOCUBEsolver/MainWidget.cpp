#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{

    // Set the displayCube solved
    initSolvedCube();

    // Display widget
    isometricCubeWidget = new IsometricCubeWidget(*displayedCube);

    //=====         BOTTOM MENU         =====//

    // Instanciation
    scramblePB = new QPushButton("Scramble", this);
    cubeInputPB = new QPushButton("Set configuration", this);
    solvePB = new QPushButton("Solve", this);
    resetPB = new QPushButton("Reset", this);
    sequencePB = new QPushButton("Send Sequence", this);
    sequenceLE = new QLineEdit(this);
    reverseSequencePB = new QPushButton("R", this);


    //=====     RESOLUTION MENU        =====//

    resolutionWidget = new ResolutionWidget();
    // Instanciation
    /*pastMovesLabel = new QLabel(this);
    nextMovesLabel = new QLabel(this);
    actMoveLabel = new QLabel(this);
    pastMovePB = new QPushButton("<", this);
    nextMovePB = new QPushButton(">", this);

    // Settings
    pastMovePB->setMaximumWidth(40);
    nextMovePB->setMaximumWidth(40);
    pastMovePB->setDisabled(TRUE);
    nextMovePB->setDisabled(TRUE);
    sResolution = new QStringList();
    actMoveID = 0;

    // Settings: widths
    nextMovesLabel->setMaximumWidth(350);
    pastMovesLabel->setMaximumWidth(350);
    actMoveLabel->setMaximumWidth(80);

    // Settings: Fonts

    int id = QFontDatabase::addApplicationFont(":/Fonts/reservoirdogs.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont rdFont(family);
    rdFont.setPointSize(30);
    actMoveLabel->setFont(rdFont);
    actMoveLabel->setAlignment(Qt::AlignHCenter);
    nextMovesLabel->setAlignment(Qt::AlignLeft);
    pastMovesLabel->setAlignment(Qt::AlignRight);*/


    //=====        RIGHT MENU           =====//

    // Instanciation
    movesPB = new QPushButton*[3]();
    movesPB[0] = new QPushButton("x", this);
    movesPB[1] = new QPushButton("y", this);
    movesPB[2] = new QPushButton("z", this);

    // Settings
    movesPB[0]->setMaximumWidth(40);
    movesPB[1]->setMaximumWidth(40);
    movesPB[2]->setMaximumWidth(40);


    //=====          LAYOUTS           =====//
    // Instanciation
    QHBoxLayout *cubeMenuLayout = new QHBoxLayout();
    QHBoxLayout *topLayout = new QHBoxLayout();
    QVBoxLayout *orientationMenuLayout = new QVBoxLayout();
    //QHBoxLayout *resolutionMenuLayout = new QHBoxLayout();
    QVBoxLayout *MainLayout = new QVBoxLayout();

    // Cube tools
    cubeMenuLayout->addWidget(cubeInputPB);
    cubeMenuLayout->addWidget(scramblePB);
    cubeMenuLayout->addWidget(solvePB);
    cubeMenuLayout->addWidget(resetPB);
    cubeMenuLayout->addWidget(sequenceLE);
    cubeMenuLayout->addWidget(sequencePB);
    cubeMenuLayout->addWidget(reverseSequencePB);

    // Orientation tools
    orientationMenuLayout->addWidget(movesPB[0]);
    orientationMenuLayout->addWidget(movesPB[1]);
    orientationMenuLayout->addWidget(movesPB[2]);

    // Top: IsometricWidget + Orientation Menu
    isometricCubeWidget->setMinimumHeight(600);
    topLayout->addWidget(isometricCubeWidget);
    topLayout->addLayout(orientationMenuLayout);

    // Resolution menu
    /*resolutionMenuLayout->addWidget(pastMovesLabel);
    resolutionMenuLayout->addWidget(pastMovePB);
    resolutionMenuLayout->addWidget(actMoveLabel);
    resolutionMenuLayout->addWidget(nextMovePB);
    resolutionMenuLayout->addWidget(nextMovesLabel);*/


    // Layout: Total
    MainLayout->addLayout(topLayout);
    MainLayout->addWidget(resolutionWidget);
    MainLayout->addLayout(cubeMenuLayout);


    //=====          CONNECTs         =====//
    connect(scramblePB, SIGNAL(clicked()), this, SLOT(scrambleSlot()));
    connect(solvePB, SIGNAL(clicked()), this, SLOT(solveSlot()));
    connect(sequencePB, SIGNAL(clicked()), this, SLOT(sendSequenceSlot()));
    connect(resetPB, SIGNAL(clicked()), this, SLOT(resetSlot()));
    connect(reverseSequencePB, SIGNAL(clicked()), this, SLOT(reverseSequenceSlot()));

    connect(movesPB[0], SIGNAL(clicked()), this, SLOT(turnXSlot()));
    connect(movesPB[1], SIGNAL(clicked()), this, SLOT(turnYSlot()));
    connect(movesPB[2], SIGNAL(clicked()), this, SLOT(turnZSlot()));

    connect(cubeInputPB, SIGNAL(clicked()), this, SLOT(startCubeInput()));
    connect(isometricCubeWidget, SIGNAL(cubieModified(int, int, color)), this, SLOT(cubieModified(int, int, color)));

    connect(resolutionWidget, SIGNAL(sendMove(QChar)), this, SLOT(mo));

    // Display settings
    this->setLayout(MainLayout);
    this->resize(1000,600);
    this->show();
}



/**********************************************************\
|******************       Slots        ********************|
\******************  a lot of slots    ********************/

/*void MainWidget::refreshResolutionState()
{
    actMoveLabel->clear();
    pastMovesLabel->clear();
    nextMovesLabel->clear();
    nextMovePB->setDisabled(TRUE);
    pastMovePB->setDisabled(TRUE);

    if(sResolution->length() > 0){
        // Enable/Disable past/next buttons
        if(actMoveID < sResolution->length())
        {
            nextMovePB->setEnabled(TRUE);
        }
        if(actMoveID>0)
        {
            pastMovePB->setEnabled(TRUE);
        }

        // Refresh the display
        for(int i = 0; i < sResolution->length(); i++)
        {
            if(i < actMoveID)
            {
                pastMovesLabel->setText(pastMovesLabel->text() + " " + sResolution->at(i));
            }else if( i > actMoveID){
                nextMovesLabel->setText(nextMovesLabel->text() + " " + sResolution->at(i));
            }else{
                actMoveLabel->setText(sResolution->at(i));
            }
        }
    }
}

void MainWidget::pastMove()
{
    displayedCube->moveSequence(Cube::reverseSequence(actMoveLabel->text()), RED, YELLOW);
    isometricCubeWidget->setCube(*displayedCube);
    actMoveID--;
    refreshResolutionState();
}

void MainWidget::nextMove()
{
    displayedCube->moveSequence(actMoveLabel->text(), RED, YELLOW);
    isometricCubeWidget->setCube(*displayedCube);
    actMoveID++;
    refreshResolutionState();
}*/

void MainWidget::receiveMove(QString move)
{
    displayedCube->moveSequence(move, RED, YELLOW);
    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::cubieModified(int x, int y, color c)
{
    displayedCube->setCubie(x, y, c);
    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::startCubeInput()
{
    inputWidget = new InputWidget();
    inputWidget->show();
//    cubeInputWidget = new CubeInputWidget();
//    cubeInputWidget->show();
}

void MainWidget::turnXSlot()
{
    isometricCubeWidget->setOrientation('x', 1);
}

void MainWidget::turnYSlot()
{
    isometricCubeWidget->setOrientation('y', 1);
}

void MainWidget::turnZSlot()
{
    isometricCubeWidget->setOrientation('z', 1);
}

void MainWidget::initSolvedCube()
{
    color solvedMatrix[18][3];

    for (int x = 0; x < 18; ++x) {
        for (int y = 0; y < 3; ++y) {
            solvedMatrix[x][y] = (color)(x / 3);
        }
    }
    displayedCube = new Cube(solvedMatrix);
}

void MainWidget::reverseSequenceSlot()
{
    sequenceLE->setText(Cube::reverseSequence(sequenceLE->text()));
}

void MainWidget::resetSlot()
{
    resolutionWidget->newSolveSequence("");

    initSolvedCube();
    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::scrambleSlot()
{
    sequenceLE->setText(displayedCube->scramble(5));
    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::solveSlot()
{
    Cube *tmpCube = new Cube(*displayedCube);
    resolutionWidget->newSolveSequence(Fridrich::solve(tmpCube));

    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::sendSequenceSlot()
{
    displayedCube->moveSequence(sequenceLE->text(), isometricCubeWidget->getFront(), isometricCubeWidget->getUp());
    isometricCubeWidget->setCube(*displayedCube);
}
