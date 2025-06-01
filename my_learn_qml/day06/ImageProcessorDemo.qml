import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import an.qt.ImageProcessor 1.0

Rectangle{

    width:640;
    height:480;
    color:"#121212";

    BusyIndicator{
        id:busy;
        running: false;
        anchors.centerIn:parent;
        z:2;
    }

    Label{
        id:stateLabel;
        visible:false;
        anchors.centerIn:parent;
    }

    Image{
        objectName:"imageViewer";
        id:imageViewer;
        asynchronous: true;
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit;
        onStatusChanged: {
            switch(imageViewer.status){
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
            default:
                break;
            }
        }
    }

    ImageProcessor{
        id:processor;
        onFinished:(newFile)=>{
            imageViewer.source = "file:///"+newFile;
        }
    }

    FileDialog{
        id:fileDialog;
        title:"Please choose a file";
        nameFilters: ["Image Files {*.jpg *.png *.gif}"];
        onAccepted:{
            console.log(fileDialog.selectedFile);
            imageViewer.source = fileDialog.selectedFile;
        }
    }

    ImageProcessorButton{
        id:openFile;
        text:"打开";
        anchors.left: parent.left;
        anchors.leftMargin: 6;
        anchors.top:parent.top;
        anchors.topMargin: 6;
        onClicked:{
            fileDialog.visible = true;
        }
        z:1;
    }
    ImageProcessorButton{
        id:quit;
        text:"关闭";
        anchors.left: openFile.right;
        anchors.leftMargin: 6;
        anchors.top:openFile.top;
        onClicked:{
            Qt.quit();
        }
        z:1;
    }

    Rectangle{
        anchors.left: parent.left;
        anchors.top:parent.top;
        anchors.bottom: openFile.bottom;
        anchors.bottomMargin: -6;
        anchors.right: quit.right;
        anchors.rightMargin: -6;
        color:"#404040";
        opacity:0.7;
    }

    Grid{
        id:op;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        rows:2;
        columns:3;
        rowSpacing: 4;
        columnSpacing: 4;
        z:1;
        ImageProcessorButton{
            text:"柔化";
            onClicked:{
                busy.running = true;
                processor.process(fileDialog.selectedFile,ImageProcessor.Soften);
            }
        }
        ImageProcessorButton{
            text:"灰度"
            onClicked:{
                busy.running = true;
                processor.process(fileDialog.selectedFile,ImageProcessor.Gray);
            }
        }
        ImageProcessorButton{
            text:"浮雕";
            onClicked:{
                busy.running = true;
                processor.process(fileDialog.selectedFile,ImageProcessor.Emboss);
            }
        }
        ImageProcessorButton{
            text:"黑白";
            onClicked:{
                busy.running = true;
                processor.process(fileDialog.selectedFile,ImageProcessor.Binarize);
            }
        }
        ImageProcessorButton{
            text:"底片";
            onClicked:{
                busy.running = true;
                processor.process(fileDialog.selectedFile,ImageProcessor.Negative);
            }
        }
        ImageProcessorButton{
            text:"锐化";
            onClicked:{
                busy.running = true;
                processor.process(fileDialog.selectedFile,ImageProcessor.Sharpen);
            }
        }
    }
    Rectangle{
        anchors.left: parent.left;
        anchors.top:op.top;
        anchors.topMargin: -4;
        anchors.bottom: parent.bottom;
        anchors.right: op.right;
        anchors.rightMargin: -4;
        color:"#404040";
        opacity:0.7;
    }

}
