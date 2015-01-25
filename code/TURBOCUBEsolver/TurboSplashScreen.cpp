#include "TurboSplashScreen.h"
#include <QCloseEvent>
#include <QDebug>

TurboSplashScreen::TurboSplashScreen(int displayTime)
{
    messages = new QStringList();
    messages->append("This splash screen looks nice, isn't it ?");

    pixmap0 = new QPixmap(":Pictures/splash/splash0.png");
    pixmap1 = new QPixmap(":Pictures/splash/splash1.png");
    this->setPixmap(*pixmap0);

    this->displayTime = displayTime;

    timer.start();
}

void TurboSplashScreen::drawContents(QPainter *painter)
{
    int elapsed = timer.elapsed();
    float remaining = displayTime - elapsed;

    float op0 = remaining / displayTime;
    float op1 = 1.0 - op0;

    painter->setOpacity(op0);
    painter->drawPixmap(0, 0, *pixmap0);
    painter->setOpacity(op1);
    painter->drawPixmap(0, 0, *pixmap1);

    painter->setOpacity(1);
    painter->setPen(QColor(255,136,0));
    painter->setFont(QFont("Arial", 15));

    if(elapsed > displayTime)
    {
        elapsed = displayTime-1;
    }

    QString msg = messages->at(elapsed/(displayTime/messages->size()));

    painter->drawText(QRect(0, this->height()-50, this->width(), this->height()-80), Qt::AlignHCenter, msg);

    update();
}

void TurboSplashScreen::addMessage(QString message)
{
    messages->append(message);
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
