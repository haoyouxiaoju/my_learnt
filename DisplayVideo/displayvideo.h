#pragma once

#include <QtWidgets/QMainWindow>
#include <QMediaDevices>
#include <QMediaPlayer>
#include <qvideowidget.h>
#include "videocontrolbar.h"

class DisplayVideo : public QWidget 
{
    Q_OBJECT

public:
    DisplayVideo(QWidget *parent = nullptr);
    ~DisplayVideo();

    //
    QMediaPlayer*const get_player() const;
    QAudioOutput* const get_audioOutput() const;
    QVideoWidget* const get_video_widget() const;


protected:
    void resizeEvent(QResizeEvent* event) override;
    void moveEvent(QMoveEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
	void leaveEvent(QEvent* event)override;

private: 

    QMediaPlayer* player;
    QVideoWidget* v_widget;
    QAudioOutput* a_out;
    VideoControlBar* bar;
};
