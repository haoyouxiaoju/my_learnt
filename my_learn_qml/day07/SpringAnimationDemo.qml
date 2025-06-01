import QtQuick

Rectangle{
    id:control
    width:320;
    height:240;
    Rectangle{
        id:rect;
        width:40;
        height:40;
        x:20;
        y:20;
        color:"red";
    }
    SpringAnimation{
        id:springX;
        target: rect;
        property:"x";
        spring:3;
        damping:0.06;
        epsilon:0.25;
    }
    SpringAnimation{
        id:springY;
        target: rect;
        property:"y";
        spring:3;
        damping:0.06;
        epsilon:0.25;
    }
    MouseArea{
        anchors.fill: parent;
        onClicked:(mouse)=>{
            springX.from = rect.x;
            springX.to = mouse.x - 5;
            springX.start();
            springY.from = rect.y;
            springY.to = mouse.y - 5;
            springY.start();
       }
    }
}
