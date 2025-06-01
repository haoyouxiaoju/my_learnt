#ifndef KEYBACKQUIT_H
#define KEYBACKQUIT_H

#include <QObject>
// #include <QGuiApplication>
// #include <QQmlApplicationEngine>
#include <QKeyEvent>

class KeyBackQuit : public QObject
{
    Q_OBJECT
public:
    explicit KeyBackQuit(QObject *parent = nullptr);
    Q_INVOKABLE bool eventFilter(QObject* watched,QEvent* e);


signals:
};

#endif // KEYBACKQUIT_H
