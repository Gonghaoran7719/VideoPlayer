#include "uploaddialog.h"
#include "ui_uploaddialog.h"
#include"QFileInfo"
#include"QFileDialog"
#include"qDebug"
#include"videoplayer.h"
#include<QProcess>
#include<QTime>
#include<QDir>
#include<QMovie>
#include"qmytcpclient.h"

#define DEFAULT_FRAME_RATE (15)

static UploadDialog * pThis = NULL;

UploadDialog::UploadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UploadDialog)
{
    ui->setupUi(this);

    qRegisterMetaType<Hobby>("Hobby");
//    connect( this , SIGNAL(SIG_GetOnePicture(QImage)) ,
//             ui->wdg_jpg , SLOT(slot_setImage(QImage)) );

    pThis = this;
    ui->sw_page->setCurrentIndex(0);

    m_recTimer = new QTimer;
    connect( m_recTimer , SIGNAL(timeout()) , this , SLOT(slot_updateRecTime()) );
   // m_recTimer->start( 500 );

    //控件初始化
    ui->cb_cam->setChecked(true);
    ui->pb_see->setEnabled(false);
    ui->pb_recordEnd->setEnabled(false);
    //初始化设备
    initDev();

    m_screenRecorder = NULL;
}

UploadDialog::~UploadDialog()
{
    delete ui;
    if( m_recTimer ) delete m_recTimer;
}

//点击浏览
void UploadDialog::on_pb_view_clicked()
{
    QString path = QFileDialog::getOpenFileName( this, "打开", "./","( *.flv *.mp4)");

    if( path.isEmpty() ) return ;

    ui->le_path->setText( path );

    //保证有temp路径
    QDir dir;
    if( !dir.exists( QDir::currentPath() + "/temp/"))
        dir.mkpath(   QDir::currentPath() + "/temp/" );

    //显示gif
    QString imgPath = SaveVideoJpg( path );

    //加载到控件
    QMovie * movie = new QMovie(imgPath);
    ui->lb_gif->setMovie( movie );
    movie->start();

    m_filePath = path;
    m_imgPath = imgPath;

    ui->pb_beginUpload ->setEnabled(true);
}


