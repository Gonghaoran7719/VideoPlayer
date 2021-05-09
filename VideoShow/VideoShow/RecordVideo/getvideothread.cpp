

#include "getvideothread.h"

#include <QTimer>
#include <QDateTime>
#include <QDebug>


SDL_Event SDLevent;
int GetVideoThread::sfp_refresh_camera(void *opaque)
{
    GetVideoThread * pthis = (GetVideoThread *)opaque;
    while ( pthis->m_isRun )
    {
        SDLevent.type = SFM_REFRESH_CAMERA;
        SDL_PushEvent(&SDLevent);
        SDL_Delay(20);
    }
    return 0;
}

void Yuv420Cut(int x,int y,int desW,int desH,int srcW,int srcH,uint8_t *srcBuffer,uint8_t *desBuffer)
{
    int tmpRange;
    int bufferIndex;

    int yIndex = 0;
    bufferIndex = 0 + x + y*srcW;
    tmpRange = srcW * desH;
    for (int i=0;i<tmpRange;) //逐行拷贝Y分量数据
    {
        memcpy(desBuffer+yIndex,srcBuffer+bufferIndex+i,desW);
        i += srcW;
        yIndex += desW;
    }

    int uIndex = desW * desH;
    int uIndexStep = srcW/2;
    int uWidthCopy = desW/2;
    bufferIndex = srcW * srcH+x/2 + y /2 *srcW / 2;
    tmpRange = srcW * desH / 4;
    for (int i=0;i<tmpRange;) //逐行拷贝U分量数据
    {
        memcpy(desBuffer+uIndex,srcBuffer+bufferIndex+i,uWidthCopy);
        i += uIndexStep;
        uIndex += uWidthCopy;
    }


    int vIndex = desW * desH +  desW * desH /4;
    int vIndexStep = srcW/2;
    int vWidthCopy = desW/2;
    bufferIndex = srcW*srcH + srcW*srcH/4 + x/2 + y /2 *srcW / 2;
    tmpRange = srcW * desH / 4;
    for (int i=0;i<tmpRange;) //逐行拷贝V分量数据
    {
        memcpy(desBuffer+vIndex,srcBuffer+bufferIndex+i,vWidthCopy);
        i += vIndexStep;
        vIndex += vWidthCopy;
    }
}

GetVideoThread::GetVideoThread()
{
    m_isRun = false;

    pFormatCtx = NULL;
    out_buffer = NULL;
    aFrame = NULL;
    pFrame = NULL;
    pFrameYUV = NULL;
    pFrameRGB = NULL;
    pCodecCtx = NULL;
    aCodecCtx = NULL;

    m_pause = false;

    m_saveVideoFileThread = NULL;

    audio_buf_size_L = 0;
    audio_buf_size_R = 0;

}


