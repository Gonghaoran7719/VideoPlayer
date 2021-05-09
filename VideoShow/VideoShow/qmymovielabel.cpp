#include "qmymovielabel.h"
#include "ui_qmymovielabel.h"
#include<qDebug>

QMyMovieLabel::QMyMovieLabel(QWidget *parent) :
    QWidget(parent),m_movie(NULL),
    ui(new Ui::QMyMovieLabel)
{
    ui->setupUi(this);

    //安装事件监听器,让lb_movie识别事件
    ui->lb_movie->installEventFilter(this);
}

QMyMovieLabel::~QMyMovieLabel()
{
    delete ui;
}

//设置动画
void QMyMovieLabel::setMovie(QMovie *movie)
{
    m_movie = movie;
    ui->lb_movie->setMovie( movie );
    movie->start();
    movie->stop();
}

//鼠标移入
void QMyMovieLabel::enterEvent(QEvent *event)
{
    if( m_movie )
    {
        m_movie->start();
    }
}

//鼠标移出
void QMyMovieLabel::leaveEvent(QEvent *event)
{
    if( m_movie )
    {
        m_movie->stop();
    }
}

//设置控件播放的url
void QMyMovieLabel::setRtmpUrl(QString url)
{
    m_rtmpUrl = url;
}

//事件过滤处理
bool QMyMovieLabel::eventFilter(QObject *watched, QEvent *event)
{
    // 动画点击
    if ( watched == ui->lb_movie && event->type() == QEvent::MouseButtonPress)
    {
        qDebug()<< "mouse Press";
        Q_EMIT SIG_labelClicked();
        return true;
    }
}

QMovie *QMyMovieLabel::movie() const
{
    return m_movie;
}



QString QMyMovieLabel::rtmpUrl() const
{
    return m_rtmpUrl;
}




