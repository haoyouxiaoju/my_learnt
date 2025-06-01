import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

Item {
    visible: true;
    width:600;
    height:480;
    BusyIndicator{
        id:busy;
        running: false;
        anchors.centerIn: parent;
        z:2;
    }

    Text{
        id:stateLabel;
        visible:false;
        anchors.centerIn: parent;
        z:3;
    }


    Image {
        id: womanImage;
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit;
        asynchronous: true;
        cache:false;
        onStatusChanged:{
            switch(womanImage.status){
            case Image.Loading:
                busy.running = true;
                stateLabel.visible = false;
                break;
            case Image.Ready:
                busy.running = false;
                break;
            case Image.Error:
                busy.running = false;
                stateLabel.visible = true;
                stateLabel.text = "ERROR";
                break;
            }
        }
    }

    Button{
        id:openFile;
        text:"Open";
        anchors.left: parent.left;
        anchors.leftMargin: 10;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 10;
        onClicked:fileDialog.open();
        z:4;
    }

    Text{
        id:imagePath;
        anchors.left: openFile.right;
        anchors.leftMargin:8;
        anchors.verticalCenter: openFile.verticalCenter;
        font.pixelSize: 18;
    }
    FileDialog{
        id:fileDialog;
        title:"Please choose a file";
        nameFilters:["Image Files{*.jpg *.png *.gif}"];
        onAccepted:{
            womanImage.source = fileDialog.selectedFile;
            var imageFile = String(fileDialog.selectedFile);
            console.log(imageFile);
            imagePath.text = imageFile.slice(8);
        }
    }

    Component.onCompleted: {
        womanImage.source = "https://tse3-mm.cn.bing.net/th/id/OIP-C.HjYIizKCiIsDIj-Dvm-udQAAAA?rs=1&pid=ImgDetMain";
    }
}
