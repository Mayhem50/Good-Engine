/********************************************************************************
** Form generated from reading UI file 'brdf.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRDF_H
#define UI_BRDF_H

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

class Ui_BRDFClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BRDFClass)
    {
        if (BRDFClass->objectName().isEmpty())
            BRDFClass->setObjectName(QStringLiteral("BRDFClass"));
        BRDFClass->resize(600, 400);
        menuBar = new QMenuBar(BRDFClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        BRDFClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BRDFClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BRDFClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BRDFClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BRDFClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BRDFClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BRDFClass->setStatusBar(statusBar);

        retranslateUi(BRDFClass);

        QMetaObject::connectSlotsByName(BRDFClass);
    } // setupUi

    void retranslateUi(QMainWindow *BRDFClass)
    {
        BRDFClass->setWindowTitle(QApplication::translate("BRDFClass", "BRDF", 0));
    } // retranslateUi

};

namespace Ui {
    class BRDFClass: public Ui_BRDFClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRDF_H
