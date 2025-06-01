import QtQuick
import QtQuick.Controls


Rectangle{
    width:480;
    height:360;
    color:"#a0b0a0";
    Grid{
        anchors.fill:parent;
        rows:2;
        columns:2;
        rowSpacing: 4;
        columnSpacing: 4;
        GroupBox{
            width: 200;
            height:120;
            title:"只读电器";
            ComboBox{
                anchors.top:parent.top;
                anchors.topMargin: 8;
                width:parent.width;
                model:["TV","CD Player","Set Top Box","Router"];
            }
        }

        GroupBox{
            width: 200;
            height:120;
            title:"可编辑水果";
            ComboBox{
                anchors.top:parent.top;
                anchors.topMargin: 8;
                width:parent.width;
                editable:true;
                model:ListModel{
                    ListElement{text:"Banana";color:"yelow"}
                }
                onAccepted:{
                    // console.log(currentText);
                    if(count<4 && find(currentText) === -1){
                        model.append({text:editText});
                        currentIndex = find(currentText);
                        if(count === 4){
                            editable = false;
                        }
                    }
                }
            }
        }

        GroupBox{
            width:200;
            height:120;
            title:"定制风格";
            MyCombobox{}
        }

        GroupBox{
            width:200;
            height:236;
            title:"月份输入";
            ComboBox{
                anchors.top:parent.top;
                anchors.topMargin: 8;
                width:parent.width;
                editable:true;
                model:ListModel{
                    // ListElement{text:"Banana";color:"yelow"}
                }
                validator:IntValidator{top:12;bottom:1;}
                onAccepted:{

                    if(count<12 && find(currentText) === -1){
                        model.append({text:editText});
                        currentIndex = find(currentText);
                        if(count === 12){
                            editable = false;
                        }
                    }
                }
            }
        }


    }


}
