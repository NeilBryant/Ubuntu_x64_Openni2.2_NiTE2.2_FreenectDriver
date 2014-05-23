#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <OpenNI.h>
#include <QVector>
#include <QKeyEvent>
#include <NiTE.h>

namespace Ui {
class MainWindow;
}

struct point
{
    float x;
    float y;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::MainWindow *ui;
    openni::VideoFrameRef frameDepth;
    openni::VideoFrameRef frameColor;
    openni::VideoStream streamColor;
    openni::VideoStream streamDepth;
    openni::Device devAnyDevice;
    QVector<openni::VideoFrameRef> colorframes;
    QVector<openni::VideoFrameRef> depthframes;
    nite::UserTrackerFrameRef mUserFrame;
    nite::UserTracker mUserTracker;
};

#endif // MAINWINDOW_H
