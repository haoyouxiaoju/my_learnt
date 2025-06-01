import QtQuick 2.15
import an.qt.ColorMaker 1.0
import QtQuick.Controls

Rectangle{
    width:360;
    height:360;
    Text{
        id:timeLabel;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.top:parent.top;
        anchors.topMargin: 4;
        font.pixelSize: 26;
    }
    ColorMaker{
        id:colorMaker;
        color:Qt.green;
    }
    Rectangle{
        id:colorRect;
        anchors.centerIn: parent;
        width:200;
        height:200;
        color:"blue";
    }
    Button{
        id:start;
        text:"start";
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        onClicked:{
            colorMaker.start();
        }
    }
    Button{
        id:stop;
        text:"stop";
        anchors.left: start.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        anchors.bottomMargin: 4;
        onClicked:{
            colorMaker.stop();
        }
    }
    function changeAlgotithm(button,algorithm){
        switch(algorithm){
        case colorMaker.RandomRGB:
            button.text = "RandomRGB";
            break;
        case colorMaker.RandomRed:
            button.text = "RandomRed";
            break;
        case colorMaker.RandomGreen:
            button.text = "RandomGreen";
            break;
        case colorMaker.RandomBlue:
            button.text = "TandomBlue";
            break;
        default:
            break;
        }
    }
    Button{
        id:colorAlgorithm;
        text:"RandomRGB";
        anchors.left:stop.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        onClicked:{
            var algorithm = (colorMaker.algorithm()+1)%5;
            changeAlgotithm(colorAlgorithm,algorithm);
            colorMaker.setAlgorithm(algorithm);
        }
    }
    Button{
        id:quit;
        text:"quit";
        anchors.left: colorAlgorithm.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        onClicked:{
            Qt.quit();
        }
    }

    Component.onCompleted: {
        colorMaker.color = Qt.rgba(0,180,120,255);
        colorMaker.setAlgorithm(ColorMaker.LinearIncrease);
        changeAlgotithm(colorAlgorithm,colorMaker.algorithm());
    }
    Connections{
        target:colorMaker;
        function onCurrentTime(strTime){
            timeLabel.text = strTime;
            timeLabel.color = colorMaker.timeColor;
        }
    }
    Connections{
        target: colorMaker;
        function onColorChanged(color){
            colorRect.color = color;
        }
    }


}
