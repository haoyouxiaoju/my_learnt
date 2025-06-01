import QtQuick 2.15

Rectangle{
    width:360;
    height:240;
    color:"#EEEEEE";
    id:rootItem;
    Rectangle{
        id:rect;
        width:15;
        height:15;
        anchors.centerIn: parent;
        color:"blue";
        ParallelAnimation {
            id:animation;
            PropertyAnimation {
                target: rect
                property: "width"
                to: 15
                duration: 1000
            }
            PropertyAnimation {
                target: rect
                property: "height"
                to: 15
                duration: 1000
            }
            // target: rect;
            // // property:"width,height";
            // to:150;
            // duration:1000;
        }
        MouseArea{
            id:mouseArea;
            anchors.fill: parent;
            onClicked:animation.running = true;

            /*
             *Qt6 不推荐直接在信号处理器里创建对象
             *
             */
            // onClicked:PropertyAnimation{
            //     target: rect;
            //     properties: "width";
            //     to:150;
            //     duration:1000;
            // }
        }
        PropertyAnimation on width{
            to:150;
            duration:1000;
            running:mouseArea.pressed;
        }

    }




}
