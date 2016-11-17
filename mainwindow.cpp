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
#include <map>

namespace fs = ::boost::filesystem;

using namespace std;
using namespace cv;


bool isInVector(const string& str, const vector<string>& vec){
    for (string s : vec){
        if (s == str)
            return true;
    }
    return false;
}

/*
seeks recursively in root for all files having extension ext,
and builds the list ret
*/
void get_all(const fs::path& root, const vector<string>& extensions, vector<string>& ret)
{
    if (!fs::exists(root) || !fs::is_directory(root)) return;

    fs::recursive_directory_iterator it(root);
    fs::recursive_directory_iterator endit;

    while (it != endit)
    {
        if (fs::is_regular_file(*it) && isInVector(it->path().extension().string(), extensions))
            ret.push_back(it->path().string());
        ++it;

    }
}

/*
computes the mean color of an image
*/
Vec3b mean(const Mat3b& m){
    unsigned long b = 0;
    unsigned long g = 0;
    unsigned long r = 0;

    unsigned char *data = (unsigned char*)(m.data);
    for (int r_c = 0; r_c < m.rows; ++r_c){
        for (int c_c = 0; c_c < m.cols * 3; c_c = c_c + 3){
            b += data[m.step * r_c + c_c];
            g += data[m.step * r_c + c_c + 1];
            r += data[m.step * r_c + c_c + 2];
        }
    }
    unsigned nPix = m.rows*m.cols;

    return Vec3b(b / nPix, g / nPix, r / nPix);
}

/*
extracts exif orientations from jpeg files.
useful if you have pictures taken with smartphones
*/
char extractEXIFOrientation(const string& img_name){
    FILE *fp = fopen(img_name.c_str(), "rb");
    if (!fp) {
        //printf("Can't open file.\n");
    }

    fseek(fp, 0, SEEK_END);
    unsigned long fsize = ftell(fp);
    rewind(fp);
    unsigned char *buf = new unsigned char[fsize];
    if (fread(buf, 1, fsize, fp) != fsize) {
        //printf("Can't read file.\n");
        delete[] buf;
    }
    fclose(fp);

    // Parse EXIF
    easyexif::EXIFInfo result;
    int code = result.parseFrom(buf, fsize);
    delete[] buf;
    if (code) {
        //printf("Error parsing EXIF: code %d\n", code);
    }

    return result.Orientation;
}

/*
rotates an image clockwise
*/
void rotateClockwise(Mat& img){
    transpose(img, img);
    flip(img, img, 1);
}

/*
fixes image given its exif orientation
*/
void rectifyByOrientation(Mat3b& img, char orientation){
    switch (orientation){
    case 1: break; //fine
    case 6: //rotate clockwise
        rotateClockwise(img);
        break;
    case 3: //flip vertically
        //ignorance is the law
        rotateClockwise(img);
        rotateClockwise(img);
        break;
    case 8: // rotate counterclockwise
        //even more ignorance!!!!
        rotateClockwise(img);
        rotateClockwise(img);
        rotateClockwise(img);
        break;
    default: break;
    }
}

/*
precomputes all the small images ("pixels") that will form the mosaic.
Also stores in an index (index_filename) the mapping with the mean color.
*/
void MainWindow::computePixelsAndIndex(const string& imagesSetFolder, Size s){

    vector<string> images;
    vector<string> extensions = { ".jpg", ".jpeg", ".JPG", ".JPEG" };
    get_all(imagesSetFolder, extensions, images);


    for (unsigned i = 0; i < images.size(); ++i)
    {
        Mat3b img = imread(images[i]);
        char orientation = extractEXIFOrientation(images[i]);
        rectifyByOrientation(img, orientation);

        Vec3b mean_color = mean(img);

        Mat3b resized;
        cv::resize(img, resized, s);

        this->pixelImageMap[to_string(i)] = resized;
        ImageMean mean;
        mean.name = to_string(i);
        mean.mean = Vec3b((int)mean_color[0], (int)mean_color[1], (int)mean_color[2]);
        this->pixelMeanVector.push_back(mean);

        int percentage = round(double(i) * 100 / images.size());
        ui->status->setText("Pixelizing images...");
        ui->progressBar->setValue(percentage);

    }
}


/*
utility structure for sorting (by similarity)
*/
struct idxVal{
    int idx;
    double val;

    bool operator<(idxVal conf){
        if (val < conf.val)return true;
        return false;
    }
};

/*
returns the nearest image given the pixel color and the forbidden ones
*/
ImageMean nearestImage(const vector<ImageMean>& index, Vec3b color, vector<unsigned char>& forbidden){
    vector<idxVal> ivals;
    for (unsigned i = 0; i < index.size(); ++i){
        Vec3b conf = index[i].mean;
        idxVal ival;
        ival.idx = i;
        ival.val = norm(color, conf);

        ivals.push_back(ival);
    }
    sort(ivals.begin(), ivals.end());

    for (unsigned i = 0; i < ivals.size(); i++){
        if (!forbidden[ivals[i].idx]){
            forbidden[ivals[i].idx] = 1;
            return index[ivals[i].idx];
        }
    }
    ImageMean err;
    return err;
}

