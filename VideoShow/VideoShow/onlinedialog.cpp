#include "onlinedialog.h"
#include "ui_onlinedialog.h"
#include<QCryptographicHash>
#include<QMessageBox>

#define MD5_KEY  12345

static  QByteArray  GetMD5(QString val)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    QString tmp = QString("%1_%2").arg(val).arg(MD5_KEY);
    hash.addData( tmp.toStdString().c_str() );
    QByteArray bt = hash.result();
    return bt.toHex();
}


OnlineDialog* OnlineDialog::m_online = NULL;
OnlineDialog::OnlineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnlineDialog),m_id(0)
{
    ui->setupUi(this);

    m_online = this;

    qsrand( QTime(0,0,0).msecsTo( QTime::currentTime() ) );
    qRegisterMetaType<Hobby>("Hobby");

    m_login = new LoginDialog();
    m_login->hide();
    connect( ui->pb_tv1 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv2 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv3 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv4 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv5 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv6 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv7 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv8 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv9 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv10 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv11 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv12 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv13 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv14 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );
    connect( ui->pb_tv15 , SIGNAL(clicked()) , this , SLOT(slot_btnClicked()) );

    connect( ui->pb_play1 , SIGNAL(SIG_labelClicked()) , this , SLOT(slot_PlayClicked()) );
    connect( ui->pb_play2 , SIGNAL(SIG_labelClicked()) , this , SLOT(slot_PlayClicked()) );
    connect( ui->pb_play3 , SIGNAL(SIG_labelClicked()) , this , SLOT(slot_PlayClicked()) );
    connect( ui->pb_play4 , SIGNAL(SIG_labelClicked()) , this , SLOT(slot_PlayClicked()) );
    connect( ui->pb_play5 , SIGNAL(SIG_labelClicked()) , this , SLOT(slot_PlayClicked()) );
    connect( ui->pb_play6 , SIGNAL(SIG_labelClicked()) , this , SLOT(slot_PlayClicked()) );
    connect( ui->pb_play7 , SIGNAL(SIG_labelClicked()) , this , SLOT(slot_PlayClicked()) );
    connect( ui->pb_play8 , SIGNAL(SIG_labelClicked()) , this , SLOT(slot_PlayClicked()) );
    connect( ui->pb_play9 , SIGNAL(SIG_labelClicked()) , this , SLOT(slot_PlayClicked()) );
    connect( ui->pb_play10 , SIGNAL(SIG_labelClicked()) , this , SLOT(slot_PlayClicked()) );


    connect( m_login , SIGNAL(SIG_loginCommit(QString,QString)) ,
              this , SLOT(slot_loginCommit(QString,QString)) );
    connect( m_login , SIGNAL(SIG_registerCommit(QString,QString,Hobby)) ,
              this , SLOT(slot_registerCommit(QString,QString,Hobby)) );

    m_tcp = new QMyTcpClient();
    connect( m_tcp , SIGNAL(SIG_ReadyData(char*,int)) ,
             this , SLOT( slot_ReadyData(char*,int)) );

    m_uploadDlg = new UploadDialog;
//    connect( m_uploadDlg , SIGNAL( SIG_UploadFile(QString,QString,Hobby)) ,
//             this , SLOT( slot_UploadFile(QString,QString,Hobby)) );
    connect( this , SIGNAL( SIG_updateProcess(qint64,qint64) ) ,
             m_uploadDlg , SLOT( slot_updateProcess(qint64,qint64)) );
    m_uploadDlg->hide();

    m_uploadWorker = new UploadWorker;
    m_uploadThread = new QThread;
    connect( m_uploadDlg , SIGNAL( SIG_UploadFile(QString,QString,Hobby)) ,
             m_uploadWorker , SLOT( slot_UploadFile(QString,QString,Hobby)) );
    m_uploadWorker ->moveToThread( m_uploadThread );
    m_uploadThread ->start();

    ui->sw_page->setCurrentIndex( 0 );
}

OnlineDialog::~OnlineDialog()
{
    if( m_login )
    {
        delete m_login;
        m_login = NULL;
    }
    if( m_tcp )
    {
        delete m_tcp;
        m_tcp = NULL;
    }
    if( m_uploadWorker )
    {
        delete m_uploadWorker ; m_uploadWorker = NULL;
    }
    if( m_uploadThread )
    {
        m_uploadThread->quit();
        m_uploadThread->wait(100);
        if( m_uploadThread->isRunning() )
        {
            m_uploadThread->terminate();
            m_uploadThread->wait(100);
        }
        delete m_uploadThread ; m_uploadThread = NULL;
    }
    delete ui;
}

