import QtQuick 2.15
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtMultimedia
import QtQuick.Controls.impl
// import Qt.labs.folderlistmodel

ApplicationWindow{
    visible:true;
    width:480;
    height:360;
    color:"black";
    title:"文件查看器"
    id:root
    property var aboutDlg : null;
    property var colorDlg : null;
    property color textColor : "green"
    property color textBackgroundColor:"black"
    menuBar:MenuBar{
        Menu{
            title:"文件";
            MenuItem{
                icon.source:"qrc:/source/res/txtFile.png";
                action:Action{
                    id:textAction;
                    icon.source: "qrc:/source/res/txtFile.png"
                    text:"文本文件"
                    onTriggered: {
                        fileDialog.selectedNameFilter.index =0// = fileDialog.nameFilters[0];
                        fileDialog.open();
                    }
                }
            }
            MenuItem{
                action:Action{
                    id:imageAction;
                    text:"图片"
                    icon.source:"qrc:/source/res/imageFile.png";
                    onTriggered: {
                        fileDialog.selectedNameFilter.index =1//  = fileDialog.nameFilters[1];
                        fileDialog.open();
                    }
                }
            }
            MenuItem{
                action:Action{
                    id:videoAction;
                    text:"视频"
                    icon.source:"qrc:/source/res/videoFile.png";
                    onTriggered: {
                        fileDialog.selectedNameFilter.index =2//  = fileDialog.nameFilters[2];
                        fileDialog.open();
                    }
                }
            }
            MenuItem{
                action:Action{
                    id:audioAction;
                    text:"音乐"
                    icon.source:"qrc:/source/res/audioFile.png";
                    onTriggered: {
                        fileDialog.selectedNameFilter.index =3//  = fileDialog.nameFilters[3];
                        fileDialog.open();
                    }
                }
            }
            MenuItem{
                text:"退出";
                onTriggered: Qt.quit();
            }
        }
        Menu{
            title:"设置";
            MenuItem{
                action:Action{
                    id:textColorAction;
                    icon.source: "qrc:/source/res/ic_textcolor.png";
                    text:"文字颜色";
                    onTriggered: root.selectColor(root.onTextColorSelectd);
                }
            }
            MenuItem{
                action:Action{
                    id:backgroundColorAction;
                    icon.source: "qrc:/source/res/ic_bkgndcolor.png";
                    text:"文字背景颜色";
                    onTriggered: root.selectColor(root.onTextBackgroundColorSelected);
                }
            }
            MenuItem{
                action:Action{
                    id:fontSizeAddAction;
                    icon.source: "qrc:/source/res/ic_fontsize2.png";
                    text:"增大字体";
                    onTriggered: textView.font.pointSize +=1;
                }
            }
            MenuItem{
                action:Action{
                    id:fontSizeMinusAction;
                    icon.source: "qrc:/source/res/ic_fontsize1.png";
                    text:"减小字体";
                    onTriggered: textView.font.pointSize -=1;
                }
            }
        }
        Menu{
            title:"帮助";
            MenuItem{
                text:"关于";
                onTriggered: root.showAbout();
            }
            MenuItem{
                text:"访问作者博客"
                onTriggered: Qt.openUrlExternally("http://blog.csdn.net/foruok");
            }
        }
    }
    ToolBar{
        RowLayout{
            id:toolBarLayout;
            ToolButton{
                action:textAction;
            }
            ToolButton{
                action:imageAction;
            }
            ToolButton{
                action:videoAction;
            }
            ToolButton{
                action:audioAction;
            }
        }
    }
    footer:Rectangle{
        id:rootFooter;
        color:"lightgray";
        implicitHeight: 30;
        width:parent.width;
        property alias text: status.text;
        Text{
            id:status;
            anchors.fill: parent;
            anchors.margins: 4;
            font.pointSize: 12;
        }
    }

    Item{
        id:centralView;
        anchors.fill: parent;
        visible:true;
        property var current:null;
        BusyIndicator{
            id:busy;
            anchors.centerIn: parent;
            running: false;
            z:3;
        }
        Image{
            id:imageViewer;
            anchors.fill: parent;
            visible:false;
            asynchronous: true;
            fillMode:Image.PreserveAspectFit;
            onStatusChanged:(status)=> {
                        switch(status)
                        {
                            case Image.Loading:
                            busy.running = true;
                            break;
                            case Image.Ready:
                            busy.running = false;
                            break;
                            case Image.Error:
                            busy.running = false;
                            rootFooter.text = "图片无法显示";
                            break;

                        }
                    }
        }
        TextArea{
            id:textView;
            anchors.fill: parent;
            readOnly: true;
            visible:false;
            wrapMode: TextEdit.WordWrap;
            font.pointSize: 12;
            color:root.textColor;
            selectionColor:"steelblue";
            selectedTextColor:"#a00000";
            // background: Rectangle{
            // color:root.textBackgroundColor;
            // }
            property var xmlhttp: null;
            function onReadOnlyChanged(){
                if(xmlhttp.readyState === 4){
                    text = xmlhttp.responseText;
                    xmlhttp.abort();
                }
            }
            function loadText(fileUrl){
                if(xmlhttp == null){
                    xmlhttp = new XMLHttpRequest();
                    xmlhttp.onreadystatechange = onReadOnlyChanged;
                }
                if(xmlhttp.readyState === 0){
                    xmlhttp.open("GET",fileUrl);
                    xmlhttp.send(null);
                }
            }
        }
        Rectangle{
            anchors.fill: parent;
            visible:false;
            MediaPlayer{
                id:player;
                property var utilDate: Date()
                // property var Duration;
                videoOutput: videoOutput;
                function msecs2String(msecs){
                    utilDate.setTime(msecs);
                    return Qt.formatTime(utilDate,"mm:ss");
                }
                onPositionChanged: (position)=>{
                               progress.text = msecs2String(position)+sDuration;
                           }
                onDurationChanged: (duration)=>{
                               sDuration = "/"+msecs2String(duration);
                           }
                onPlaybackStateChanged: (playbackState)=>{
                                switch(playbackState){
                                    case MediaPlayer.PlayingState:
                                    state.text ="播放中";
                                    break;
                                    case MediaPlayer.PausedState:
                                    state.text ="已暂停";
                                    break;
                                    case MediaPlayer.StoppedState:
                                    state.text="停止";
                                    break;
                                }

                            }

                onMediaStatusChanged: (status)=>{
                              switch(status){
                                  case MediaPlayer.LoadingMedia:
                                  case MediaPlayer.BufferingMedia:
                                  busy.running = true;
                                  break;
                                  case MediaPlayer.InvalidMedia:
                                  rootFooter.text = "无法播放";
                                  busy.running = false;
                                  break;
                                  case MediaPlayer.BufferedMedia:
                                  case MediaPlayer.LoadedMedia:
                                  busy.running = false;
                                  break;
                              }
                          }
            }
            VideoOutput{
                id:videoOutput;
                anchors.fill: parent;
                // onVisibleChanged: {
                //     playerState.visible = visible;
                //     if(visible === false){
                //         player.stop();
                //     }
                // }
                MouseArea{
                    anchors.fill: parent;
                    onClicked: {
                        switch(player.playbackState){
                        case MediaPlayer.PauseState:
                        case MediaPlayer.StoppedState:
                            player.play();
                            break;
                        case MediaPlayer.PlayingState:
                            player.pause();
                            break;
                        }
                    }
                }
            }
        }
        Rectangle{
            id:playerState;
            color:"gray";
            radius:16;
            opacity:0.8;
            visible:false;
            z:2;
            implicitHeight: 80;
            implicitWidth: 200;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 16;
            Column{
                anchors.fill: parent;
                anchors.leftMargin: 12;
                anchors.rightMargin: 12;
                anchors.topMargin: 6;
                anchors.bottomMargin: 6;
                spacing:4;
                Text{
                    id:state;
                    font.pointSize: 14;
                    color:"blue";
                }
                Text{
                    id:progress;
                    font.pointSize: 12;
                    color:"white";
                }
            }
        }


    }


    FileDialog{
        id:fileDialog;
        title:qsTr("Please choose an file")
        nameFilters: [
            "Text Files {*.txt *.ini *.log *.c *.h *.java *.cpp *.html *.xml}",
            "Image Files {*.jpg *.png *.gif *.bmp *.ico}",
            "Video Files {*.ts *.mp4 *.avi *.flv *.mkv *.3gp}",
            "Audio Files {*.mp3 *.ogg *.wav *.ape *.ra}",
            "*.*"
        ];
        onAccepted: {
            var filepath = String(selectedFile)
            if(Qt.platform.os === "windows"){
                rootFooter.text = filepath.slice(8);
            }else{
                rootFooter.text = filepath.slice(7);
            }
            var dot = filepath.lastIndexOf(".");
            var sep = filepath.lastIndexOf("/");
            if(dot > sep){
                var ext = filepath.substring(dot);
                root.processFile(selectedFile,ext.toLowerCase())
            }else{
                rootFooter.text = "Not Supported!";
            }
        }
    }
    function processFile(fileUrl,ext){
        var i = 0;
        for(;i<fileDialog.nameFilters.length;i++){
            if(fileDialog.nameFilters[i].search(ext) !== -1)break;
        }
        switch(i){
        case 0:
            if(centralView.current !== textView){
                if(centralView.current != null){
                    centralView.current.visible = false;
                }
                textView.visible = true;
                centralView.current = textView;
            }
            textView.loadText(fileUrl);
            break;
        case 1:
            if(centralView.current !== imageViewer){
                if(centralView.current != null){
                    centralView.current.visible = false;
                }
                imageViewer.visible = true;
                centralView.current = imageViewer;
            }
            imageViewer.source = fileUrl;
            break;
        case 2:
        case 3:
            if(centralView.current != videoOutput){
                if(centralView.current != null){
                    centralView.current.visible = false;
                }
                videoOutput.visible = true;
                centralView.current = videoOutput;
            }
            player.source = fileUrl;
            player.play();
            break;
        default:
            rootFooter.text = "抱歉,处理不了";
            break;
        }
    }

    function selectColor(func){
        if(colorDlg == null){
            colorDlg = Qt.createQmlObject('import QtQuick 2.15;import QtQuick.Dialogs;ColorDialog{}',root,"colorDlg");
            colorDlg.accepted.connect(func);
            colorDlg.accepted.connect(onColorDlgClosed);
            colorDlg.rejected.connect(onColorDlgClosed);
            colorDlg.visible = true;
        }
    }
    function showAbout(){
        if(aboutDlg == null){
            aboutDlg = Qt.createQmlObject(`
                          import QtQuick 2.15
                          import QtQuick.Dialogs
                          MessageDialog {
                          icon: StandardIcon.Information
                          title: "关于"
                          text: "文件查看器示例\n版本 1.0"
                          standardButtons: StandardButton.Ok
                          }`, root, "aboutDlg")
            aboutDlg.accepted.connect(onAboutDlgClosed);
            aboutDlg.rejected.connect(onAboutDlgClosed);
            aboutDlg.visible = true;
        }
    }

    function onAboutDlgClosed(){
        aboutDlg.destroy();
        aboutDlg = null;
    }
    function onColorDlgClosed(){
        colorDlg.destroy();
        colorDlg = null;
    }
    function onTextColorSelectd(){
        console.log(colorDlg.color)
        root.textColor = colorDlg.color;
    }
    function onTextBackgroundColorSelected(){
        root.textBackgroundColor = colorDlg.color;
    }

}




























