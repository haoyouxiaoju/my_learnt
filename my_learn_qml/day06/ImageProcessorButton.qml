import QtQuick
import QtQuick.Controls.Basic

Button {
    id: control
    text: qsTr("Button")

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.down ? "#17a81a" : "#21be2b"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 70
        implicitHeight: 25
        border.width: control.pressed?2:1;
        border.color: (control.pressed || control.hovered)?"#00A060":"#888888";
        radius:6;
        gradient: Gradient{
            GradientStop{
                position:0;
                color:control.pressed?"#cccccc":"#e0e0e0";
            }
            GradientStop{
                position:1;
                color:control.pressed?"#aaaaaa":"#cccccc";
            }
        }
    }
}

