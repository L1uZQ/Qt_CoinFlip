#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include"playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写paintevent
    void paintEvent(QPaintEvent *);

    PlayScene * pScene = NULL;

signals:
    void ChooseSceneBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
