#include "videocontrolbar.h"
#include <QTime>
#include <iostream>
#include <QMouseEvent>
#include <QFile>
#include <QAudioOutput>
#include "displayvideo.h"

VideoControlBar::VideoControlBar(DisplayVideo *parent)
	: QWidget(nullptr),_parent(parent), lastDuration(0)
{
	Q_ASSERT(parent != nullptr); //parent不能为空

	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);    //隐藏标题栏（无边框）
	//setAttribute(Qt::WA_StyledBackground);      //启用样式背景绘制
	//setAttribute(Qt::WA_TranslucentBackground); //背景透明
	// 必须先在父窗口启用透明背景
	setAttribute(Qt::WA_Hover);
	setAttribute(Qt::WA_StaticContents);
	this->setLayout(ui.verticalLayout);

	// 在创建 QComboBox 后添加事件过滤器
	ui.comboBox->installEventFilter(this);

	slider_widget = new QWidget();
	slider_widget->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);    //隐藏标题栏（无边框）
	slider_widget->setAttribute(Qt::WA_Hover);
	slider_widget->setAttribute(Qt::WA_StaticContents);
	slider_widget->setFixedSize(45, 150);
	_sound_slider = new QSlider(Qt::Vertical,slider_widget);
	_sound_slider->setRange(0, 100);
	_sound_slider->setValue(_parent->get_audioOutput()->volume()*100);

	_sound_label = new QLabel(slider_widget);
	_sound_label->setText(QString::number(parent->get_audioOutput()->volume()*100));
	qDebug() << "audio output volume" << parent->get_audioOutput()->volume();
	QFile sound_style(":/qss/sound_slider.qss");
	//QFile sound_style("D:\\myfiles\\code\\qt\\DisplayVideo\\qss\\sound_slider.qss");
	if (sound_style.open(QIODevice::ReadOnly | QIODeviceBase::Text)) {
		QString styleSheet = QLatin1String(sound_style.readAll());
		qDebug() << styleSheet;
		slider_widget->setStyleSheet(styleSheet);
		sound_style.close();
	}
	else {
		qWarning() << "failed to open qss files:" << sound_style.errorString();
	}
	slider_widget->show();

	// 创建 QFrame 包裹滑块
	QFrame* sliderFrame = new QFrame(slider_widget);
	QHBoxLayout* frameLayout = new QHBoxLayout(sliderFrame);
	frameLayout->addWidget(_sound_slider);   
	frameLayout->setAlignment(Qt::AlignCenter);  // 让 QFrame 内的滑块居中

	QVBoxLayout* sound_layout = new QVBoxLayout(slider_widget);
	sound_layout->setContentsMargins(0, 5, 0, 5);
	sound_layout->setSpacing(5);
	//sound_layout->setAlignment(Qt::AlignHCenter);  // 水平居中
	sound_layout->addWidget(_sound_label);
	sound_layout->addWidget(sliderFrame);




	//连接信号与槽
	__init_slots();

}

VideoControlBar::~VideoControlBar()
{
	slider_widget->deleteLater();

}

void VideoControlBar::set_duration(qint64 duration)
{
	qDebug() << "set duration:" << duration;
	this->__init_slider_value(duration);
	ui.duration_label->setText("/" + QTime::fromMSecsSinceStartOfDay(duration).toString("mm:ss"));
}

void VideoControlBar::set_current_time(qint64 cur_time)
{
	//qDebug() << "set current time:" << cur_time;
	ui.cur_label->setText(QTime::fromMSecsSinceStartOfDay(cur_time).toString("mm:ss"));
	this->__set_slider_position(cur_time);
}

void VideoControlBar::__init_slots()
{
	QMediaPlayer* player = _parent->get_player();
	QAudioOutput* audio_out = _parent->get_audioOutput();

	//跟随视频播放调整进度条
	connect(player, &QMediaPlayer::positionChanged, [this,player](qint64 position) {
		//qDebug() << " position :" << position;
		this->set_current_time(position);
		});
	// 更改视频的时长
	connect(player, &QMediaPlayer::mediaStatusChanged, [this,player](QMediaPlayer::MediaStatus status) {
		qDebug() << "media status is change :" << status;
		switch (status) {
		case QMediaPlayer::LoadedMedia:
		case QMediaPlayer::BufferedMedia:
		case QMediaPlayer::PlayingState:
			qint64 currentDuration = player->duration();
			if (currentDuration != lastDuration) {  // 仅当值变化时更新
				this->set_duration(currentDuration);
				lastDuration = currentDuration;
			}
			break;
		}
		});
	//视频播放 -- slider控制
	connect(ui.horizontalSlider, &QSlider::sliderMoved, [this, player](qint64 value) {
		player->setPosition(value);
		this->set_current_time(value);
		});
	//音量调节触发的状态
	connect(_sound_slider, &QSlider::sliderMoved, [this,audio_out](qint64 value) {
		qDebug() << "sound slider value is " << value;
		audio_out->setVolume(value*1.0/100);
		_sound_label->setText(QString::number(value));

		});
	//显示音量控制slider
	connect(ui.sound_button, &QPushButton::clicked, [this]() {
		//将slider_widget移到按钮上方
		QPoint point = ui.sound_button->mapToGlobal(QPoint(0, 0));
		this->slider_widget->move(point.x(),point.y()-this->slider_widget->height()-ui.horizontalSlider->height());
		qDebug() << "slider button point " << point;

		this->slider_widget->show();
		//this->slider_widget->move(point.x(),point.y());

		});
	//暂停键
	connect(ui.start, &QPushButton::clicked, [this, player]() {
		switch (player->playbackState()) {
		case QMediaPlayer::PlayingState:
			player->pause();  // 如果正在播放，则暂停
			break;
		case QMediaPlayer::PausedState:
		case QMediaPlayer::StoppedState:
			player->play();   // 如果暂停或停止，则播放
			break;
		default:
			break;
		}
		});
	//设置视频播放速度
	connect(ui.comboBox, &QComboBox::currentTextChanged, [this, player]() {
		qDebug() << "comboBox currentIndex:" << ui.comboBox->currentIndex();
		player->setPlaybackRate(qreal((ui.comboBox->currentIndex() + 1) * 0.5));
		});

	connect(ui.maximize_button, &QPushButton::clicked, [this]() {
		QWidget* widget = this->_parent;
		qDebug() << "ui maximize button clicked widget is Maximized:"<<widget->isMaximized();
		if (widget->isMaximized()) {
			widget->showNormal();  // 如果已经是最大化，则还原
		}
		else {
			widget->showMaximized();  // 如果不是最大化，则最大化
		}
		});


}

void VideoControlBar::__set_slider_position(qint64 cur_time)
{
	ui.horizontalSlider->setValue(cur_time);
}

void VideoControlBar::__init_slider_value(qint64 duration)
{
	ui.horizontalSlider->setRange(0, duration);
	ui.horizontalSlider->setValue(0);

}


void VideoControlBar::leaveEvent(QEvent* event)
{
	QWidget::leaveEvent(event);
	if (this->isVisible()) {
		//this->hide();
	}
}

void VideoControlBar::focusOutEvent(QFocusEvent* event)
{
	QWidget::focusOutEvent(event);
}

bool VideoControlBar::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == ui.comboBox && event->type() == QEvent::MouseButtonPress) {
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
		if (mouseEvent->button() == Qt::LeftButton) {
			// 阻止事件继续传播
			event->accept();
			ui.comboBox->showPopup();
			return true;
		}
	}
	return QWidget::eventFilter(obj, event);
}
