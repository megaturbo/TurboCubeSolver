#ifndef RESOLUTIONWIDGET_H
#define RESOLUTIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>

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
    void playpauseSlot();

private slots:
    void infoSlot();

signals:
    void sendMove(QString);

private:
    QPushButton *infoPB;
    QPushButton *nextMovePB;
    QPushButton *pastMovePB;
    QPushButton *playpausePB;
    QLabel *actMoveLabel;
    QLabel *crossLabel;
    QLabel *f2lLabel;
    QLabel *ollLabel;
    QLabel *pllLabel;
    QLabel *nbMovesLabel;
    QStringList CFOPlist;
    QLineEdit *timeLE;
    QTimer *timer;

    // Part sizes
    int actMoveID;
    int endC;
    int endF;
    int endO;
    int endP;

    void initDisplay();
    void refreshDisplay();

};

#endif // RESOLUTIONWIDGET_H
