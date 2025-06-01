#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class TableModelPhonePrivate;
class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit  TableModel(QObject* parent = nullptr);
    ~TableModel();
    //基础
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    //
private:
    TableModelPhonePrivate* m_phoneModel;
};


#endif // TABLEMODEL_H
