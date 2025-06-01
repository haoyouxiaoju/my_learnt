import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
RadioButton {
    id: control
    text: qsTr("RadioButton")
    indicator: Rectangle {
        implicitWidth: 16;
        implicitHeight: 12;
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 6
        border.color: control.hovered ? "darkblue" : "gray"

        Rectangle {
            anchors.fill: parent;
            radius: 5;
            color: "#0000A0";
            visible: control.checked;
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        color: control.activeFocus ? "blue" : "black"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}



