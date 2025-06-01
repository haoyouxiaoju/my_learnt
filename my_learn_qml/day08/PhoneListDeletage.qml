import QtQuick 2.15
import QtQuick.Layouts

Rectangle{
    id:control;
    Item{
        id:wrapper;
        width:parent.width;
        height:30;
        MouseArea{
            anchors.fill: parent;
            onClicked:wrapper.ListView.view.currentIndex = index;
        }
        RowLayout{
            anchors.left: parent.left;
            anchors.verticalCenter: parent.verticalCenter;
            spacing:0;
            PhoneListItemText{
                id:coll;
                text :name;
                Layout.preferredWidth: 120;
            }
            PhoneListItemText{
                text :cost;
                Layout.preferredWidth: 80;
            }
            PhoneListItemText{
                text :manufacturer;
                Layout.fillWidth: true;
            }
        }

    }
}
