#include "savevideofile.h"

#include <QFileInfo>
#include <QDir>

//参考
//https://blog.csdn.net/leixiaohua1020/article/details/25430425?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Edefault-5.control&dist_request_id=&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Edefault-5.control
//https://www.ffmpeg.org/doxygen/0.6/output-example_8c-source.html
/**
*  Add ADTS header at the beginning of each and every AAC packet.
*  This is needed as MediaCodec encoder generates a packet of raw
*  AAC data.
*
*  Note the packetLen must count in the ADTS header itself !!! .
*注意，这里的packetLen参数为raw aac Packet Len + 7; 7 bytes adts header
**/
void addADTStoPacket(uint8_t* packet, int packetLen)
{
   int profile = 2;  //AAC LC，MediaCodecInfo.CodecProfileLevel.AACObjectLC;
   int freqIdx = 4;  //32K, 见后面注释avpriv_mpeg4audio_sample_rates中32000对应的数组下标，来自ffmpeg源码
   int chanCfg = 2;  //见后面注释channel_configuration，Stero双声道立体声

   /*int avpriv_mpeg4audio_sample_rates[] = {
       96000, 88200, 64000, 48000, 44100, 32000,
               24000, 22050, 16000, 12000, 11025, 8000, 7350
   };
   channel_configuration: 表示声道数chanCfg
   0: Defined in AOT Specifc Config
   1: 1 channel: front-center
   2: 2 channels: front-left, front-right
   3: 3 channels: front-center, front-left, front-right
   4: 4 channels: front-center, front-left, front-right, back-center
   5: 5 channels: front-center, front-left, front-right, back-left, back-right
   6: 6 channels: front-center, front-left, front-right, back-left, back-right, LFE-channel
   7: 8 channels: front-center, front-left, front-right, side-left, side-right, back-left, back-right, LFE-channel
   8-15: Reserved
   */

   // fill in ADTS data
   packet[0] = (uint8_t)0xFF;
   packet[1] = (uint8_t)0xF9;
   packet[2] = (uint8_t)(((profile-1)<<6) + (freqIdx<<2) +(chanCfg>>2));
   packet[3] = (uint8_t)(((chanCfg&3)<<6) + (packetLen>>11));
   packet[4] = (uint8_t)((packetLen&0x7FF) >> 3);
   packet[5] = (uint8_t)(((packetLen&7)<<5) + 0x1F);
   packet[6] = (uint8_t)0xFC;
}


//SaveVideoFileThread::SaveVideoFileThread()
//{
//    isStop = false;

//    m_containsVideo = true;
//    m_containsAudio = true;

//    videoDataQueneHead = NULL;
//    videoDataQueneTail = NULL;

//    videoBufferCount = 0;

//    m_videoFrameRate = 15;

//    lastVideoNode = NULL;

//    mBitRate = 450000;

//    audio_pts = 0;
//    video_pts = 0;

//}


void SaveVideoFileThread::setContainsVideo(bool value)
{
    m_containsVideo = value;
}

void SaveVideoFileThread::setContainsAudio(bool value)
{
    m_containsAudio = value;
}

void SaveVideoFileThread::setVideoFrameRate(int value)
{
    m_videoFrameRate = value;
}

void SaveVideoFileThread::setFileName(QString filePath)
{
//    mFilePath = filePath;
    std::string str = filePath.toStdString();
    char * buf = (char*) str.c_str();
    strcpy_s(mFilePath,buf);
}

void SaveVideoFileThread::setQuantity(int value)
{
    mBitRate = 450000 + (value - 5) * 50000;
}

void SaveVideoFileThread::videoDataQuene_Input(uint8_t * buffer, int size, int64_t time)
{
//    qDebug()<<"void SaveVideoFileThread::videoDataQuene_Input(uint8_t * buffer,int size,long time)"<<time;
    BufferDataNode * node = (BufferDataNode*)malloc(sizeof(BufferDataNode));
    node->bufferSize = size;
    node->next = NULL;
    node->time = time;

    node->buffer = buffer;
//    node->buffer = (uint8_t *)malloc(size);
//    memcpy(node->buffer,buffer,size);

    mVideoMutex.lock();

    mVideoDataList.append(node);

    mVideoMutex.unlock();
//qDebug()<<__FUNCTION__<<videoBufferCount<<time;
    if (videoBufferCount >= 50)
    {
        QString logStr = QString("encode too slow! count=%1")
                    .arg(videoBufferCount);
        qDebug()<<logStr;
    }

}

