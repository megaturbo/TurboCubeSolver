#include "mainwidget.h"
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{

    // Set the displayCube solved
    initSolvedCube();

    // Display widget
    isometricCubeWidget = new IsometricCubeWidget(*displayedCube);

    //=====         BOTTOM MENU         =====//

    // Instanciation
    scramblePB = new QPushButton("Scr&amble", this);
    cubeInputPB = new QPushButton("Enter &configuration", this);
    solvePB = new QPushButton("&Solve", this);
    resetPB = new QPushButton("&Reset", this);
    sequencePB = new QPushButton("Send Sequence", this);
    sequenceLE = new QLineEdit(this);
    reverseSequencePB = new QPushButton("R", this);

    sequenceLE->setFocus();

    //=====     RESOLUTION MENU        =====//

    resolutionWidget = new ResolutionWidget();

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

    connect(resolutionWidget, SIGNAL(sendMove(QString)), this, SLOT(receiveMove(QString)));

    // Display settings
    this->setLayout(MainLayout);
    this->resize(1000,600);

    isometricCubeWidget->setOrientation(YELLOW, RED);

    this->show();
}

void MainWidget::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return){
        sendSequenceSlot();
    }
}

/**********************************************************\
|******************       Slots        ********************|
\******************  a lot of slots    ********************/

void MainWidget::receiveMove(QString move)
{
    displayedCube->moveSequence(move, RED, YELLOW);
    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::cubieModified(int x, int y, color c)
{
    displayedCube->setSticker(x, y, c);
    isometricCubeWidget->setCube(*displayedCube);
}

void MainWidget::startCubeInput()
{
    if(isometricCubeWidget->getConfig()){
        if(displayedCube->validateCube()){
            isometricCubeWidget->setConfig(false);
            cubeInputPB->setText("Enter &configuration");
            solvePB->setEnabled(true);
        } else {
            QMessageBox::information(this, tr("Cube error"),
                                     tr("The cube you tried to input is in an impossible configuration."),
                                     QMessageBox::Ok | QMessageBox::Default);
        }
    } else {
        isometricCubeWidget->setConfig(true);
        cubeInputPB->setText("Confirm &configuration");
        solvePB->setDisabled(true);
    }
}

void MainWidget::turnXSlot()
{
    isometricCubeWidget->changeOrientation('x', 1);
}

void MainWidget::turnYSlot()
{
    isometricCubeWidget->changeOrientation('y', 1);
}

void MainWidget::turnZSlot()
{
    isometricCubeWidget->changeOrientation('z', 1);
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
    resolutionWidget->resetDisplay();

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
    isometricCubeWidget->setOrientation(YELLOW, RED);
}

void MainWidget::sendSequenceSlot()
{
    displayedCube->moveSequence(sequenceLE->text(), isometricCubeWidget->getFront(), isometricCubeWidget->getUp());
    isometricCubeWidget->setCube(*displayedCube);
}
