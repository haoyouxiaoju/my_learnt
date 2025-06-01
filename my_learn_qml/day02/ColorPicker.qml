import QtQuick

Rectangle{
    id:colorPicker;
    width:50;
    height:30;
    color: "blue";
    signal colorPicked(color clr);
    function configureBorder(){
        colorPicker.border.width = colorPicker.focus ?2:0;
        colorPicker.border.color = colorPicker.focus?"#90D750":"#808080";
    }
    MouseArea{
        anchors.fill:parent;
        onClicked:(mouse)=>{
            colorPicker.colorPicked(colorPicker.color);
            mouse.accepted = true;
            colorPicker.focus = true;
        }
    }
    Keys.onReturnPressed: (event)=>{
        colorPicker.colorPicked(colorPicker.color);
        event.accepted = true;
    }
    Keys.onSpacePressed: (event)=>{
        colorPicker.colorPicked(colorPicker.color);
        event.accepted = true;
    }
    onFocusChanged:{
        configureBorder();
    }
    Component.onCompleted:{
        configureBorder();
    }
}

