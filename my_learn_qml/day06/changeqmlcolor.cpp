#include "changeqmlcolor.h"

#include <QColor>
#include <QVariant>
ChangeQmlColor::ChangeQmlColor(QObject *target, QObject *parent)
    : QObject{parent}
    , m_timer(this)
    , m_target(target)
    , gen(rd())
    , dist(0,255)
{
    connect(&m_timer,&QTimer::timeout,this,&ChangeQmlColor::onTimeout);
    m_timer.start(1000);

}

ChangeQmlColor::~ChangeQmlColor(){}

void ChangeQmlColor::onTimeout()
{
    QColor color = QColor::fromRgb(getRandomNumber(),getRandomNumber(),getRandomNumber());
    m_target->setProperty("color",color);

}

int ChangeQmlColor::getRandomNumber(){
    return dist(gen);
}
