#include "mycoin.h"
#include<QDebug>
MyCoin::MyCoin(QString butImg)
{
    QPixmap pixmap;
    bool ret = pixmap.load(butImg);
    if(!ret){
        qDebug()<<butImg<<"加载失败";
    }

    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));


    time1 = new QTimer(this);
    time2 = new QTimer(this);

    connect(time1,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->min > this->max){
            this->min = 1;
            this->isAnimation = false;
            time1->stop();
        }
    });


    connect(time2,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->max < this->min){
            this->max = 8;
            this->isAnimation = false;
            time2->stop();
        }
    });

}

void MyCoin::changeFlag()
{
    if(this->flag)//正面
    {
        time1->start(30);
        this->isAnimation = true; //在动画开始时置为true，结束后置为false
        this->flag = false;
    }
    else{
        time2->start(30);
        this->isAnimation = true;
        this->flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || isWin) //如果是在动画期间，忽略鼠标的按下事件
    {
        return ;
    }
    else{
        return QPushButton::mousePressEvent(e);
    }
}
