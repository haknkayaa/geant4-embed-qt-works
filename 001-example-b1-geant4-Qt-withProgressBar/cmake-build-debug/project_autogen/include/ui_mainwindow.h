/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *runButton;
    QPushButton *chooseFile;
    QProgressBar *progressBar;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(460, 225);
        MainWindow->setMouseTracking(true);
        MainWindow->setTabletTracking(true);
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setCursor(QCursor(Qt::ArrowCursor));
        centralwidget->setMouseTracking(true);
        centralwidget->setTabletTracking(true);
        centralwidget->setFocusPolicy(Qt::StrongFocus);
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(3, 3, 0, 0);
        runButton = new QPushButton(centralwidget);
        runButton->setObjectName(QString::fromUtf8("runButton"));

        verticalLayout_2->addWidget(runButton);

        chooseFile = new QPushButton(centralwidget);
        chooseFile->setObjectName(QString::fromUtf8("chooseFile"));

        verticalLayout_2->addWidget(chooseFile);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        verticalLayout_2->addWidget(progressBar);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 460, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        runButton->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        chooseFile->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "EAbs: ", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "EGap:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "LAbs:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "LGap:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
