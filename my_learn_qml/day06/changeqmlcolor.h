#ifndef CHANGEQMLCOLOR_H
#define CHANGEQMLCOLOR_H

#include <QObject>
#include <QTimer>
#include <random>

class ChangeQmlColor : public QObject
{
    Q_OBJECT
public:
    explicit ChangeQmlColor(QObject* target ,QObject *parent = nullptr);
    ~ChangeQmlColor();
protected slots:
    void onTimeout();

    int getRandomNumber();


private:
    QTimer m_timer;
    QObject* m_target;

    std::random_device rd;       // 真随机数
    std::mt19937 gen;            // 随机数引擎
    std::uniform_int_distribution<> dist; // 分布器

};

#endif // CHANGEQMLCOLOR_H
