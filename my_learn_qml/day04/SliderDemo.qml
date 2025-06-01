import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Controls.Basic

Rectangle{
    width:320;
    height:240;
    color:"lightgray";
    Row{
        anchors.fill:parent;
        spacing:20;
        Column{
            width:200;
            spacing:16;
            Text{
                id:sliderStat;
                color:"blue";
                text:"current-0.1";
            }
            Slider{
                id:slider1;
                width:200;
                height:30;
                stepSize:0.01;
                from:0;
                to:100;
                value:0.1;
                onValueChanged: {
                    sliderStat.text = " current -"+slider1.value;
                }
            }
            Text{
                id:sliderStat2;
                color:"blue";
                text:"current-0.1";
            }
            Slider{
                id:slider2;
                width:200;
                height:30;
                from:0;
                to:100;
                stepSize:20;
                value:1;
                snapMode: Slider.NoSnap;
                onValueChanged: {
                    sliderStat2.text = " current -"+slider2.value;
                }
            }
            Text{
                id:sliderStat3;
                color:"blue";
                text:"current-0.1";
            }
            Slider{
                id:slider3;
                width:200;
                height:30;
                from:0;
                to:100;
                stepSize:20;
                value:1;
                snapMode: Slider.SnapAlways;
                onValueChanged: {
                    sliderStat3.text = " current -"+slider3.value;
                }
            }
            Text{
                id:sliderStat4;
                color:"blue";
                text:"current-0.1";
            }
            Slider{
                id:slider4;
                width:200;
                height:30;
                from:0;
                to:100;
                stepSize:20;
                value:1;
                snapMode: Slider.SnapOnRelease;
                onValueChanged: {
                    sliderStat4.text = " current -"+slider4.value;
                }
            }
            Slider{
                id:customGrooveAndHandle;
                width:200;
                height:30;
                from:0;
                to:100;
                stepSize:0.1;
                value:0;
                //背景
                background: Rectangle{
                    implicitHeight: 8;
                    implicitWidth: 100;
                    color:"gray";
                    radius: 8;
                    //进度
                    Rectangle {
                               width: customGrooveAndHandle.visualPosition * parent.width
                               height: parent.height
                               color: "#21be2b"
                               radius: 2
                    }
                }
                //滑块
                handle:Rectangle{
                    // anchors.centerIn: parent;
                    anchors.top: parent.top;
                    anchors.topMargin: -2;
                    color:customGrooveAndHandle.pressed?"white":"lightgray";
                    border.color: "gray";
                    border.width: 2;
                    x :customGrooveAndHandle.visualPosition * parent.width - width/2;
                    width:34;
                    height:34;
                    radius:12;
                    Text{
                        text:  Math.floor(customGrooveAndHandle.value)+'%';
                        color:"blue";
                        anchors.centerIn: parent;
                    }
                }

            }
            Slider{
                id:slider7;
                width:30;
                height:200;
                from:0;
                to:100;
                stepSize:20;
                value:1;
                snapMode: Slider.SnapOnRelease;
                orientation:Qt.Vertical;
            }
        }
    }


}
