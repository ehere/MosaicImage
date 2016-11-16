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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *pic_original;
    QLabel *pic_process;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *status;
    QProgressBar *progressBar;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *pic_path;
    QPushButton *btn_select_image;
    QPushButton *btn_select_imageset_folder;
    QLineEdit *pic_folder;
    QPushButton *btn_save_folder;
    QLineEdit *pic_final_path;
    QPushButton *btn_start;
    QLineEdit *width;
    QLineEdit *height;
    QComboBox *comboBox;
    QLabel *label_8;
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
        pic_original->setScaledContents(true);
        pic_process = new QLabel(centralWidget);
        pic_process->setObjectName(QStringLiteral("pic_process"));
        pic_process->setGeometry(QRect(620, 250, 551, 411));
        pic_process->setAutoFillBackground(true);
        pic_process->setScaledContents(true);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(390, 130, 16, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 130, 141, 31));
        label_3->setFont(font);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(230, 180, 221, 31));
        label_4->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(610, 70, 141, 31));
        label_5->setFont(font);
        status = new QLabel(centralWidget);
        status->setObjectName(QStringLiteral("status"));
        status->setGeometry(QRect(700, 70, 231, 31));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(false);
        progressBar->setGeometry(QRect(610, 100, 331, 23));
        progressBar->setValue(0);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 670, 571, 41));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(620, 670, 561, 41));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);
        pic_path = new QLineEdit(centralWidget);
        pic_path->setObjectName(QStringLiteral("pic_path"));
        pic_path->setGeometry(QRect(110, 20, 371, 31));
        btn_select_image = new QPushButton(centralWidget);
        btn_select_image->setObjectName(QStringLiteral("btn_select_image"));
        btn_select_image->setGeometry(QRect(480, 20, 75, 31));
        btn_select_imageset_folder = new QPushButton(centralWidget);
        btn_select_imageset_folder->setObjectName(QStringLiteral("btn_select_imageset_folder"));
        btn_select_imageset_folder->setGeometry(QRect(480, 70, 75, 31));
        pic_folder = new QLineEdit(centralWidget);
        pic_folder->setObjectName(QStringLiteral("pic_folder"));
        pic_folder->setGeometry(QRect(110, 70, 371, 31));
        btn_save_folder = new QPushButton(centralWidget);
        btn_save_folder->setObjectName(QStringLiteral("btn_save_folder"));
        btn_save_folder->setGeometry(QRect(980, 20, 75, 31));
        pic_final_path = new QLineEdit(centralWidget);
        pic_final_path->setObjectName(QStringLiteral("pic_final_path"));
        pic_final_path->setGeometry(QRect(610, 20, 371, 31));
        btn_start = new QPushButton(centralWidget);
        btn_start->setObjectName(QStringLiteral("btn_start"));
        btn_start->setGeometry(QRect(950, 70, 111, 51));
        width = new QLineEdit(centralWidget);
        width->setObjectName(QStringLiteral("width"));
        width->setGeometry(QRect(250, 130, 113, 31));
        height = new QLineEdit(centralWidget);
        height->setObjectName(QStringLiteral("height"));
        height->setGeometry(QRect(430, 130, 121, 31));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(470, 180, 41, 31));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(520, 180, 31, 31));
        label_8->setFont(font);
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
        label_5->setText(QApplication::translate("MainWindow", "\340\270\252\340\270\226\340\270\262\340\270\231\340\270\260 : ", 0));
        status->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_6->setText(QApplication::translate("MainWindow", "\340\270\225\340\270\261\340\270\247\340\270\255\340\270\242\340\271\210\340\270\262\340\270\207\340\270\243\340\270\271\340\270\233\340\271\200\340\270\243\340\270\264\340\271\210\340\270\241\340\270\225\340\271\211\340\270\231", 0));
        label_7->setText(QApplication::translate("MainWindow", "\340\270\225\340\270\261\340\270\247\340\270\255\340\270\242\340\271\210\340\270\262\340\270\207\340\270\243\340\270\271\340\270\233\340\270\227\340\270\265\340\271\210\340\271\200\340\270\252\340\270\243\340\271\207\340\270\210\340\271\201\340\270\245\340\271\211\340\270\247", 0));
        pic_path->setText(QString());
        pic_path->setPlaceholderText(QApplication::translate("MainWindow", "\340\270\243\340\270\271\340\270\233\340\270\225\340\271\211\340\270\231\340\270\211\340\270\232\340\270\261\340\270\232", 0));
        btn_select_image->setText(QApplication::translate("MainWindow", "\340\270\204\340\271\211\340\270\231\340\270\253\340\270\262", 0));
        btn_select_imageset_folder->setText(QApplication::translate("MainWindow", "\340\270\204\340\271\211\340\270\231\340\270\253\340\270\262", 0));
        pic_folder->setPlaceholderText(QApplication::translate("MainWindow", "\340\271\202\340\270\237\340\270\245\340\271\200\340\270\224\340\270\255\340\270\243\340\271\214\340\270\243\340\270\271\340\270\233\340\270\240\340\270\262\340\270\236\340\270\233\340\270\243\340\270\260\340\270\201\340\270\255\340\270\232", 0));
        btn_save_folder->setText(QApplication::translate("MainWindow", "\340\270\204\340\271\211\340\270\231\340\270\253\340\270\262", 0));
        pic_final_path->setPlaceholderText(QApplication::translate("MainWindow", "\340\271\202\340\270\237\340\270\245\340\271\200\340\270\224\340\270\255\340\270\243\340\271\214\340\270\233\340\270\245\340\270\262\340\270\242\340\270\227\340\270\262\340\270\207", 0));
        btn_start->setText(QApplication::translate("MainWindow", "\340\271\200\340\270\243\340\270\264\340\271\210\340\270\241\340\270\227\340\270\263\340\270\207\340\270\262\340\270\231", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
         << QApplication::translate("MainWindow", "9", 0)
         << QApplication::translate("MainWindow", "10", 0)
        );
        label_8->setText(QApplication::translate("MainWindow", "%", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
