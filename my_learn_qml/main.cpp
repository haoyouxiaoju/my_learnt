#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include "day05/keybackquit.h"
// #include "day06/colormaker.h"
// #include "day06/changeqmlcolor.h"
// #include "day06/imageprocessor.h"
// #include "day08/videolistmodel.h"
#include "day08/tablemodel.h"

#include <QColor>
#include <QValidator>
#include <QMetaObject>
#include <QDebug>
#include <cstdlib>


int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);
    app.installEventFilter(new KeyBackQuit);
    // qmlRegisterType<ColorMaker>("an.qt.ColorMaker",1,0,"ColorMaker");
    // qmlRegisterType<ImageProcessor>("an.qt.ImageProcessor",1,0,"ImageProcessor");
    // qmlRegisterType<VideoListModel>("an.qt.CModel",1,0,"VideoListModel");
    qmlRegisterType<TableModel>("xiaoju.demo.model",1,0,"TableModel");

    #ifndef _WIN32
    setenv("QML_XHR_ALLOW_FILE_READ", "1", 1);
    #else
    _putenv("QML_XHR_ALLOW_FILE_READ=1");
    #endif


    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("lean_02", "Main");


    return app.exec();
}
