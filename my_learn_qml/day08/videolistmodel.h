#ifndef VIDEOLISTMODEL_H
#define VIDEOLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

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

#endif // VIDEOLISTMODEL_H
