# TableView

qt6对TableView改动比较大,书中的例子很难改

如果想使用书中的例子可以参考[TableModel QML Type | Qt 6.9](https://doc.qt.io/qt-6/qml-qt-labs-qmlmodels-tablemodel.html)

我这里就写一个基础的TableModel,参考书中的videolistmodel.h写的

主要多出这一步判断DisplayRole,因为在tableView中Delegate自定义的是每一个表格,所以直接model.属性,会让一行表格都是一个数据,参考了官方文档使用model.display所以需要对data进行修改

```
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    // 如果是 DisplayRole，返回当前列对应的数据
    if (role == Qt::DisplayRole) {
        return m_phoneModel->m_phone[index.row()]->at(index.column()); 
    }
    return m_phoneModel->m_phone[index.row()]->at(role-Qt::UserRole);
}
```

特别表头这里`text: ["name", "cost", "manu"][column]  // 列标题文本`推荐还是让model来设置,需要给TableModel里面提供一个接口返回值

```
// 1. 水平表头（列标题）
		HorizontalHeaderView {
			id: horizontalHeader
			syncView: tableView
			Layout.fillWidth: true
			height: 30  // 表头高度

			delegate: Rectangle {
				color: "#3A3A3A"  // 表头背景色
				implicitWidth:  tableView.columnWidthProvider(column)
				implicitHeight: tableView.rowHeightProvider(row);

				Text {
					anchors.centerIn: parent
					text: ["name", "cost", "manu"][column]  // 列标题文本
					color: "white"
					font.bold: true
				}
			}
		}
```



```
tabmodel.h
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
```

```
tableModel.cpp
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
```

```
Rectangle{
	id:control;
	width:400;
	height: 400;
	ColumnLayout {
		id:columnLayout;
		anchors.fill: parent
		spacing: 0
		// 1. 水平表头（列标题）
		HorizontalHeaderView {
			id: horizontalHeader
			syncView: tableView
			Layout.fillWidth: true
			height: 30  // 表头高度

			delegate: Rectangle {
				color: "#3A3A3A"  // 表头背景色
				implicitWidth:  tableView.columnWidthProvider(column)
				implicitHeight: tableView.rowHeightProvider(row);

				Text {
					anchors.centerIn: parent
					text: ["name", "cost", "manu"][column]  // 列标题文本
					color: "white"
					font.bold: true
				}
			}
		}


		TableView{
			id:tableView;
			// anchors.fill: parent
			Layout.fillWidth: true
			Layout.fillHeight: true  // 使用Layout替代anchors.fill
			model: TableModel{}
			property int selectCurrentRow: -1
			delegate:Rectangle{
				implicitWidth:  tableView.columnWidthProvider(column)
				implicitHeight: tableView.rowHeightProvider(row);
				color: tableView.selectCurrentRow === row ? "lightblue" :(row % 2 === 0 ? "white" : "#f5f5f5")
				// border.width: 1;
				Text{
					text:model.display
					anchors.centerIn: parent // 居中

				}
				// 点击效果
				MouseArea {
					anchors.fill: parent
					onClicked: {
						// tableView.currentRow = row //tableView 没办法更新
						tableView.selectCurrentRow = row // 手动更新选中行
						console.log("Clicked row:", row, "column:", column)
						console.log("tableView.currentRow:", tableView.currentRow)

					}
				}
			}
			focus:true;
			function columnWidthProvider(column) { return [150, 100, 200][column]  // 分别为三列设置不同宽度
			}
			function rowHeightProvider(row) {
				return 40  // 固定行高
			}

		}

	}
}

```

