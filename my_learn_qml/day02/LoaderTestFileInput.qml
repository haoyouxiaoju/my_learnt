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

    Loader{
        id:redLoader;
        width:80;
        height:60;
        focus: true;
        anchors.left:parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        // sourceComponent: colorComponent;
        source:"ColorPicker.qml";
        KeyNavigation.left: blueLoader;
        KeyNavigation.right: blueLoader;
        KeyNavigation.tab: blueLoader;
        onLoaded:{
            item.color = "red";
            item.focus = true;
            // item.loader = redLoader;
        }
        onFocusChanged:(focus)=>{
            // console.log(item.focus);
            // console.log(focus);
            item.focus = focus;
        }
    }

    Loader{
        id:blueLoader;
        anchors.left:redLoader.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        // sourceComponent: colorComponent;
        source:"ColorPicker.qml";
        KeyNavigation.left: redLoader;
        KeyNavigation.right: redLoader;
        KeyNavigation.tab: redLoader;
        onLoaded:{
            item.color = "blue";
            // item.focus = true;
            // item.loader = blueLoader;
        }
        onFocusChanged:(focus)=>{
            // console.log(item.focus);
            // console.log(focus);
            item.focus = focus;
        }
    }

    Connections{
        target:redLoader.item;
        function onColorPicked(clr){
            colorText.color = clr;
            if(!redLoader.focus){
                redLoader.focus = true;
                blueLoader.focus = false;
            }
        }
    }
    Connections{
        target:blueLoader.item;
        function onColorPicked(clr){
            colorText.color = clr;
            if(!blueLoader.focus){
                blueLoader.focus = true;
                redLoader.focus = false;
            }
        }
    }
}