BufferDataNode *SaveVideoFileThread::videoDataQuene_get(int64_t time)
{
    BufferDataNode * node = NULL;

    mVideoMutex.lock();

    while(mVideoDataList.size()!= 0 )
    {
        node = mVideoDataList.takeFirst();
        if( mVideoDataList.size() == 0) break;
        if( time>node->time )
        {
            av_free(node->buffer);
            node->buffer = NULL;
            free(node);
            node = NULL;
        }else
        {
            break;
        }
    }
//    if(mVideoDataList.size()!= 0)
//       node = mVideoDataList.takeFirst();
   qDebug()<<__FUNCTION__<<mVideoDataList.size();

    mVideoMutex.unlock();

    return node;
}

void SaveVideoFileThread::audioDataQuene_Input(const uint8_t *buffer, const int &size)
{
    BufferDataNode  *node = (BufferDataNode*)malloc(sizeof(BufferDataNode));
//    node->buffer = buffer;
    node->bufferSize = size;
    node->next = NULL;

    node->buffer = (uint8_t*)buffer;
//    node->buffer = (uint8_t *)malloc(size);
//    memcpy(node->buffer,buffer,size);

    mAudioMutex.lock();

    mAudioDataList.append(node);

//qDebug()<<__FUNCTION__<<audioBufferCount<<size;
    mAudioMutex.unlock();

}

BufferDataNode  * SaveVideoFileThread::audioDataQuene_get()
{
    BufferDataNode  *node = NULL;
    mAudioMutex.lock();

    if (mAudioDataList.size() != 0 )
    {
        node = mAudioDataList.takeFirst();

       qDebug()<<__FUNCTION__<<mAudioDataList.size();
    }

    mAudioMutex.unlock();

    return node;
}


/*
 * add an audio output stream
 */
void SaveVideoFileThread::add_audio_stream(OutputStream *ost, AVFormatContext *oc,
                                                AVCodec **codec,
                                                enum AVCodecID codec_id)
{
    AVCodecContext *aCodecCtx;
    int i;

    /* find the video encoder */
    *codec = avcodec_find_encoder(codec_id);
    if (!codec) {
        fprintf(stderr, "codec not found\n");
        exit(1);
    }

    ost->st = avformat_new_stream(oc, NULL);
    if (!ost->st) {
        fprintf(stderr, "Could not alloc stream\n");
        exit(1);
    }

    ost->st->id = oc->nb_streams-1;

    const AVCodec* aCodec = *codec;

    aCodecCtx = avcodec_alloc_context3(aCodec);
    if (!aCodecCtx)
    {
        fprintf(stderr, "Could not alloc an encoding context\n");
        exit(1);
    }

    ///先用这句话找出 aac编码器支持的 sample_fmt
    /// 我找出的是 AV_SAMPLE_FMT_FLTP
    const enum AVSampleFormat *p = aCodec->sample_fmts;
    fprintf(stderr, "aac encoder sample format is: %s \n",av_get_sample_fmt_name(*p));

    ost->enc = aCodecCtx;

//    aCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
    aCodecCtx->sample_fmt = AV_SAMPLE_FMT_FLTP;
    aCodecCtx->sample_rate= 44100;
    aCodecCtx->channels = 2;
    aCodecCtx->channel_layout=av_get_default_channel_layout(aCodecCtx->channels);

//    aCodecCtx->channels       = av_get_channel_layout_nb_channels(aCodecCtx->channel_layout);
//    aCodecCtx->channel_layout = AV_CH_LAYOUT_STEREO;

//    aCodecCtx->profile=FF_PROFILE_AAC_LOW; //（可参考AAC格式简介）
//    aCodecCtx->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;

//    aCodecCtx->bit_rate = 64000;


    ost->st->time_base.num = 1; // = (AVRational){ 1, c->sample_rate };
    ost->st->time_base.den = aCodecCtx->sample_rate;

    qDebug()<<__FUNCTION__;
}

