import QtQuick
import QtQuick.Controls.Basic

    ComboBox {
        id: control
        model:["Google","IBM","Digia"];
        anchors.top: parent.top;
        anchors.topMargin: 8;
        width:parent.width;


        delegate: ItemDelegate {
            id: delegate

            required property var model
            required property int index

            width: control.width
            contentItem: Text {
                text: delegate.model[control.textRole]
                color: "#21be2b"
                font: control.font
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
            }
            highlighted: control.highlightedIndex === index
        }

        indicator: Canvas {
            id: canvas
            x: control.width - width - control.rightPadding
            y: control.topPadding + (control.availableHeight - height) / 2
            width: 16
            height: 18
            contextType: "2d"


            Connections {
                target: control
                function onPressedChanged() { canvas.requestPaint(); }
            }

            onPaint: {
                var ctx = getContext("2d");
                ctx.save();
                ctx.strokeStyle = "black";
                ctx.lineWidth =2;
                ctx.beginPath();
                ctx.moveTo(1, 8);
                ctx.lineTo(8, 16);
                ctx.lineTo(15 , 8);
                ctx.stroke();
                ctx.restore();
            }
        }

        contentItem: Text {
            // leftPadding: 20;
            anchors.centerIn: canvas;
            rightPadding: control.indicator.width + control.spacing

            text: control.displayText
            font: control.font
            color: control.pressed ? "#17a81a" : "#21be2b"
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            // implicitWidth: 120
            implicitHeight: 24;
            color: (control.hovered || control.pressed )? "#e0e0e0" : "#c0c0c0";
            border.color: (control.hovered || control.pressed )? "blue" : "gray";
            border.width: control.editable ? 0 : 1;
            radius: 2;
        }

        popup: Popup {
            y: control.height - 1
            width: control.width
            height: Math.min(contentItem.implicitHeight, control.Window.height - topMargin - bottomMargin)
            padding: 1

            contentItem: ListView {
                clip: true
                implicitHeight: contentHeight
                model: control.popup.visible ? control.delegateModel : null
                currentIndex: control.highlightedIndex

                ScrollIndicator.vertical: ScrollIndicator { }
            }

            background: Rectangle {
                border.color: "#21be2b"
                radius: 2
            }
        }
    }



