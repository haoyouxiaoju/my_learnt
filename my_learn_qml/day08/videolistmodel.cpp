#include "videolistmodel.h"
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QFile>
#include <QStringRef>

using VideoData = QVector<QString>;

class VideoListModelPrivate{
public:
    VideoListModelPrivate():m_bError(false){
        int role = Qt::UserRole;
        m_roleNames.insert(role++,"name");
        m_roleNames.insert(role++,"date");
        m_roleNames.insert(role++,"director_tag");
        m_roleNames.insert(role++,"director");
        m_roleNames.insert(role++,"actor_tag");
        m_roleNames.insert(role++,"actor");
        m_roleNames.insert(role++,"rating_tag");
        m_roleNames.insert(role++,"rating");
        m_roleNames.insert(role++,"desc_tag");
        m_roleNames.insert(role++,"desc");
        m_roleNames.insert(role++,"img");
        m_roleNames.insert(role++,"playpage");
        m_roleNames.insert(role++,"playtimes");
    }
    ~VideoListModelPrivate(){clear();}

    void load(){
        QXmlStreamReader reader;
        QFile file(m_strXmlFile);
        if(!file.exists()){
            m_bError = true;
            m_strError = m_strXmlFile+" File Not Found!";
            return;
        }
        if(!file.open(QFile::ReadOnly)){
            m_bError = true;
            m_strError = file.errorString();
            return;
        }
        reader.setDevice(&file);
        QStringView elementName;
        VideoData* video;
        while(!reader.atEnd()){
            reader.readNext();
            if(reader.isStartElement()){
                elementName = reader.name();
                if(elementName == "video"){
                    video = new VideoData();
                    QXmlStreamAttributes attrs = reader.attributes();
                    video->append(attrs.value("name").toString());
                    video->append(attrs.value("date").toString());
                }else if(elementName == "attr"){
                    video->append(reader.attributes().value("tag").toString());
                    video->append(reader.readElementText());
                }
                else if(elementName == "poster"){
                    video->append(reader.attributes().value("img").toString());
                }else if(elementName == "page"){
                    video->append(reader.attributes().value("link").toString());
                }else if(elementName == "playtimes"){
                    video->append(reader.readElementText());
                }
            }else if(reader.isEndElement()){
                elementName = reader.name();
                if(elementName == "video"){
                    m_videos.append(video);
                    video = nullptr;
                }
            }
        }
        file.close();
        if(reader.hasError()){
            m_bError = true;
            m_strError = reader.errorString();
        }
    }
    void reset(){
        m_bError = false;
        m_strError.clear();
        clear();
    }
    void clear(){
        int count = m_videos.size();
        if(count > 0){
            for(int i=0;i<count;i++){
                delete m_videos.at(i);
            }
            m_videos.clear();
        }
    }

    QString m_strXmlFile;
    QString m_strError;
    bool m_bError;
    QHash<int,QByteArray> m_roleNames;
    QVector<VideoData*> m_videos;
};


VideoListModel::VideoListModel(QObject *parent)
    : QAbstractListModel{parent},m_dptr{new VideoListModelPrivate}
{}

VideoListModel::~VideoListModel(){
    if(m_dptr != nullptr){
        delete m_dptr;
        m_dptr = nullptr;
    }
}

int VideoListModel::rowCount(const QModelIndex& parent) const{
    return m_dptr->m_videos.size();
}

QVariant VideoListModel::data(const QModelIndex& index,int role) const{
    VideoData* d = m_dptr->m_videos[index.row()];
    return d->at(role-Qt::UserRole);
}

QHash<int,QByteArray> VideoListModel::roleNames() const{
    return m_dptr->m_roleNames;
}

QString VideoListModel::source() const{
    return m_dptr->m_strXmlFile;
}

void VideoListModel::setSource(const QString& filePath) {
    // 替换 "qrc:" 为 ":"（Qt 资源路径的正确格式）
    QString resourcePath = filePath;
    resourcePath.replace("qrc:", ":");  // 例如 "qrc:/source/res/videos.xml" → ":/source/res/videos.xml"

    m_dptr->m_strXmlFile = resourcePath;
    reload();
    if(m_dptr -> m_bError){
        qDebug()<<"VideoListModel,error = "<<m_dptr->m_strError;
    }
}

QString VideoListModel::errorString() const{
    return m_dptr->m_strError;
}

bool VideoListModel::hasError() const{
    return m_dptr->m_bError;
}

void VideoListModel::reload(){
    beginResetModel();
    m_dptr->reset();
    m_dptr->load();
    endResetModel();
}

void VideoListModel::remove(int index){
    beginRemoveRows(QModelIndex(),index,index);
    delete m_dptr->m_videos.takeAt(index);
    endRemoveRows();
}
























