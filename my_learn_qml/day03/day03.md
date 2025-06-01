##### 位于P175 的选择你喜欢的手机操作系统

今天学习遇到了之前遇到的一个重复问题`Qt6移除了QtQuick.Controls.Styles模块`,但情况不同,此次是需要自定义样式然后重复给多个RadioButton使用.

在书中例子是使用Component定义了RadioButton的Sytle样式,但由于Styles模块已移除且Component已不再用于自定义组件.

Qt6的话是要对自定义的控件额外写qml文件,如何自定义控件可以直接参考或复制官方文档[自定义 Qt Quick Controls |Qt 快速控制 |Qt 6.9.0 版本](https://doc.qt.io/qt-6/qtquickcontrols-customize.html#creating-a-custom-style)中案例修改,
对于自定义控件**记得添加**`import QtQuick.Controls.Basic`否则会打印出`QML QQuickText: The current style does not support customization of this control (property: "contentItem" item: QQuickText(0x19b78927f50, parent=0x0, geometry=0,0 0x0 ?)). Please customize a non-native style (such as Basic, Fusion, Material, etc). For more information, see: https://doc.qt.io/qt-6/qtquickcontrols2-customize.html#customization-reference`

以下俩代码段是我对书中案例的修改

```
//PreferredMobileOs.qml
//在同级目录下再创建一个PreferredRadioButton.qml用于自定义radio控件
import QtQuick
import QtQuick.Controls
Rectangle{
    width:320;
    height:300;
    color:"#d0d0d0";
    Rectangle{
        id:resultHolder;
        color:"#a0a0a0";
        width:200;
        height:60;
        anchors.centerIn:parent;
        visible:false;
        z:2;
        opacity:0.8;    //不透明度
        border.width: 2;
        border.color:"#808080";
        Text{
            id:result;
            anchors.centerIn:parent;
            font.pointSize: 20;
            color:"blue";
            font.bold:true;
        }
    }
    ButtonGroup{
        id:mos;
    }

    Text{
        id:notation;
        text: "Please select thr best mobile os;";
        anchors.top: parent.top;
        anchors.topMargin: 16;
        anchors.left: parent.left;
        anchors.leftMargin: 8;
    }

    PreferredRadioButton{
        id:android;
        text:"Android";
        ButtonGroup.group:mos;
        anchors.top: notation.bottom;
        anchors.topMargin: 4;
        anchors.left: notation.left;
        anchors.leftMargin: 20;
        checked:true;
        focus:true;
        activeFocusOnTab: true;
        onClicked:resultHolder.visible = false;
    }
    PreferredRadioButton{
        id:ios;
        text:"iOS";
        ButtonGroup.group:mos;
        anchors.top: android.bottom;
        anchors.topMargin: 4;
        anchors.left: notation.left;
        anchors.leftMargin: 20;
        // checked:true;
        // focus:true;
        activeFocusOnTab: true;
        onClicked:resultHolder.visible = false;
    }
    PreferredRadioButton{
        id:wp;
        text:"Windows Phone";
        ButtonGroup.group:mos;
        anchors.top: ios.bottom;
        anchors.topMargin: 4;
        anchors.left: notation.left;
        anchors.leftMargin: 20;
        // checked:true;
        // focus:true;
        activeFocusOnTab: true;
        onClicked:resultHolder.visible = false;
    }
    Button{
        id:confirm;
        text:"Confirm";
        anchors.top:wp.bottom;
        anchors.topMargin: 8;
        anchors.left: notation.left;
        onClicked:{
            // console.log("onclicked");
            result.text = mos.checkedButton.text;
             // console.log(mos.checkedButton.text);
            resultHolder.visible = true;
        }
    }
}
```

```
//PreferredRadioButton.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
RadioButton {
    id: control
    text: qsTr("RadioButton")
    indicator: Rectangle {
        implicitWidth: 16;
        implicitHeight: 12;
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 6
        border.color: control.hovered ? "darkblue" : "gray"

        Rectangle {
            anchors.fill: parent;
            radius: 5;
            color: "#0000A0";
            visible: control.checked;
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        color: control.activeFocus ? "blue" : "black"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
```

参考文档:

[Qt Quick Controls 的更改 |Qt 快速控制 |Qt 6.9.0 版本](https://doc.qt.io/qt-6/qtquickcontrols-changes-qt6.html#styles)

[自定义 Qt Quick Controls |Qt 快速控制 |Qt 6.9.0 版本](https://doc.qt.io/qt-6/qtquickcontrols-customize.html#creating-a-custom-style)