QString UploadDialog::SaveVideoJpg( QString FilePath )
{
    std::string tmp = FilePath.toStdString();
    char* file_path = (char*)tmp.c_str();

    AVFormatContext *pFormatCtx;
    AVCodecContext *pCodecCtx;
    AVCodec *pCodec;
    AVFrame *pFrame, *pFrameRGB;
    AVPacket *packet;
    uint8_t *out_buffer;
    static struct SwsContext *img_convert_ctx;
    int videoStream, i, numBytes;
    int ret, got_picture;
    av_register_all();
    //初始化 FFMPEG 调用了这个才能正常适用编码器和解码器
    //Allocate an AVFormatContext.
    pFormatCtx = avformat_alloc_context();
    if (avformat_open_input(&pFormatCtx, file_path, NULL, NULL) != 0) {
        qDebug() << "can't open the file." ;
        return QString();
    }
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        qDebug() <<"Could't find stream infomation.";
        return QString();
    }
    videoStream = -1;
    ///循环查找视频中包含的流信息，直到找到视频类型的流
    ///便将其记录下来 保存到 videoStream 变量中///这里现在只处理视频流 音频流先不管他
    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
        }
    }
    ///如果 videoStream 为-1 说明没有找到视频流
    if (videoStream == -1) {
        qDebug() <<"Didn't find a video stream.";
        return QString();
    }
    ///查找解码器
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL) {
        qDebug() <<"Codec not found." ;
        return QString();
    }
    ///打开解码器
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        qDebug() <<"Could not open codec." ;
        return QString();
    }
    pFrame = av_frame_alloc();
    pFrameRGB = av_frame_alloc();
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
                                     pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
                                     AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);
    numBytes = avpicture_get_size(AV_PIX_FMT_RGB32,
                                  pCodecCtx->width,pCodecCtx->height);
    out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *) pFrameRGB, out_buffer, AV_PIX_FMT_RGB32,
                   pCodecCtx->width, pCodecCtx->height);
    int y_size = pCodecCtx->width * pCodecCtx->height;
    packet = (AVPacket *) malloc(sizeof(AVPacket)); //分配一个 packet
    av_new_packet(packet, y_size); //分配 packet 的数据
    int index = 0;
    int nCount = 0;
    while(1)
    {
        if (av_read_frame(pFormatCtx, packet) < 0)
        {
            break; //这里认为视频读取完了
        }
        if (packet->stream_index == videoStream) {
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,packet);
            if (ret < 0) {
                qDebug() <<"decode error." ;
                return QString();
            }
            if (got_picture && pFrame->key_frame == 1 && pFrame->pict_type ==
                    AV_PICTURE_TYPE_I) {
                sws_scale(img_convert_ctx,
                          (uint8_t const * const *) pFrame->data,
                          pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                          pFrameRGB->linesize);
                QImage tmpImg((uchar
                               *)out_buffer,pCodecCtx->width,pCodecCtx->height,QImage::Format_RGB32);
                QImage image = tmpImg.scaled( 640 , 320,
                                              Qt::KeepAspectRatio );

                image.save( QString("./temp/%1.jpg").arg( nCount , 2 , 10 , QChar('0')) );
                //arg( nCount , 2 , 10 , QChar('0')) )  2 占2位 10 10进制   QChar('0') 缺省补'0'
                nCount ++;
                if(nCount == 6)
                {
                    av_free_packet(packet);
                    break;
                }
            }
        }
        av_free_packet(packet);
    }
    av_free(out_buffer);
    av_free(pFrameRGB);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);

    QProcess p(0);

    p.start("cmd"  );//开启cmd窗口
    p.waitForStarted();
    QString curPath = QDir::currentPath();
    curPath.replace("/","\\\\");

    QString strcd = QString("%1/ \n").arg(QCoreApplication::applicationDirPath());
             strcd.replace("/","\\\\");
             strcd = QString("cd /d ")+strcd;

            p.write( strcd.toLocal8Bit() );

            QString imgName = QString("%1\\\\temp\\\\%2.gif")
    .arg(curPath).arg(QTime::currentTime().toString("hhmmsszzz")); //使用时间自定义文件名,避免进程占用,写入文件失败
            QString cmd = QString("ffmpeg -r 2 -i %1\\\\temp\\\\").arg(curPath); // “C:/ffmpeg/ffmpeg.exe”
                    cmd += "%02d.jpg ";
                    cmd += imgName;
                    cmd += " \n";

            qDebug() << "cmd "<< cmd;
            p.write( cmd.toLocal8Bit() );

            p.closeWriteChannel();
            p.waitForFinished();

            qDebug()<< QString::fromLocal8Bit( p.readAllStandardOutput() );
            p.close();



    return imgName;
}

//开始上传
void UploadDialog::on_pb_beginUpload_clicked()
{
    Hobby hy;
    hy.dance    = ui->cb_dance   ->isChecked()?1:0;
    hy.edu      = ui->cb_edu     ->isChecked()?1:0;
    hy.ennegy   = ui->cb_ennegy  ->isChecked()?1:0;
    hy.food     = ui->cb_food    ->isChecked()?1:0;
    hy.funny    = ui->cb_funny   ->isChecked()?1:0;
    hy.music    = ui->cb_music   ->isChecked()?1:0;
    hy.outside  = ui->cb_outside ->isChecked()?1:0;
    hy.video    = ui->cb_video   ->isChecked()?1:0;

    emit SIG_UploadFile( m_filePath , m_imgPath , hy);
}
#include<qdesktopwidget.h>
static void FFMPEG_Callback(void* ptr, int level, const char* fmt, va_list vl);
//初始化设备
void UploadDialog::initDev()
{
    av_register_all();
    avformat_network_init();
    avdevice_register_all();
    AVFormatContext * pFormatCtx = avformat_alloc_context();

    av_log_set_callback(&FFMPEG_Callback);

    AVDictionary* options = NULL;
    av_dict_set(&options,"list_devices","true",0);
    AVInputFormat *iformat = av_find_input_format("dshow");
    avformat_open_input(&pFormatCtx,"video=dummy",iformat,&options);

    iformat = av_find_input_format("vfwcap");
    avformat_open_input(&pFormatCtx,"list",iformat,NULL);

    rct = qApp->desktop()->screenGeometry(); //获取用户的桌面大小, 用于录制屏幕的尺寸.
}
//回调函数
static bool isDShowVideoBegin = false;
static bool isDShowAudioBegin = false;
static bool isVFWVideoBegin = false;
static void FFMPEG_Callback(void* ptr, int level, const char* fmt, va_list vl)
{
    // 可以根据 level 的级别选择要打印显示的内容
    if (level <= AV_LOG_INFO)
    {
        char buffer[1024];
        vsprintf(buffer, fmt, vl); //获得打印的数据, 保存到 buffer 中.
        std::string strbuf = buffer;
        QString str = QString::fromStdString( strbuf );

        qDebug() << str;
        if( str.contains("DirectShow video devices" ) )
        {
            isDShowVideoBegin = true;
            isDShowAudioBegin = false;
            return;
        }
        if( str.contains("DirectShow audio devices" ) )
        {
            isDShowVideoBegin = false;
            isDShowAudioBegin = true;
            return;
        }
        if( str.contains("Driver 0" ) )
        {
            isDShowVideoBegin = false;
            isDShowAudioBegin = false;
            isVFWVideoBegin = true;
            return;
        }
        int index = str.indexOf("\"");
        str = str.remove(0,index);
        str = str.remove("\"");
        str = str.remove("\n");
        str = str.remove("\r");
        if( str.left(1)== " " )
            str = str.mid(1);
        if( str.isEmpty() || str.contains("%s") )
            return;
        if (isDShowVideoBegin)
        {
            if ( "screen-capture-recorder" != str
                 &&!str.contains("dev")&&!str.contains("Virtual") )
                pThis->setVideoDevice(str);
        }
        else if (isDShowAudioBegin)
        {
            if ("virtual-audio-capturer" != str&&!str.contains("dev"))
                pThis->setAudioDevice(str);
        } else if( isVFWVideoBegin )
        {
            if( pThis->videoDevList.size() == 0 && str.contains("Microsoft WDM Image Capture" ) )
            {
                    pThis->setVideoDevice(str);
                    return;
            }
        }
    }
}