void SaveVideoFileThread::open_audio(AVFormatContext *oc, AVCodec *codec, OutputStream *ost)
{
    AVCodecContext *aCodecCtx = ost->enc;

    /* open it */
    if (avcodec_open2(aCodecCtx, codec, NULL) < 0)
    {
        qDebug("could not open codec\n");
        exit(1);
    }

    mONEFrameSize = av_samples_get_buffer_size(NULL, aCodecCtx->channels, aCodecCtx->frame_size, aCodecCtx->sample_fmt, 1);
    qDebug()<< "mONEFrameSize" << mONEFrameSize;
    ost->frame           = av_frame_alloc();
    ost->frameBuffer     = (uint8_t *)av_malloc(mONEFrameSize);
    ost->frameBufferSize = mONEFrameSize;

    ///这句话必须要(设置这个frame里面的采样点个数)
    int oneChannelBufferSize = mONEFrameSize / aCodecCtx->channels; //计算出一个声道的数据
    int nb_samplesize = oneChannelBufferSize / av_get_bytes_per_sample(aCodecCtx->sample_fmt); //计算出采样点个数
    ost->frame->nb_samples = nb_samplesize;

    ///这2种方式都可以
//    avcodec_fill_audio_frame(ost->frame, aCodecCtx->channels, aCodecCtx->sample_fmt,(const uint8_t*)ost->frameBuffer, mONEFrameSize, 0);
    av_samples_fill_arrays(ost->frame->data, ost->frame->linesize, ost->frameBuffer, aCodecCtx->channels, ost->frame->nb_samples, aCodecCtx->sample_fmt, 0);

    ost->tmp_frame = nullptr;

    /* copy the stream parameters to the muxer */
    int ret = avcodec_parameters_from_context(ost->st->codecpar, aCodecCtx);
    if (ret < 0)
    {
        qDebug()<<"Could not copy the stream parameters";
        fprintf(stderr, "Could not copy the stream parameters\n");
        exit(1);
    }
    qDebug()<<__FUNCTION__;
}

/*
 * encode one audio frame and send it to the muxer
 * return 1 when encoding is finished, 0 otherwise
 */
//static int write_audio_frame(AVFormatContext *oc, OutputStream *ost)
bool SaveVideoFileThread::write_audio_frame(AVFormatContext *oc, OutputStream *ost)
{
 //    qDebug()<<"write_audio_frame";
    AVCodecContext *aCodecCtx = ost->enc;

    AVPacket pkt;
    av_init_packet(&pkt);

    AVPacket *packet = &pkt;

    AVFrame *aFrame;

    BufferDataNode* node = NULL;
    node = audioDataQuene_get();
    if ( node )
    {
        aFrame = ost->frame;

        memcpy(ost->frameBuffer, node->buffer, node->bufferSize);

        free(node->buffer);

        node->buffer = NULL;

        free(node);

        node = NULL;

        aFrame->pts = ost->next_pts;
        ost->next_pts  += aFrame->nb_samples;
    }
    else
    {
       //    qDebug()<<"1 return false";
        return false;
    }

    if (aFrame)
    {
        AVRational rational;
        rational.num = 1;
        rational.den = aCodecCtx->sample_rate;
        aFrame->pts = av_rescale_q(ost->samples_count, rational, aCodecCtx->time_base);
        ost->samples_count += aFrame->nb_samples;
    }

    /* send the frame for encoding */
    int ret = avcodec_send_frame(aCodecCtx, aFrame);
    if (ret < 0)
    {
        qDebug()<<"ret false";
        fprintf(stderr, "Error sending the frame to the audio encoder\n");
        return false;
    }

    /* read all the available output packets (in general there may be any
     * number of them */
    while (ret >= 0)
    {
        ret = avcodec_receive_packet(aCodecCtx, packet);

        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF || ret < 0)
        {
            char errstr[AV_ERROR_MAX_STRING_SIZE] = {0};
            av_make_error_string(errstr, AV_ERROR_MAX_STRING_SIZE, ret);
            QString logStr = QString("!!!!!!!!!! Error encoding audio frame: %1 ret=%2")
                        .arg(QString(errstr))
                        .arg(ret);
            qDebug()<<logStr;
            return false;
        }

        ////
        /* rescale output packet timestamp values from codec to stream timebase */
        av_packet_rescale_ts(&pkt, aCodecCtx->time_base, ost->st->time_base);
        pkt.stream_index = ost->st->index;

//        audio_pts = pkt.pts;

        ///由于MP4文件的时间基不是1/1000，因此这里转成毫秒的形式，方便显示和计算。
        ///将Pts转换成毫秒的形式，这里pts仅仅用于显示，不会修改写入文件的pts
        audio_pts = av_rescale_q(pkt.pts, ost->st->time_base, {1, 1000});

        /* Write the compressed frame to the media file. */
        ret = av_interleaved_write_frame(oc, &pkt);
        if (ret < 0)
        {
            char errstr[AV_ERROR_MAX_STRING_SIZE] = {0};
            av_make_error_string(errstr, AV_ERROR_MAX_STRING_SIZE, ret);
            QString logStr = QString("!!!!!!!!!! Error while writing audio frame: %1 ret=%2")
                        .arg(QString(errstr))
                        .arg(ret);
            qDebug()<<logStr;
        }

        av_packet_unref(packet);
        break;
    }

    return true;

}

