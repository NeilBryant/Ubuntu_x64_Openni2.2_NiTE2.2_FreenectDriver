#include "colorlistener.h"
#include <QDebug>

ColorListener::ColorListener(QMainWindow *w,QVector<openni::VideoFrameRef> *frames,bool f)
{
    this->isUpdate = f;
    this->w = w;
    this->frames = frames;
}

void ColorListener::onNewFrame(openni::VideoStream& vs)
{
    openni::VideoFrameRef frame;
    vs.readFrame(&frame);
    frames->push_back(frame);
    if(isUpdate) w->update();
}
