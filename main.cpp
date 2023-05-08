#include "mainscene.h"
#include <QApplication>
#include"dataconfig.h"
#include<QDebug>
#include<iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w; //主页面
    w.show();

//    //测试数据
//    dataConfig config;
//    for(int i=0; i<4; i++)
//    {
//        for(int j=0; j<4; j++)
//        {
//            std::cout<<config.mData[1][i][j];
//        }
//        std::cout<<std::endl;
//    }

    return a.exec();  //让程序阻塞不退出
}