void SaveVideoFileThread::close_audio(AVFormatContext *oc, OutputStream *ost)
{
    avcodec_free_context(&ost->enc);
    av_frame_free(&ost->frame);

    if (ost->tmp_frame != nullptr)
    av_frame_free(&ost->tmp_frame);

    if (ost->frameBuffer != NULL)
    {
        av_free(ost->frameBuffer);
        ost->frameBuffer = NULL;
    }
}


/* add a video output stream */
void SaveVideoFileThread::add_video_stream(OutputStream *ost, AVFormatContext *oc,
                       AVCodec **codec,
                       enum AVCodecID codec_id)
{
    AVCodecContext *c;

    /* find the video encoder */
    *codec = avcodec_find_encoder(codec_id);
    if (!codec) {
        fprintf(stderr, "codec not found\n");
        exit(1);
    }

    ost->st = avformat_new_stream(oc, NULL);
    if (!ost->st) {
        fprintf(stderr, "Could not alloc stream\n");
        exit(1);
    }

    ost->st->id = oc->nb_streams-1;

    c = avcodec_alloc_context3(*codec);
    if (!c) {
        fprintf(stderr, "Could not alloc an encoding context\n");
        exit(1);
    }
    ost->enc = c;

    c->codec_id = codec_id;

qDebug()<<__FUNCTION__<<c<<c->codec<<c->codec_id<<codec_id;

    /* resolution must be a multiple of two */
    c->width = WIDTH;
    c->height = HEIGHT;
    /* time base: this is the fundamental unit of time (in seconds) in terms
       of which frame timestamps are represented. for fixed-fps content,
       timebase should be 1/framerate and timestamp increments should be
       identically 1. */
//    c->time_base.den = m_videoFrameRate;
//    c->time_base.num = 1;
//    c->gop_size = 12; /* emit one intra frame every twelve frames at most */
    c->gop_size = m_videoFrameRate;
    c->pix_fmt = AV_PIX_FMT_YUV420P;

//    视频编码器常用的码率控制方式包括abr(平均码率)，crf(恒定码率)，cqp(恒定质量)，
//    ffmpeg中AVCodecContext显示提供了码率大小的控制参数，但是并没有提供其他的控制方式。
//    ffmpeg中码率控制方式分为以下几种情况：
//    1.如果设置了AVCodecContext中bit_rate的大小，则采用abr的控制方式；
//    2.如果没有设置AVCodecContext中的bit_rate，则默认按照crf方式编码，crf默认大小为23（此值类似于qp值，同样表示视频质量）；
//    3.如果用户想自己设置，则需要借助av_opt_set函数设置AVCodecContext的priv_data参数。下面给出三种控制方式的实现代码：

