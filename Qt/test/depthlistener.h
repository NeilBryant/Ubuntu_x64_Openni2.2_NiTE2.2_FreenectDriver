#ifndef DEPTHLISTENER_H
#define DEPTHLISTENER_H

#include <OpenNI.h>

class DepthListener:public openni::VideoStream::NewFrameListener
{
public:
    DepthListener();
};

#endif // DEPTHLISTENER_H
