在使用qml自带的model绑定数据确实挺不好用的,而c++来实现这个我也是第一次用,刚开始挺不理解为什么c++实现内部中是int==>data,qml中用的是string类型怎么从string映射到data.

书中的描述是: roleNames() 返回一个哈希表,将role与role-name关联起来.当QML中提供role-name时,那么就可以反查到role,进而以查到role来调用data()就可以获取到实际数据.

我的理解是Qt 自动调用 roleNames() 获取所有角色名称然后构建string=>int,根据字符串就可以找到对应的整数 role,再调用 data(index, role)获取实际数据。不过还是疑惑为什么不直接设计成 QHash<QByteArray,int> roleNames();

具体如何继承QAbstractListModel写子类可以看官方文档[QAbstractListModel Class | Qt Core | Qt 6.9.0](https://doc.qt.io/qt-6/qabstractlistmodel.html)的Subclassing部分

```
class VideoListModelPrivate;
class VideoListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChange)
public:
    explicit VideoListModel(QObject *parent = nullptr);
    ~VideoListModel();
    int rowCount(const QModelIndex& parent)const;
    QVariant data(QModelIndex const& index,int role) const;
    QHash<int,QByteArray> roleNames() const;
    QString source() const;
    void setSource(const QString& filePath);
    Q_INVOKABLE QString errorString() const;
    Q_INVOKABLE bool hasError() const;
    Q_INVOKABLE void reload();
    Q_INVOKABLE void remove(int index);

signals:
    void sourceChange();

private:
    VideoListModelPrivate *m_dptr;
};
```

参考文档:

[QAbstractListModel Class | Qt Core | Qt 6.9.0](https://doc.qt.io/qt-6/qabstractlistmodel.html)



### TableModel

[自定义的简单TableModel例子](./TableModel.md)