GetVideoThread::~GetVideoThread()
{

}
static int interrupt_cb(void *ctx)
{
    GetVideoThread* pThis = (GetVideoThread*)ctx;
    int  timeout  = 3;
    if(av_gettime() - pThis->lastReadPacktTime > timeout *1000 *1000)
    {
        return -1;
    }
    return 0;
}
ErroCode GetVideoThread::init(QString videoDevName, bool useDesk, bool useCam, QString audioDevName, bool useAudio)
{
    isBegin = true;
        av_register_all();
        avformat_network_init();
        avdevice_register_all();

    AVCodec			*pCodec = NULL;
    AVCodec			*aCodec = NULL;

    pFormatCtx = avformat_alloc_context();
//    pFormatCtx->interrupt_callback.callback = interrupt_cb;
//    pFormatCtx->interrupt_callback.opaque = (void*)this;


    if (useAudio)
    {
        QString audioDevOption = QString("audio=%1").arg(audioDevName);
        AVInputFormat *ifmt = av_find_input_format("dshow");
        std::string str = audioDevOption.toStdString();
        char* buf = (char*)str.c_str();
        lastReadPacktTime = av_gettime();
        if(avformat_open_input(&pFormatCtx,buf,ifmt,NULL)!=0){
            fprintf(stderr,"Couldn't open input stream audio.（无法打开输入流）\n");
            return AudioOpenFailed;
        }
    }

    if (useDesk)
    {
        QString videoDevOption = QString("video=%1").arg("desktop");
        AVInputFormat *ifmt1=av_find_input_format("gdigrab");
        AVDictionary *d = nullptr;
         av_dict_set(&d,"framerate","25",0); //帧率 15
        lastReadPacktTime = av_gettime();
        if(avformat_open_input(&pFormatCtx,"desktop",ifmt1,&d)!=0){
            qDebug()<<"Couldn't open input stream video.（无法打开输入流）\n";
            return VideoOpenFailed;
        }
    }else if(useCam)
    {
        //Set own video device's name
        AVDictionary *d = nullptr;
        av_dict_set_int(&d, "rtbufsize", 52428800, 0);
        av_dict_set(&d,"videosize","640x480",0); //可以在这里设置摄像头采样分辨率
        av_dict_set(&d,"framerate","25",0); //帧率

        QString videoDevOption = QString("video=%1").arg(videoDevName);
        AVInputFormat *ifmt1=av_find_input_format("dshow");
        qDebug()<<videoDevOption;
        std::string str = videoDevOption.toStdString();
        char* buf = (char*)str.c_str();
        lastReadPacktTime = av_gettime();
        if(avformat_open_input(&pFormatCtx,buf,ifmt1,&d)!=0){
            qDebug()<<"打开另一个视频流";

            AVInputFormat *ifmt=av_find_input_format("vfwcap");
            if( avformat_open_input(&pFormatCtx, 0, ifmt,&d) != 0 )
            {
                qDebug()<<"无法打开所有视频流";
                return VideoOpenFailed;
            }
        }
    }

    videoindex=-1;
    pCodecCtx = NULL;
    //寻找到获取的流
    if(avformat_find_stream_info(pFormatCtx,NULL)<0)
    {
       // printf("Couldn't find stream information.\n");
        return VideoOpenFailed;
    }

    if (useDesk||useCam)
    {

        for(i=0; i<pFormatCtx->nb_streams; i++)
            if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
            {
                videoindex=i;
                break;
            }
        if(videoindex==-1)
        {
            printf("Didn't find a video stream.（没有找到视频流）\n");
            return VideoOpenFailed;
        }

        pCodecCtx = pFormatCtx->streams[videoindex]->codec;
        pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
        if(pCodec == NULL)
        {
            printf("video Codec not found.\n");
            return VideoDecoderOpenFailed;
        }

        if(avcodec_open2(pCodecCtx, pCodec,NULL)<0)
        {
            printf("Could not open video codec.\n");
            return VideoDecoderOpenFailed;
        }

        pFrame=av_frame_alloc();
        pFrameYUV=av_frame_alloc();
        pFrameRGB=av_frame_alloc();
        out_buffer=(uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));
        avpicture_fill((AVPicture *)pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);

        out_buffer_rgb=(uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_RGB32, pCodecCtx->width, pCodecCtx->height));
        avpicture_fill((AVPicture *)pFrameRGB, out_buffer_rgb, AV_PIX_FMT_RGB32, pCodecCtx->width, pCodecCtx->height);

        img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
                pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
                AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

        img_convert_ctx_rgb = sws_getContext(pCodecCtx->width, pCodecCtx->height,
                pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
                AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);

         setPicRange(0,0,pCodecCtx->width, pCodecCtx->height);

         this->m_saveVideoFileThread->setWidth(pCodecCtx->width, pCodecCtx->height);
    }

    audioindex = -1;
    aCodecCtx = NULL;
    if (useAudio)
    {

        for(i=0; i<pFormatCtx->nb_streams; i++)
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO)
        {
            audioindex=i;
            break;
        }
        if(audioindex==-1)
        {
            printf("Didn't find a video stream.（没有找到视频流）\n");
            return AudioOpenFailed;
        }

        aCodecCtx = pFormatCtx->streams[audioindex]->codec;

        aCodec = avcodec_find_decoder(aCodecCtx->codec_id);
        if(aCodec == NULL)
        {
            printf("audio Codec not found.\n");
            return AudioDecoderOpenFailed;
        }

        if(avcodec_open2(aCodecCtx, aCodec,NULL)<0)
        {
            printf("Could not open video codec.\n");
            return AudioDecoderOpenFailed;
        }

        qDebug()<<"audio info:";
        qDebug()<<"audio info:"<<aCodecCtx->sample_fmt<<aCodecCtx->bit_rate<<aCodecCtx->sample_rate<<aCodecCtx->channels;

        aFrame=av_frame_alloc();
        ///////////////////////////////////////////////
        //重采样设置选项-----------------------------------------------------------start
        aFrame_ReSample = nullptr;

        //frame->16bit 44100 PCM 统一音频采样格式与采样率
        swrCtx = nullptr;

        //输入的声道布局
        int in_ch_layout;

        /// 新版ffmpeg编码aac只支持输入AV_SAMPLE_FMT_FLTP的数据
        /// 强制将音频重采样成44100 双声道  AV_SAMPLE_FMT_FLTP
        //重采样设置选项----------------
        //输入的采样格式
        in_sample_fmt = aCodecCtx->sample_fmt;
        //输出的采样格式 32bit PCM
        out_sample_fmt = AV_SAMPLE_FMT_FLTP;
        //输入的采样率
        in_sample_rate = aCodecCtx->sample_rate;
        //输入的声道布局
        in_ch_layout = aCodecCtx->channel_layout;

        //输出的采样率
        out_sample_rate = 44100;
        //输出的声道布局

        //输出的声道布局
        out_ch_layout = AV_CH_LAYOUT_STEREO;
        audio_tgt_channels = av_get_channel_layout_nb_channels(out_ch_layout);

