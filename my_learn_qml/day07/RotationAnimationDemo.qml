import QtQuick
import QtQuick.Controls



Rectangle{
    id:cotrol;
    width:320;
    height:240;
    color:"#EEE";
    Rectangle{
        id:rect;
        width:60;
        height:40;
        color:"blue";
        anchors.left: parent.left;
        anchors.leftMargin: 20;
        anchors.verticalCenter: parent.verticalCenter;
        MouseArea{
            id:mouseArea1;
            anchors.fill: parent;
            onClicked:animation1.start();
        }
        RotationAnimation{
            id:animation1;
            target:rect;
            to:90;
            duration:1500;
            direction:RotationAnimation.Counterclockwise;
        }
    }
    Rectangle{
        id:rect2;
        width:60;
        height:40;
        color:"red";
        x:80;
        y:150;
        // anchors.left: rect.right;
        // anchors.leftMargin: 20;
        // anchors.verticalCenter: parent.verticalCenter;
        MouseArea{
            id:mouseArea2;
            anchors.fill: parent;
            onClicked: animation2.start();
        }
        ParallelAnimation{
           id:animation2;
           PropertyAnimation{
               target: rect2;
               property: "y";
               to:0;
               duration:450;
           }
           PropertyAnimation{
               target: rect2;
               property:"x";
               to:0;
               duration:450;
           }

           RotationAnimation{
               target: rect2;
               to:60;
               duration:450;
               direction:RotationAnimation.Counterclockwise;
           }
        }
    }
}
