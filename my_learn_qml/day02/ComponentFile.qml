import QtQuick
import QtQuick.Controls

Item {
Rectangle{
    width:320;
    height:240;
    color:"#EEEEEE";
    Text{
        id:coloredText;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top:parent.top;
        anchors.topMargin: 4;
        text:"Hello Qt Quick Component";
        font.pixelSize: 32;
    }
    function setTextColor(clr){
        coloredText.color = clr;
    }
    ColorPicker{
        id:redColor;
        color:"red";
        focus:true;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        KeyNavigation.left: pinkColor;
        KeyNavigation.right: blueColor;
        KeyNavigation.tab:blueColor;
        onColorPicked:(clr)=> {
            coloredText.color = clr;
        }
    }

    ColorPicker{
        id:blueColor;
        color:"blue";
        // focus:true;
        anchors.left: redColor.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        KeyNavigation.left: redColor;
        KeyNavigation.right: pinkColor;
        KeyNavigation.tab:pinkColor;
        // onColorPicked: {
        //     coloredText.color = clr;
        // }
    }

    ColorPicker{
        id:pinkColor;
        color:"pink";
        focus:true;
        anchors.left: blueColor.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        KeyNavigation.left: blueColor;
        KeyNavigation.right: redColor;
        KeyNavigation.tab:redColor;
        // onColorPicked: {
        //     coloredText.color = clr;
        // }
    }

    Component.onCompleted: {
        blueColor.colorPicked.connect(setTextColor);
        pinkColor.colorPicked.connect(setTextColor);
    }
}
}

