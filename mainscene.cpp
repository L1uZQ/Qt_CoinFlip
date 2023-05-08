#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QTimer>
#include <QSound>
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    setFixedSize(320, 588); //设置固定大小

    setWindowIcon(QIcon(":/res/Coin0001.png"));  //设置图标

    setWindowTitle("翻硬币主场景");

    //退出按钮的实现
    connect(ui->actionQuit, &QAction::triggered, [=](){
        this->close();
    });


    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);

    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");

    startBtn->setParent(this);

    startBtn->move(this->width()*0.5-startBtn->width()*0.5, this->height()*0.7);


    connect(startBtn, &MyPushButton::clicked,[=](){
        startBtn->zoom1(); //向下跳跃
        startBtn->zoom2(); //向上跳跃

        //播放音效
        startSound->play();

        QTimer::singleShot(500,this,[=](){
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });

    });

    connect(chooseScene,&ChooseLevelScene::ChooseSceneBack,[=](){
        this->setGeometry(chooseScene->geometry());
        this->show();
    });

}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");

    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);

    painter.drawPixmap(10,30,pix);
}


MainScene::~MainScene()
{
    delete ui;
}
