import QtQuick
import QtQuick.Controls

Rectangle{
    id:rootItem;
    width:360;
    height:300;
    color:Qt.rgba(0.1,0.2,0.3,1);
    property int count:0;
    property Component component:null;
    Text{
        id:colorText;
        text:"Hello World!";
        anchors.centerIn:parent;
        font.pixelSize: 24;
    }
    function changeTextColor(clr){
        colorText.color = clr;
    }
    function createColorPicker(clr){
        if(rootItem.component == null){
            rootItem.component = Qt.createComponent("ColorPicker.qml");
        }
        var colorPicker;
        if(rootItem.component.status == Component.Ready){
            var y = 35*Math.floor((rootItem.count/5)) ;
            var x = rootItem.count%5*55
            // console.log(y);
            colorPicker = rootItem.component.createObject(rootItem,{"color":clr,"x":x,"y":y});
            colorPicker.colorPicked.connect(rootItem,changeTextColor);
            if(rootItem.count %2 ==1){
                colorPicker.destroy(1000);
            }
        }
        rootItem.count++;
    }

    Button{
        id:add;
        text:"add";
        anchors.left:parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        onClicked:{
            createColorPicker(Qt.rgba(Math.random(),Math.random(),Math.random(),1))
        }
    }


}
