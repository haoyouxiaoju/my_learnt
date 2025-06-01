import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtLocation 6.8

Rectangle{
    id:control
    width:500;
    height:500;

    TabBar {
        id: bar
        width: control.width
        TabButton {
            text: qsTr("Home")
            Image{
                visible: true
                width:40;
                height:40;
                source:"qrc:/source/icons/avatar7.jpg";
            }

        }
        TabButton {
            text: qsTr("Discover")
        }
        TabButton {
            text: qsTr("Activity")
        }
    }

    StackLayout {
        id:stackLayout;
        anchors.top: bar.bottom;
        anchors.topMargin: 5;
        // anchors.fill: parent;
        currentIndex: bar.currentIndex
        Item {
            id: homeTab
            Rectangle{
                width: control.width;
                height: control.height;
                color:Qt.rgba(0.1,0.2,0.3,1);

            }
        }
        Item {
            id: discoverTab
            Rectangle{
                width: control.width;
                height: control.height;
                color:Qt.rgba(0.2,0.3,0.3,1);
            }
        }
        Item {
            id: activityTab
            Rectangle{
                width: control.width;
                height: control.height;
                color:Qt.rgba(0.5,0.2,0.6,1);
            }
        }

    }


}




