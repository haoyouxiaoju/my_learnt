import QtQuick 2.15
import QtQml.XmlListModel
import QtQuick.Layouts
import an.qt.CModel 1.0

Rectangle{
    width:360;
    height:400;
    color:"#EEEEEE";
    Component{
        id:videoDelegate;
        Item{
            id:wrapper;
            width:parent.width;
            height:120;
            MouseArea{
                anchors.fill:parent;
                onClicked:wrapper.ListView.view.currentIndex = index;
            }
            Image{
                id:poster;
                anchors.left: parent.left;
                anchors.top:parent.top;
                source:img;
                width:80;
                height:120;
                fillMode:Image.PreserveAspectFit;
            }
            ColumnLayout{
                anchors.left: poster.right;
                anchors.leftMargin:4;
                anchors.right: wrapper.right;
                anchors.top:poster.top;
                height:parent.height;
                spacing: 2;
                VideoListViewText{
                    Layout.fillWidth: true;
                    text:"<b>"+name+"</b>("+rating+","+playtimes+")";
                }
                VideoListViewText{
                    text:date;
                    Layout.fillWidth: true;
                }
                VideoListViewText{
                    text:director_tag+":<font color=\"#0000aa\">"+director+"</font>";
                    Layout.fillWidth: true;
                }
                VideoListViewText{
                    text:actor_tag+":<font color=\"#0000aa\">"+actor+"</font>";
                    Layout.fillWidth: true;
                }
                VideoListViewText{
                    text:desc;
                    Layout.fillWidth: true;
                    Layout.fillHeight:true;
                    wrapMode:Text.Wrap;
                    maximumLineCount: 2;
                }

            }
        }
    }

    ListView{
        id:listView;
        anchors.fill: parent;
        spacing:4;
        delegate:videoDelegate;
        model:VideoListModel{source:"qrc:/source/res/videos.xml";}
        focus:true;
        highlight: Rectangle{
            width:parent.width;
            color:"lightblue";
        }
    }
}
