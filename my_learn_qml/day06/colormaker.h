#ifndef COLORMAKER_H
#define COLORMAKER_H

#include <QObject>
#include <QColor>
#include <random>


class ColorMaker : public QObject
{
    Q_OBJECT
    // Q_ENUMS(GenerateAlgorithm) 弃用了


    //
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged )
    Q_PROPERTY(QColor timeColor READ timeColor NOTIFY timeColorChanged)//缺少NOTIFY会有警告

public:

    enum GenerateAlgorithm{
        RandomRGB,
        RandomRed,
        RandomGreen,
        RandomBlue,
        LinearIncrease
    };
    Q_ENUM(GenerateAlgorithm)	//需要放在enum声明后面33

    explicit ColorMaker(QObject *parent = nullptr);
    ~ColorMaker();

    QColor color() const;	//const此处强调此函数为成员函数,不修改成员变量,编译器会进行检测是否发生修改
    void setColor(const QColor& color);
    QColor timeColor() const;

    Q_INVOKABLE GenerateAlgorithm algorithm() const;
    Q_INVOKABLE void setAlgorithm(GenerateAlgorithm algorithm);

    inline int getRandomNumber(){
        return dist(gen);
    }

signals:
    void colorChanged(const QColor& color);
    void timeColorChanged(const QColor& color);
    void currentTime(const QString& strTime);

public slots:
    void start();
    void stop();

protected:
    void timerEvent(QTimerEvent* e) override;

private:
    GenerateAlgorithm m_algorithm;
    QColor m_currentColor;
    int m_nColorTimer;

    std::random_device rd;       // 真随机数
    std::mt19937 gen;            // 随机数引擎
    std::uniform_int_distribution<> dist; // 分布器

};

#endif // COLORMAKER_H
