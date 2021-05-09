
#ifndef GetVideoThread_H
#define GetVideoThread_H

#include <QThread>
#include"videoplayer.h"
extern "C"
{
    #include"SDL_thread.h"
}

#include "savevideofile.h"

#define SFM_REFRESH_CAMERA  (SDL_USEREVENT + 2)
enum ErroCode
{
    AudioOpenFailed = 0,
    VideoOpenFailed,
    AudioDecoderOpenFailed,
    VideoDecoderOpenFailed,
    SUCCEED
};


class GetVideoThread : public QThread
{
    Q_OBJECT

public:
    explicit GetVideoThread();
    ~GetVideoThread();
    ErroCode init(QString videoDevName, bool useDesk, bool useCam, QString audioDevName, bool useAudio);

    void deInit();

    void startRecord();
    void pauseRecord();
    void restoreRecord();
    void stopRecord();

    void setPicRange(int x,int y,int w,int h);

    void setSaveVideoFileThread(SaveVideoFileThread * p);

    static int sfp_refresh_camera(void *opaque);
signals:
    void SIG_GetOneImage(QImage img);
protected:
    void run();

private:

    AVFormatContext	*pFormatCtx;
    int				i, videoindex ,audioindex;
    AVCodecContext	*pCodecCtx,*aCodecCtx;

    AVFrame	*pFrame,*aFrame,*pFrameYUV , *pFrameRGB;
    uint8_t *out_buffer , *out_buffer_rgb;

    ///以下变量用于音频重采样
    /// 由于新版ffmpeg编码aac只支持AV_SAMPLE_FMT_FLTP，因此采集到音频数据后直接进行重采样
    /// 重采样成44100的32 bits 双声道数据(AV_SAMPLE_FMT_FLTP)
    AVFrame *aFrame_ReSample;
    SwrContext *swrCtx;

    enum AVSampleFormat in_sample_fmt; //输入的采样格式
    enum AVSampleFormat out_sample_fmt;//输出的采样格式 16bit PCM
    int in_sample_rate;//输入的采样率
    int out_sample_rate;//输出的采样率
    int audio_tgt_channels; ///av_get_channel_layout_nb_channels(out_ch_layout);
    int out_ch_layout;
    ///用于存储读取到的音频数据
    /// 由于平面模式的pcm存储方式为：LLLLLLLLLLLLLLLLLLLLLRRRRRRRRRRRRRRRRRRRRR，因此这里需要将左右声道数据分开存放
    DECLARE_ALIGNED(16, uint8_t, audio_buf_L) [AVCODEC_MAX_AUDIO_FRAME_SIZE * 4];
    unsigned int audio_buf_size_L;
    DECLARE_ALIGNED(16, uint8_t, audio_buf_R) [AVCODEC_MAX_AUDIO_FRAME_SIZE * 4];
    unsigned int audio_buf_size_R;

    ///////////////////////////////////////////////////////////////////////////////
    int pic_x;
    int pic_y;
    int pic_w;
    int pic_h;

    struct SwsContext *img_convert_ctx_rgb  ,*img_convert_ctx;
    bool m_isRun;
    bool m_pause;


    SaveVideoFileThread * m_saveVideoFileThread;
public:
    int64_t lastReadPacktTime  ;
    SDL_Thread* video_tid;
    bool isBegin;
};

#endif // GetVideoThread_H
