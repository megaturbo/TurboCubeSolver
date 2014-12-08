/********************************************************************************
** Form generated from reading UI file 'turbocubesolver.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TURBOCUBESOLVER_H
#define UI_TURBOCUBESOLVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TURBOCUBEsolver
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TURBOCUBEsolver)
    {
        if (TURBOCUBEsolver->objectName().isEmpty())
            TURBOCUBEsolver->setObjectName(QStringLiteral("TURBOCUBEsolver"));
        TURBOCUBEsolver->resize(400, 300);
        menuBar = new QMenuBar(TURBOCUBEsolver);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        TURBOCUBEsolver->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TURBOCUBEsolver);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TURBOCUBEsolver->addToolBar(mainToolBar);
        centralWidget = new QWidget(TURBOCUBEsolver);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        TURBOCUBEsolver->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TURBOCUBEsolver);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TURBOCUBEsolver->setStatusBar(statusBar);

        retranslateUi(TURBOCUBEsolver);

        QMetaObject::connectSlotsByName(TURBOCUBEsolver);
    } // setupUi

    void retranslateUi(QMainWindow *TURBOCUBEsolver)
    {
        TURBOCUBEsolver->setWindowTitle(QApplication::translate("TURBOCUBEsolver", "TURBOCUBEsolver", 0));
    } // retranslateUi

};

namespace Ui {
    class TURBOCUBEsolver: public Ui_TURBOCUBEsolver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TURBOCUBESOLVER_H
