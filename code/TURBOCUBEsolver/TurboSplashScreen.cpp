#include "TurboSplashScreen.h"
#include <QCloseEvent>
#include <QDebug>
#include <QGlobal.h>
#include <QTime>

TurboSplashScreen::TurboSplashScreen(int displayTime)
{
    messages = new QStringList();
    messages->append("This splash screen looks nice, doesn't it ?");
    messages->append("Such cube");
    messages->append("much matrix");
    messages->append("so rubiks");
    messages->append("wow");
    messages->append("MANY PINK SO AMAZE");
    messages->append("turbodoge");
    messages->append("Painting stickers...");
    messages->append("Fixing cubie parity...");
    messages->append("Carving wooden cubies...");
    messages->append("Lubricating processor...");
    messages->append("TURBO-scrambling cube frenetically...");
    messages->append("Swapping mispositionned cubies...");

    pixmap0 = new QPixmap(":Pictures/splash/splash0.png");
    pixmap1 = new QPixmap(":Pictures/splash/splash1.png");
    this->setPixmap(*pixmap0);

    this->displayTime = displayTime;

    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());
    msg = messages->at(qrand() % messages->size());
    middle = false;

    timer.start();
}

TurboSplashScreen::~TurboSplashScreen()
{

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

    if(remaining < displayTime / 2 && !middle){
        qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());
        msg = messages->at(qrand() % messages->size());
        middle = true;
    }
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
