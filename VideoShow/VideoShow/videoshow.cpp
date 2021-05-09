#include "videoshow.h"
#include "ui_videoshow.h"
#include"qDebug"

VideoShow::VideoShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoShow)
{
    ui->setupUi(this);

    m_Player = new VideoPlayer;
    connect(m_Player , SIGNAL(SIG_GetOneImage(QImage)) ,
            ui->wdg_video , SLOT(slot_setImage(QImage)) );
    connect( m_Player , SIGNAL(SIG_PlayerStateChanged(int))
             ,this , SLOT(slot_PlayerStateChanged(int)) );
    connect( m_Player , SIGNAL(SIG_TotalTime(qint64))
             ,this , SLOT(slot_getTotalTime(qint64)) );

    connect( ui->slider_videoProcess , SIGNAL(SIG_valueChanged(int)),
             this , SLOT(slot_videoSliderValueChanged(int)) );
    m_Timer = new QTimer; //定时器-获取当前视频时间
    connect(m_Timer,SIGNAL(timeout()),this,SLOT(slot_TimerTimeOut()));
    m_Timer->setInterval(500);

    slot_PlayerStateChanged(PlayerState::Stop);

    m_onlineDialog = new OnlineDialog();
    m_onlineDialog->hide();

    connect( m_onlineDialog , SIGNAL(SIG_PlayTV(OnlineDialog::TVList)) ,
             this , SLOT( slot_PlayTV(OnlineDialog::TVList)) );

    connect( m_onlineDialog , SIGNAL(SIG_PlayUrl(QString)),
             this , SLOT(slot_PlayUrl(QString)) );
}

extern int quit;
VideoShow::~VideoShow()
{
    if( m_Player )
    {
        m_Player->m_videoState.quit = 1;
        m_Player->quit();
        if( m_Player->isRunning() )
        {
            m_Player->terminate();
            m_Player->wait();
        }
        delete m_Player;
    }
    if( m_onlineDialog )
    {
        delete m_onlineDialog;
        m_onlineDialog = NULL;
    }
    delete ui;
}

//更新播放器的总时间
void VideoShow::slot_getTotalTime(qint64 uSec)
{
    qDebug()<< __func__;
    qint64 Sec = uSec/1000000;

    ui->slider_videoProcess->setRange(0,Sec);//精确到秒

    QString hStr = QString("00%1").arg(Sec/3600);
    QString mStr = QString("00%1").arg(Sec/60);
    QString sStr = QString("00%1").arg(Sec%60);

    QString str = QString("%1:%2:%3").arg(hStr.right(2)).arg(mStr.right(2)).arg(sStr.right(2));
    ui->lb_videoTotalTime->setText(str);

}

//定时器更新进度
void VideoShow::slot_TimerTimeOut()
{
    if (QObject::sender() == m_Timer)
    {
        qint64 Sec = m_Player->getCurrentTime()/1000000;

        ui->slider_videoProcess->setValue(Sec);

        QString hStr = QString("00%1").arg(Sec/3600);
        QString mStr = QString("00%1").arg(Sec/60%60);
        QString sStr = QString("00%1").arg(Sec%60);

        QString str = QString("%1:%2:%3").arg(hStr.right(2)).arg(mStr.right(2)).arg(sStr.right(2));
        ui->lb_videoCurrentTime->setText(str);

        if(ui->slider_videoProcess->value() == ui->slider_videoProcess->maximum()
                && m_Player->m_playerState == PlayerState::Stop)
        {
            slot_PlayerStateChanged( PlayerState::Stop );
        }else if(ui->slider_videoProcess->value() + 1  == ui->slider_videoProcess->maximum()
                && m_Player->m_playerState == PlayerState::Stop)
        {
            slot_PlayerStateChanged( PlayerState::Stop );
        }
    }
}
//跳转进度
void VideoShow::slot_videoSliderValueChanged(int value)
{
    if( QObject :: sender() == ui->slider_videoProcess )
    {
        if( this->m_playType != FromLocal ) return;
        m_Player->seek( (qint64)value*1000000 );  // 精确到微秒
    }
}

//状态切换
void VideoShow::slot_PlayerStateChanged(int state)
{
     switch( state )
     {
        case PlayerState::Stop:
            qDebug()<< "VideoPlayer::Stop";
            ui->wdg_video->hide();
            ui->wdg_black->show();
            m_Timer->stop();
            ui->slider_videoProcess->setValue(0);
            ui->lb_videoTotalTime->setText("00:00:00");
            ui->lb_videoCurrentTime->setText("00:00:00");
            ui->lb_videoName->setText("");
            ui->pb_play->show();
            ui->pb_pause->hide();
            this->update();
            isStop = true;
        break;
        case PlayerState::Playing:
             qDebug()<< "VideoPlayer::Playing";
             ui->wdg_video->show();
             ui->wdg_black->hide();
             ui->pb_play->hide();
             ui->pb_pause->show();
             m_Timer->start();
             this->update();
             isStop = false;
        break;
     }
}
#include<QFileDialog>
#include<QMessageBox>

