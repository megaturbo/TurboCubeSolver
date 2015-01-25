#ifndef TURBOSPLASHSCREEN_H
#define TURBOSPLASHSCREEN_H

#include <QSplashScreen>
#include <QPainter>
#include <QElapsedTimer>

class TurboSplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    TurboSplashScreen();
    virtual void mousePressEvent(QMouseEvent *);

protected:
    virtual void drawContents(QPainter *painter);

private:
    QPixmap *pixmap0;
    QPixmap *pixmap1;
    QPixmap *actPixmap;

    QElapsedTimer timer;

    void closeEvent(QCloseEvent *event);

signals:
    void splashTerminated();

};

#endif // TURBOSPLASHSCREEN_H
