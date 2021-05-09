#ifndef VIDEOSHOW_H
#define VIDEOSHOW_H

#include <QWidget>
#include"videoplayer.h"
#include<QTimer>
#include"onlinedialog.h"
namespace Ui {
class VideoShow;
}

class VideoShow : public QWidget
{
    Q_OBJECT

public:
    explicit VideoShow(QWidget *parent = 0);
    ~VideoShow();

    enum PlayType
    {
        FromLocal,
        FromOnline
    };

private slots:
    void on_pb_play_clicked();


    void on_pb_open_clicked();

    void on_pb_pause_clicked();

    void on_pb_stop_clicked();

    void slot_PlayerStateChanged(int state);
    void slot_getTotalTime(qint64 uSec);
    void slot_TimerTimeOut();
    void slot_videoSliderValueChanged(int value);
    void on_pb_online_clicked();
    void slot_PlayTV(OnlineDialog::TVList tv);

    void slot_PlayUrl(QString url);
private:
    Ui::VideoShow *ui;

    VideoPlayer *m_Player;
    QTimer *m_Timer;
    OnlineDialog *m_onlineDialog;

public:
    int isStop;//代表当前是否是停止状态
    PlayType m_playType;
};

#endif // VIDEOSHOW_H
