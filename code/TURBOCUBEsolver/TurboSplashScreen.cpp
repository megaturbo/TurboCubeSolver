#include "TurboSplashScreen.h"
#include <QCloseEvent>
#include <QDebug>

TurboSplashScreen::TurboSplashScreen()
{
    pixmap0 = new QPixmap(":Pictures/splash/splash0.png");
    pixmap1 = new QPixmap(":Pictures/splash/splash1.png");
    this->setPixmap(*pixmap0);

    timer.start();

}

void TurboSplashScreen::drawContents(QPainter *painter)
{
    float remaining = 2500 - timer.elapsed();

    float op0 = remaining / 2500;
    float op1 = 1.0 - op0;

    qDebug() << "ela: " << timer.elapsed();
    qDebug() << "op0: " << op0;
    qDebug() << "op1: " << op1;

    painter->setOpacity(op0);
    painter->drawPixmap(0, 0, *pixmap0);
    painter->setOpacity(op1);
    painter->drawPixmap(0, 0, *pixmap1);

    update();
}
void TurboSplashScreen::closeEvent(QCloseEvent *event)
{
    emit splashTerminated();
    event->accept();
}

void TurboSplashScreen::mousePressEvent(QMouseEvent *)
{
    this->close();
}
