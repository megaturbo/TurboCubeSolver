/**
    @author: Thomas Roulin
*/
#include "resolutionwidget.h"

#include <QBoxLayout>
#include <QFontDatabase>
#include <QGroupBox>
#include <QDebug>
#include "Cube.h"
#include <QMessageBox>
#include <QDebug>

ResolutionWidget::ResolutionWidget(QWidget *parent)
    : QWidget(parent)
{
    initDisplay();
    resetDisplay();
}

/**
 * Refresh the whole widget, show the actual move, reset the buttons, etc...
 */
void ResolutionWidget::refreshDisplay()
{
    int lengthSequence = CFOPlist.length();

    if(actMoveID < lengthSequence){
        QPixmap movePixmap(":Pictures/moves/" + CFOPlist.at(actMoveID) + ".png");
        actMoveLabel->setPixmap(movePixmap);
    }else{
        actMoveLabel->clear();
    }

    // Concat strings
    QString C = "";
    QString F = "";
    QString O = "";
    QString P = "";
    QString tmpBefore;
    QString tmpAfter;

    for(int i = 0; i < CFOPlist.size(); i++)
    {
        tmpBefore = "";
        tmpAfter = " ";

        if(i == actMoveID)
        {
            tmpBefore += "<b>";
            tmpAfter += "</b>";
        }

        if(i < endC)
        {
            C += tmpBefore + CFOPlist.at(i) + tmpAfter;

        }else if(i < endF)
        {
            F += tmpBefore + CFOPlist.at(i) + tmpAfter;
        }else if(i < endO)
        {
            O += tmpBefore + CFOPlist.at(i) + tmpAfter;
        }else if(i < endP)
        {
            P += tmpBefore + CFOPlist.at(i) + tmpAfter;
        }
    }

    if(C == ""){
        C == "Cross already solved";
    } else {
        C == "Cross: " + C;
    }
    if(F == ""){
        F == "F2L already solved";
    } else {
        F == "F2L: " + F;
    }
    if(O == ""){
        O == "OLL already solved";
    } else {
        O == "OLL: " + O;
    }
    if(P == ""){
        P == "PLL already solved";
    } else {
        P == "PLL: " + P;
    }

    // Refresh label content
    crossLabel->setText(C);
    f2lLabel->setText(F);
    ollLabel->setText(O);
    pllLabel->setText(P);

    if(endP == 0)
    {
        nbMovesLabel->setText("<b>The cube is already solved.</b>");
    }


    // Enable/disable the buttons which should be.
    if(actMoveID > 0)
    {
        pastMovePB->setEnabled(true);
    }else{
        pastMovePB->setDisabled(true);
    }
    if(actMoveID >= lengthSequence)
    {
        nextMovePB->setDisabled(true);
    }else{
        nextMovePB->setEnabled(true);
    }
}

/**
 * Go back one move
 */
void ResolutionWidget::pastMove()
{
    if(pastMovePB->isEnabled())
    {
        emit sendMove(Cube::reverseSequence(CFOPlist.at(actMoveID-1)));
        actMoveID--;
        refreshDisplay();
    }
}

/**
 * Do the next move
 */
void ResolutionWidget::nextMove()
{
    if(nextMovePB->isEnabled())
    {
        emit sendMove(CFOPlist.at(actMoveID));
        actMoveID++;
        refreshDisplay();
    }
}

/**
 * Create the whole display, instanciate all the QObjects, Layouts and GroupBoxes
 */
