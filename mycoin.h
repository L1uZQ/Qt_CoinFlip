#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include<QString>
#include<QPushButton>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString butImg);

    int posX,posY;
    bool flag;

    void changeFlag();//执行翻转效果
    QTimer * time1; //正面翻反面定时器
    QTimer * time2; //反面翻正面定时器
    int min = 1;
    int max = 8;

    bool isAnimation = false; //能否翻转的标志，默认不能翻转，点击时可以

    bool isWin = false; //胜利标志

    //重写按钮的按下事件
    void mousePressEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYCOIN_H