//打开文件 并播放
void VideoShow::on_pb_open_clicked()
{
    //打开文件 弹出对话框 参数:父窗口, 标题, 默认路径, 筛选器
    QString path = QFileDialog::getOpenFileName(this,"选择要播放的文件" , "F:/",
            "视频文件 (*.flv *.rmvb *.avi *.MP4 *.mkv);; 所有文件(*.*);;");
    if(!path.isEmpty())
    {
        qDebug()<< path ;
        QFileInfo info(path);
        if( info.exists() )
        {
            m_playType = FromLocal;
            m_Player->stop( true ); //如果播放 你要先关闭
            m_Player->setFileName(path);
            ui->lb_videoName->setText( info.baseName() );
            slot_PlayerStateChanged(PlayerState::Playing);
        }
        else
        {
            QMessageBox::information( this, "提示" , "打开文件失败");
        }
    }
}
//播放键  --> 暂停到播放
void VideoShow::on_pb_play_clicked()
{
    //点击之后 , 开启线程 ( 获取图片, 显示到控件 )
//    qDebug()<< "VideoShow"<<QThread::currentThread()->currentThreadId();
//    m_Player->start();

    if( isStop ) return;
    m_Player->play();
    if(m_Player->getPlayerState() == PlayerState::Playing)
    {
        ui->pb_play->hide();
        ui->pb_pause->show();
        this->update();
    }
}
//暂停  --> 播放到暂停
void VideoShow::on_pb_pause_clicked()
{
    if( isStop ) return;//停止状态自然不能播放
    if( this->m_playType != FromLocal ) return;
    m_Player->pause();

    if( m_Player->getPlayerState() == PlayerState::Pause)
    {
        ui->pb_play->show();
        ui->pb_pause->hide();
        this->update();
    }
}

//停止
void VideoShow::on_pb_stop_clicked()
{
    m_Player->stop(true);
}

//弹出网络模块
void VideoShow::on_pb_online_clicked()
{
    m_onlineDialog->show();
}

//播放网络tv
void VideoShow::slot_PlayTV(OnlineDialog::TVList tv)
{
    m_Player->stop( true ); //如果播放 你要先关闭
//    m_Player->setFileName("rtmp://...");
//    ui->lb_videoName->setText( "湖南卫视" );
    m_playType = FromOnline;
    switch( tv )
    {
        case OnlineDialog::HuNanTv:
        m_Player->setFileName("rtmp://58.200.131.2:1935/livetv/hunantv");//湖南卫视
        ui->lb_videoName->setText( "湖南卫视" );
        break;
        case OnlineDialog::GuangXiTv:
        m_Player->setFileName("rtmp://58.200.131.2:1935/livetv/gxtv");  //广西卫视
        ui->lb_videoName->setText( "广西卫视" );
        break;
        case OnlineDialog::DongFangTv:
        m_Player->setFileName("rtmp://58.200.131.2:1935/livetv/dftv");  //东方卫视
        ui->lb_videoName->setText( "东方卫视" );
        break;
        case OnlineDialog::HeiLongJiangTv:
        m_Player->setFileName("rtmp://58.200.131.2:1935/livetv/hljtv");  //黑龙江卫视
        ui->lb_videoName->setText( "黑龙江卫视" );
        break;
        case OnlineDialog::ZheJiangTv:
        m_Player->setFileName("rtmp://58.200.131.2:1935/livetv/zjtv");  //浙江卫视
        ui->lb_videoName->setText( "浙江卫视" );
        break;
        case OnlineDialog::LiaoNingTv:
        m_Player ->setFileName("rtmp://58.200.131.2:1935/livetv/lntv");  //辽宁卫视
        ui->lb_videoName->setText( "辽宁卫视" );
        break;
        case OnlineDialog::NingXiaTv:
        m_Player ->setFileName("rtmp://58.200.131.2:1935/livetv/nxtv");  //宁夏卫视
        ui->lb_videoName->setText( "宁夏卫视" );
        break;
        case OnlineDialog::ShanDongTv:
        m_Player ->setFileName("rtmp://58.200.131.2:1935/livetv/sdtv");  //山东卫视
        ui->lb_videoName->setText( "山东卫视" );
        break;
        case OnlineDialog::JiangsuTv:
        m_Player ->setFileName("rtmp://58.200.131.2:1935/livetv/jstv");  //江苏卫视
        ui->lb_videoName->setText( "江苏卫视" );
        break;
        case OnlineDialog::ChongQingTv:
        m_Player ->setFileName("rtmp://58.200.131.2:1935/livetv/cqtv");  //重庆卫视
        ui->lb_videoName->setText( "重庆卫视" );
        break;
        case OnlineDialog::ShenZhenTv:
        m_Player ->setFileName("rtmp://58.200.131.2:1935/livetv/sztv");  //深圳卫视
        ui->lb_videoName->setText( "深圳卫视" );
        break;
        case OnlineDialog::JiangxiTv:
        m_Player ->setFileName("rtmp://58.200.131.2:1935/livetv/jxtv");  //江西卫视
        ui->lb_videoName->setText( "江西卫视" );
        break;
        case OnlineDialog::AnHuiTv:
        m_Player ->setFileName("rtmp://58.200.131.2:1935/livetv/ahtv");  //安徽卫视
        ui->lb_videoName->setText( "安徽卫视" );
        break;
        case OnlineDialog::SiChuanTv:
        m_Player ->setFileName("rtmp://58.200.131.2:1935/livetv/sctv");  //四川卫视
        ui->lb_videoName->setText( "四川卫视" );
        break;
        case OnlineDialog::TianJinTv:
        m_Player ->setFileName("rtmp://58.200.131.2:1935/livetv/tjtv");  //天津卫视
        ui->lb_videoName->setText( "天津卫视" );
        break;

        default:
        break;
    }

    slot_PlayerStateChanged(PlayerState::Playing);
}

//播放url
void VideoShow::slot_PlayUrl(QString url)
{
    m_Player->stop( true ); //如果播放 你要先关闭

    m_playType = FromOnline;

    m_Player ->setFileName( url );  //url
    ui->lb_videoName->setText( "" );

    slot_PlayerStateChanged(PlayerState::Playing);
}