void ResolutionWidget::initDisplay()
{
    QString rdDefault = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/Fonts/reservoirdogs.ttf")).at(0);
    QFont rdFont(rdDefault);
    rdFont.setPointSize(30);

    infoPB = new QPushButton("Information", this);
    infoPB->setFixedWidth(100);

    pastMovePB = new QPushButton("<", this);
    actMoveLabel = new QLabel(this);
    nextMovePB = new QPushButton(">", this);

    pastMovePB->setFont(rdFont);
    actMoveLabel->setFont(rdFont);
    nextMovePB->setFont(rdFont);
    pastMovePB->setFixedSize(100,100);
    actMoveLabel->setFixedSize(100,100);
    actMoveLabel->setStyleSheet("border-image:url(:Pictures/moves/background.png);");
    nextMovePB->setFixedSize(100,100);

    crossLabel = new QLabel(this);
    f2lLabel = new QLabel(this);
    ollLabel = new QLabel(this);
    pllLabel = new QLabel(this);
    nbMovesLabel = new QLabel(this);

    crossLabel->setMinimumWidth(300);
    f2lLabel->setMinimumWidth(300);
    ollLabel->setMinimumWidth(300);
    pllLabel->setMinimumWidth(300);

    QGroupBox *groupBox = new QGroupBox("Resolution", this);
    QVBoxLayout *cfopLayout = new QVBoxLayout();
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QHBoxLayout *cfopInformationLayout = new QHBoxLayout();
    QVBoxLayout *infoLayout = new QVBoxLayout();

    cfopLayout->addWidget(crossLabel);
    cfopLayout->addWidget(f2lLabel);
    cfopLayout->addWidget(ollLabel);
    cfopLayout->addWidget(pllLabel);

    cfopInformationLayout->addLayout(cfopLayout);

    infoLayout->addWidget(nbMovesLabel);
    infoLayout->addWidget(infoPB);
    nbMovesLabel->setFixedWidth(200);
    cfopInformationLayout->addLayout(infoLayout);

    mainLayout->addWidget(pastMovePB);
    mainLayout->addWidget(actMoveLabel);
    mainLayout->addWidget(nextMovePB);
    mainLayout->addLayout(cfopInformationLayout);

    groupBox->setLayout(mainLayout);

    QVBoxLayout *megaMainLayout = new QVBoxLayout();

    megaMainLayout->addWidget(groupBox);

    connect(pastMovePB, SIGNAL(clicked()), this, SLOT(pastMove()));
    connect(nextMovePB, SIGNAL(clicked()), this, SLOT(nextMove()));
    connect(infoPB, SIGNAL(clicked()), this, SLOT(infoSlot()));

    this->setLayout(megaMainLayout);
}

/**
 * Display a brief information when the information button is pressed by the user.
 */
void ResolutionWidget::infoSlot()
{
    QMessageBox infoBox;
    infoBox.setInformativeText("Before following resolution step, don't forget to keep the yellow face on the top and the red face againt you.");
    infoBox.setText("<h3>Resolution information</h3>");
    infoBox.setStandardButtons(QMessageBox::Ok);
    infoBox.setDefaultButton(QMessageBox::Ok);

    QPixmap exportSuccess(":Pictures/yellowUredF");
    infoBox.setIconPixmap(exportSuccess);

    infoBox.exec();
}

/**
 * Receive a new sequence and the refresh the display
 * @param solveSequence: The actual new sequence
 */
void ResolutionWidget::newSolveSequence(QString solveSequence)
{
    actMoveID = 0;
    resetDisplay();
    nextMovePB->setEnabled(true);

    solveSequence.chop(1);
    CFOPlist = solveSequence.split(' ');

    // Get parts sizes
    endC = CFOPlist.at(0).toInt();
    endF = CFOPlist.at(1).toInt() + endC;
    endO = CFOPlist.at(2).toInt() + endF;
    endP = CFOPlist.at(3).toInt() + endO;

    // remove the sizes
    CFOPlist.removeAt(0);
    CFOPlist.removeAt(0);
    CFOPlist.removeAt(0);
    CFOPlist.removeAt(0);

    nbMovesLabel->setText("Solution found in <b>"+QString::number(CFOPlist.size()) + "</b> moves");

    refreshDisplay();
}

void ResolutionWidget::resetDisplay()
{
    CFOPlist.clear();
    actMoveLabel->clear();
    crossLabel->clear();
    f2lLabel->clear();
    ollLabel->clear();
    pllLabel->clear();
    nbMovesLabel->clear();
    pastMovePB->setDisabled(true);
    nextMovePB->setDisabled(true);
}
