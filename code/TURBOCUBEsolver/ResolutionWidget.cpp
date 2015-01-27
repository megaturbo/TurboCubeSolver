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
#include <QDoubleValidator>

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
        C = "<b>Already solved</b>";
    }
    if(F == ""){
        F = "<b>Already solved</b>";
    }
    if(O == ""){
        O = "<b>Already solved</b>";
    }
    if(P == ""){
        P = "<b>Already solved</b>";
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
        pausePB->setDisabled(true);
        playPB->setDisabled(true);
        timer->stop();
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
        playPB->setDisabled(false);
        timer->stop();
        pausePB->setDisabled(true);
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

    playPB = new QPushButton("Play", this);
    pausePB = new QPushButton("Pause", this);
    timeLE = new QLineEdit("1.0", this);
    timeLE->setValidator(new QDoubleValidator(0.01, 10, 3, this));
    timeLE->setMaximumWidth(50);
    playPB->setMaximumWidth(50);
    pausePB->setMaximumWidth(50);
    pausePB->setDisabled(true);
    playPB->setDisabled(true);
    timer = new QTimer(this);

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
    QVBoxLayout *bigLayout = new QVBoxLayout();
    QVBoxLayout *cfopLayout = new QVBoxLayout();
    QVBoxLayout *cfopLabelLayout = new QVBoxLayout();
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QHBoxLayout *cfopInformationLayout = new QHBoxLayout();
    QHBoxLayout *cfopMainLayout = new QHBoxLayout();
    QVBoxLayout *infoLayout = new QVBoxLayout();
    QHBoxLayout *playLayout = new QHBoxLayout();

    QLabel *crossTitle = new QLabel("Cross", this);
    QLabel *f2lTitle = new QLabel("F2L", this);
    QLabel *ollTitle = new QLabel("OLL", this);
    QLabel *pllTitle = new QLabel("PLL", this);

    crossTitle->setMaximumWidth(50);
    f2lTitle->setMaximumWidth(50);
    ollTitle->setMaximumWidth(50);
    pllTitle->setMaximumWidth(50);

    cfopLabelLayout->addWidget(crossTitle);
    cfopLabelLayout->addWidget(f2lTitle);
    cfopLabelLayout->addWidget(ollTitle);
    cfopLabelLayout->addWidget(pllTitle);

    cfopLayout->addWidget(crossLabel);
    cfopLayout->addWidget(f2lLabel);
    cfopLayout->addWidget(ollLabel);
    cfopLayout->addWidget(pllLabel);

    playLayout->addWidget(playPB);
    playLayout->addWidget(pausePB);
    playLayout->addWidget(timeLE);

    cfopMainLayout->addLayout(cfopLabelLayout);
    cfopMainLayout->addLayout(cfopLayout);

    cfopInformationLayout->addLayout(cfopMainLayout);

    infoLayout->addWidget(nbMovesLabel);
    infoLayout->addWidget(infoPB);
    nbMovesLabel->setFixedWidth(200);
    cfopInformationLayout->addLayout(infoLayout);

    mainLayout->addWidget(pastMovePB);
    mainLayout->addWidget(actMoveLabel);
    mainLayout->addWidget(nextMovePB);
    mainLayout->addLayout(cfopInformationLayout);

    bigLayout->addLayout(playLayout);
    bigLayout->addLayout(mainLayout);

    groupBox->setLayout(bigLayout);

    QVBoxLayout *megaMainLayout = new QVBoxLayout();

    megaMainLayout->addWidget(groupBox);

    connect(pastMovePB, SIGNAL(clicked()), this, SLOT(pastMove()));
    connect(nextMovePB, SIGNAL(clicked()), this, SLOT(nextMove()));
    connect(infoPB, SIGNAL(clicked()), this, SLOT(infoSlot()));
    connect(playPB, SIGNAL(clicked()), this, SLOT(playSlot()));
    connect(pausePB, SIGNAL(clicked()), this, SLOT(pauseSlot()));
    connect(timer, SIGNAL(timeout()), this, SLOT(nextMove()));

    this->setLayout(megaMainLayout);
}

/**
 * Display a brief information when the information button is pressed by the user.
 */
void ResolutionWidget::infoSlot()
{
    QMessageBox infoBox;
    QString infoText;
    infoText += "The notation works as follows. Each letter represents a face rotation:<br/>";
    infoText += "<ul><li>U is <b>up</b></li><li>F is <b>front</b></li><li>R is <b>right</b></li><li>L is <b>left</b></li><li>D is <b>down</b></li><li>B is <b>back</b></li></ul>";
    infoText += "<br/>The letter tells you to move that face clockwise by a quarter turn. ";
    infoText += "A letter with an apostrophe tells you to move that face anticlockwise by a quarter turn. ";
    infoText += "A letter with a 2 tells you to move that face by half a turn.<br/><br/>";
    infoText += "If you intend to use that notation for the resolution step, don't forget to keep the yellow face ";
    infoText += "up and the red face againt you, as the program solves it this way.";
    infoText += "<br/><br/>More info at <a href=\"http://solvethecube.com/notation\">http://solvethecube.com/notation</a>.";
    infoBox.setInformativeText(infoText);
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
    playPB->setEnabled(true);

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
    playPB->setDisabled(true);
    pausePB->setDisabled(true);
    timer->stop();
}

void ResolutionWidget::playSlot(){
    if(CFOPlist.size() > 0){
        timer->start((timeLE->text().toDouble()) * 1000);
        playPB->setDisabled(true);
        pausePB->setDisabled(false);
    }
}

void ResolutionWidget::pauseSlot(){
    if(timer->isActive()){
        timer->stop();
        playPB->setDisabled(false);
        pausePB->setDisabled(true);
    }
}
