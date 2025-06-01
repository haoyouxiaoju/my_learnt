import QtQuick 2.15
import QtQuick.Controls

Rectangle{
    width:320;
    height: 400;
    color:"blue";
    Component{
        id:tabItem;
        Rectangle{
            width:100;
            height:100;
            anchors.fill: parent;
            color: rgba(Math.random(),Math.random(),Math.random(),1);
        }
    }

    Button{
        id:addButton;
        text:"add";
        width:60;
        height:35;
        anchors.top: parent.top;
        anchors.topMargin: 5;
        anchors.left: parent.left;
        anchors.leftMargin: 5;
        onClicked:{

        }
    }





}
