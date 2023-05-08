#include "mypushbutton.h"
#include<QDebug>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    normalImgPath = normalImg;
    pressImgPath = pressImg;

    QPixmap pixmap;

    bool ret = pixmap.load(normalImgPath);
    if(!ret){
        qDebug() <<"加载图片失败";
    }

    //设置图片的固定尺寸
    this->setFixedSize(pixmap.width(),pixmap.height());

    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pixmap);

    //设置图标大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}


void MyPushButton::zoom1() //按钮向下弹
{
    //创建动画对象
    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation1->setDuration(200);
    //创建起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置缓和曲线  QEasingCurve::OutBounce为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);

    //开始执行动画
    animation1->start();

}

void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation2 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation2->setDuration(200);
    //创建起始位置
    animation2->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //创建结束位置
    animation2->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置缓和曲线  QEasingCurve::OutBounce为弹跳效果
    animation2->setEasingCurve(QEasingCurve::OutBounce);

    //开始执行动画
    animation2->start();
}


//重写两个mouseevent函数
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(pressImgPath!="")
    {
        QPixmap pixmap;
        bool ret = pixmap.load(pressImgPath);

        if(!ret)
        {
            qDebug()<<pressImgPath<<"加载图片失败";
        }

        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    //交给父类执行按下事件
    return QPushButton::mousePressEvent(e);
}



void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath !="")
    {
        QPixmap pixmap;
        bool ret = pixmap.load(normalImgPath);

        if(!ret)
        {
            qDebug()<<"加载图片失败";
        }

        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    }
    return QPushButton::mouseReleaseEvent(e);
}


