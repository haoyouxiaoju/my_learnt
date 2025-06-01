import QtQuick 2.15
import QtQuick.Controls.Basic

Button {
    id: control
    text: qsTr("Button")
    property alias iconSource:icon.source;
    property alias iconWidth:icon.width;
    property alias iconHeight:icon.height;
    contentItem: Text {
        id:text;
        text: control.text
        font: control.font
        anchors.left:control.left ;
        anchors.leftMargin: iconWidth+4;
        // anchors.top: control.top;
        anchors.verticalCenter: backgroundControl.verticalCenter;
        // horizontalAlignment: Text.AlignHCenter
        // anchors.margins: 4;
        color:control.pressed?"blue":(parent.hovered?"#0000a0":"white")
    }

    background: Rectangle {
        id:backgroundControl;
        implicitWidth: 120;
        implicitHeight: 50;
        color:"transparent";
        opacity: enabled ? 1 : 0.3;
        border.color:"#949494";
        border.width: control.hovered?2:0
        radius: 6
        Image {
            id: icon
            width:16;
            height:16;
            anchors.left: parent.left;
            anchors.verticalCenter: parent.verticalCenter;
        }
    }
}
