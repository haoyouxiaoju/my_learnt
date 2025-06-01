#include "imageprocessor.h"
#include <functional>
#include <QEvent>
#include <QRunnable>
#include <QCoreApplication>
#include <QPointer>
#include <QDir>
#include <QThreadPool>
#include <QImage>


using AlgorithmFunction = std::function<void(QString,QString)>;

class AlgorithmRunnable;
//自定义事件id
class ExcutedEvent:public QEvent{
public:
    ExcutedEvent(AlgorithmRunnable* r):QEvent(evType()),m_runnable(r){}
    AlgorithmRunnable* m_runnable;
    static QEvent::Type evType(){
        if(s_evType == QEvent::None){
            s_evType = (QEvent::Type)registerEventType();
        }
        return s_evType;
    }
private:
    static QEvent::Type s_evType;
};
//
//init ExcuteEvent
QEvent::Type ExcutedEvent::s_evType = QEvent::None;

// image opertor function
static void __gray(QString sourceFile,QString destFile);
static void __binarize(QString sourceFile,QString destFile);
static void __negative(QString sourceFile,QString destFile);
static void __emboss(QString sourceFile,QString destFile);
static void __sharpen(QString sourceFile,QString destFile);
static void __soften(QString sourceFile,QString destFile);
static AlgorithmFunction g_functions[ImageProcessor::AlgorithmCount] = {
    __gray,
    __binarize,
    __negative,
    __emboss,
    __sharpen,
    __soften
};

class AlgorithmRunnable : public QRunnable{
public:
    AlgorithmRunnable(
        QString sourceFile,
        QString destFile,
        ImageProcessor::ImageAlgorithm algorithm,
        QObject* observer
    ):	m_observer(observer)
     ,	m_sourceFilePath(sourceFile)
     ,	m_destFilePath(destFile)
     ,	m_algorithm(algorithm){}
    ~AlgorithmRunnable(){}

    void run(){
        g_functions[m_algorithm](m_sourceFilePath,m_destFilePath);
        QCoreApplication::postEvent(m_observer,new ExcutedEvent(this));
    }

    QPointer<QObject> m_observer;
    QString m_sourceFilePath;
    QString m_destFilePath;
    ImageProcessor::ImageAlgorithm m_algorithm;
};

class ImageProcessorPrivate:public QObject{
public:
    ImageProcessorPrivate(ImageProcessor* processor)
        :QObject(processor)
        ,m_processor(processor)
        ,m_tempPath(QDir::currentPath())
    {
        ExcutedEvent::evType();
    }
    ~ImageProcessorPrivate(){}
    bool event(QEvent* e){
        if(e->type() == ExcutedEvent::evType()){
            ExcutedEvent* ee = (ExcutedEvent*)e;
            if(m_runnables.contains(ee->m_runnable)){
                m_notifiedAlgorithm = ee->m_runnable->m_algorithm;
                m_notifiedSourceFile = ee->m_runnable->m_sourceFilePath;
                emit m_processor->finished(ee->m_runnable->m_destFilePath);
                m_runnables.removeOne(ee->m_runnable);
            }
            delete ee->m_runnable;
            return true;
        }
        return QObject::event(e);
    }

    void process(QString sourceFile,ImageProcessor::ImageAlgorithm algorithm){
        qDebug()<<"sourceFile = "<<sourceFile;
        QFileInfo fi(sourceFile);
        QString destFile = QString("%1/%2_%3").arg(m_tempPath).arg((int)algorithm).arg(fi.fileName());
        qDebug()<<"destFile = "<<destFile;
        AlgorithmRunnable *r = new AlgorithmRunnable(sourceFile,destFile,algorithm,this);
        m_runnables.append(r);
        r->setAutoDelete(false);
        QThreadPool::globalInstance()->start(r);
    }

    ImageProcessor* m_processor;
    QList<AlgorithmRunnable*> m_runnables;
    QString m_notifiedSourceFile;
    ImageProcessor::ImageAlgorithm m_notifiedAlgorithm;
    QString m_tempPath;
};




const QString &ImageProcessor::sourceFile() const
{
    return m_d->m_notifiedSourceFile;
}

void ImageProcessor::setTempPath(const QString &tmpPath)
{
    m_d->m_tempPath = tmpPath;
}

ImageProcessor::ImageProcessor(QObject *parent)
    :QObject(parent)
    ,m_d(new ImageProcessorPrivate(this))
{}

