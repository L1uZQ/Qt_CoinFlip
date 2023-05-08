#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"
class PlayScene: public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int index);
    int levalIndex; //记录关卡索引

    int gameArray[4][4]; //记录关卡数据

    //
    void paintEvent(QPaintEvent *);

    MyCoin * coinBtn[4][4]; //所有的金币按钮

signals:
    void playSceneBack();


public slots:

};

#endif // PLAYSCENE_H
