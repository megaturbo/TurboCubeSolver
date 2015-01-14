#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{

    // Set the displayCube solved
    initSolvedCube();

    // Display widget
    isometricCubeWidget = new IsometricCubeWidget(*displayedCube);

    // Menu
    scramblePB = new QPushButton("Scramble", this);
    cubeInputPB = new QPushButton("Set configuration", this);
    solvePB = new QPushButton("Solve", this);
    resetPB = new QPushButton("Reset", this);
    sequencePB = new QPushButton("Send Sequence", this);
    sequenceLE = new QLineEdit(this);
    reverseSequencePB = new QPushButton("R", this);

    // Menu: orientation
    movesPB = new QPushButton*[3]();

    movesPB[0] = new QPushButton("x", this);
    movesPB[1] = new QPushButton("y", this);
    movesPB[2] = new QPushButton("z", this);

    movesPB[0]->setMaximumWidth(40);
    movesPB[1]->setMaximumWidth(40);
    movesPB[2]->setMaximumWidth(40);

    // Layouts
    QHBoxLayout *menuLayout = new QHBoxLayout();
    QHBoxLayout *topLayout = new QHBoxLayout();
    QVBoxLayout *MainLayout = new QVBoxLayout();
    QVBoxLayout *orientationMenuLayout = new QVBoxLayout();

    // Layout: Menu
    menuLayout->addWidget(cubeInputPB);
    menuLayout->addWidget(scramblePB);
    menuLayout->addWidget(solvePB);
    menuLayout->addWidget(resetPB);
    menuLayout->addWidget(sequenceLE);
    menuLayout->addWidget(sequencePB);
    menuLayout->addWidget(reverseSequencePB);

    // Layout: orientation menu
    orientationMenuLayout->addWidget(movesPB[0]);
    orientationMenuLayout->addWidget(movesPB[1]);
    orientationMenuLayout->addWidget(movesPB[2]);

    isometricCubeWidget->setMinimumHeight(600);
    topLayout->addWidget(isometricCubeWidget);
    topLayout->addLayout(orientationMenuLayout);

    // Layout: Total
    MainLayout->addLayout(topLayout);
    MainLayout->addLayout(menuLayout);

    // CONNECT
    connect(scramblePB, SIGNAL(clicked()), this, SLOT(scrambleSlot()));
    connect(solvePB, SIGNAL(clicked()), this, SLOT(solveSlot()));
    connect(sequencePB, SIGNAL(clicked()), this, SLOT(sendSequenceSlot()));
    connect(resetPB, SIGNAL(clicked()), this, SLOT(resetSlot()));
    connect(reverseSequencePB, SIGNAL(clicked()), this, SLOT(reverseSequenceSlot()));

    connect(movesPB[0], SIGNAL(clicked()), this, SLOT(turnXSlot()));
    connect(movesPB[1], SIGNAL(clicked()), this, SLOT(turnYSlot()));
    connect(movesPB[2], SIGNAL(clicked()), this, SLOT(turnZSlot()));

    connect(cubeInputPB, SIGNAL(clicked()), this, SLOT(startCubeInput()));

    // Display settings
    this->setLayout(MainLayout);
    this->resize(1000,600);
    this->show();
}

void MainWidget::startCubeInput()
{
    cubeInputWidget = new CubeInputWidget();
    cubeInputWidget->show();
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
    Fridrich::solve(displayedCube);
    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::sendSequenceSlot()
{
    displayedCube->moveSequence(sequenceLE->text(), isometricCubeWidget->getFront(), isometricCubeWidget->getUp());
    isometricCubeWidget->setCube(*displayedCube);
}
