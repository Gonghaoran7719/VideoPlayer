#ifndef UPLOADDIALOG_H
#define UPLOADDIALOG_H

#include <QDialog>
#include<QImage>
#include"logindialog.h"
#include<QTimer>
#include<QTime>
#include"screenrecorder.h"

namespace Ui {
class UploadDialog;
}

class UploadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UploadDialog(QWidget *parent = 0);
    ~UploadDialog();
    void clear();
    QString SaveVideoJpg(QString FilePath);
signals:
    void SIG_GetOnePicture(QImage image);
    void SIG_UploadFile(QString filePath , QString imgPath , Hobby by );
public slots:
    void on_pb_view_clicked();

    void on_pb_beginUpload_clicked();
    void slot_updateProcess( qint64 cur , qint64 max);
    void initDev();
    void setVideoDevice(QString str);
    void setAudioDevice(QString str);
private slots:
    void on_pb_page1_clicked();

    void on_pb_page2_clicked();

    void on_cb_cam_clicked();

    void on_cb_desk_clicked();

    void slot_updateRecTime();

    void on_pb_recordBegin_clicked();

    void on_pb_recordEnd_clicked();

    void on_pb_rtmpUrl_clicked();

    void on_pb_savePath_clicked();

private:
    Ui::UploadDialog *ui;
    QString m_filePath;
    QString m_imgPath;
public:
    QTime m_recTime;
    QTimer * m_recTimer;
    QString m_savePath;

    QRect rct;
    QStringList videoDevList;
    ScreenRecorder *m_screenRecorder;
};

#endif // UPLOADDIALOG_H
