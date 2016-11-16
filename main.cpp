#include "mainwindow.h"
#include <QApplication>





using namespace std;


/*
main function
*/
int main(int argc, char** argv){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
