#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{

    initSolvedCube();

    isometricCubeWidget = new IsometricCubeWidget(*displayedCube);

    scramblePB = new QPushButton("Scramble");
    solvePB = new QPushButton("Solve");
    resetPB = new QPushButton("Reset");
    sequencePB = new QPushButton("Send Sequence");
    sequenceLE = new QLineEdit();


    QHBoxLayout *btLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();

    // Buttons
    btLayout->addWidget(scramblePB);
    btLayout->addWidget(solvePB);
    btLayout->addWidget(resetPB);
    btLayout->addWidget(sequenceLE);
    btLayout->addWidget(sequencePB);

    vLayout->addWidget(isometricCubeWidget);
    vLayout->addLayout(btLayout);

    // CONNECT
    connect(scramblePB, SIGNAL(clicked()), this, SLOT(scrambleSlot()));
    connect(solvePB, SIGNAL(clicked()), this, SLOT(solveSlot()));
    connect(sequencePB, SIGNAL(clicked()), this, SLOT(sendSequenceSlot()));
    connect(resetPB, SIGNAL(clicked()), this, SLOT(resetSlot()));

    this->setLayout(vLayout);
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

void MainWidget::resetSlot()
{
    initSolvedCube();
    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::scrambleSlot()
{
    displayedCube->scramble();
    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::solveSlot()
{
    Fridrich::solve(displayedCube);
    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::sendSequenceSlot()
{
    displayedCube->moveSequence(sequenceLE->text(), RED, YELLOW);
    isometricCubeWidget->setCube(*displayedCube);
}
