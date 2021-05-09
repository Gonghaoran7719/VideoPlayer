#ifndef ONLINEDIALOG_H
#define ONLINEDIALOG_H

#include <QDialog>
#include"logindialog.h"
#include"qmytcpclient.h"
#include"Packdef.h"
#include"uploaddialog.h"
#include"QObject"
#include<QThread>
#include<qmap>

namespace Ui {
class OnlineDialog;
}

class UploadWorker: public QObject
{
    Q_OBJECT
public slots:
    void slot_UploadFile(QString filePath,QString imgPath,Hobby hy);
};


class OnlineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnlineDialog(QWidget *parent = 0);
    ~OnlineDialog();

    enum TVList
    {
            HuNanTv,
            GuangXiTv,
            DongFangTv,
            ZheJiangTv,
            JiangsuTv,
            HeiLongJiangTv,
            LiaoNingTv,
            ShanDongTv,
            AnHuiTv,
            JiangxiTv,
            SiChuanTv,
            TianJinTv,
            ChongQingTv,
            NingXiaTv,
            ShenZhenTv
    };
signals:
    void  SIG_PlayTV( OnlineDialog::TVList tv);
    void  SIG_updateProcess(qint64,qint64);
    void  SIG_PlayUrl(QString url);
public slots:
    void on_pb_login_clicked();
    void slot_btnClicked();

    void slot_loginCommit(QString name,QString password );
    void slot_registerCommit(QString name ,QString password ,Hobby hy);
    void slot_ReadyData(char* buf ,int nlen);
    void slot_loginRs(char *buf, int nlen);
    void slot_registerRs(char *buf, int nlen);
    void slot_uploadRs(char *buf, int nlen);
    void slot_downloadRs(char *buf, int nlen);
    void slot_fileBlockRq(char *buf, int nlen);

    void slot_PlayClicked();
    void slot_UploadFile(QString filePath,QString imgPath,Hobby hy);
    void UploadFile( QString filePath ,Hobby hy , QString gifName = "" );
    void on_pb_upload_clicked();


private:
    Ui::OnlineDialog *ui;
    LoginDialog * m_login;
    QMyTcpClient * m_tcp;
    QString m_userName;
    int m_id;
    UploadDialog *m_uploadDlg;
    QThread * m_uploadThread;
    UploadWorker* m_uploadWorker;
    QMap<int , FileInfo*> m_mapVideoIDTOFileInfo;

public:
    static OnlineDialog* m_online;
private slots:
    void on_pb_tvShow_clicked();
    void on_pb_video_clicked();
    void on_pb_fresh_clicked();
};

#endif // ONLINEDIALOG_H
