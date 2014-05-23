#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <colorlistener.h>
#include <QImage>
#include <QColor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openni::OpenNI::initialize();
    devAnyDevice.open(openni::ANY_DEVICE);
    setGeometry(0,0,1280,480);
    nite::NiTE::initialize();
    mUserTracker.create();

    streamDepth.create( devAnyDevice, openni::SENSOR_DEPTH );
    streamColor.create( devAnyDevice, openni::SENSOR_COLOR );
    streamColor.addNewFrameListener(new ColorListener(this,&colorframes,0));
    streamDepth.addNewFrameListener(new ColorListener(this,&depthframes,1));
    streamColor.start();
    streamDepth.start();
}

MainWindow::~MainWindow()
{
    delete ui;
    streamDepth.destroy();
    streamColor.destroy();
    devAnyDevice.close();
    nite::NiTE::shutdown();
    openni::OpenNI::shutdown();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    if(!colorframes.isEmpty())
    {
        openni::VideoFrameRef frame(*colorframes.begin());
        QImage colorImage((uchar*)frame.getData(),frame.getWidth(),frame.getHeight(),QImage::Format_RGB888);
        p.drawImage(0,0,colorImage);
        colorframes.pop_front();
    }
    if(!depthframes.isEmpty())
    {
        openni::VideoFrameRef frame(*depthframes.begin());
        QImage depthImage((uchar*)frame.getData(),frame.getWidth(),frame.getHeight(),QImage::Format_RGB16);
        p.drawImage(640,0,depthImage);
        depthframes.pop_front();
    }
    mUserTracker.readFrame(&mUserFrame);
    const nite::Array<nite::UserData> &mUsers = mUserFrame.getUsers();
    for(int i=0;i<mUsers.getSize();++i)
    {
        const nite::UserData &tUser = mUsers[i];
        if(tUser.isNew())
        {
            mUserTracker.startSkeletonTracking(tUser.getId());
        }

        const nite::Skeleton &mSkeleton = tUser.getSkeleton();
        if(mSkeleton.getState() == nite::SKELETON_TRACKED)
        {
            const nite::Point3f &mHEAD = mSkeleton.getJoint(nite::JOINT_HEAD).getPosition();
            const nite::Point3f &mNECK = mSkeleton.getJoint(nite::JOINT_NECK).getPosition();
            const nite::Point3f &mLEFT_SHOULDER = mSkeleton.getJoint(nite::JOINT_LEFT_SHOULDER).getPosition();
            const nite::Point3f &mRIGHT_SHOULDER = mSkeleton.getJoint(nite::JOINT_RIGHT_SHOULDER).getPosition();
            const nite::Point3f &mLEFT_ELBOW = mSkeleton.getJoint(nite::JOINT_LEFT_ELBOW).getPosition();
            const nite::Point3f &mRIGHT_ELBOW = mSkeleton.getJoint(nite::JOINT_RIGHT_ELBOW).getPosition();
            const nite::Point3f &mLEFT_HAND = mSkeleton.getJoint(nite::JOINT_LEFT_HAND).getPosition();
            const nite::Point3f &mRIGHT_HAND = mSkeleton.getJoint(nite::JOINT_RIGHT_HAND).getPosition();
            const nite::Point3f &mTORSO = mSkeleton.getJoint(nite::JOINT_TORSO).getPosition();
            const nite::Point3f &mLEFT_HIP = mSkeleton.getJoint(nite::JOINT_LEFT_HIP).getPosition();
            const nite::Point3f &mRIGHT_HIP = mSkeleton.getJoint(nite::JOINT_RIGHT_HIP).getPosition();
            const nite::Point3f &mLEFT_KNEE = mSkeleton.getJoint(nite::JOINT_LEFT_KNEE).getPosition();
            const nite::Point3f &mRIGHT_KNEE = mSkeleton.getJoint(nite::JOINT_RIGHT_KNEE).getPosition();
            const nite::Point3f &mLEFT_FOOT = mSkeleton.getJoint(nite::JOINT_LEFT_FOOT).getPosition();
            const nite::Point3f &mRIGHT_FOOT = mSkeleton.getJoint(nite::JOINT_RIGHT_FOOT).getPosition();

            point HEAD;
            point NECK;
            point LEFT_SHOULDER;
            point RIGHT_SHOULDER;
            point LEFT_ELBOW;
            point RIGHT_ELBOW;
            point LEFT_HAND;
            point RIGHT_HAND;
            point TORSO;
            point LEFT_HIP;
            point RIGHT_HIP;
            point LEFT_KNEE;
            point RIGHT_KNEE;
            point LEFT_FOOT;
            point RIGHT_FOOT;

            mUserTracker.convertJointCoordinatesToDepth(mHEAD.x,mHEAD.y,mHEAD.z,&HEAD.x,&HEAD.y);
            mUserTracker.convertJointCoordinatesToDepth(mNECK.x,mNECK.y,mNECK.z,&NECK.x,&NECK.y);
            mUserTracker.convertJointCoordinatesToDepth(mLEFT_SHOULDER.x,mLEFT_SHOULDER.y,mLEFT_SHOULDER.z,&LEFT_SHOULDER.x,&LEFT_SHOULDER.y);
            mUserTracker.convertJointCoordinatesToDepth(mRIGHT_SHOULDER.x,mRIGHT_SHOULDER.y,mRIGHT_SHOULDER.z,&RIGHT_SHOULDER.x,&RIGHT_SHOULDER.y);
            mUserTracker.convertJointCoordinatesToDepth(mLEFT_ELBOW.x,mLEFT_ELBOW.y,mLEFT_ELBOW.z,&LEFT_ELBOW.x,&LEFT_ELBOW.y);
            mUserTracker.convertJointCoordinatesToDepth(mRIGHT_ELBOW.x,mRIGHT_ELBOW.y,mRIGHT_ELBOW.z,&RIGHT_ELBOW.x,&RIGHT_ELBOW.y);
            mUserTracker.convertJointCoordinatesToDepth(mLEFT_HAND.x,mLEFT_HAND.y,mLEFT_HAND.z,&LEFT_HAND.x,&LEFT_HAND.y);
            mUserTracker.convertJointCoordinatesToDepth(mRIGHT_HAND.x,mRIGHT_HAND.y,mRIGHT_HAND.z,&RIGHT_HAND.x,&RIGHT_HAND.y);
            mUserTracker.convertJointCoordinatesToDepth(mTORSO.x,mTORSO.y,mTORSO.z,&TORSO.x,&TORSO.y);
            mUserTracker.convertJointCoordinatesToDepth(mLEFT_HIP.x,mLEFT_HIP.y,mLEFT_HIP.z,&LEFT_HIP.x,&LEFT_HIP.y);
            mUserTracker.convertJointCoordinatesToDepth(mRIGHT_HIP.x,mRIGHT_HIP.y,mRIGHT_HIP.z,&RIGHT_HIP.x,&RIGHT_HIP.y);
            mUserTracker.convertJointCoordinatesToDepth(mLEFT_KNEE.x,mLEFT_KNEE.y,mLEFT_KNEE.z,&LEFT_KNEE.x,&LEFT_KNEE.y);
            mUserTracker.convertJointCoordinatesToDepth(mRIGHT_KNEE.x,mRIGHT_KNEE.y,mRIGHT_KNEE.z,&RIGHT_KNEE.x,&RIGHT_KNEE.y);
            mUserTracker.convertJointCoordinatesToDepth(mLEFT_FOOT.x,mLEFT_FOOT.y,mLEFT_FOOT.z,&LEFT_FOOT.x,&LEFT_FOOT.y);
            mUserTracker.convertJointCoordinatesToDepth(mRIGHT_FOOT.x,mRIGHT_FOOT.y,mRIGHT_FOOT.z,&RIGHT_FOOT.x,&RIGHT_FOOT.y);
            p.setPen(QColor(255,0,0));
            p.setBrush(QColor(255,0,0));
            p.drawEllipse(HEAD.x,HEAD.y,10,10);
            p.drawEllipse(NECK.x,NECK.y,10,10);
            p.drawEllipse(LEFT_SHOULDER.x,LEFT_SHOULDER.y,10,10);
            p.drawEllipse(RIGHT_SHOULDER.x,RIGHT_SHOULDER.y,10,10);
            p.drawEllipse(LEFT_ELBOW.x,LEFT_ELBOW.y,10,10);
            p.drawEllipse(RIGHT_ELBOW.x,RIGHT_ELBOW.y,10,10);
            p.drawEllipse(LEFT_HAND.x,LEFT_HAND.y,10,10);
            p.drawEllipse(RIGHT_HAND.x,RIGHT_HAND.y,10,10);
            p.drawEllipse(TORSO.x,TORSO.y,10,10);
            p.drawEllipse(LEFT_HIP.x,LEFT_HIP.y,10,10);
            p.drawEllipse(RIGHT_HIP.x,RIGHT_HIP.y,10,10);
            p.drawEllipse(LEFT_KNEE.x,LEFT_KNEE.y,10,10);
            p.drawEllipse(RIGHT_KNEE.x,RIGHT_KNEE.y,10,10);
            p.drawEllipse(LEFT_FOOT.x,LEFT_FOOT.y,10,10);
            p.drawEllipse(RIGHT_FOOT.x,RIGHT_FOOT.y,10,10);
            p.drawLine(LEFT_HAND.x,LEFT_HAND.y,LEFT_ELBOW.x,LEFT_ELBOW.y);
            p.drawLine(LEFT_ELBOW.x,LEFT_ELBOW.y,LEFT_SHOULDER.x,LEFT_SHOULDER.y);
            p.drawLine(LEFT_SHOULDER.x,LEFT_SHOULDER.y,TORSO.x,TORSO.y);
            p.drawLine(RIGHT_HAND.x,RIGHT_HAND.y,RIGHT_ELBOW.x,RIGHT_ELBOW.y);
            p.drawLine(RIGHT_ELBOW.x,RIGHT_ELBOW.y,RIGHT_SHOULDER.x,RIGHT_SHOULDER.y);
            p.drawLine(RIGHT_SHOULDER.x,RIGHT_SHOULDER.y,TORSO.x,TORSO.y);
            p.drawLine(LEFT_FOOT.x,LEFT_FOOT.y,LEFT_KNEE.x,LEFT_KNEE.y);
            p.drawLine(LEFT_KNEE.x,LEFT_KNEE.y,LEFT_HIP.x,LEFT_HIP.y);
            p.drawLine(LEFT_HIP.x,LEFT_HIP.y,TORSO.x,TORSO.y);
            p.drawLine(RIGHT_FOOT.x,RIGHT_FOOT.y,RIGHT_KNEE.x,RIGHT_KNEE.y);
            p.drawLine(RIGHT_KNEE.x,RIGHT_KNEE.y,RIGHT_HIP.x,RIGHT_HIP.y);
            p.drawLine(RIGHT_HIP.x,RIGHT_HIP.y,TORSO.x,TORSO.y);
            p.drawLine(HEAD.x,HEAD.y,NECK.x,NECK.y);
            p.drawLine(NECK.x,NECK.y,TORSO.x,TORSO.y);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
        case Qt::Key_Escape:
            close();
            break;
    }
}
