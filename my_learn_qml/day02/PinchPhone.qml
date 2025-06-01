import QtQuick 2.15

// 电脑上无法进行手机上操作对于触摸事件不做继续,直接步入下一站

Item {
    width:360;
    height:360;
    focus:true;
    Rectangle{
        id:transformRect;
        width:100;
        height:100;
        color:"blue";
        anchors.centerIn:parent;
    }
    PinchArea{
        anchors.fill: parent;
        pinch.maximumScale: 20;
        pinch.minimumScale: 0.2;
        pinch.minimumRotation: 0;
        pinch.maximumRotation: 90;
        pinch.target: transformRect;
        onPinchStarted:{
            pinch.accepted =true;
        }
        onPinchUpdated:{
            transformRect.scale *= pinch.scale;
            transformRect.retation +=pinch.rotation;
        }
        onPinchFinished:{
            transformRect.scale *= pinch.scale;
            transformRect.rotation += pinch.rotation;
        }
    }


}
