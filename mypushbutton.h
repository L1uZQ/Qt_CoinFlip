#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H


#include<QPushButton>
#include<QWidget>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg, QString pressImg = "");

    void zoom1();
    void zoom2();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    QString normalImgPath, pressImgPath;


signals:

public slots:
};

#endif // MYPUSHBUTTON_H
