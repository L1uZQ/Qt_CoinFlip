#include "playscene.h"
#include<QDebug>
#include<QMainWindow>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>

PlayScene::PlayScene(int index)
{
    qDebug()<<"当前关卡为："<<index;
    this->levalIndex = index;
    //设置窗口固定大小
    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("翻金币");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    QAction * quitAction = startMenu->addAction("退出");

    connect(quitAction, &QAction::triggered,[=](){
        this->close();
    });


    //创建返回按钮
    MyPushButton * closeBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    closeBtn->setParent(this);

    closeBtn->move(this->width()-closeBtn->width(), this->height()-closeBtn->height());

    connect(closeBtn,&MyPushButton::clicked,[=](){
        QTimer::singleShot(250,this,[=](){
           this->hide();
           emit this->playSceneBack();
        });
    });


}


//重写paintevent函数
void PlayScene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);

}
