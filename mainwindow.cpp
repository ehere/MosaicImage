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

/*
structure to map an image to its mean color
*/
struct ImageMean{
    string name;
    Vec3b mean;
};

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
self explanatory
*/
void printProgress(int percentage, unsigned elapsed, unsigned etl){
    cout << "\rProgress:|";
    char bar_length = 15;
    char number_of_progress_chars = round(percentage * bar_length / 100);

    for (unsigned j = 0; j < number_of_progress_chars; ++j) cout << "=";
    cout << ">";
    for (unsigned j = 0; j < bar_length - number_of_progress_chars; ++j) cout << " ";
    cout << "| " << percentage << "%, Time elapsed: " << elapsed << " seconds, ETL: " << etl << " seconds.";
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
void
computePixelsAndIndex(const string& imagesSetFolder, const string& pixelFolder, Size s, const string& index_filename){

    cout << "Pixelizing images from " << imagesSetFolder << ". This might take a while." << endl;
    vector<string> images;
    vector<string> extensions = { ".jpg", ".jpeg", ".JPG", ".JPEG" };
    get_all(imagesSetFolder, extensions, images);

    fs::remove_all(pixelFolder);
    fs::create_directory(pixelFolder);
    ofstream out_index(pixelFolder + index_filename);

    clock_t begin = clock();

    for (unsigned i = 0; i < images.size(); ++i)
    {
        Mat3b img = imread(images[i]);
        char orientation = extractEXIFOrientation(images[i]);
        rectifyByOrientation(img, orientation);

        Vec3b mean_color = mean(img);

        Mat3b resized;
        cv::resize(img, resized, s);

        ostringstream out_filename;
        out_filename << pixelFolder << setfill('0') << setw(5) << i << ".png";
        imwrite(out_filename.str(), resized);

        out_index << out_filename.str() << "\t" << (int)mean_color[0] << " " << (int)mean_color[1] << " " << (int)mean_color[2] << endl;

        //Measuring time for progress...
        clock_t end = clock();
        int percentage = round(double(i) * 100 / images.size());

        unsigned elapsed = double(end - begin) / CLOCKS_PER_SEC;
        unsigned etl = (double(elapsed) / i)*(images.size() - i);

        printProgress(percentage, elapsed, etl);
    }
    out_index.close();

    cout << endl << "Done." << endl;
}

/*
reads the precomputed mean colors from file
*/
void readIndexFile(const string& index_filename, vector<ImageMean>& index){
    ifstream in(index_filename);
    string line;
    while (getline(in, line)){
        stringstream ss(line);
        ImageMean im;
        unsigned r, g, b;
        ss >> im.name >> b >> g >> r;

        im.mean = Vec3b(b, g, r);
        index.push_back(im);
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
                current_working_directory().c_str(),
                "All files (*.*)"
                );
    ui->pic_path->setText(filename);
    this->originalImageFilePath = filename.toUtf8().constData();
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
                current_working_directory().c_str(),
                QFileDialog::ShowDirsOnly);
    ui->pic_folder->setText(folder);
    this->imagesSetFolder = folder.toUtf8().constData();
}


void MainWindow::on_btn_3_clicked()
{
    QString folder = QFileDialog::getExistingDirectory(
                this,
                tr("Select Folder"),
                current_working_directory().c_str(),
                QFileDialog::ShowDirsOnly);
    ui->pic_final_path->setText(folder);
    this->targetFolder = folder.toUtf8().constData();
    this->targetFolder.append("/output.png");

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
    //pixel_folder
    this->pixelFolder = "pixels/";
    //pixel_size
    this->pixelSize = Size(50, 50);
    //resize
    this->resize_x = 0.1;
    this->resize_y = 0.1;
    //skip_interval
    this->skip_interval = 100;

    fs::path dir(this->pixelFolder);
    if(fs::create_directory(this->pixelFolder)){
        std::cerr<< "Directory Created: "<< this->pixelFolder <<std::endl;
    }

    computePixelsAndIndex(this->imagesSetFolder, this->pixelFolder, this->pixelSize, this->index_filename);


    cout << "Rendering mosaic for image " << this->originalImageFilePath << "..." << endl;
    vector<ImageMean> index;
    readIndexFile(this->pixelFolder + this->index_filename, index);

    Mat3b src = imread(this->originalImageFilePath);

    cv::resize(src, src, Size(0, 0), this->resize_x, this->resize_y);
    Mat3b output(src.rows*this->pixelSize.height, src.cols*this->pixelSize.width);
    vector<unsigned char> forbidden(index.size());

    for (int i = 0; i < src.rows; ++i){
        for (int j = 0; j < src.cols; ++j){

            if (((i*src.cols + j) % this->skip_interval) == 0)
                forbidden = vector<unsigned char>(index.size());

            Vec3b color = src(i, j);

            ImageMean best_match = nearestImage(index, color, forbidden);
            Mat3b pixel = imread(best_match.name);

            Rect bound(j*this->pixelSize.width, i*this->pixelSize.height, this->pixelSize.width, this->pixelSize.height);
            pixel.copyTo(output.rowRange(i*this->pixelSize.height, i*this->pixelSize.height + this->pixelSize.height).colRange(j*this->pixelSize.width, j*this->pixelSize.width + this->pixelSize.width));
        }
    }
    ui->pic_process->setPixmap(QPixmap::fromImage(Mat2QImage(output)));
    imwrite(this->targetFolder, output);

    cout << endl << "Done. Mosaic image has been written to output.png" << endl;

}
