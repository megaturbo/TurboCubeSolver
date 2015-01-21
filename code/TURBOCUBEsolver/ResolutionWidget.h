#ifndef RESOLUTIONWIDGET_H
#define RESOLUTIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class ResolutionWidget : public QWidget
{
    Q_OBJECT

public:
    ResolutionWidget(QWidget *parent = 0);
    void resetDisplay();

public slots:
    void newSolveSequence(QString);
    void pastMove();
    void nextMove();

private slots:
    void infoSlot();

signals:
    void sendMove(QString);

private:
    QPushButton *infoPB;
    QPushButton *nextMovePB;
    QPushButton *pastMovePB;
    QLabel *actMoveLabel;
    QLabel *crossLabel;
    QLabel *f2lLabel;
    QLabel *ollLabel;
    QLabel *pllLabel;
    QStringList CFOPSequence;
    QStringList CFOPlist;
    int startF;
    int startO;
    int startP;
    int actMoveID;

    void initDisplay();
    void refreshDisplay();

};

#endif // RESOLUTIONWIDGET_H
