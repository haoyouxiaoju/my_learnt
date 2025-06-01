import QtQuick
import QtQuick.Controls

Rectangle{
    id:rootItem;
    width:320;
    height:240;
    color:"#C0C0C0";
    property bool colorPickerShow :false;
    Text{
        id:colorText;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        text:"Hellor World";
        font.pixelSize: 32;
    }

    Button{
        id:ctrlButton;
        text:"Show";
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        onClicked:{
            if(rootItem.colorPickerShow){
                redLoader.sourceComponent = undefined;
                blueLoader.source = "";
                rootItem.colorPickerShow = false;
                ctrlButton.text = "Show";
            }else{
                redLoader.source = "ColorPicker.qml";
                redLoader.item.colorPicked.connect(onPickedRed);
                blueLoader.source = "ColorPicker.qml";
                blueLoader.item.colorPicked.connect(onPickedBlue);
                redLoader.focus = true;
                rootItem.colorPickerShow = true;
                ctrlButton.text = "Hide";
            }
        }

    }


    Loader{
        id:redLoader;
        width:80;
        height:60;
        focus: true;
        anchors.left:ctrlButton.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        // sourceComponent: colorComponent;
        // source:"ColorPicker.qml";
        KeyNavigation.left: blueLoader;
        KeyNavigation.right: blueLoader;
        KeyNavigation.tab: blueLoader;
        onLoaded:{
            if(item){
                item.color = "red";
                item.focus = true;
            }
            // item.loader = redLoader;
        }
        onFocusChanged:(focus)=>{
            if(item){
                item.focus = focus;
            }
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
        // sourceComponent: colorComponent;
        // source:"ColorPicker.qml";
        KeyNavigation.left: redLoader;
        KeyNavigation.right: redLoader;
        KeyNavigation.tab: redLoader;
        onLoaded:{
            if(item){
                item.color = "blue";
            }
            // item.focus = true;
            // item.loader = blueLoader;
        }
        onFocusChanged:(focus)=>{
            // console.log(item.focus);
            // console.log(focus);
            if(item){
                item.focus = focus;
            }
        }
    }


        function onPickedRed(clr){
            colorText.color = clr;
            if(!redLoader.focus){
                redLoader.focus = true;
                blueLoader.focus = false;
            }
        }

        function onPickedBlue(clr){
            colorText.color = clr;
            if(!blueLoader.focus){
                blueLoader.focus = true;
                redLoader.focus = false;
            }
        }

}
