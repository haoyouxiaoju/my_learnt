#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>

class ImageProcessorPrivate;
class ImageProcessor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sourceFile READ sourceFile );
    Q_PROPERTY(ImageAlgorithm algorithm READ algorithm)
public:
    enum ImageAlgorithm{
        Gray,
        Binarize,
        Negative,
        Emboss,Sharpen,
        Soften,
        AlgorithmCount
    };
    Q_ENUM(ImageAlgorithm);

    const QString& sourceFile() const;
    ImageAlgorithm algorithm() const;
    void setTempPath(const QString& tmpPath);
    explicit ImageProcessor(QObject *parent = nullptr);
    ~ImageProcessor();

signals:
    void finished(QString netwFile);
    void progress(int value);

public slots:
    void process(QString file,ImageAlgorithm algorithm);
    void abort(QString file,ImageAlgorithm algorithm);

private:
    ImageProcessorPrivate *m_d;

};

#endif // IMAGEPROCESSOR_H
