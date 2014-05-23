#ifndef COLORLISTENER_H
#define COLORLISTENER_H

#include <OpenNI.h>
#include <QVector>
#include <QMainWindow>

class ColorListener:public openni::VideoStream::NewFrameListener
{
public:
    ColorListener(QMainWindow *w,QVector<openni::VideoFrameRef> *frames,bool f);
    void onNewFrame(openni::VideoStream& vs);
private:
    QVector<openni::VideoFrameRef> *frames;
    QMainWindow *w;
    bool isUpdate;
};

#endif // COLORLISTENER_H
