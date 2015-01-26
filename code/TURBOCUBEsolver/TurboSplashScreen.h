#ifndef TURBOSPLASHSCREEN_H
#define TURBOSPLASHSCREEN_H

#include <QSplashScreen>
#include <QPainter>
#include <QElapsedTimer>

class TurboSplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    TurboSplashScreen(int displayTime);
    ~TurboSplashScreen();
    virtual void mousePressEvent(QMouseEvent *);
    void addMessage(QString message);

protected:
    virtual void drawContents(QPainter *painter);

private:
    QPixmap *pixmap0;
    QPixmap *pixmap1;
    QElapsedTimer timer;
    QStringList *messages;
    QString msg;
    bool middle;

    int displayTime;

    void closeEvent(QCloseEvent *event);

signals:
    void splashTerminated();

};

#endif // TURBOSPLASHSCREEN_H
