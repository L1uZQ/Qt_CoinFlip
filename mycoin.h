#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include<QString>
#include<QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString butImg);
signals:

public slots:
};

#endif // MYCOIN_H
