#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPicture>
#include <iostream>
#include <opencv2\opencv.hpp>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <iomanip>
#include <direct.h>
#include <ctime>
#include "exif.h"

namespace fs = ::boost::filesystem;

using namespace std;
using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    string targetFolder;
    string originalImageFilePath;
    string imagesSetFolder;
    string pixelFolder;
    string index_filename = "index.txt";
    Size pixelSize;
    string input_image;
    double resize_x;
    double resize_y;
    char pixelize;
    char mosaicize;
    unsigned skip_interval;
private slots:
    void on_btn_select_image_clicked();

    void on_btn_select_imageset_folder_clicked();

    void on_btn_save_folder_clicked();

    void on_btn_start_clicked();

    void computePixelsAndIndex(const string& imagesSetFolder, const string& pixelFolder, Size s, const string& index_filename);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H