// 点击 登录/注册
void OnlineDialog::on_pb_login_clicked()
{
    m_login->show();
}

//电视节目点击响应
void OnlineDialog::slot_btnClicked()
{
    if(QObject::sender() == ui->pb_tv1)
    {
        emit SIG_PlayTV( OnlineDialog::HuNanTv);
    }else if(QObject::sender() == ui->pb_tv2)
    {
        emit SIG_PlayTV( OnlineDialog::GuangXiTv);
    }else if(QObject::sender() == ui->pb_tv3)
    {
        emit SIG_PlayTV( OnlineDialog::DongFangTv);
    }else if(QObject::sender() == ui->pb_tv4)
    {
        emit SIG_PlayTV( OnlineDialog::ZheJiangTv);
    }else if(QObject::sender() == ui->pb_tv5)
    {
        emit SIG_PlayTV( OnlineDialog::JiangsuTv);
    }
    else if(QObject::sender() == ui->pb_tv6)
    {
        emit SIG_PlayTV( OnlineDialog::HeiLongJiangTv);
    }
    else if(QObject::sender() == ui->pb_tv7)
    {
        emit SIG_PlayTV( OnlineDialog::LiaoNingTv);
    }
    else if(QObject::sender() == ui->pb_tv8)
    {
        emit SIG_PlayTV( OnlineDialog::ShanDongTv);
    }
    else if(QObject::sender() == ui->pb_tv9)
    {
        emit SIG_PlayTV( OnlineDialog::AnHuiTv );
    }
    else if(QObject::sender() == ui->pb_tv10)
    {
        emit SIG_PlayTV( OnlineDialog::JiangxiTv);
    }
    else if(QObject::sender() == ui->pb_tv11)
    {
        emit SIG_PlayTV( OnlineDialog::SiChuanTv);
    }
    else if(QObject::sender() == ui->pb_tv12)
    {
        emit SIG_PlayTV( OnlineDialog::TianJinTv);
    }
    else if(QObject::sender() == ui->pb_tv13)
    {
        emit SIG_PlayTV( OnlineDialog::ChongQingTv);
    }
    else if(QObject::sender() == ui->pb_tv14)
    {
        emit SIG_PlayTV( OnlineDialog::NingXiaTv);
    }
    else if(QObject::sender() == ui->pb_tv15)
    {
        emit SIG_PlayTV( OnlineDialog::ShenZhenTv);
    }

}

//登录提交  MD5
void OnlineDialog::slot_loginCommit(QString name, QString password)
{
    m_userName = name;
    std::string strName = name.toStdString();
    char* bufName = (char*)strName.c_str();

    QByteArray bt = GetMD5( password );

    STRU_LOGIN_RQ rq;
    strcpy_s(  rq.m_szUser ,    MAX_SIZE , bufName);
    memcpy( rq.m_szPassword , bt.data() , bt.length()  );

    if(  m_tcp->SendData( (char*)&rq , sizeof(rq) ) < 0  )
    {
        QMessageBox::about( this , "提示","网络故障");
    }
}
//注册提交
void OnlineDialog::slot_registerCommit(QString name, QString password, Hobby hy)
{
    std::string strName = name.toStdString();
    char* bufName = (char*)strName.c_str();

    QByteArray bt = GetMD5( password );

    STRU_REGISTER_RQ rq;
    strcpy_s(  rq.m_szUser ,    MAX_SIZE , bufName);
    memcpy( rq.m_szPassword , bt.data() , bt.length()  );

    rq.dance   = hy.dance   ;
    rq.edu     = hy.edu     ;
    rq.ennegy  = hy.ennegy  ;
    rq.food    = hy.food    ;
    rq.funny   = hy.funny   ;
    rq.music   = hy.music   ;
    rq.outside = hy.outside ;
    rq.video   = hy.video   ;

    if(  m_tcp->SendData( (char*)&rq , sizeof(rq) ) < 0  )
    {
        QMessageBox::about( this , "提示","网络故障");
    }
}
//tcp网络接收
void OnlineDialog::slot_ReadyData(char *buf, int nlen)
{
    int nType =  *(int*) buf;
    switch( nType )
    {
        case DEF_PACK_LOGIN_RS:
            slot_loginRs( buf,   nlen);

        break;
        case DEF_PACK_REGISTER_RS:
            slot_registerRs( buf,   nlen);

        break;
        case DEF_PACK_UPLOAD_RS:
            slot_uploadRs( buf,   nlen);
        break;
        case DEF_PACK_DOWNLOAD_RS:
            slot_downloadRs( buf,   nlen);
        break;
        case DEF_PACK_FILEBLOCK_RQ:
            slot_fileBlockRq( buf,   nlen);
        break;
    }
    delete [] buf;
}
//用户登录回复
void OnlineDialog::slot_loginRs(char *buf, int nlen)
{

    STRU_LOGIN_RS *rs = (STRU_LOGIN_RS *) buf;
    switch( rs ->m_lResult )
    {
        case userid_no_exist :
            QMessageBox::about( m_login , "提示" , "用户不存在, 登录失败");
        break;
        case password_error :
            QMessageBox::about( m_login , "提示" , "用户密码错误, 登录失败");
        break;
        case login_sucess :
            QMessageBox::about( m_login , "提示" , "登录成功");
            //界面
            ui->lb_name->setText( QString("您好, %1") .arg(m_userName));
            m_login->hide();
            m_id = rs->m_UserID ;

            //下载列表文件
            STRU_DOWNLOAD_RQ rq;
            rq.m_nUserId = m_id;
            m_tcp->SendData( (char*)&rq , sizeof(rq));

        break;
    }
}
//用户注册回复
void OnlineDialog::slot_registerRs(char *buf, int nlen)
{
    STRU_REGISTER_RS * rs = (STRU_REGISTER_RS * ) buf;
    switch( rs->m_lResult )
    {
        case userid_is_exist:
            QMessageBox::about( m_login , "提示" , "用户已存在, 注册失败");
        break;
        case register_sucess:
            QMessageBox::about( m_login , "提示" , "注册成功");
        break;
    }
}


