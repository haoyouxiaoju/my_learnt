#include "tablemodel.h"

using PhoneData = QVector<QString>;
class TableModelPhonePrivate{
public:
    TableModelPhonePrivate():m_bError(false){
        int role = Qt::UserRole;
        m_roleNames[Qt::DisplayRole] = "display";
        m_roleNames.insert(role++,"name");
        m_roleNames.insert(role++,"cost");
        m_roleNames.insert(role++,"manufacturer");

        PhoneData* item;
        for(int i=0;i<5;i++){
            item = new PhoneData;
            item->push_back("iphone"+QString::number(i));
            item->push_back(QString::number(i*1000));
            item->push_back("IPHONE"+QString::number(i));
            m_phone.push_back(item);
        }

    }
    ~TableModelPhonePrivate(){clear();}

    void reset(){
        m_bError = false;
        m_strError.clear();
        clear();
    }
    void clear(){
        int count = m_phone.size();
        if(count > 0){
            for(int i=0;i<count;i++){
                delete m_phone.at(i);
            }
            m_phone.clear();
        }
    }

    QString m_strXmlFile;
    QString m_strError;
    bool m_bError;
    QHash<int,QByteArray> m_roleNames;
    QVector<PhoneData*> m_phone;
};


TableModel::TableModel(QObject *parent)
    :QAbstractTableModel(parent),m_phoneModel(new TableModelPhonePrivate)
{
}

TableModel::~TableModel()
{
    if(m_phoneModel){
        delete m_phoneModel;
        m_phoneModel = nullptr;
    }
}

int TableModel::rowCount(const QModelIndex &) const
{
    return m_phoneModel->m_phone.size();
}

int TableModel::columnCount(const QModelIndex &) const
{
    if( m_phoneModel->m_phone.isEmpty())   return 0;
    return  m_phoneModel->m_phone.at(0)->size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    // 如果是 DisplayRole，返回当前列对应的数据
    if (role == Qt::DisplayRole) {
        return m_phoneModel->m_phone[index.row()]->at(index.column());
    }
    return m_phoneModel->m_phone[index.row()]->at(role-Qt::UserRole);
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return m_phoneModel->m_roleNames;
}
