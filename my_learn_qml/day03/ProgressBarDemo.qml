import QtQuick
import QtQuick.Controls


Rectangle{
    width:480;
    height:20;
    color:"#a0b0a0";
    Row{
        anchors.fill: parent;
        anchors.margins: 10;
        spacing:8;
        ProgressBar{
            from:0;
            to:100;
            value:40;
            width:150;
            height:20;
            Timer{
                interval: 1000;
                repeat: true;
                running: true;
                onTriggered: {
                    if(parent.value < 99.1){
                        parent.value += 1;
                    }else{
                    stop();
                    }
                }
            }

        }

        ProgressBar{
            rotation:90;
            from:0;
            to:1;
            value:0.2;
            width:200;
            height:20;
            Timer{
                interval: 1000;
                repeat:true;
                running: true;
                onTriggered: {
                    parent.value = Math.random();
                }
            }

        }

        ProgressBar{
            from:0;
            to:1;
            value:0.2;
            width:80;
            height:16;
            indeterminate: true;
        }
        Column{
            anchors.margins: 10;
            spacing:8;
            MyProgressBar{
                Timer{
                    interval: 1000;
                    repeat:true;
                    running: true;
                    onTriggered: {
                        parent.value = Math.random();
                    }
                }
            }
            MyProgressBar{
                indeterminate: true;
            }
        }


    }

}