//上传回复
void OnlineDialog::slot_uploadRs(char *buf, int nlen)
{
    STRU_UPLOAD_RS * rs = (STRU_UPLOAD_RS * ) buf;
    switch( rs->m_nResult )
    {
        case 1:
            QMessageBox::about( m_login , "提示" , "上传成功");
        break;

    }
}
#include<QDir>
//处理下载回复
void OnlineDialog::slot_downloadRs(char *buf, int nlen)
{
    STRU_DOWNLOAD_RS * rs = (STRU_DOWNLOAD_RS *)buf;

    //文件头

    //给FileInfo 赋值

    FileInfo * info = new FileInfo;
    // videoid 作为文件的标示 , fileid 用来区分不同控件
    info->videoId = rs->m_nVideoId;
    info->fileId = rs->m_nFileId;
    info->fileName = rs->m_szFileName;

//    (./temp/);
    QDir dir;
    if( !dir.exists( QDir::currentPath() +"/temp/"))
    {
        dir.mkpath(QDir::currentPath() +"/temp/");
    }
    info->filePath = QString("./temp/%1").arg(rs->m_szFileName);

    info->filePos = 0;
    info->fileSize = rs->m_nFileSize;

    info->rtmpUrl = QString( "rtmp://%1/vod%2").arg(DEF_SERVER_IP).arg( rs->m_rtmp ); //  //1/104.mp4

    qDebug()<< "rtmp -- "<< info->rtmpUrl;
    // rtmp://192.168.0.10/vod//1/104.mp4
    info->pFile = new QFile(info->filePath);

    if( info->pFile->open(QIODevice::WriteOnly))
    {
        m_mapVideoIDTOFileInfo[ info->videoId ] = info;
    }else
    {
        delete info;
    }
}

//下载文件块
void OnlineDialog::slot_fileBlockRq(char *buf, int nlen)
{
    STRU_FILEBLOCK_RQ * rq = (STRU_FILEBLOCK_RQ *)buf;

    auto ite = m_mapVideoIDTOFileInfo.find( rq->m_nFileId );
    if(  ite ==  m_mapVideoIDTOFileInfo.end())  return;

    FileInfo* info =    m_mapVideoIDTOFileInfo[ rq->m_nFileId ];

    int64_t res =  info->pFile->write( rq->m_szFileContent , rq->m_nBlockLen );
    info->filePos += res;

    if( info->filePos >= info->fileSize )
    {
        //关闭文件
        info->pFile->close();
        //删除该节点
        m_mapVideoIDTOFileInfo.erase( ite );
        //设置到控件
        //info->fileId --> 控件号码
        QString pbNum = QString("pb_play%1").arg(info->fileId);
        QMyMovieLabel * pb_play = ui->sw_page->findChild<QMyMovieLabel *>(pbNum);

        QMovie *LastMovie = pb_play->movie();
        if( LastMovie && LastMovie->isValid() )
        {
            delete LastMovie;
        }
        QMovie *movie = new QMovie(info->filePath);
        movie->setScaledSize( QSize(150,120 ) );

        pb_play->setMovie(movie);
        pb_play->setRtmpUrl( info->rtmpUrl);

        //回收info
        delete info;
        info = NULL;
    }
}