    c->bit_rate = mBitRate;

#if 0
    ///平均码率
    //目标的码率，即采样的码率；显然，采样码率越大，视频大小越大
    c->bit_rate = mBitRate;

#elif 1
    ///恒定码率
//    量化比例的范围为0~51，其中0为无损模式，23为缺省值，51可能是最差的。该数字越小，图像质量越好。从主观上讲，18~28是一个合理的范围。18往往被认为从视觉上看是无损的，它的输出视频质量和输入视频一模一样或者说相差无几。但从技术的角度来讲，它依然是有损压缩。
//    若Crf值加6，输出码率大概减少一半；若Crf值减6，输出码率翻倍。通常是在保证可接受视频质量的前提下选择一个最大的Crf值，如果输出视频质量很好，那就尝试一个更大的值，如果看起来很糟，那就尝试一个小一点值。
//    av_opt_set(c->priv_data, "crf", "31.000", AV_OPT_SEARCH_CHILDREN);

#else
    ///qp的值和crf一样
//    av_opt_set(c->priv_data, "qp", "31.000",AV_OPT_SEARCH_CHILDREN);
#endif

#if TEST_OPT

    av_opt_set(pCodecCtx,"b","400000",0);		//bitrate
    //Another method
    //av_opt_set_int(pCodecCtx,"b",400000,0);	//bitrate

    av_opt_set(pCodecCtx,"time_base","1/25",0);	//time_base
    av_opt_set(pCodecCtx,"bf","5",0);			//max b frame
    av_opt_set(pCodecCtx,"g","25",0);			//gop
    av_opt_set(pCodecCtx,"qmin","10",0);		//qmin/qmax
    av_opt_set(pCodecCtx,"qmax","51",0);

#else

//    pCodecCtx->time_base.num = 1;
//    pCodecCtx->time_base.den = 25;
//    pCodecCtx->max_b_frames=5;
//    pCodecCtx->bit_rate = 400000;
//    pCodecCtx->gop_size=25;
//    pCodecCtx->qmin = 10;
//    pCodecCtx->qmax = 51;

    /* time base: this is the fundamental unit of time (in seconds) in terms
       of which frame timestamps are represented. for fixed-fps content,
       timebase should be 1/framerate and timestamp increments should be
       identically 1. */
    ost->st->time_base = { 1, m_videoFrameRate };
    c->time_base       = ost->st->time_base;
//    c->gop_size = 12; /* emit one intra frame every twelve frames at most */
    c->gop_size = m_videoFrameRate * 2; ///I帧间隔

//    //固定允许的码率误差，数值越大，视频越小
//    c->bit_rate_tolerance = mBitRate;

//    //H264 还可以设置很多参数 自行研究吧
////    pCodecCtx->me_range = 16;
////    pCodecCtx->max_qdiff = 1;
//    c->qcompress = 0.85;
    c->qmin = 16;
    c->qmax = 31;

////    //采用（qmin/qmax的比值来控制码率，1表示局部采用此方法，0表示全局）
////    c->rc_qsquish = 0;

////    //因为我们的量化系数q是在qmin和qmax之间浮动的，
////    //qblur表示这种浮动变化的变化程度，取值范围0.0～1.0，取0表示不削减
////    c->qblur = 1.0;

//std::cout<<"mBitRate"<<mBitRate<<m_videoFrameRate;

////    ///b_frame_strategy
////    ///如果为true，则自动决定什么时候需要插入B帧，最高达到设置的最大B帧数。
////    ///如果设置为false,那么最大的B帧数被使用。
////    c->b_frame_strategy = 1;
////    c->max_b_frames = 5;

#endif


    if (c->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
        /* just for testing, we also add B frames */
        c->max_b_frames = 2;
    }
    if (c->codec_id == AV_CODEC_ID_MPEG1VIDEO){
        /* Needed to avoid using macroblocks in which some coeffs overflow.
           This does not happen with normal video, it just happens here as
           the motion of the chroma plane does not match the luma plane. */
        c->mb_decision=2;
    }

}

static AVFrame *alloc_picture(enum AVPixelFormat pix_fmt, int width, int height)
{
    AVFrame *picture;
    int ret;

    picture = av_frame_alloc();
    if (!picture)
        return NULL;

    picture->format = pix_fmt;
    picture->width  = width;
    picture->height = height;

    /* allocate the buffers for the frame data */
    ret = av_frame_get_buffer(picture, 32);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate frame data.\n");
        exit(1);
    }

    return picture;
}

