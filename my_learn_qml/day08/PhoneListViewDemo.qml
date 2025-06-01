import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts


Rectangle{
    width:360;
    height: 300;
    color:"#EEEEEE";
    Component{
        id:phoneDelegate;
        Item{
            id:wrapper;
            width:parent.width;
            height:30;
            MouseArea{
                anchors.fill: parent;
                onClicked:wrapper.ListView.view.currentIndex = index;
                onDoubleClicked: wrapper.ListView.view.model.remove(index);
            }
            RowLayout{
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;
                spacing:0;
                PhoneListItemText{
                    text :name;
                    Layout.preferredWidth: 120;
                }
                PhoneListItemText{
                    text :cost;
                    Layout.preferredWidth: 80;
                }
                PhoneListItemText{
                    text :manufacturer;
                    Layout.fillWidth: true;
                }
            }

        }
    }
    ListView{
        id:listView;
        anchors.fill: parent;
        delegate: phoneDelegate;
        header:Component{
            id:headerView;
            Item{
                width:parent.width;
                height:30;
                RowLayout{
                    anchors.left: parent.left;
                    anchors.verticalCenter: parent.verticalCenter;
                    spacing:8;
                Text{
                    text :"name";
                    font.bold: true;
                    Layout.preferredWidth: 120;
                }
                Text{
                    text :"cost";
                    font.bold: true;
                    Layout.preferredWidth: 80;
                }
                Text{
                    text :"manufacturer";
                    font.bold: true;
                    Layout.fillWidth: true;
                }
                }
            }
        }

        model:ListModel{
            id:phoneModel;
            ListElement{
                name:"IPhone";
                cost:"1000";
                manufacturer:"Apple";
            }
            ListElement{
                name:"IPhone";
                cost:"1001";
                manufacturer:"Apple";
            }
            ListElement{
                name:"IPhone";
                cost:"1002";
                manufacturer:"Apple";
            }
            ListElement{
                name:"IPhone";
                cost:"1003";
                manufacturer:"Apple";
            }
        }
        footer:Component{
            id:footerView;
            Item{
                id:footerViewItem;
                width: parent.width;
                height:30;
                property alias text: txt.text;
                signal clean();
                 Text{
                     id:txt;
                     anchors.left: parent.left;
                     anchors.top: parent.top;
                     anchors.bottom: parent.bottom;
                width: parent.width;
                font.italic: true;
                color:"blue";
                height:30;
                verticalAlignment: Text.AlignVCenter;
            }
                Button{
                    id:clear;
                    anchors.right: append.left;
                    anchors.verticalCenter: parent.verticalCenter;
                    text:"Clear";
                    onClicked:footerViewItem.clean();
                }
                Button{
                    id:append;
                    anchors.right: parent.right;
                    anchors.verticalCenter: parent.verticalCenter;
                    text:"append";
                    onClicked:{
                        listView.model.append({
                          "name":"Mx3",
                          "cost":"1799",
                          "manufacturer":"MeiZu"

                        })
                    }
                }
            }


        }

        focus:true;
        add:Transition{
            ParallelAnimation{
                NumberAnimation{
                    property:"opacity";
                    from:0;
                    to:1.0;
                    duration:1000;
                }
                NumberAnimation{
                    property:"y";
                    from:0;
                    duration:1000;
                }
            }
        }
        displaced:Transition{
            SpringAnimation{
                property:"y";
                spring:3;
                damping:0.1;
                epsilon:0.25;
            }
        }
        remove:Transition{
            SequentialAnimation{
                NumberAnimation{
                    property:"y";
                    to:0;
                    duration:600;
                }
                NumberAnimation{
                    property:"opacity";
                    to:0;
                    duration:400;
                }
            }
        }

        highlight: Rectangle{
            color:"lightblue";
        }
        onCurrentIndexChanged: {
            if(listView.currentIndex >= 0){
                var data = listView.model.get(listView.currentIndex);
                listView.footerItem.text = data.name +","+data.cost+","+data.manufacturer;
            }else{
                listView.footerItem.text = "";
            }
        }
        Component.onCompleted: {
            listView.footerItem.clean.connect(listView.model.clear);
        }
    }
}

