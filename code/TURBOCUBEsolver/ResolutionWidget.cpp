#include "resolutionwidget.h"

#include <QBoxLayout>
#include <QFontDatabase>
#include <QGroupBox>
#include <QDebug>
#include "Cube.h"
#include <QMessageBox>

ResolutionWidget::ResolutionWidget(QWidget *parent)
    : QWidget(parent)
{
    initDisplay();
    resetDisplay();

}

void ResolutionWidget::refreshDisplay()
{

    QStringList actSequence = CFOPSequence.join(' ').split(' ');
    int lengthSequence = actSequence.length();

    if(actMoveID < lengthSequence){
        actMoveLabel->setText(actSequence.at(actMoveID));
    }else{
        actMoveLabel->clear();
    }

    int c_end = CFOPSequence.at(0).split(' ').size();
    int f_end = CFOPSequence.at(1).split(' ').size() + c_end;
    int o_end = CFOPSequence.at(2).split(' ').size() + f_end;
    int p_end = CFOPSequence.at(3).split(' ').size() + o_end;

    QString C = "";
    QString F = "";
    QString O = "";
    QString P = "";
    QString tmp;
    QString tmp2;

    for(int i = 0; i < CFOPlist.size(); i++)
    {
        tmp = "";
        tmp2 = " ";

        if(i == actMoveID)
        {
            tmp += "<b>";
            tmp2 += "</b>";
        }

        if(i < c_end)
        {
            C += tmp + CFOPlist.at(i) + tmp2;

        }else if(i < f_end)
        {
            F += tmp + CFOPlist.at(i) + tmp2;
        }else if(i < o_end)
        {
            O += tmp + CFOPlist.at(i) + tmp2;
        }else if(i < p_end)
        {
            P += tmp + CFOPlist.at(i) + tmp2;
        }
    }

    crossLabel->setText(C);
    f2lLabel->setText(F);
    ollLabel->setText(O);
    pllLabel->setText(P);

    if(actMoveID > 0)
    {
        pastMovePB->setEnabled(true);
    }else{
        pastMovePB->setDisabled(true);
    }
    if(actMoveID >= lengthSequence )
    {
        nextMovePB->setDisabled(true);
    }else{
        nextMovePB->setEnabled(true);
    }
}

void ResolutionWidget::pastMove()
{
    if(pastMovePB->isEnabled())
    {
        emit sendMove(Cube::reverseSequence(CFOPlist.at(actMoveID-1)));
        actMoveID--;
        refreshDisplay();
    }
}

void ResolutionWidget::nextMove()
{
    if(nextMovePB->isEnabled())
    {
        emit sendMove(CFOPlist.at(actMoveID));
        actMoveID++;
        refreshDisplay();
    }
}

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
    nextMovePB->setFixedSize(100,100);

    crossLabel = new QLabel(this);
    f2lLabel = new QLabel(this);
    ollLabel = new QLabel(this);
    pllLabel = new QLabel(this);

    crossLabel->setMinimumWidth(300);
    f2lLabel->setMinimumWidth(300);
    ollLabel->setMinimumWidth(300);
    pllLabel->setMinimumWidth(300);

    QGroupBox *groupBox = new QGroupBox("Resolution", this);
    QVBoxLayout *cfopLayout = new QVBoxLayout();
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QHBoxLayout *cfopInformationLayout = new QHBoxLayout();

    cfopLayout->addWidget(crossLabel);
    cfopLayout->addWidget(f2lLabel);
    cfopLayout->addWidget(ollLabel);
    cfopLayout->addWidget(pllLabel);

    cfopInformationLayout->addLayout(cfopLayout);
    cfopInformationLayout->addWidget(infoPB);

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

void ResolutionWidget::newSolveSequence(QString solveSequence)
{
    actMoveID = 0;
    resetDisplay();
    nextMovePB->setEnabled(true);

    QStringList cfop = solveSequence.split("]");
    // remove the first character which is '[' cuz of the string concatenation
    for(int i = 0; i < cfop.length(); i++)
    {
        cfop[i].remove(0, 1);
    }

    CFOPSequence.append(cfop.at(0));
    CFOPSequence.append(cfop.at(1).split('|').join(' '));  // cuz f2l 4 pairs
    CFOPSequence.append(cfop.at(2));
    CFOPSequence.append(cfop.at(3));

    CFOPlist = CFOPSequence.join(' ').split(' ');

    refreshDisplay();

}

void ResolutionWidget::resetDisplay()
{
    CFOPSequence.clear();
    CFOPlist.clear();
    actMoveLabel->clear();
    crossLabel->clear();
    f2lLabel->clear();
    ollLabel->clear();
    pllLabel->clear();
    pastMovePB->setDisabled(true);
    nextMovePB->setDisabled(true);
}
