import QtQuick
import QtQuick.Controls.Basic

Button{
    id:control;
    background:Rectangle{
        implicitWidth:70;
        implicitHeight: 30;
        border.width: control.hovered?2:1;
        border.color:control.hovered?"#c0c0c0":"#909090";
        color:control.pressed?"#a0a0a0":"#707070";
    }
    contentItem:Text{
        anchors.fill: parent;
        font.pointSize: 12;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        text:control.text;
        color:(control.hovered && !control.pressed) ? "blue":"white";
    }
}

