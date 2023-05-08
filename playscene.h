#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
class PlayScene: public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int index);
    int levalIndex; //记录关卡索引

    //
    void paintEvent(QPaintEvent *);

signals:
    void playSceneBack();


public slots:

};

#endif // PLAYSCENE_H