//        //输出的声道布局
//        out_ch_layout = av_get_default_channel_layout(audio_tgt_channels); ///AV_CH_LAYOUT_STEREO
//        out_ch_layout &= ~AV_CH_LAYOUT_STEREO;

        if (in_ch_layout <= 0)
        {
            if (aCodecCtx->channels == 2)
            {
                in_ch_layout = AV_CH_LAYOUT_STEREO;
            }
            else
            {
                in_ch_layout = AV_CH_LAYOUT_MONO;
            }
        }
//qDebug()<<"1111:"<<in_sample_fmt<<in_sample_rate<<in_ch_layout<<aCodecCtx->channels<<out_sample_fmt<<out_sample_rate<<out_ch_layout<<audio_tgt_channels;
        swrCtx = swr_alloc_set_opts(nullptr, out_ch_layout, out_sample_fmt, out_sample_rate,
                                             in_ch_layout, in_sample_fmt, in_sample_rate, 0, nullptr);

        /** Open the resampler with the specified parameters. */
        int ret = swr_init(swrCtx);
        if (ret < 0)
        {
            char buff[128]={0};
            av_strerror(ret, buff, 128);

            printf("Could not open resample context %s\n", buff);
            swr_free(&swrCtx);
            swrCtx = nullptr;

            return AudioDecoderOpenFailed;
        }
        ///////////////////////////////////////////////
       // m_saveVideoFileThread->setAudioCodecContext(aCodecCtx);
    }
    return SUCCEED;
}

void GetVideoThread::deInit()
{
    if (out_buffer)
    {
        av_free(out_buffer);
        out_buffer = NULL;
    }
    if (out_buffer_rgb)
    {
        av_free(out_buffer_rgb);
        out_buffer_rgb = NULL;
    }
    if (aFrame)
    {
        av_free(aFrame);
        aFrame = NULL;
    }

    if (pFrame)
    {
        av_free(pFrame);
        pFrame = NULL;
    }

    if (pFrameYUV)
    {
        av_free(pFrameYUV);
        pFrameYUV = NULL;
    }

    if (pFrameRGB)
    {
        av_free(pFrameRGB);
        pFrameRGB = NULL;
    }

    if (pCodecCtx)
        avcodec_close(pCodecCtx);
    if (aCodecCtx)
        avcodec_close(aCodecCtx);

    avformat_close_input(&pFormatCtx);

    avformat_free_context(pFormatCtx);

}

void GetVideoThread::startRecord()
{
    m_isRun = true;
    start();

//    this->video_tid = SDL_CreateThread(sfp_refresh_camera,"sfp_refresh_camera",this);
}

void GetVideoThread::pauseRecord()
{
    m_pause = true;
}

void GetVideoThread::restoreRecord()
{
    m_pause = false;
}

void GetVideoThread::stopRecord()
{
    m_isRun = false;
//    SDL_Quit();
}

void GetVideoThread::setPicRange(int x,int y,int w,int h)
{
//    pic_x = x;
//    pic_y = y;
//    pic_w = w;
//    pic_h = h;

    pic_x = 0;
    pic_y = 0;
    pic_w = w;
    pic_h = h;
}

void GetVideoThread::setSaveVideoFileThread(SaveVideoFileThread * p)
{
    m_saveVideoFileThread = p;
}

