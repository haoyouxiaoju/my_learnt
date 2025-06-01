import QtQuick 2.15
import xiaoju.demo.model
import QtQuick.Controls
import QtQuick.Layouts

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
