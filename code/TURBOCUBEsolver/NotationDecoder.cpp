#include "NotationDecoder.h"

#include <QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    //Instanciation
    entry = new QLineEdit(this);
    btn_decode = new QPushButton("Decode",this);
    moves_instructions = new QTextEdit(this);

    //Layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(entry, 0, 0);
    layout->addWidget(btn_decode, 0, 1);
    layout->addWidget(moves_instructions, 1,0);

    this->setLayout(layout);

    connect(btn_decode, SIGNAL(clicked()), this, SLOT(decode()));

}

void Widget::decode()
{
    QString encoded = entry->text();
    QString *decoded = new QString();

    QStringList split = encoded.split(' ');

    foreach (QString move, split) {

        if(isAMove(move.at(0)))
        {
            decoded->append("Turn ");
            decoded->append(move[0]);

            if(move.length()>1)
            {
                if(move[1]=='2')
                {
                    decoded->append(" +180°");
                }else{
                    decoded->append(" -90°");
                }
            }else{
                decoded->append(" +90°");
            }
            decoded->append("\n");
        }

    }



    moves_instructions->setText(*decoded);
}

bool Widget::isAMove(QChar qc)
{
    char c = qc.toLatin1();
    switch (c) {
    case 'F':
    case 'B':
    case 'L':
    case 'R':
    case 'U':
    case 'D':
        return true;
        break;
    default:
        return false;
        break;
    }
}