void SaveVideoFileThread::open_video(AVFormatContext *oc, AVCodec *codec, OutputStream *ost)
{
    AVCodecContext *c = ost->enc;

    // Set Option
    AVDictionary *param = 0;
    //H.264
    //av_dict_set(&param, "preset", "slow", 0);
    av_dict_set(&param, "preset", "superfast", 0);
    av_dict_set(&param, "tune", "zerolatency", 0);  //实现实时编码

    c->thread_count = 16;
    c->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

qDebug()<<__FUNCTION__<<"333";
    int ret = 0;
    if (ret = avcodec_open2(c, codec,&param) < 0){
      qDebug()<<("Failed to open video encoder!\n")<<ret;
      exit(1);
    }
qDebug()<<__FUNCTION__<<"333"<<c->pix_fmt<<AV_PIX_FMT_YUV420P;

    /* allocate the encoded raw picture */
    {
        ost->frame = av_frame_alloc();

        ost->frame->format = c->pix_fmt;
        ost->frame->width  = c->width;
        ost->frame->height = c->height;

        int numBytes_yuv = avpicture_get_size(AV_PIX_FMT_YUV420P, c->width,c->height);

        uint8_t * out_buffer_yuv = (uint8_t *) av_malloc(numBytes_yuv * sizeof(uint8_t));

        avpicture_fill((AVPicture *) ost->frame, out_buffer_yuv, AV_PIX_FMT_YUV420P,
                c->width, c->height);

        ost->frameBuffer = out_buffer_yuv;
        ost->frameBufferSize = numBytes_yuv;

//        /* allocate the buffers for the frame data */
//        int ret = av_frame_get_buffer(ost->frame, 0);
//        if (ret < 0) {
//            fprintf(stderr, "Could not allocate frame data.\n");
//            exit(1);
//        }

    }
//    ost->frame = alloc_picture(c->pix_fmt, c->width, c->height);
//    if (!ost->frame) {
//        fprintf(stderr, "Could not allocate picture\n");
//        exit(1);
//    }

    /* If the output format is not YUV420P, then a temporary YUV420P
     * picture is needed too. It is then converted to the required
     * output format. */
    ost->tmp_frame = NULL;
    if (c->pix_fmt != AV_PIX_FMT_YUV420P) {
        ost->tmp_frame = alloc_picture(AV_PIX_FMT_YUV420P, c->width, c->height);
        if (!ost->tmp_frame) {
            fprintf(stderr, "Could not allocate temporary picture\n");
            exit(1);
        }
    }

    /* copy the stream parameters to the muxer */
    ret = avcodec_parameters_from_context(ost->st->codecpar, c);
    if (ret < 0) {
        fprintf(stderr, "Could not copy the stream parameters\n");
        exit(1);
    }

}

