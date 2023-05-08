#include"playscene.h"
#include<QDebug>
#include<QMainWindow>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include"mycoin.h"
#include<QTimer>
#include<QLabel>
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>

PlayScene::PlayScene(int index)
{
    qDebug()<<"当前关卡为："<<index;
    this->levalIndex = index;

    //初始化代表该关卡的金币初始状态的二维数组
    dataConfig config;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            gameArray[i][j] = config.mData[this->levalIndex][i][j];
        }
    }


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


    //返回音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);

    //创建返回按钮
    MyPushButton * closeBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    closeBtn->setParent(this);

    closeBtn->move(this->width()-closeBtn->width(), this->height()-closeBtn->height());

    connect(closeBtn,&MyPushButton::clicked,[=](){
        backSound->play();
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


    //提前创建胜利图片，并隐藏在屏幕外部
    QLabel *winlabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winlabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winlabel->setPixmap(tmpPix);
    winlabel->setParent(this);
    winlabel->move((this->width()-tmpPix.width())*0.5, -tmpPix.height());


    QSound * flipSound = new QSound(":/res/ConFlipSound.wav",this);
    QSound * winSound = new QSound(":/res/LevelWinSound.wav",this);

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

            QString img;
            if(gameArray[i][j]==1){
                img=":/res/Coin0001.png";
            }
            else if(gameArray[i][j]==0){
                img=":/res/Coin0008.png";
            }


            MyCoin * coin = new MyCoin(img);
            coin->setParent(this);
            coin->move(59+i*50, 204+j*50);
            coin->posX = i;//x坐标
            coin->posY = j;//y坐标
            coin->flag =gameArray[i][j]; //正反标志

            coinBtn[i][j]=coin;

            connect(coin, &MyCoin::clicked,[=](){
                //翻转音效
                flipSound->play();
                coin->changeFlag();
                gameArray[i][j] = gameArray[i][j]==0 ? 1:0;


                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        gameArray[coin->posX+1][coin->posY]=
                                gameArray[coin->posX+1][coin->posY] ==0?1:0;
                    }
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        gameArray[coin->posX-1][coin->posY]=
                                gameArray[coin->posX-1][coin->posY] ==0?1:0;
                    }
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        gameArray[coin->posX][coin->posY+1]=
                                gameArray[coin->posX][coin->posY+1] ==0?1:0;
                    }
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        gameArray[coin->posX][coin->posY-1]=
                                gameArray[coin->posX][coin->posY-1] ==0?1:0;
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for(int i=0; i<4; i++)
                    {
                        for(int j=0; j<4; j++)
                        {
                            if(coinBtn[i][j]->flag==false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin)
                    {
                        //胜利音效
                        winSound->play();
//                        qDebug()<<"胜利";
                        QPropertyAnimation * animation1
                                = new QPropertyAnimation(winlabel,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(winlabel->x(),winlabel->y(),
                                           winlabel->width(),winlabel->height()));

                        animation1->setEndValue(QRect(winlabel->x(),winlabel->y()+winlabel->height()+this->height()*0.1,
                                           winlabel->width(),winlabel->height()));

                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();

                        //禁用所有按钮点击事件
                        for(int i=0; i<4; i++)
                        {
                            for(int j=0; j<4; j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                    }


                });

            });


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


