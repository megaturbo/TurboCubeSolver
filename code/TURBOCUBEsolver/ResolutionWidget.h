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
    void reset();

public slots:
    void newSolveSequence(QString);

signals:
    void sendMove(QString);

private:
    QPushButton *nextMovePB;
    QPushButton *pastMovePB;
    QLabel *actMoveLabel;
    QLabel *crossLabel;
    QLabel *f2lLabel;
    QLabel *ollLabel;
    QLabel *pllLabel;
    QStringList *resolutionSequence;
    int actMoveID;

};

#endif // RESOLUTIONWIDGET_H
