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
    solvePB = new QPushButton("Solve", this);
    resetPB = new QPushButton("Reset", this);
    sequencePB = new QPushButton("Send Sequence", this);
    sequenceLE = new QLineEdit(this);
    reverseSequencePB = new QPushButton("R", this);

    // Menu: orientation
    movesPB[0] = new QPushButton("x", this);
    movesPB[1] = new QPushButton("y", this);
    movesPB[2] = new QPushButton("z", this);

    // Layouts
    QHBoxLayout *menuLayout = new QHBoxLayout();
    QHBoxLayout *topLayout = new QHBoxLayout();
    QVBoxLayout *MainLayout = new QVBoxLayout();
    QVBoxLayout *orientationMenuLayout = new QVBoxLayout();

    // Layout: Menu
    menuLayout->addWidget(scramblePB);
    menuLayout->addWidget(solvePB);
    menuLayout->addWidget(resetPB);
    menuLayout->addWidget(sequenceLE);
    menuLayout->addWidget(sequencePB);
    menuLayout->addWidget(reverseSequencePB);

    //orientationMenuLayout->addWidget(movesPB[0]);
    //orientationMenuLayout->addWidget(movesPB[1]);
    //orientationMenuLayout->addWidget(movesPB[2]);

    topLayout->addWidget(isometricCubeWidget);
    //topLayout->addLayout(orientationMenuLayout);

    // Layout: Total
    MainLayout->addLayout(topLayout);
    MainLayout->addLayout(menuLayout);

    // CONNECT
    connect(scramblePB, SIGNAL(clicked()), this, SLOT(scrambleSlot()));
    connect(solvePB, SIGNAL(clicked()), this, SLOT(solveSlot()));
    connect(sequencePB, SIGNAL(clicked()), this, SLOT(sendSequenceSlot()));
    connect(resetPB, SIGNAL(clicked()), this, SLOT(resetSlot()));
    connect(reverseSequencePB, SIGNAL(clicked()), this, SLOT(reverseSequenceSlot()));

    // Display settings
    this->setLayout(MainLayout);
    this->resize(1000,600);
    this->show();
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
    sequenceLE->setText(displayedCube->scramble());
    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::solveSlot()
{
    Fridrich::solve(displayedCube);
    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::sendSequenceSlot()
{
    displayedCube->moveSequence(sequenceLE->text(), RED, WHITE);
    isometricCubeWidget->setCube(*displayedCube);
}
