#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPicture>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_1_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*)"
                );
    ui->pic_path->setText(filename);
    if(QString::compare(filename, QString())!=0){
        QImage image;
        bool valid = image.load(filename);
        if(valid){
            ui->pic_original->setPixmap(QPixmap::fromImage(image));
        }else{
            //
        }
    }
}

void MainWindow::on_btn_2_clicked()
{
    QString folder = QFileDialog::getExistingDirectory(
                this,
                tr("Select Folder"),
                "C://",
                QFileDialog::ShowDirsOnly);
    ui->pic_folder->setText(folder);
}


void MainWindow::on_btn_3_clicked()
{
    QString folder = QFileDialog::getExistingDirectory(
                this,
                tr("Select Folder"),
                "C://",
                QFileDialog::ShowDirsOnly);
    ui->pic_final_path->setText(folder);
}



void MainWindow::on_btn_start_clicked()
{

}
