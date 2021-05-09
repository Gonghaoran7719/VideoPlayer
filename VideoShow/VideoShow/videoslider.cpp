#include "videoslider.h"
#include<QStyle>
VideoSlider::VideoSlider(QWidget *parent) : QSlider(parent)
{

}

void VideoSlider::mousePressEvent(QMouseEvent *event)
{
    int value = QStyle::sliderValueFromPosition(
    minimum(), maximum(), event->pos().x(), width());
    setValue(value);
    /*emit*/Q_EMIT SIG_valueChanged(value);

}
