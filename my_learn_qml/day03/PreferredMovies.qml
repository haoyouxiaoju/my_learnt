import QtQuick
import QtQuick.Controls

Rectangle {
    width:320;
    height:300;
    color:"#d0d0d0";

    Rectangle{
        id:resultHolder;
        color:"#a0a0a0";
        width:220;
        height:80;
        anchors.centerIn: parent;
        visible:false;
        z:2;
        opacity:0.8;
        border.width:2;
        border.color:"#808080";
        radius:8;
        Text{
            id:result;
            anchors.fill:parent;
            anchors.margins:5;
            font.pointSize: 16;
            color:"blue";
            font.bold:true;
            wrapMode:Text.Wrap;
        }
    }
    GroupBox{
        id:groupBox;
        title: "Please select the best love movies";
        anchors.top: parent.top;
        anchors.topMargin: 8;
        anchors.left: parent.left;
        anchors.leftMargin: 20;
        width:280;
        height:160;
        Column{
            id:movies;
            anchors.top:parent.top;
            anchors.topMargin: 8;
            anchors.left: parent.left;
            anchors.leftMargin: 20;
            spacing:8;
            PreferredMobiesCheckBox{
                text:"廊桥遗梦";
                onClicked:resultHolder.visible = false;
            }
            PreferredMobiesCheckBox{
                text:"人鬼情未了";
                onClicked:resultHolder.visible = false;
            }
            PreferredMobiesCheckBox{
                text:"触不到的恋人";
                onClicked:resultHolder.visible = false;
            }
            PreferredMobiesCheckBox{
                text:"西雅图夜未眠";
                onClicked:resultHolder.visible = false;
            }
        }
    }




    Button{
        id:confirm;
        text:"Confirm";
        anchors.top:groupBox.bottom;
        anchors.topMargin: 8;
        anchors.left: parent.left;
        onClicked:{
            var str = Array();
            var index= 0;
            var count = movies.children.length;
            for(var i =0; i<count;++i){
                if(movies.children[i].checked){
                    str[index++] = movies.children[i].text;
                }
            }
            if(index > 0){
                result.text = str.join();
                resultHolder.visible = true;
            }
        }
    }

}