bool SaveVideoFileThread::write_video_frame(AVFormatContext *oc, OutputStream *ost, double time)
{
    int out_size, ret = 0;
    AVCodecContext *c;
    int got_packet = 0;

    c = ost->enc;
//qDebug()<<__FUNCTION__<<"0000"<<time;
    BufferDataNode *node = videoDataQuene_get(time);
    if (node == NULL)
    {
//        qDebug()<<__FUNCTION__<<"0000 000"<<time;
//        return false;
        if( !lastVideoNode)
            node = lastVideoNode  ;
        else
            return false;
    }
    else
    {
        if (node != lastVideoNode)
        {
//            if (lastVideoNode != NULL)
//            {
//                av_free(lastVideoNode->buffer);
//                free(lastVideoNode);
//            }

            lastVideoNode = node;
        }
    }
    if( !node ) return false;
    memcpy(ost->frameBuffer, node->buffer, node->bufferSize);

    av_free(node->buffer);
    node->buffer = NULL;
    free(node);
    node = NULL;
//不知为何下面这两种方式都不行
//        int y_size = c->width * c->height;
//        memcpy(ost->frame->data[0], node->buffer, y_size * 3 / 2);

//        memcpy(ost->frame->data[0], node->buffer, y_size);
//        memcpy(ost->frame->data[1], node->buffer+ y_size, y_size*5/4);
//        memcpy(ost->frame->data[2], node->buffer+ y_size*5/4, y_size*5/4);
//qDebug()<<__FUNCTION__<<"000 1111";

    ost->frame->pts = ost->next_pts++;

//qDebug()<<__FUNCTION__<<"1111";

    AVPacket pkt = { 0 };
//    av_init_packet(&pkt);

    /* encode the image */
    out_size = avcodec_encode_video2(c, &pkt, ost->frame, &got_packet);

    if (got_packet)
    {
//qDebug()<<__FUNCTION__<<"111"<<ost->frame->pts<<pkt.pts<<c->time_base.num<<c->time_base.den<<ost->st->time_base.den<<ost->st->time_base.num;
        /* rescale output packet timestamp values from codec to stream timebase */
        av_packet_rescale_ts(&pkt, c->time_base, ost->st->time_base);
        pkt.stream_index = ost->st->index;
//qDebug()<<__FUNCTION__<<"222"<<ost->frame->pts<<pkt.pts<<time<<node->time;

//        video_pts = pkt.pts;

        ///由于MP4文件的时间基不是1/1000，因此这里转成毫秒的形式，方便显示和计算。
        ///将Pts转换成毫秒的形式，这里pts仅仅用于显示，不会修改写入文件的pts
        video_pts = av_rescale_q(pkt.pts, ost->st->time_base, {1, 1000});

        /* Write the compressed frame to the media file. */
        ret = av_interleaved_write_frame(oc, &pkt);
        if (ret < 0)
        {
            char errstr[AV_ERROR_MAX_STRING_SIZE] = {0};
            av_make_error_string(errstr, AV_ERROR_MAX_STRING_SIZE, ret);
            QString logStr = QString("!!!!!!!!!! Error while writing video frame: %1 ret=%2")
                        .arg(QString(errstr))
                        .arg(ret);
             qDebug()<<logStr;
        }

        av_packet_unref(&pkt);
    }

    return true;

}

void SaveVideoFileThread::close_video(AVFormatContext *oc, OutputStream *ost)
{
    avcodec_free_context(&ost->enc);
    av_frame_free(&ost->frame);

    if (ost->tmp_frame != NULL)
        av_frame_free(&ost->tmp_frame);

    if (ost->frameBuffer != NULL)
    {
        av_free(ost->frameBuffer);
        ost->frameBuffer = NULL;
    }

}

int64_t SaveVideoFileThread::getVideoPts()
{
    return video_pts;
}

int64_t SaveVideoFileThread::getAudioPts()
{
    return audio_pts;
}

