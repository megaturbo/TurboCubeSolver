#include "resolutionwidget.h"

#include <QBoxLayout>
#include <QFontDatabase>
#include <QGroupBox>
#include <QDebug>

ResolutionWidget::ResolutionWidget(QWidget *parent)
    : QWidget(parent)
{
    QString rdDefault = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/Fonts/reservoirdogs.ttf")).at(0);
    QFont rdFont(rdDefault);
    rdFont.setPointSize(30);

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

    cfopLayout->addWidget(crossLabel);
    cfopLayout->addWidget(f2lLabel);
    cfopLayout->addWidget(ollLabel);
    cfopLayout->addWidget(pllLabel);

    mainLayout->addWidget(pastMovePB);
    mainLayout->addWidget(actMoveLabel);
    mainLayout->addWidget(nextMovePB);
    mainLayout->addLayout(cfopLayout);

    groupBox->setLayout(mainLayout);

    QVBoxLayout *megaMainLayout = new QVBoxLayout();

    megaMainLayout->addWidget(groupBox);

    this->setLayout(megaMainLayout);
}

void ResolutionWidget::newSolveSequence(QString solveSequence)
{
    actMoveID = 0;
    QStringList cfop = solveSequence.split("]");

    qDebug() << solveSequence;

    // remove the first character which is '[' cuz of the string concatenation
    for(int i = 0; i < cfop.length(); i++)
    {
        cfop[i].remove(1, 1);
    }

    resolutionSequence = new QStringList(cfop.join(' '));

    QStringList crossList = cfop.at(0).split(' ');
    QStringList f2lPairsList = cfop.at(1).split('|');
    QStringList ollList = cfop.at(2).split(' ');
    QStringList pllList = cfop.at(3).split(' ');

    crossLabel->setText(crossList.join(' '));
    f2lLabel->setText(f2lPairsList.join(' '));
    ollLabel->setText(ollList.join(' '));
    pllLabel->setText(pllList.join(' '));
}
