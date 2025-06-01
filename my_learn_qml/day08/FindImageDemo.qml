import QtQuick 2.15
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Dialogs


Window{
    id:control;
    visible:true;
    height: 480;
    width:800;
    minimumHeight: 480;
    minimumWidth: 800;
    objectName:"qmlWin";
    color:"black";
    title:qsTr("ImageViewer");
    property var localComp;
    property var localView;
    property var netComp;
    property var netView;

    function backKeyProcess(){
        if(control.localView !== undefined){
            control.localView.destroy();
            control.localView = undefined;
        }else if(control.netView !== undefined){
            control.netView.destroy();
            control.netView = undefined;
        }else{
            Qt.quit();
        }
    }
    Column{
        id:actionPanel;
        anchors.centerIn: parent;
        spacing:4;
        FlatButton{
           id:find;
           iconSource: "qrc:/source/icons/avatar7.jpg";
           text:qsTr("Search Internet");
           font.pointSize: 14;
           onClicked:{
              if(control.netComp === undefined){
                  control.netComp = Qt.createComponent("ImageDigger.qml");
              }
              if(control.netView === undefined){
                  control.netView = control.netComp.createObject(control,{"focus":"true"})
                  control.netView.back.connect(control.onNetViewBack);
              }
           }
        }
        FlatButton{
           id:local;
           iconSource: "qrc:/source/icons/avatar.png";
           text:qsTr("Local Image");
           font.pointSize: 14;
           onClicked:{
              if(control.localComp === undefined){
                  control.localComp = Qt.createComponent("LocalViewer.qml");
              }
              if(control.localView === undefined){
                  control.localView = control.localComp.createObject(control,{"focus":"true"})
                  control.localView.back.connect(control.onLocalViewBack);
              }
           }
        }
    }
    function onLocalViewBack(){
        localView.destroy();
        localView=undefined;
    }
    function onNetViewBack(){
        netView.destroy();
        netView=undefined;
    }

}