ImageProcessor::ImageAlgorithm ImageProcessor::algorithm() const
{
    return m_d->m_notifiedAlgorithm;
}

ImageProcessor::~ImageProcessor() {
    delete m_d;
}

void ImageProcessor::process(QString file, ImageAlgorithm algorithm)
{
    m_d->process(file,algorithm);
}

void ImageProcessor::abort(QString file, ImageAlgorithm algorithm)
{
    int size = m_d ->m_runnables.size();
    AlgorithmRunnable *r;
    for(int i=0;i<size;++i){
        r = m_d->m_runnables.at(i);
        if(r->m_sourceFilePath == file && r->m_algorithm == algorithm){
            m_d->m_runnables.removeAt(i);
            break;
        }
    }
}


void __gray(QString sourceFile,QString destFile){
    // 移除 "file:///" 前缀（如果存在）
    if (sourceFile.startsWith("file:///")) {
        sourceFile.remove(0, 8);  // 移除前8个字符（"file:///"）
    }

    // 检查文件是否存在
    if (!QFile::exists(sourceFile)) {
        qDebug() << "File not found:" << sourceFile;
        return;
    }
    QImage image(sourceFile);
    if(image.isNull()){
        qDebug()<<"load"<<sourceFile<<" failed!";
        return;
    }
    int width = image.width();
    int height = image.height();
    QRgb color;
    int gray;
    for(int i=0;i<width;++i){
        for(int j=0;j<height;++j){
            color = image.pixel(i,j);
            gray = qGray(color);
            image.setPixelColor(i,j,qRgba(gray,gray,gray,qAlpha(color)));
        }
    }
    qDebug()<<"destFile = "<<destFile;
    image.save(destFile);
}
void __binarize(QString sourceFile,QString destFile){
    // 移除 "file:///" 前缀（如果存在）
    if (sourceFile.startsWith("file:///")) {
        sourceFile.remove(0, 8);  // 移除前8个字符（"file:///"）
    }
    // 检查文件是否存在
    if (!QFile::exists(sourceFile)) {
        qDebug() << "File not found:" << sourceFile;
        return;
    }
    QImage image(sourceFile);
    if(image.isNull()){
        qDebug()<<"load"<<sourceFile<<" failed!";
        return;
    }
    int width = image.width();
    int height = image.height();
    QRgb color;
    QRgb avg;
    QRgb black = qRgb(0,0,0);
    QRgb white = qRgb(255,255,255);
    for(int i=0;i<width;++i){
        for(int j=0;j<height;++j){
            color = image.pixel(i,j);
            avg = (qRed(color)+qGreen(color)+qBlue(color))/3;
            image.setPixelColor(i,j,avg>77?white:black);
        }
    }
    image.save(destFile);
}
void __negative(QString sourceFile,QString destFile){
    // 移除 "file:///" 前缀（如果存在）
    if (sourceFile.startsWith("file:///")) {
        sourceFile.remove(0, 8);  // 移除前8个字符（"file:///"）
    }
    // 检查文件是否存在
    if (!QFile::exists(sourceFile)) {
        qDebug() << "File not found:" << sourceFile;
        return;
    }
    QImage image(sourceFile);
    if(image.isNull()){
        qDebug()<<"load"<<sourceFile<<" failed!";
        return;
    }
    int width = image.width();
    int height = image.height();
    QRgb color;
    QRgb negative;
    for(int i=0;i<width;++i){
        for(int j=0;j<height;++j){
            color = image.pixel(i,j);
            negative = qRgba(255-qRed(color),255-qGreen(color),255-qBlue(color),qAlpha(color));
            image.setPixelColor(i,j,negative);
        }
    }
    image.save(destFile);
}
void __emboss(QString sourceFile, QString destFile) {
    // 处理文件路径
    if (sourceFile.startsWith("file:///")) {
        sourceFile.remove(0, 8);
    }
    if (!QFile::exists(sourceFile)) {
        qDebug() << "File not found:" << sourceFile;
        return;
    }

    QImage image(sourceFile);
    if (image.isNull()) {
        qDebug() << "Failed to load image:" << sourceFile;
        return;
    }

    int width = image.width();
    int height = image.height();
    QImage embossImage(width, height, image.format());

    // 浮雕强度参数（可调整）
    const int offset = 128; // 亮度偏移量
    const int strength = 2; // 差值增强系数（越大对比越强）

    for (int y = 1; y < height; ++y) {
        for (int x = 1; x < width; ++x) {
            // 当前像素和左上方像素的差值
            QRgb current = image.pixel(x, y);
            QRgb topLeft = image.pixel(x - 1, y - 1);

            int r = qBound(0, (qRed(current) - qRed(topLeft)) * strength + offset, 255);
            int g = qBound(0, (qGreen(current) - qGreen(topLeft)) * strength + offset, 255);
            int b = qBound(0, (qBlue(current) - qBlue(topLeft)) * strength + offset, 255);
            int a = qAlpha(current);

            embossImage.setPixel(x, y, qRgba(r, g, b, a));
        }
    }

    // 边缘处理（填充第一行和第一列）
    for (int x = 0; x < width; ++x) embossImage.setPixel(x, 0, image.pixel(x, 0));
    for (int y = 0; y < height; ++y) embossImage.setPixel(0, y, image.pixel(0, y));

    if (!embossImage.save(destFile)) {
        qDebug() << "Failed to save embossed image:" << destFile;
    } else {
        qDebug() << "Embossed image saved to:" << destFile;
    }
}
void __sharpen(QString sourceFile,QString destFile){
    // 移除 "file:///" 前缀（如果存在）
    if (sourceFile.startsWith("file:///")) {
        sourceFile.remove(0, 8);  // 移除前8个字符（"file:///"）
    }
    // 检查文件是否存在
    if (!QFile::exists(sourceFile)) {
        qDebug() << "File not found:" << sourceFile;
        return;
    }
    QImage image(sourceFile);
    if(image.isNull()){
        qDebug()<<"load"<<sourceFile<<" failed!";
        return;
    }
    int width = image.width();
    int height = image.height();
    int threshold = 80;
    QImage sharpen(width,height,QImage::Format_ARGB32);
    int r,g,b,gradientR,gradientG,gradientB;
    QRgb rgb00,rgb01,rgb10;
    for(int i=0;i<width;++i){
        for(int j=0;j<height;++j){
            if(image.valid(i,j)&&image.valid(i+1,j)&&image.valid(i,j+1)){
                rgb00 = image.pixel(i,j);
                rgb01 = image.pixel(i,j+1);
                rgb10 = image.pixel(i+1,j);
                r = qRed(rgb00);
                g = qGreen(rgb00);
                b = qBlue(rgb00);
                gradientR = abs(r-qRed(rgb01)) + abs(r-qRed(rgb10));
                gradientG = abs(g-qGreen(rgb01)) + abs(r-qGreen(rgb10));
                gradientB = abs(b-qBlue(rgb01)) + abs(r-qBlue(rgb10));

                if(gradientR > threshold){
                    r = qMin(gradientR+100,255);
                }
                if(gradientG > threshold){
                    g = qMin(gradientG+100,255);
                }
                if(gradientB > threshold){
                    b = qMin(gradientB+100,255);
                }
                sharpen.setPixel(i,j,qRgb(r,g,b));
            }
        }
    }
    image.save(destFile);
}
void __soften(QString sourceFile,QString destFile){
    // 移除 "file:///" 前缀（如果存在）
    if (sourceFile.startsWith("file:///")) {
        sourceFile.remove(0, 8);  // 移除前8个字符（"file:///"）
    }
    // 检查文件是否存在
    if (!QFile::exists(sourceFile)) {
        qDebug() << "File not found:" << sourceFile;
        return;
    }
    QImage image(sourceFile);
    if(image.isNull()){
        qDebug()<<"load"<<sourceFile<<" failed!";
        return;
    }
    int width = image.width();
    int height = image.height();
    int r,g,b;
    QRgb color;
    int xLimit = width -1;
    int yLimit = height -1;
    int ds[9] = {-1,0,1,1,1,0,-1,-1,0};
    int dp[9] = {-1,-1,-1,0,1,1,1,0,0};
    for(int i=1;i<xLimit;++i){
        for(int j=1;j<yLimit;++j){
            r=g=b=0;
            for(int m=0;m<9;m++){
                int s =i+ds[m];
                int p =j+dp[m];
                color = image.pixel(s,p);
                r += qRed(color);
                g += qGreen(color);
                b += qBlue(color);
            }
            r =qMin(255,qMax(0,(int)(r/9.0))) ;
            g =qMin(255,qMax(0,(int)(g/9.0))) ;
            b =qMin(255,qMax(0,(int)(b/9.0))) ;
            image.setPixel(i,j,qRgb(r,g,b));
        }
    }
    image.save(destFile);
}