void UploadDialog::setVideoDevice( QString str)
{
     qDebug()<<"设备名: "<<str;
     videoDevList.append( str );
     ui->cbx_cam->addItem(str);
}
void UploadDialog::setAudioDevice( QString str )
{
     qDebug()<<"设备名: "<<str;
     ui->cbx_audio->addItem(str);
}


//更新进度条
void UploadDialog::slot_updateProcess(qint64 cur, qint64 max)
{
    ui->pgb_upload->setMaximum( max);
    ui->pgb_upload->setValue( cur );
}

//清空
void UploadDialog::clear()
{
    ui->le_path->setText("");
    ui->pb_beginUpload->setEnabled(false);
   // emit SIG_GetOnePicture( QImage() );
    ui->pgb_upload->setValue( 0 );

    //gif
    QMovie* movie = ui->lb_gif->movie();
    if( movie && movie->isValid() )
    {
        delete movie;
    }
}

//上传页
void UploadDialog::on_pb_page1_clicked()
{
    ui->sw_page->setCurrentIndex(0);
}

//录制页
void UploadDialog::on_pb_page2_clicked()
{
    ui->sw_page->setCurrentIndex(1);
}

//勾选摄像头
void UploadDialog::on_cb_cam_clicked()
{
    ui->cb_cam ->setChecked( true);
    ui->cb_desk ->setChecked( false );
}

//勾选桌面
void UploadDialog::on_cb_desk_clicked()
{
    ui->cb_cam ->setChecked( false );
    ui->cb_desk ->setChecked( true );
}

//更新录制时间
void UploadDialog::slot_updateRecTime()
{
    int sumSec = m_recTime.secsTo( QTime::currentTime() );

    int nMin = sumSec /60;
    int nSec = sumSec % 60;
    QString strTime = QString("%1:%2").arg(nMin ,2, 10 , QChar('0') )
            .arg(nSec ,2, 10 , QChar('0'));

    ui->lb_recTime ->setText( strTime );
}

