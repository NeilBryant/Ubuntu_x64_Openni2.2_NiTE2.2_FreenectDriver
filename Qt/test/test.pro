#-------------------------------------------------
#
# Project created by QtCreator 2014-05-22T23:03:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    colorlistener.cpp

HEADERS  += mainwindow.h \
    colorlistener.h

FORMS    += mainwindow.ui

INCLUDEPATH +=	/home/y/kinect/Demo/OpenNI2_Include\
		/home/y/kinect/Demo/NiTE2_Include

LIBS += -L/home/y/kinect/Demo -lOpenNI2 -lOpenNI2.jni -lNiTE2 -lNiTE2.jni
