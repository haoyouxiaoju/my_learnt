import QtQuick
import QtQuick.Controls

Item {
    id:keyMoveTextItem;
    anchors.fill:parent;
    // width:320;
    // height:240;
    Rectangle{
        anchors.fill:parent;
        color:"gray";
        focus:true;
        Keys.enabled: true;
        Keys.onEscapePressed: {
            Qt.quit();
        }
        Keys.forwardTo: [moveText,checkLike];
        Text{
            id:moveText;
            text:"MOVE TEXT";
            // anchors.centerIn:parent;
            x:20;
            y:20;
            width:200;
            height:30;
            color:"yellow";
            font{
                bold:true;
                pixelSize:24;
            }
            Keys.enabled: true;
            Keys.onPressed:
                (event)=>{
                    switch(event.key){
                        case Qt.Key_Right:
                        x+=10;
                        break;
                        case Qt.Key_Up:
                        y-=10;
                        break;
                        case Qt.Key_Left:
                        x-=10;
                        break;
                        case Qt.Key_Down:
                        y+=10;
                        break;
                        default:
                        return;
                    }
                    event.accepted = true;
                }
        }
        CheckBox{
            id:checkLike;
            text:"like Qt Quick";
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 10;
            anchors.left: parent.left;
            anchors.leftMargin: 10;
            z:1;
        }
    }
}