#include<QMessageBox>
//开始录制
void UploadDialog::on_pb_recordBegin_clicked()
{
    //设置 录制
    if(m_screenRecorder && m_screenRecorder->m_saveVideoFileThread &&
            m_screenRecorder->m_saveVideoFileThread->isRunning() )
    {
        QMessageBox::critical(this , "提示","正在处理录制视频,稍后再来");
        return;
    }
    QString audioDevName = ui->cbx_audio->currentText();
    QString CamDevName = ui->cbx_cam->currentText();
    if( m_savePath.remove(" ").isEmpty())
    {
        QMessageBox::critical(this,"提示"," 先设置保存文件的名字! ");
        return;
    }
    if (audioDevName.isEmpty()||CamDevName.isEmpty())
    {
        QMessageBox::critical(this,"提示","出错了,音频或视频设备未就绪，程序无法运行！");
        return;
    }
    if (m_screenRecorder){
        delete m_screenRecorder;  m_screenRecorder = NULL;
    }
    m_screenRecorder = new ScreenRecorder;

    connect(m_screenRecorder , SIGNAL(SIG_GetOneImage(QImage)) ,
            ui->wdg_videoItem , SLOT(slot_setImage(QImage)) );

    std::string str = m_savePath.toStdString();
    char* buf =(char*)str.c_str();
    m_screenRecorder->setFileName(buf);

    m_screenRecorder->setVideoFrameRate(DEFAULT_FRAME_RATE);//设置帧率 默认 15 , 可以开
    //放设置添加帧率
    if (ui->cb_desk->isChecked()) //看是摄像头还是桌面
    {
        if (m_screenRecorder->init("desktop",true,false,audioDevName,true) == SUCCEED)
        {
            m_screenRecorder->startRecord();
        }
        else
        {
            QMessageBox::critical(this,"提示","出错了,初始化录屏设备失败！");
            return;
        }
    }
    else
    {
        if (m_screenRecorder->init(CamDevName,false,true,audioDevName,true) == SUCCEED)
        {
            m_screenRecorder->startRecord();
        }
        else
        {
            QMessageBox::critical(this,"提示","出错了,初始化音频设备失败！");
            return;
        }
    }

    m_recTime = QTime::currentTime();
    m_recTimer->start(500);


    //封闭控件
    ui->cbx_audio->setEnabled( false );
    ui->cbx_cam->setEnabled(false);
    ui->cb_cam->setEnabled(false);
    ui->cb_desk->setEnabled(false);
    ui->pb_recordBegin->setEnabled(false);
    ui->pb_recordEnd->setEnabled(true);

    ui->pb_see->setEnabled(false);
    ui->pb_rtmpUrl->setEnabled(false);
    ui->pb_savePath->setEnabled( false );


}


//关闭录制
void UploadDialog::on_pb_recordEnd_clicked()
{
    //停止录像
    if( m_screenRecorder )
    m_screenRecorder->stopRecord();


    m_recTimer->stop();

    ui->lb_recTime->setText("00:00");
    //封闭控件
    ui->cbx_audio->setEnabled( true );
    ui->cbx_cam->setEnabled(true);
    ui->cb_cam->setEnabled(true);
    ui->cb_desk->setEnabled(true);
    ui->pb_recordBegin->setEnabled(true);
    ui->pb_recordEnd->setEnabled(false);

    ui->pb_see->setEnabled(true);
    ui->pb_rtmpUrl->setEnabled(true);
    ui->pb_savePath->setEnabled( true );

    ui->lb_res->setText( m_savePath +" 录制成功");
    m_savePath="";
    QImage img;
    img.fill( Qt::black);

    ui->wdg_videoItem->slot_setImage( img );//结束录制, 发送黑色图片, 清空显示
}

//直播设置路径
void UploadDialog::on_pb_rtmpUrl_clicked()
{
    // videotest   conf  videotest appName --> rtmp路径

    //直播  conf   tst1  --> rtmp   tst2  ... tst3  ...  10000
    // mysql  t_live    id --> appName    id=1   appNanme  tst1
//    id  appName
//    10    tst1
//    12    tst2
//    0    tst3    id 10  --> rtmp地址    rtmp://服务器ip/appName
    ui->le_savePath->setText( "" );
    QString rtmpUrl = QString("rtmp://%1/videotest").arg(DEF_SERVER_IP);
    m_savePath = rtmpUrl;
    ui->le_broadcast->setText( m_savePath );

}

#include<QFileDialog>
//设置本地存储路径
void UploadDialog::on_pb_savePath_clicked()
{
    QString tmpPath = QTime::currentTime().toString("hhmmsszzz");
    tmpPath += ".flv";
    tmpPath += "F:/"+ tmpPath;
    QString path = QFileDialog::getSaveFileName( this ,"保存",tmpPath ,"(视频文件 *.flv)");
    if( path.remove(" ").isEmpty() )
    {
        QMessageBox::about(this ,"提示","重新设置");
        return;
    }
    ui->le_broadcast->setText( "" );
    m_savePath = path.replace("/" , "\\\\");

    ui->le_savePath->setText( m_savePath );
}
