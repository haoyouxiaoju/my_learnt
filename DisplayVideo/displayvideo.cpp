#include "displayvideo.h"
#include <qoverload.h>
#include <qaudiooutput.h>
#include <QTimer>
#include <QVideoSink>
#include <QVideoFrame>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <qgraphicsvideoitem.h>

DisplayVideo::DisplayVideo(QWidget* parent)
    : QWidget(parent)
{
    this->setMouseTracking(true);
    v_widget = new QVideoWidget(this);
    qDebug() << "v_widget rect:"<<v_widget->rect();
    v_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    v_widget->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    a_out = new QAudioOutput(this);
    a_out->setVolume(0.2);


    player = new QMediaPlayer(this);
    player->setVideoOutput(v_widget);
    player->setAudioOutput(a_out);

    player->setSource(QUrl("http://192.168.91.129/vod/35A.mp4/index.m3u8"));

    //a_out->setVolume(10);
    player->pause(); // 初始暂停，等待缓冲
    bar = new VideoControlBar(this);
    bar->hide();
    qDebug() << "bar rect:"<<bar->rect();

    // 增强状态监控
    connect(player, &QMediaPlayer::mediaStatusChanged, [this](QMediaPlayer::MediaStatus status) {
        qDebug() << "媒体状态变化:" << status;
        if (status == QMediaPlayer::LoadedMedia) {
            qDebug() << "媒体已加载完成";
        }
        if (status == QMediaPlayer::BufferedMedia || status == QMediaPlayer::BufferingMedia ) {
            player->play();
        }
        });

 
    connect(player, &QMediaPlayer::playbackStateChanged, [](QMediaPlayer::PlaybackState state) {
        qDebug() << "播放状态:" << state;
        });
    connect(player, &QMediaPlayer::hasVideoChanged, [this](bool videoAvailable) {
        if (videoAvailable == true) {
        }
        });
    
    connect(player, &QMediaPlayer::positionChanged, [this](qint64 position) {
        //qDebug() << " position :" << position;
        //this->bar->set_current_time(position);
        });
    //写这个的原因是以为视频开头会黑屏,如果直接设置player的position为0不能解决
    //通过尝试,设置105刚刚好
    //可能跟视频的关键帧有关吧
	QTimer* timer = new QTimer;
	connect(timer, &QTimer::timeout, [=]() {
		qDebug() << "Media status:" << player->mediaStatus();
		qDebug() << "是否支持seek:" << player->isSeekable(); // 此时再检查
		if (player->isSeekable() == true) {
			player->setPosition(105);
			qDebug() << "durantion" << player->duration();
			timer->stop();
            timer->deleteLater();
		}
		});
	timer->start(1000); // 每 100ms 检查一次   
}

DisplayVideo::~DisplayVideo()
{
    //在videoControlBar构造函数中并没有对传入参数进行挂靠
    //所以bar不会因为this的析构而析构
    bar->deleteLater();
}

QMediaPlayer* const DisplayVideo::get_player() const
{
    return this->player;
}

QAudioOutput* const DisplayVideo::get_audioOutput() const
{
    return this->a_out;
}

QVideoWidget* const DisplayVideo::get_video_widget() const
{
    return this->v_widget;
}

void DisplayVideo::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    v_widget->resize(event->size());
	bar->resize(QSize(event->size().width(), bar->height()));
    QPoint point = v_widget->mapToGlobal(QPoint(0, 0));
	bar->move(point.x(), point.y() + v_widget->height() - bar->height());
}

void DisplayVideo::moveEvent(QMoveEvent* event)
{
    QWidget::moveEvent(event);
    //if (bar->isVisible()) {
		bar->move(event->pos().x(), event->pos().y() + v_widget->height() - bar->height());
    //}
}

void DisplayVideo::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);
    //qDebug() << "mouse pos" << event->pos();
    if (!bar->isVisible()) {
		bar->show();
    }
}

void DisplayVideo::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);
    if (!bar->underMouse()) {  // 检查点击是否在bar上
        bar->hide();
    }
}

void DisplayVideo::leaveEvent(QEvent* event)
{
	QWidget::leaveEvent(event);
    // 获取全局鼠标位置
    QPoint globalPos = QCursor::pos();
    // 转换为当前窗口的坐标
    QPoint windowPos = this->mapFromGlobal(globalPos);
    if (windowPos.y() + bar->height() > this->height()) {
        return;
    }
	if (bar->isVisible()) {
		bar->hide();
	}
}
