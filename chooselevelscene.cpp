#include "chooselevelscene.h"
#include <QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QtDebug>
#include"mypushbutton.h"
#include<QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588); //窗口大小固定

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));//图标

    this->setWindowTitle("选择关卡");


    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");

    //信号槽
    connect(quitAction,&QAction::triggered,[=](){
       this->close();//退出
    });

    QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton * closeBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    closeBtn->setParent(this);

    //  返回按钮设置在窗口右下方
    closeBtn->move(this->width()-closeBtn->width(), this->height()-closeBtn->height());
    connect(closeBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        QTimer::singleShot(250,this,[=](){
           this->hide();
            emit this->ChooseSceneBack();
        });
    });


    //选择关卡音效
    QSound * chooseSound = new QSound(":/res/TapButtonSound.wav",this);

    //创建选择关卡按钮
    for(int i=0; i<20; i++)
    {
        //创建按钮
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70, 130+(i/4)*70);

        //按钮上的文字
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        //设置居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->move(25+(i%4)*70, 130+(i/4)*70);
        //鼠标事件穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);


        connect(menuBtn, &MyPushButton::clicked, [=](){
//            qDebug()<<i;
            chooseSound->play();

            if(pScene==NULL){
                this->hide();
                pScene = new PlayScene(i+1);
                pScene->setGeometry(this->geometry());
                pScene->show();

                //返回之后销毁游戏页面
                connect(pScene, &PlayScene::playSceneBack,[=](){
                    this->setGeometry(pScene->geometry());
                    this->show();
                    delete pScene;
                    pScene = NULL;
                });

            }
        });

    }

}


void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //在当前页面创建一个画家
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,
                       30, pix.width(),pix.height(),pix);

}
