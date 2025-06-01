import QtQuick
import QtQuick.Controls.Basic

CheckBox {
    id: control
    text: qsTr("CheckBox")
    checked: true

    indicator: Rectangle {
        implicitWidth: 14
        implicitHeight: 14
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 3
        border.color: control.hovered ? "darkblue" : "gray";
        border.width: 1;
        Canvas{
            anchors.fill: parent;
            anchors.margins: 3;
            visible:control.checked;
            onPaint: {
                var ctx = getContext("2d");
                ctx.save();
                ctx.strokeStyle = "#c00020";
                ctx.lineWidth=2;
                ctx.beginPath();
                ctx.moveTo(0,0);
                ctx.lineTo(width,height);
                ctx.moveTo(0,height);
                ctx.lineTo(width,0);
                ctx.stroke();
                ctx.restore();
            }
        }

    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.down ? "bluea" : "black"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
