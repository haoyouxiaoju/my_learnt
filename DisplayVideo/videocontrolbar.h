#pragma once

#include <QWidget>
#include "ui_videocontrolbar.h"

class DisplayVideo;

class VideoControlBar : public QWidget
{
	Q_OBJECT

public:
	VideoControlBar(DisplayVideo *parent = nullptr);
	~VideoControlBar();

	void set_duration(qint64 duration); //设置视频时长 初始化slider的值
	void set_current_time(qint64 cur_time);//设置当前时长 同时修改进度条

	
private:
	void __init_slots();

	void __set_slider_position(qint64 cur_time); //修改进度
	void __init_slider_value(qint64 duration);  //初始化slider的最大值



protected:
	void leaveEvent(QEvent* event)override;
	void focusOutEvent(QFocusEvent* event) override;
	bool eventFilter(QObject* obj, QEvent* event) override;




private:
	Ui::VideoControlBar ui;

	DisplayVideo* _parent; //获取player;

	QWidget* slider_widget;//存放_sound_slider和_sound_label
	QSlider* _sound_slider; //调节声音
	QLabel* _sound_label;	//显示当前声音大小
	qint64 lastDuration; //保存最后一次更改视频duration的值
};
