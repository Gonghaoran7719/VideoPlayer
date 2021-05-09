/********************************************************************************
** Form generated from reading UI file 'videoshow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOSHOW_H
#define UI_VIDEOSHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <videoitem.h>
#include <videoslider.h>

QT_BEGIN_NAMESPACE

class Ui_VideoShow
{
public:
    QVBoxLayout *verticalLayout;
    VideoItem *wdg_video;
    QWidget *wdg_black;
    QWidget *wdg_ctrl;
    QVBoxLayout *verticalLayout_2;
    QWidget *wdg_process;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lb_videoCurrentTime;
    VideoSlider *slider_videoProcess;
    QLabel *lb_videoTotalTime;
    QWidget *wdg_ctrl_content;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_open;
    QPushButton *pb_play;
    QPushButton *pb_pause;
    QPushButton *pb_stop;
    QLabel *lb_videoName;
    QPushButton *pb_volumn;
    VideoSlider *slider_volumn;
    QPushButton *pb_online;

    void setupUi(QWidget *VideoShow)
    {
        if (VideoShow->objectName().isEmpty())
            VideoShow->setObjectName(QStringLiteral("VideoShow"));
        VideoShow->resize(800, 540);
        VideoShow->setMinimumSize(QSize(800, 540));
        VideoShow->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        verticalLayout = new QVBoxLayout(VideoShow);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        wdg_video = new VideoItem(VideoShow);
        wdg_video->setObjectName(QStringLiteral("wdg_video"));
        wdg_video->setMinimumSize(QSize(800, 0));

        verticalLayout->addWidget(wdg_video);

        wdg_black = new QWidget(VideoShow);
        wdg_black->setObjectName(QStringLiteral("wdg_black"));

        verticalLayout->addWidget(wdg_black);

        wdg_ctrl = new QWidget(VideoShow);
        wdg_ctrl->setObjectName(QStringLiteral("wdg_ctrl"));
        wdg_ctrl->setMinimumSize(QSize(401, 90));
        wdg_ctrl->setMaximumSize(QSize(16777215, 90));
        wdg_ctrl->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        verticalLayout_2 = new QVBoxLayout(wdg_ctrl);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        wdg_process = new QWidget(wdg_ctrl);
        wdg_process->setObjectName(QStringLiteral("wdg_process"));
        wdg_process->setMinimumSize(QSize(801, 30));
        wdg_process->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_2 = new QHBoxLayout(wdg_process);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 9, -1, 0);
        lb_videoCurrentTime = new QLabel(wdg_process);
        lb_videoCurrentTime->setObjectName(QStringLiteral("lb_videoCurrentTime"));

        horizontalLayout_2->addWidget(lb_videoCurrentTime);

        slider_videoProcess = new VideoSlider(wdg_process);
        slider_videoProcess->setObjectName(QStringLiteral("slider_videoProcess"));
        slider_videoProcess->setMinimumSize(QSize(100, 0));
        slider_videoProcess->setMaximumSize(QSize(11111111, 16777215));
        slider_videoProcess->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(slider_videoProcess);

        lb_videoTotalTime = new QLabel(wdg_process);
        lb_videoTotalTime->setObjectName(QStringLiteral("lb_videoTotalTime"));

        horizontalLayout_2->addWidget(lb_videoTotalTime);


        verticalLayout_2->addWidget(wdg_process);

        wdg_ctrl_content = new QWidget(wdg_ctrl);
        wdg_ctrl_content->setObjectName(QStringLiteral("wdg_ctrl_content"));
        wdg_ctrl_content->setMinimumSize(QSize(801, 60));
        wdg_ctrl_content->setMaximumSize(QSize(16777215, 60));
        horizontalLayout = new QHBoxLayout(wdg_ctrl_content);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pb_open = new QPushButton(wdg_ctrl_content);
        pb_open->setObjectName(QStringLiteral("pb_open"));
        pb_open->setMinimumSize(QSize(40, 40));
        pb_open->setMaximumSize(QSize(40, 40));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/open_normal.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_open->setIcon(icon);
        pb_open->setIconSize(QSize(40, 40));
        pb_open->setAutoDefault(true);
        pb_open->setFlat(true);

        horizontalLayout->addWidget(pb_open);

        pb_play = new QPushButton(wdg_ctrl_content);
        pb_play->setObjectName(QStringLiteral("pb_play"));
        pb_play->setMinimumSize(QSize(40, 40));
        pb_play->setMaximumSize(QSize(40, 40));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/start_white.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_play->setIcon(icon1);
        pb_play->setIconSize(QSize(40, 40));
        pb_play->setAutoDefault(true);
        pb_play->setFlat(true);

        horizontalLayout->addWidget(pb_play);

        pb_pause = new QPushButton(wdg_ctrl_content);
        pb_pause->setObjectName(QStringLiteral("pb_pause"));
        pb_pause->setMinimumSize(QSize(40, 40));
        pb_pause->setMaximumSize(QSize(40, 40));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/pause_white.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_pause->setIcon(icon2);
        pb_pause->setIconSize(QSize(40, 40));
        pb_pause->setAutoDefault(true);
        pb_pause->setFlat(true);

        horizontalLayout->addWidget(pb_pause);

        pb_stop = new QPushButton(wdg_ctrl_content);
        pb_stop->setObjectName(QStringLiteral("pb_stop"));
        pb_stop->setMinimumSize(QSize(40, 40));
        pb_stop->setMaximumSize(QSize(40, 40));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/stop_white.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_stop->setIcon(icon3);
        pb_stop->setIconSize(QSize(40, 40));
        pb_stop->setAutoDefault(true);
        pb_stop->setFlat(true);

        horizontalLayout->addWidget(pb_stop);

        lb_videoName = new QLabel(wdg_ctrl_content);
        lb_videoName->setObjectName(QStringLiteral("lb_videoName"));
        lb_videoName->setMinimumSize(QSize(0, 40));
        lb_videoName->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lb_videoName);

        pb_volumn = new QPushButton(wdg_ctrl_content);
        pb_volumn->setObjectName(QStringLiteral("pb_volumn"));
        pb_volumn->setMinimumSize(QSize(40, 40));
        pb_volumn->setMaximumSize(QSize(40, 40));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/voice_white.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_volumn->setIcon(icon4);
        pb_volumn->setIconSize(QSize(40, 40));
        pb_volumn->setAutoDefault(true);
        pb_volumn->setFlat(true);

        horizontalLayout->addWidget(pb_volumn);

        slider_volumn = new VideoSlider(wdg_ctrl_content);
        slider_volumn->setObjectName(QStringLiteral("slider_volumn"));
        slider_volumn->setMinimumSize(QSize(100, 0));
        slider_volumn->setMaximumSize(QSize(100, 16777215));
        slider_volumn->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(slider_volumn);

        pb_online = new QPushButton(wdg_ctrl_content);
        pb_online->setObjectName(QStringLiteral("pb_online"));
        pb_online->setMinimumSize(QSize(40, 40));
        pb_online->setMaximumSize(QSize(40, 40));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/color.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_online->setIcon(icon5);
        pb_online->setIconSize(QSize(40, 40));
        pb_online->setAutoDefault(true);
        pb_online->setFlat(true);

        horizontalLayout->addWidget(pb_online);


        verticalLayout_2->addWidget(wdg_ctrl_content);


        verticalLayout->addWidget(wdg_ctrl);


        retranslateUi(VideoShow);

        QMetaObject::connectSlotsByName(VideoShow);
    } // setupUi

    void retranslateUi(QWidget *VideoShow)
    {
        VideoShow->setWindowTitle(QApplication::translate("VideoShow", "VideoShow", Q_NULLPTR));
        lb_videoCurrentTime->setText(QApplication::translate("VideoShow", "00:00:00", Q_NULLPTR));
        lb_videoTotalTime->setText(QApplication::translate("VideoShow", "00:00:00", Q_NULLPTR));
        pb_open->setText(QString());
        pb_play->setText(QString());
        pb_pause->setText(QString());
        pb_stop->setText(QString());
        lb_videoName->setText(QApplication::translate("VideoShow", "\345\275\261\347\211\207\345\220\215", Q_NULLPTR));
        pb_volumn->setText(QString());
        pb_online->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VideoShow: public Ui_VideoShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOSHOW_H
