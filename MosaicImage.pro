#-------------------------------------------------
#
# Project created by QtCreator 2016-11-16T14:45:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MosaicImage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    exif.cpp

HEADERS  += mainwindow.h \
    exif.h

FORMS    += mainwindow.ui
INCLUDEPATH += C:/opencv/bulid-mingw/install/include \
                C:/boost/include
LIBS += -LC:/opencv/bulid-mingw/install/x86/mingw/bin \
        -lopencv_core310 \
        -lopencv_highgui310 \
        -lopencv_imgcodecs310 \
        -lopencv_imgproc310 \
        -LC:/boost/libs \
        -lboost_filesystem-mgw53-mt-1_62 \
        -lboost_system-mgw53-mt-1_62