/*
reads the file holding parameters settings
*/
std::string current_working_directory()
{
    char working_directory[MAX_PATH+1] ;
    GetCurrentDirectoryA( sizeof(working_directory), working_directory ) ; // **** win32 specific ****
    return working_directory ;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("Photo Mosaic");
    ui->width->setValidator(new QIntValidator(20,150,this));
    ui->height->setValidator(new QIntValidator(20,150,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_select_image_clicked()
{
    string directory = this->originalImageFilePath;
    if(directory.empty()){
        directory = current_working_directory();
    }
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                directory.c_str(),
                "All files (*.*)"
                );
    if(!filename.toUtf8().isEmpty()){
        ui->pic_path->setText(filename);
        this->originalImageFilePath = filename.toUtf8().constData();

        if(QString::compare(filename, QString())!=0){
            QImage image;
            bool valid = image.load(filename);
            if(valid){
                ui->pic_original->setPixmap(QPixmap::fromImage(image).scaled(ui->pic_original->size(),Qt::KeepAspectRatio));
            }
        }
    }
}

void MainWindow::on_btn_select_imageset_folder_clicked()
{
    string directory = this->imagesSetFolder;
    if(directory.empty()){
        directory = current_working_directory();
    }
    QString folder = QFileDialog::getExistingDirectory(
                this,
                tr("Select Folder"),
                directory.c_str(),
                QFileDialog::ShowDirsOnly);
    if(!folder.toUtf8().isEmpty()){
        ui->pic_folder->setText(folder);
        this->imagesSetFolder = folder.toUtf8().constData();
    }
}


void MainWindow::on_btn_save_folder_clicked()
{
    string directory = this->targetFolder;
    if(directory.empty()){
        directory = current_working_directory().append("/untitled.png");
    }
    QString folder = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                  directory.c_str(),
                                                  tr("Images (*.png *.xpm *.jpg)"));
    if(!folder.toUtf8().isEmpty()){
        ui->pic_final_path->setText(folder);
        this->targetFolder = folder.toUtf8().constData();
    }
}

QImage Mat2QImage(const cv::Mat3b &src) {
        QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
        for (int y = 0; y < src.rows; ++y) {
                const cv::Vec3b *srcrow = src[y];
                QRgb *destrow = (QRgb*)dest.scanLine(y);
                for (int x = 0; x < src.cols; ++x) {
                        destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
                }
        }
        return dest;
}

void MainWindow::on_btn_start_clicked()
{
    ui->btn_start->setEnabled(false);
    //pixel_size
    int width = ui->width->text().toInt();
    int height = ui->height->text().toInt();
    this->pixelSize = Size(width, height);
    //resize
    float percent = ui->comboBox->currentText().toFloat();
    this->resize_x = percent/100.0;
    this->resize_y = percent/100.0;
    //skip_interval
    this->skip_interval = 100;

    computePixelsAndIndex(this->imagesSetFolder, this->pixelSize);

    vector<ImageMean> index = this->pixelMeanVector;

    Mat3b src = imread(this->originalImageFilePath);

    cv::resize(src, src, Size(0, 0), this->resize_x, this->resize_y);
    Mat3b output(src.rows*this->pixelSize.height, src.cols*this->pixelSize.width);
    vector<unsigned char> forbidden(index.size());

    int percentage = 0;
    ui->status->setText("Rendering images...");
    ui->progressBar->setValue(percentage);
    long count = 0;
    for (int i = 0; i < src.rows; ++i){
        for (int j = 0; j < src.cols; ++j){
            count += 1;
            if(count % 500 == 0){
                percentage = round((count * 100) / (src.rows * src.cols));
                ui->progressBar->setValue(percentage);
            }

            if (((i*src.cols + j) % this->skip_interval) == 0)
                forbidden = vector<unsigned char>(index.size());

            Vec3b color = src(i, j);

            ImageMean best_match = nearestImage(index, color, forbidden);

            Mat3b pixel = this->pixelImageMap[best_match.name];

            Rect bound(j*this->pixelSize.width, i*this->pixelSize.height, this->pixelSize.width, this->pixelSize.height);
            pixel.copyTo(output.rowRange(i*this->pixelSize.height, i*this->pixelSize.height + this->pixelSize.height).colRange(j*this->pixelSize.width, j*this->pixelSize.width + this->pixelSize.width));
        }
    }
    ui->status->setText("Saving File...");
    ui->status->repaint();
    ui->pic_process->setPixmap(QPixmap::fromImage(Mat2QImage(output)).scaled(ui->pic_process->size(),Qt::KeepAspectRatio));
    imwrite(this->targetFolder, output);
    ui->status->setText("Done.");
    ui->progressBar->setValue(100);
    ui->btn_start->setEnabled(true);
}


