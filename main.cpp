#include "mainscene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w; //主页面
    w.show();

    return a.exec();  //让程序阻塞不退出
}
