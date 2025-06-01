import QtQuick
import QtQuick.Controls

Rectangle{
    width:320;
    height:240;
    color:"#C0C0C0";
    Text{
        id:colorText;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        text:"Hellor World";
        font.pixelSize: 32;
    }

    Component{
        id:colorComponent;
        Rectangle{
            id:colorPicker;
            width:50;
            height:30;
            signal colorPicked(color clr);
            Keys.enabled: true;
            property Item loader;
            border.width:focus?2:0;
            border.color: focus?"#90D750":"#808080";
            MouseArea{
                anchors.fill: parent;
                onPressed: {
                    colorPicker.colorPicked(colorPicker.color);
                    loader.focus = true;
                }
            }
            Keys.onReturnPressed:(event)=> {
                colorPicker.colorPicked(colorPicker.color);
                event.accepted = true;
            }
            Keys.onSpacePressed:(event)=> {
                colorPicker.colorPicked(colorPicker.color);
                event.accepted = true;
            }
        }
    }

    Loader{
        id:redLoader;
        width:80;
        height:60;
        focus: true;
        anchors.left:parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        sourceComponent: colorComponent;
        KeyNavigation.left: blueLoader;
        KeyNavigation.right: blueLoader;
        KeyNavigation.tab: blueLoader;
        onLoaded:{
            item.color = "red";
            item.focus = true;
            item.loader = redLoader;
        }
        onFocusChanged:(focus)=>{
            item.focus = focus;
            // console.log(item.focus);
            // console.log(focus);
        }
    }

    Loader{
        id:blueLoader;
        anchors.left:redLoader.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        sourceComponent: colorComponent;
        KeyNavigation.left: redLoader;
        KeyNavigation.right: redLoader;
        KeyNavigation.tab: redLoader;
        onLoaded:{
            item.color = "blue";
            // item.focus = true;
            item.loader = blueLoader;
        }
        onFocusChanged:(focus)=>{
            item.focus = focus;
            // console.log(item.focus);
            // console.log(focus);
        }
    }

    Connections{
        target:redLoader.item;
        function onColorPicked(clr){
            colorText.color = clr;
        }
    }
    Connections{
        target:blueLoader.item;
        function onColorPicked(clr){
            colorText.color = clr;
        }
    }
}
