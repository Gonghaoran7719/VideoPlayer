#ifndef QMYMOVIELABEL_H
#define QMYMOVIELABEL_H

#include <QWidget>
#include<QMovie>
#include<QEvent>
#include<QMovie>

namespace Ui {
class QMyMovieLabel;
}

class QMyMovieLabel : public QWidget
{
    Q_OBJECT

public:
    explicit QMyMovieLabel(QWidget *parent = 0);
    ~QMyMovieLabel();
    QString rtmpUrl() const;

    QMovie *movie() const;

signals:
    void SIG_labelClicked();
public slots:
    void setMovie(QMovie * movie);
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent *event);
    void setRtmpUrl(QString url);
    virtual bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::QMyMovieLabel *ui;
    QMovie *m_movie;
    QString m_rtmpUrl;

};

#endif // QMYMOVIELABEL_H
