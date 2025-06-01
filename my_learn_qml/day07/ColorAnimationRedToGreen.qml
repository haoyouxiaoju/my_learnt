import QtQuick

Rectangle{
    width:320;
    height:240;
    color:"#EEEEEE";
    Rectangle{
        id:rect;
        color:"red";
        width:60;
        height:60;
        radius:30;
        anchors.centerIn: parent;
        ColorAnimation{
            id:colorAnimation;
            target:rect;
            property:"color";
            to:"green";
            duration:1500;
        }
        MouseArea{
            id:mouseArea;
            anchors.fill: parent;
            onClicked:colorAnimation.start();
        }
    }
}