//点播项被点击
void OnlineDialog::slot_PlayClicked()
{
    QMyMovieLabel * pb_play = (QMyMovieLabel *)QObject::sender();

    Q_EMIT SIG_PlayUrl(  pb_play->rtmpUrl() );
}

//上传文件响应
void OnlineDialog::slot_UploadFile(QString filePath, QString imgPath, Hobby hy)
{
    //上传
    qDebug()<< "上传开始";
    UploadFile( imgPath , hy );
    UploadFile( filePath , hy , imgPath );

}

#include<QFileInfo>
//上传文件
void OnlineDialog::UploadFile(QString filePath, Hobby hy , QString gifName  )
{
    //兼容中文
    QFileInfo info(filePath);
    QString FileName = info.fileName();
    std::string strName = FileName.toStdString();
    const char* file_name = strName.c_str();

    
    STRU_UPLOAD_RQ rq;
    rq.m_nFileId = qrand()%10000;
    rq.m_nFileSize = info.size();
    strcpy_s( rq.m_szFileName , MAX_PATH , file_name );
    
    QByteArray bt =  filePath.right( filePath.length() - filePath.lastIndexOf('.') -1 ).toLatin1();
    
    memcpy(rq.m_szFileType  ,bt.data() , bt.length() );
    
    if( !gifName.isEmpty() )
    {
        QFileInfo info(gifName);
        strcpy_s( rq.m_szGifName , MAX_PATH  , info.fileName().toLocal8Bit().data() );
    }
    memcpy(  rq.m_szHobby , &hy ,sizeof(hy) );
    rq.m_UserId = m_id;
    
    m_tcp->SendData( (char*)&rq , sizeof( rq ));
    
    FileInfo  fi;
    fi.fileId = rq.m_nFileId;
    fi.fileName = FileName;
    fi.filePath = filePath;
    fi.filePos = 0;
    fi.fileSize = rq.m_nFileSize;
    fi.pFile = new QFile(filePath);  
    
    if( fi.pFile->open(QIODevice::ReadOnly))
    {
        while(1)
        {
            STRU_FILEBLOCK_RQ blockrq;
            
             int64_t res = fi.pFile->read( blockrq.m_szFileContent , MAX_CONTENT_LEN);
             fi.filePos += res;
             blockrq.m_nBlockLen = res ;
             blockrq.m_nFileId = rq.m_nFileId;
             blockrq.m_nUserId = m_id;
             
             m_tcp->SendData( (char* ) &blockrq , sizeof( blockrq));
             emit SIG_updateProcess( fi.filePos , fi.fileSize);
             
             if( fi.filePos >= fi.fileSize )
             {
                 fi.pFile->close();
                 delete fi.pFile;
                 fi.pFile = NULL;
                 break;
             }
        }
    }
}


//点击上传视频
void OnlineDialog::on_pb_upload_clicked()
{
//    if( m_id == 0 )
//    {
//        QMessageBox::about( this , "提示" , "先登录");
//        return;
//    }
    m_uploadDlg->clear();
    m_uploadDlg->show();
}

//工作者 上传流程
void UploadWorker::slot_UploadFile(QString filePath, QString imgPath, Hobby hy)
{
    OnlineDialog::m_online->slot_UploadFile( filePath , imgPath , hy );
}

//地方台分页
void OnlineDialog::on_pb_tvShow_clicked()
{
    ui->sw_page->setCurrentIndex( 0 );
}

//点播分页
void OnlineDialog::on_pb_video_clicked()
{
    if( !m_id )
    {
        QMessageBox::about(this, "提示" , "先登录")   ;
        return;
    }
    ui->sw_page->setCurrentIndex( 1 );
}


//刷新
void OnlineDialog::on_pb_fresh_clicked()
{
    if( !m_id )
    {
        QMessageBox::about(this, "提示" , "先登录")   ;
        return;
    }

    STRU_DOWNLOAD_RQ rq;
    rq.m_nUserId = m_id ;
    m_tcp ->SendData( (char*)&rq , sizeof(rq));
}