void GetVideoThread::run()
{

//    struct SwsContext *img_convert_ctx = NULL;

    int y_size = 0;
    int yuvSize = 0;
    int size = 0;

    if (pCodecCtx)
    {

        //-------------------------------------------------------------//

//        int numBytes = avpicture_get_size(AV_PIX_FMT_YUV420P, pCodecCtx->width,pCodecCtx->height);
//        out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
//        avpicture_fill((AVPicture *) pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P,pCodecCtx->width, pCodecCtx->height);

//        img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
        //------------------------------

        y_size = pCodecCtx->width * pCodecCtx->height;
        //yuvSize = pic_w * pic_h;
        yuvSize = pCodecCtx->width * pCodecCtx->height;
        size = avpicture_get_size(pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);

    }

    int ret, got_frame;

    AVPacket *packet=(AVPacket *)av_malloc(sizeof(AVPacket));
//    //Output Information-----------------------------
  //  printf("File Information（文件信息）---------------------\n");
  //  av_dump_format(pFormatCtx,0,NULL,0);
    printf("-------------------------------------------------\n");

    qint64 firstTime = QDateTime::currentMSecsSinceEpoch();

    bool m_getFirst = false;
    qint64 timeIndex = 0;

    while(m_isRun )
    {

      //  qDebug()<<"av_read_frame";
        lastReadPacktTime = av_gettime();
        if (av_read_frame(pFormatCtx, packet)<0)
        {
            qDebug()<<"read failed!";
            SDL_Delay(10);
            continue;
        }

//        if (m_pause)
//        {
//            av_free_packet(packet);
//            msleep(10);
//            continue;
//        }

        if(packet->stream_index==videoindex)
        {
//            SDL_WaitEvent(&SDLevent);
//            if(SDLevent.type==SFM_REFRESH_CAMERA)
//            {
                long time = 0;
                if (m_saveVideoFileThread)
                {
                    if (m_getFirst)
                    {
                        qint64 secondTime = QDateTime::currentMSecsSinceEpoch();

                        time = secondTime - firstTime + timeIndex;
                    }
                    else
                    {
                        firstTime = QDateTime::currentMSecsSinceEpoch();
                        timeIndex = m_saveVideoFileThread->getVideoPts()*1000;
                        m_getFirst = true;
                    }

                }

                ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_frame, packet);

                if(ret < 0)
                {
                    printf("video Decode Error.（解码错误）\n");
                    return;
                }

                if(got_frame && pCodecCtx)
                {

                    sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
                    sws_scale(img_convert_ctx_rgb, (const uint8_t* const*)pFrame->data, pFrame->linesize,
                              0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
                    if (m_saveVideoFileThread)
                    {
                        uint8_t * picture_buf = (uint8_t *)av_malloc(size);
                        memcpy(picture_buf,pFrameYUV->data[0],y_size);
                        memcpy(picture_buf+y_size,pFrameYUV->data[1],y_size/4);
                        memcpy(picture_buf+y_size+y_size/4,pFrameYUV->data[2],y_size/4);
                        //注意回收 不然过一会就废
                        // uint8_t * yuv_buf = (uint8_t *)av_malloc(size);

                        //抛出显示信号
                        QImage tmpImg((uchar *)out_buffer_rgb,pCodecCtx->width,pCodecCtx->height,QImage::Format_RGB32);
                        QImage image = tmpImg.copy(); //把图像复制一份 传递给界面显示
                        //UploadDlg::m_pThis->refreshRecord( image );

                        Q_EMIT SIG_GetOneImage( image );
                        ///将YUV图像裁剪成目标大小
                         //Yuv420Cut(0,0,pCodecCtx->width,pCodecCtx->height,pCodecCtx->width,pCodecCtx->height,picture_buf,yuv_buf);
                         m_saveVideoFileThread->videoDataQuene_Input(/*yuv_buf*/picture_buf,yuvSize*3/2,time);
                         //av_free(picture_buf);
                    }
                }
//            }
//            else if(SDLevent.type==SDL_QUIT){
//                        m_isRun=false;
//                        break;
//            }
        }
        else if(packet->stream_index == audioindex)
        {

            if ( isBegin && m_saveVideoFileThread->mVideoDataList.size() == 0  )//音频线程开始需要等视频线程
            {
                av_packet_unref(packet);
                qDebug()<<"video delay";
                SDL_Delay(10);
                continue;
            }
            isBegin = false;

            ret = avcodec_decode_audio4(aCodecCtx, aFrame, &got_frame, packet);
            if(ret < 0)
            {
                fprintf(stderr,"video Audio Error.\n");
                return;
            }

            if (got_frame)
            {
                /// 这里重采样成44100 双声道 AV_SAMPLE_FMT_FLTP
                if (aFrame_ReSample == nullptr)
                {
                    aFrame_ReSample = av_frame_alloc();

                    int nb_samples = av_rescale_rnd(swr_get_delay(swrCtx, out_sample_rate) + aFrame->nb_samples, out_sample_rate, in_sample_rate, AV_ROUND_UP);

//                  av_samples_fill_arrays(aFrame_ReSample->data, aFrame_ReSample->linesize, audio_buf_resample, audio_tgt_channels, aFrame_ReSample->nb_samples, out_sample_fmt, 0);

                    aFrame_ReSample->format = out_sample_fmt;
                    aFrame_ReSample->channel_layout = out_ch_layout;
                    aFrame_ReSample->sample_rate = out_sample_rate;
                    aFrame_ReSample->nb_samples = nb_samples;

                    ret = av_frame_get_buffer(aFrame_ReSample, 0);
                    if (ret < 0)
                    {
                        fprintf(stderr, "Error allocating an audio buffer\n");
                        exit(1);
                    }

                }

                int len2 = swr_convert(swrCtx, aFrame_ReSample->data, aFrame_ReSample->nb_samples, (const uint8_t**)aFrame->data, aFrame->nb_samples);
                int resampled_data_size = av_samples_get_buffer_size(NULL, audio_tgt_channels, aFrame_ReSample->nb_samples, out_sample_fmt, 1);
                int OneChannelDataSize = resampled_data_size / audio_tgt_channels;

                if (m_saveVideoFileThread)
                {
                    memcpy(audio_buf_L + audio_buf_size_L, aFrame_ReSample->data[0], OneChannelDataSize);
                    audio_buf_size_L += OneChannelDataSize;

                    if (audio_tgt_channels >= 2)
                    {
                        memcpy(audio_buf_R + audio_buf_size_R, aFrame_ReSample->data[1], OneChannelDataSize);
                        audio_buf_size_R += OneChannelDataSize;
                    }

                    int index = 0;
                    int ONEAudioSize = m_saveVideoFileThread->getONEFrameSize();

                    if( ONEAudioSize == 0 )
                    {
                        av_packet_unref(packet);
                        continue;
                    }

                    int leftSize  = audio_buf_size_L;

                    ONEAudioSize /= audio_tgt_channels;

                    ///由于采集到的数据很大，而编码器一次只需要很少的数据。
                    ///因此将采集到的数据分成多次传给编码器。
                    /// 由于平面模式的pcm存储方式为：LLLLLLLLLLLLLLLLLLLLLRRRRRRRRRRRRRRRRRRRRR，因此这里合并完传给编码器就行了
                    while(1)
                    {

//                        if( !m_isRun ) break;
                        if (leftSize >= ONEAudioSize)
                        {
                            uint8_t * buffer = (uint8_t *)malloc(ONEAudioSize * audio_tgt_channels);
                            memcpy(buffer, audio_buf_L+index, ONEAudioSize);

                            if (audio_tgt_channels >= 2)
                            {
                                memcpy(buffer+ONEAudioSize, audio_buf_R+index, ONEAudioSize);
                            }

                            m_saveVideoFileThread->audioDataQuene_Input((uint8_t*)buffer, ONEAudioSize * audio_tgt_channels);

                            index    += ONEAudioSize;
                            leftSize -= ONEAudioSize;
                        }
                        else
                        {
                            if (leftSize > 0)
                            {
                                memcpy(audio_buf_L, audio_buf_L+index, leftSize);
                                memcpy(audio_buf_R, audio_buf_R+index, leftSize);
                            }
                            audio_buf_size_L = leftSize;
                            audio_buf_size_R = leftSize;
                            break;
                        }
                    }
                }
            }
        }

        av_packet_unref(packet);
    }

    sws_freeContext(img_convert_ctx);
    sws_freeContext(img_convert_ctx_rgb);

    qDebug()<<"record stopping...";

    m_pause = false;

    deInit();

    qDebug()<<"record finished!";
    if( videoindex != -1)
    {
        QImage img;
        img.fill( Qt::black );
        Q_EMIT SIG_GetOneImage( img );
    }
}
