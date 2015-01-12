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

    // Layouts
    QHBoxLayout *btLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();

    // Layout: Menu
    btLayout->addWidget(scramblePB);
    btLayout->addWidget(solvePB);
    btLayout->addWidget(resetPB);
    btLayout->addWidget(sequenceLE);
    btLayout->addWidget(sequencePB);
    btLayout->addWidget(reverseSequencePB);

    // Layout: Total
    vLayout->addWidget(isometricCubeWidget);
    vLayout->addLayout(btLayout);

    // CONNECT
    connect(scramblePB, SIGNAL(clicked()), this, SLOT(scrambleSlot()));
    connect(solvePB, SIGNAL(clicked()), this, SLOT(solveSlot()));
    connect(sequencePB, SIGNAL(clicked()), this, SLOT(sendSequenceSlot()));
    connect(resetPB, SIGNAL(clicked()), this, SLOT(resetSlot()));
    connect(reverseSequencePB, SIGNAL(clicked()), this, SLOT(reverseSequenceSlot()));

    // Display settings
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
    displayedCube->moveSequence(sequenceLE->text(), RED, YELLOW);
    isometricCubeWidget->setCube(*displayedCube);
}
