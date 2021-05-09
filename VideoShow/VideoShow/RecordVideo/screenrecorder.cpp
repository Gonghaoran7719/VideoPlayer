
#include "screenrecorder.h"

#include <QDateTime>
#include <QDebug>

ScreenRecorder::ScreenRecorder()
{
    m_videoThread = new GetVideoThread();
    m_audioThread = new GetVideoThread();

    m_saveVideoFileThread = new SaveVideoFileThread;
    //m_saveVideoFileThread = 0;
    m_videoThread->setSaveVideoFileThread(m_saveVideoFileThread);
    m_audioThread->setSaveVideoFileThread(m_saveVideoFileThread);

    connect( m_videoThread , SIGNAL(SIG_GetOneImage(QImage)) , this , SIGNAL(SIG_GetOneImage(QImage)) );
//    av_register_all();
//    avformat_network_init();
//    avdevice_register_all();
}


ScreenRecorder::~ScreenRecorder()
{
    delete m_videoThread;
    delete m_audioThread;

    if (m_saveVideoFileThread)
    {
        delete m_saveVideoFileThread;
    }

}

void ScreenRecorder::setFileName(char *str)
{
    if (m_saveVideoFileThread != NULL)
        m_saveVideoFileThread->setFileName(str);
}

ErroCode ScreenRecorder::init(QString videoDevName, bool useDesk,bool useCam , QString audioDevName, bool useAudio)
{
    m_useVideo = useDesk||useCam/*false*/;
    m_useAudio = useAudio/*false*/;

    if ( m_useVideo )
    {
        ErroCode code = m_videoThread->init(videoDevName,useDesk,useCam,"",false);
        if (code != SUCCEED)
        {
            qDebug()<<"视频初始化失败";
            return code;
        }
    }

    if (m_useAudio)
    {
        ErroCode code = m_audioThread->init("",false,false,audioDevName,useAudio);
        if (code != SUCCEED)
        {
            qDebug()<<"音频初始化失败";
            return code;
        }
    }


    if (m_saveVideoFileThread != NULL)
    {
        m_saveVideoFileThread->setContainsVideo(m_useVideo);
        m_saveVideoFileThread->setContainsAudio(m_useAudio);
    }

    return SUCCEED;
}

void ScreenRecorder::startRecord()
{
    if (m_saveVideoFileThread != NULL)
        m_saveVideoFileThread->startEncode();

    if (m_useVideo)
    {
        m_videoThread->startRecord();
    }

    if (m_useAudio)
    {
        m_audioThread->startRecord();
    }
}

void ScreenRecorder::pauseRecord()
{
    if (m_useVideo)
    {
        m_videoThread->pauseRecord();
    }

    if (m_useAudio)
    {
        m_audioThread->pauseRecord();
    }
}

void ScreenRecorder::restoreRecord()
{
    if (m_useVideo)
    {
        m_videoThread->restoreRecord();
    }

    if (m_useAudio)
    {
        m_audioThread->restoreRecord();
    }
}

void ScreenRecorder::stopRecord()
{    
    if (m_useAudio)
    {
        m_audioThread->stopRecord();
    }

//    if (m_useAudio)
//    {
//        while(m_audioThread->isRunning())
//        {
//            SDL_Delay(10);
//        }
//    }
    if (m_useVideo)
    {
        m_videoThread->stopRecord();
    }

//    if (m_useVideo)
//    {
//        while(m_videoThread->isRunning())
//        {
//            SDL_Delay(10);
//        }
//    }

    if (m_saveVideoFileThread != NULL)
        m_saveVideoFileThread->stopEncode();

}

void ScreenRecorder::setPicRange(int x,int y,int w,int h)
{
    m_videoThread->setPicRange(x,y,w,h);

    if (m_saveVideoFileThread != NULL)
    m_saveVideoFileThread->setWidth(w, h);

}

void ScreenRecorder::setVideoFrameRate(int value)
{
    if (m_saveVideoFileThread != NULL)
        m_saveVideoFileThread->setVideoFrameRate(value);
}

double ScreenRecorder::getVideoPts()
{
    if (m_saveVideoFileThread != NULL)
    {
        return m_saveVideoFileThread->getVideoPts();
    }
    else
    {
        return 0;
    }

}

double ScreenRecorder::getAudioPts()
{
    if (m_saveVideoFileThread != NULL)
    {
        return m_saveVideoFileThread->getAudioPts();
    }
    else
    {
        return 0;
    }
}
