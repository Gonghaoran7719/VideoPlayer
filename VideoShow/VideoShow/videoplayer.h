#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QThread>
#include<QImage>
#include"packetqueue.h"



extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libavutil/pixfmt.h"
    #include "libswscale/swscale.h"
    #include "libavformat/avformat.h"
    #include "libavdevice/avdevice.h"
    #include"libswresample/swresample.h"
    #include"libavutil/time.h"
    #include "SDL.h"
}

enum PlayerState
{
    Playing = 0,
    Pause,
    Stop
};

class VideoPlayer ;
typedef struct VideoState {
    AVFormatContext *pFormatCtx;//相当于视频”文件指针”
    ///////////////音频///////////////////////////////////
    AVStream    *audio_st; //音频流
    PacketQueue *audioq;//音频缓冲队列
    AVCodecContext *pAudioCodecCtx ;//音频解码器信息指针
    int audioStream;//视频音频流索引
    double audio_clock; ///<pts of last decoded frame 音频时钟
    SDL_AudioDeviceID audioID; //音频ID
    AVFrame out_frame; //设置参数，供音频解码后的swr_alloc_set_opts使用。
    //////////////////////////////////////////////////////
    ///////////////视频///////////////////////////////////
    AVStream    *video_st; //视频流
    PacketQueue *videoq;//视频队列
    AVCodecContext *pCodecCtx ;//音频解码器信息指针
    int videoStream;//视频音频流索引
    double video_clock; ///<pts of last decoded frame 视频时钟
    SDL_Thread *video_tid;  //视频线程id
    /////////////////////////////////////////////////////

    //////////////////////////////////////////////////////
    /// 播放控制的变量
    bool isPause;//暂停标志
    bool quit; //停止
    bool readFinished; //读线程文件读取完毕
    bool readThreadFinished; //读取线程是否结束
    bool videoThreadFinished; // 视频线程是否结束
    /////////////////////////////////////////////////////
    //// 跳转相关的变量
    int             seek_req; //跳转标志 -- 读线程
    int64_t         seek_pos; //跳转的位置 -- 微秒
    int             seek_flag_audio;//跳转标志 -- 用于音频线程中
    int             seek_flag_video;//跳转标志 -- 用于视频线程中
    double          seek_time; //跳转的时间(秒)  值和seek_pos是一样的
    //////////////////////////////////////////////////////
    bool beginFrame; //播放网络视频的起始帧标志
    //////////////////////////////////////////////////////
    int64_t start_time; //单位 微秒
    VideoState()
    {
        audio_clock = video_clock  = start_time = 0;
    }
    VideoPlayer* m_player;//用于调用函数
} VideoState;


class VideoPlayer : public QThread
{
    Q_OBJECT
public:
    explicit VideoPlayer();

signals:
    void SIG_GetOneImage( QImage image);
    void SIG_PlayerStateChanged(int state);
    void SIG_TotalTime( qint64 time );
public slots:
    void SendGetOneImage(QImage &img);
public:
    void run(); // 线程函数  当你调用 start() --> run()
    QString m_fileName;//

    ////////////////////////////
    ///播放控制
    void play();
    void pause();
    void stop( bool isWait); //是否阻塞等待结束
    void setFileName(const QString &fileName);
    void seek(int64_t pos);//跳转

    VideoState m_videoState; //音视频同步状态成员
    PlayerState m_playerState;
    PlayerState getPlayerState() const;
    double getCurrentTime();
    int64_t getTotalTime();

};

#endif // VIDEOPLAYER_H
