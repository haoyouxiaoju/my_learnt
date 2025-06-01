#include "keybackquit.h"

KeyBackQuit::KeyBackQuit(QObject *parent)
    : QObject{parent}
{}

bool KeyBackQuit::eventFilter(QObject *watched, QEvent *e)
{
    switch(e->type()){
    case QEvent::KeyPress:
        if(Qt::Key_Back == ((QKeyEvent*)e)->key()){
            e->accept();
            return true;
        }
        break;
    case QEvent::KeyRelease:
        if(Qt::Key_Back == ((QKeyEvent*)e)->key()){
            e->accept();
            qApp->quit();
            return true;
        }
        break;
    default:
        break;
    }
    return QObject::eventFilter(watched,e);
}