void SaveVideoFileThread::run()
{
    int writeFileIndex = 1;

    while(1)
    {
        if (isStop)
        {
            break;
        }

        if (WIDTH <= 0 || HEIGHT <= 0)
        {
            msleep(100);
            continue;
        }

        QString filePath;

//        if (writeFileIndex > 1)
//        {
//            QFileInfo fileInfo(mFilePath);

//            filePath = QString("%1/%2_%3.%4")
//                    .arg(fileInfo.absoluteDir().path())
//                    .arg(fileInfo.baseName())
//                    .arg(writeFileIndex)
//                    .arg(fileInfo.suffix());
//        }
//        else
//        {
//            filePath = mFilePath;
//        }
//        filePath = mFilePath;
//        //emit sig_StartWriteFile(filePath);

//        char filename[1280] = {0};
//        strcpy(filename, filePath.toLocal8Bit());
//        writeFileIndex++;

        OutputStream video_st = { 0 }, audio_st = { 0 };
        AVOutputFormat *fmt;
        AVFormatContext *oc;
        AVCodec *audio_codec, *video_codec;
        int have_video = 0, have_audio = 0;

        int i;

        /* allocate the output media context */
        avformat_alloc_output_context2(&oc, NULL, /*NULL*/"flv", /*filename*/mFilePath);
        if (!oc)
        {
            printf("Could not deduce output format from file extension: using MPEG.\n");
            avformat_alloc_output_context2(&oc, NULL, "mpeg", /*filename*/mFilePath);
        }

        if (!oc)
        {
            fprintf(stderr,"Could not deduce output format from file extension: using MPEG.\n");

            QString logStr = QString("!!!!!!!!!! Could not deduce output format from file extension ... %1").arg(filePath);
            qDebug()<<logStr;

            SDL_Delay(1000);

            continue;
        }

        fmt = oc->oformat;

        if (m_containsVideo)
        {
            qDebug()<<fmt->video_codec;
            if (fmt->video_codec != AV_CODEC_ID_NONE)
            {
                add_video_stream(&video_st, oc, &video_codec, AV_CODEC_ID_H264);
                have_video = 1;
            }
            qDebug()<<"333";
        }

        if (m_containsAudio)
        {
            if (fmt->audio_codec != AV_CODEC_ID_NONE)
            {
                add_audio_stream(&audio_st, oc, &audio_codec, AV_CODEC_ID_AAC);
                have_audio = 1;
            }
        }

        /* Now that all the parameters are set, we can open the audio and
         * video codecs and allocate the necessary encode buffers. */
        if (have_video)
            open_video(oc, video_codec, &video_st);

        if (have_audio)
            open_audio(oc, audio_codec, &audio_st);

        av_dump_format(oc, 0, mFilePath, 1);

        /* open the output file, if needed */
        if (!(fmt->flags & AVFMT_NOFILE))
        {
            if (avio_open(&oc->pb, mFilePath, AVIO_FLAG_WRITE) < 0)
            {
                qDebug()<<"Could not open "<<mFilePath;
    //            return;

                QString logStr = QString("!!!!!!!!!! Could not open %1").arg(mFilePath);
                qDebug()<<logStr;

                SDL_Delay(1000);

                continue;

            }
        }

        /* write the stream header, if any */
    //    av_write_header(oc);
        avformat_write_header(oc, NULL);

        video_pts = 0;
        audio_pts = 0;

        while(1)
        {
    //        qDebug()<<__FUNCTION__<<video_st.next_pts<<audio_st.next_pts<<video_pts<<audio_pts;

            /* select the stream to encode */
            if (!have_video || (av_compare_ts(video_st.next_pts, video_st.enc->time_base, audio_st.next_pts, audio_st.enc->time_base) <= 0))
            {
                qDebug()<<"video_pts"<<video_pts ;
                if (!write_video_frame(oc, &video_st, video_pts))
                {
//                    if (isStop)
//                    {
//                        break;
//                    }
                    msleep(1);
                }
            }
            else
            {
                if (!write_audio_frame(oc, &audio_st))
                {
//                    if (isStop )
//                    {
////                        if( mAudioDataList.size() > 0 )
////                            continue;
//                        break;
//                    }
//                    if( mAudioDataList.size() == 0 )
                    msleep(1);
                }
            }
            if (isStop )
            {
                if( mAudioDataList.size() == 0 || mVideoDataList.size() == 0)
                {
                    if( mAudioDataList.size() != 0 )
                    {
                        write_audio_frame(oc, &audio_st);
                    }else if( mVideoDataList.size() != 0 )
                    {
                        write_video_frame(oc, &video_st, video_pts);
                    }
                    if( mAudioDataList.size() == 0 && mVideoDataList.size() == 0)
                    break;
                }
            }
        }

        QString logStr = QString("!!!!!!!!!! av_write_trailer ... %1").arg(mFilePath);
    //    AppConfig::WriteLog(logStr);
        qDebug()<<logStr;

        av_write_trailer(oc);

        logStr = QString("!!!!!!!!!! av_write_trailer finised! %1").arg(mFilePath);
    //    AppConfig::WriteLog(logStr);
        qDebug()<<logStr;
        //emit sig_StopWriteFile(filePath);

        qDebug()<<"void RTMPPushThread::run() finished!";

        /* close each codec */
        if (have_video)
            close_video(oc, &video_st);
        if (have_audio)
            close_audio(oc, &audio_st);

        /* free the streams */
        for(i = 0; i < oc->nb_streams; i++) {
            av_freep(&oc->streams[i]->codec);
            av_freep(&oc->streams[i]);
        }

        if (!(fmt->flags & AVFMT_NOFILE)) {
            /* close the output file */
            avio_close(oc->pb);
        }

        /* free the stream */
        avformat_free_context(oc);
    }

    qDebug()<<"void RTMPPushThread::run() finished! 222";
}

void SaveVideoFileThread::setWidth(int width,int height)
{
    WIDTH = width;
    HEIGHT = height;
}

bool SaveVideoFileThread::startEncode()
{
    isStop = false;
     start();

    return true;
}

bool SaveVideoFileThread::stopEncode()
{
    isStop = true;

    return true;
}
