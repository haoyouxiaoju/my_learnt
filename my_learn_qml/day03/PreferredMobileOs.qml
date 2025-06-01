import QtQuick
import QtQuick.Controls

Rectangle{
    width:320;
    height:300;
    color:"#d0d0d0";
    Rectangle{
        id:resultHolder;
        color:"#a0a0a0";
        width:200;
        height:60;
        anchors.centerIn:parent;
        visible:false;
        z:2;
        opacity:0.8;    //不透明度
        border.width: 2;
        border.color:"#808080";
        Text{
            id:result;
            anchors.centerIn:parent;
            font.pointSize: 20;
            color:"blue";
            font.bold:true;
        }
    }
    ButtonGroup{
        id:mos;
    }

    Text{
        id:notation;
        text: "Please select thr best mobile os;";
        anchors.top: parent.top;
        anchors.topMargin: 16;
        anchors.left: parent.left;
        anchors.leftMargin: 8;
    }

    PreferredRadioButton{
        id:android;
        text:"Android";
        ButtonGroup.group:mos;
        anchors.top: notation.bottom;
        anchors.topMargin: 4;
        anchors.left: notation.left;
        anchors.leftMargin: 20;
        checked:true;
        focus:true;
        activeFocusOnTab: true;
        onClicked:resultHolder.visible = false;
    }
    PreferredRadioButton{
        id:ios;
        text:"iOS";
        ButtonGroup.group:mos;
        anchors.top: android.bottom;
        anchors.topMargin: 4;
        anchors.left: notation.left;
        anchors.leftMargin: 20;
        // checked:true;
        // focus:true;
        activeFocusOnTab: true;
        onClicked:resultHolder.visible = false;
    }
    PreferredRadioButton{
        id:wp;
        text:"Windows Phone";
        ButtonGroup.group:mos;
        anchors.top: ios.bottom;
        anchors.topMargin: 4;
        anchors.left: notation.left;
        anchors.leftMargin: 20;
        // checked:true;
        // focus:true;
        activeFocusOnTab: true;
        onClicked:resultHolder.visible = false;
    }
    Button{
        id:confirm;
        text:"Confirm";
        anchors.top:wp.bottom;
        anchors.topMargin: 8;
        anchors.left: notation.left;
        onClicked:{
            // console.log("onclicked");
            result.text = mos.checkedButton.text;//Qt6中将当前选择的RadioButton为checkedButton属性
             // console.log(mos.checkedButton.text);
            resultHolder.visible = true;
        }
    }
}
