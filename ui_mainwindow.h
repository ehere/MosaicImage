/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *pic_original;
    QLabel *pic_process;
    QTextBrowser *height;
    QTextBrowser *width;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QTextBrowser *percentage;
    QLabel *label_5;
    QLabel *status;
    QProgressBar *progressBar;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *pic_path;
    QPushButton *btn_1;
    QPushButton *btn_2;
    QLineEdit *pic_folder;
    QPushButton *btn_3;
    QLineEdit *pic_final_path;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1199, 775);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pic_original = new QLabel(centralWidget);
        pic_original->setObjectName(QStringLiteral("pic_original"));
        pic_original->setGeometry(QRect(20, 250, 551, 411));
        pic_original->setAutoFillBackground(true);
        pic_process = new QLabel(centralWidget);
        pic_process->setObjectName(QStringLiteral("pic_process"));
        pic_process->setGeometry(QRect(620, 250, 551, 411));
        pic_process->setAutoFillBackground(true);
        height = new QTextBrowser(centralWidget);
        height->setObjectName(QStringLiteral("height"));
        height->setGeometry(QRect(450, 130, 101, 21));
        width = new QTextBrowser(centralWidget);
        width->setObjectName(QStringLiteral("width"));
        width->setGeometry(QRect(300, 130, 101, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(420, 130, 16, 21));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(190, 130, 61, 21));
        label_3->setFont(font);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(190, 160, 181, 21));
        label_4->setFont(font);
        percentage = new QTextBrowser(centralWidget);
        percentage->setObjectName(QStringLiteral("percentage"));
        percentage->setGeometry(QRect(400, 160, 151, 21));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(610, 70, 141, 21));
        label_5->setFont(font);
        status = new QLabel(centralWidget);
        status->setObjectName(QStringLiteral("status"));
        status->setGeometry(QRect(760, 70, 221, 21));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(610, 100, 371, 23));
        progressBar->setValue(24);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(200, 680, 181, 21));
        label_6->setFont(font);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(820, 680, 181, 21));
        label_7->setFont(font);
        pic_path = new QLineEdit(centralWidget);
        pic_path->setObjectName(QStringLiteral("pic_path"));
        pic_path->setGeometry(QRect(110, 20, 371, 31));
        btn_1 = new QPushButton(centralWidget);
        btn_1->setObjectName(QStringLiteral("btn_1"));
        btn_1->setGeometry(QRect(480, 20, 75, 31));
        btn_2 = new QPushButton(centralWidget);
        btn_2->setObjectName(QStringLiteral("btn_2"));
        btn_2->setGeometry(QRect(480, 70, 75, 31));
        pic_folder = new QLineEdit(centralWidget);
        pic_folder->setObjectName(QStringLiteral("pic_folder"));
        pic_folder->setGeometry(QRect(110, 70, 371, 31));
        btn_3 = new QPushButton(centralWidget);
        btn_3->setObjectName(QStringLiteral("btn_3"));
        btn_3->setGeometry(QRect(980, 20, 75, 31));
        pic_final_path = new QLineEdit(centralWidget);
        pic_final_path->setObjectName(QStringLiteral("pic_final_path"));
        pic_final_path->setGeometry(QRect(610, 20, 371, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1199, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pic_original->setText(QString());
        pic_process->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "X", 0));
        label_3->setText(QApplication::translate("MainWindow", "\340\270\202\340\270\231\340\270\262\340\270\224\340\270\243\340\270\271\340\270\233", 0));
        label_4->setText(QApplication::translate("MainWindow", "\340\270\242\340\271\210\340\270\255\340\270\202\340\270\231\340\270\262\340\270\224\340\270\243\340\270\271\340\270\233\340\270\225\340\271\211\340\270\231\340\270\211\340\270\232\340\270\261\340\270\232\340\271\200\340\270\253\340\270\245\340\270\267\340\270\255", 0));
        label_5->setText(QApplication::translate("MainWindow", "\340\270\252\340\270\226\340\270\262\340\270\231\340\270\260\340\270\201\340\270\262\340\270\243\340\270\227\340\270\263\340\270\207\340\270\262\340\270\231 : ", 0));
        status->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_6->setText(QApplication::translate("MainWindow", "\340\270\225\340\270\261\340\270\247\340\270\255\340\270\242\340\271\210\340\270\262\340\270\207\340\270\243\340\270\271\340\270\233\340\271\200\340\270\243\340\270\264\340\271\210\340\270\241\340\270\225\340\271\211\340\270\231", 0));
        label_7->setText(QApplication::translate("MainWindow", "\340\270\225\340\270\261\340\270\247\340\270\255\340\270\242\340\271\210\340\270\262\340\270\207\340\270\243\340\270\271\340\270\233\340\270\227\340\270\265\340\271\210\340\271\200\340\270\252\340\270\243\340\271\207\340\270\210\340\271\201\340\270\245\340\271\211\340\270\247", 0));
        pic_path->setText(QString());
        pic_path->setPlaceholderText(QApplication::translate("MainWindow", "\340\270\243\340\270\271\340\270\233\340\270\225\340\271\211\340\270\231\340\270\211\340\270\232\340\270\261\340\270\232", 0));
        btn_1->setText(QApplication::translate("MainWindow", "\340\270\204\340\271\211\340\270\231\340\270\253\340\270\262", 0));
        btn_2->setText(QApplication::translate("MainWindow", "\340\270\204\340\271\211\340\270\231\340\270\253\340\270\262", 0));
        pic_folder->setPlaceholderText(QApplication::translate("MainWindow", "\340\271\202\340\270\237\340\270\245\340\271\200\340\270\224\340\270\255\340\270\243\340\271\214\340\270\243\340\270\271\340\270\233\340\270\240\340\270\262\340\270\236\340\270\233\340\270\243\340\270\260\340\270\201\340\270\255\340\270\232", 0));
        btn_3->setText(QApplication::translate("MainWindow", "\340\270\204\340\271\211\340\270\231\340\270\253\340\270\262", 0));
        pic_final_path->setPlaceholderText(QApplication::translate("MainWindow", "\340\271\202\340\270\237\340\270\245\340\271\200\340\270\224\340\270\255\340\270\243\340\271\214\340\270\233\340\270\245\340\270\262\340\270\242\340\270\227\340\270\262\340\270\207", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
