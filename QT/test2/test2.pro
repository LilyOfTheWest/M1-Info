QT       += core
QT       -= gui
TARGET = test2
CONFIG   += console
CONFIG   -= app_bundle
CONFIG  -= qt
TEMPLATE = app
SOURCES += main.cpp
INCLUDEPATH += C:/OpenCV-3.1.0/release/include
LIBS += -LC:/OpenCV-3.1.0/release/x86/mingw/lib \
    -lopencv_core310 \
    -lopencv_imgcodecs310 \
    -lopencv_highgui310 \
    -lopencv_imgproc310 \
    -lopencv_features2d310 \
    -lopencv_calib3d310
OTHER_FILES +=\
    img.jpg
