#include "playscene.h"
#include<QDebug>
#include<QMainWindow>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include"mycoin.h"
#include<QTimer>
#include<QLabel>

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


    //显示当前关卡
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(19);
    label->setFont(font);
    QString str = QString("level: %1").arg(this->levalIndex);
    label->setText(str);
    //QRect(int left, int top, int width, int height)
    label->setGeometry(QRect(30,this->height()-50,120,50));


    //创建金币的背景图片
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            //绘制背景图片
            QLabel * label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57+i*50, 200+j*50);

            MyCoin * coin = new MyCoin(":/res/Coin0001.png");
            coin->setParent(this);
            coin->move(59+i*50, 204+j*50);
        }
    }


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
