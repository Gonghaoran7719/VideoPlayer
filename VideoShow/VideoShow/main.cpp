#include "videoshow.h"
#include <QApplication>

#undef main
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoShow w;
    w.show();

    return a.exec();
}
