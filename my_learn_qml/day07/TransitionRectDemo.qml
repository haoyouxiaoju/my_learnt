import QtQuick

Rectangle{
    id:control;
    width:360;
    height:240;
    color:"#EEEEEE";
    Rectangle{
        id:rect;
        color:"gray";
        width:50;
        height:50;
        anchors.centerIn: parent;
        MouseArea{
            id:mouseArea;
            anchors.fill: parent;
        }
        states:State{
            name:"pressed";
            when:mouseArea.pressed;
            PropertyChanges {
                target: rect;
                color:"green";
                scale:"2.0";
            }
        }
        transitions:Transition{
            NumberAnimation{
                property:"scale";
                easing.type: Easing.InOutQuad;
                duration:1000;
            }
            ColorAnimation{
                duration:600;
            }
        }
    }
}
