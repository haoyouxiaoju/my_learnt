import QtQuick
// import QtQuick.VirtualKeyboard
import QtQuick.Controls
import QtMultimedia
// import QtQuick.Layouts
// import an.qt.ColorMaker 1.0
// import QtQuick.Controls.Styles
// import "./day02"
// import "./day03"
// import "./day04"
// import "./day05"
// import "./day06"
// import "./day07"
// import "./day08"
import "./day09"
 // import Qt.labs.qmlmodels

// Window{
//     objectName:"rootObject";
//     width:360;
//     height:360;
//     visible:true;
//     Text{
//         objectName:"textLabel";
//         text:"Hello World";
//         anchors.centerIn:parent;
//         font.pixelSize: 26;
//     }
//     Button{
//         objectName:"quitButtom";
//         anchors.right: parent.right;
//         anchors.rightMargin: 4;
//         anchors.bottom: parent.bottom;
//         anchors.bottomMargin:4;
//         text:"quit";
//     }
// }

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    // ChooseImageDisplay{}
    // MySignal{}
    // ChangeColorRect{}
    // KeyMoveText{}
    // StartTimer{}
    // PinchPhone{}
    // ColorPicker{}
    // ComponentFile{}
    // LoaderTest{}
    // LoaderTestFileInput{}
    // LoaderTestFileInput2{}
    // CreateControls{}
    // CreateControls2{}
    // PreferredMobileOs{}
    // PreferredMovies{}
    // ComboboxDemo{}
    // ProgressBarDemo{}
    // MyTabView{
    //     width: 400;
    //     height:500;
    // }
    // MyStackView{}
    // SliderDemo{}
    // FlickableDemo{}
    // CanvasTransform{}
    // AuthCodeItem{}
    // CanvasClipDemo{}
    // CanvasFilesDemo{}
    // ColorMakerDemo{}
    // CallQmlDemo{}

    // PhoneTableSimple{}
    // FindImageDemo{}
    // SimpleMusic{}
    // SimpleCameraDemo{}

    FileReaderDemo{}
    


    // ImageProcessorDemo{}
    // PropertAnimationStandalone{}
    // PropertyAnimationSwap{}
    // NumberAnimationSquareToCircle{}
    // ColorAnimationRedToGreen{}
    // RotationAnimationDemo{}
    // PathAnimationDemo{}
    // SmoothedAnimationDemo{}
    // SpringAnimationDemo{}
    // SequentialAnimationDemo{}
    // StateDemo{}
    // ParentChangeDemo{}
    // TransitionRectDemo{}
    // Image {
        // id: iamge1
        // source: "qrc:/source/icons/bubble_1.png"
    // }
    // Bubbleshot{}
    // PhoneListViewDemo{}
    // VideoListXml{}
    // Canvas{
    //     width:400;
    //     height:300;
    //     id:root;
    //     property  string iconUrl : "qrc:/source/icons/avatar.png";
    //     property string womanUrl : "https://tse3-mm.cn.bing.net/th/id/OIP-C.HjYIizKCiIsDIj-Dvm-udQAAAA?rs=1&pid=ImgDetMain";
    //     Image{
    //         id:poster;
    //         source:root.womanUrl;
    //         visible:false;
    //         onStatusChanged:(status)=>{
    //             if(status === Image.Ready){
    //                 root.requestPaint();
    //             }
    //         }
    //     }

    //     onPaint:{
    //         var ctx = getContext("2d");
    //         // ctx.beginPath(); //没有用,只能发送requestPaint(); 图片才显示
    //         // ctx.drawImage(iconUrl,0,0);s
    //         // ctx.drawImage(womanUrl,200,50);
    //         ctx.drawImage(poster,100,50);
    //         // ctx.fill();
    //     }
    //     // Component.onCompleted: loadImage(iconUrl);
    //     // onImageLoaded: requestPaint();
    // }



    // Button{
    //     text:"test";
    //     width: 200;
    //     height:150;
    //     onClicked:test();
    // }

    // function test (){
    //     console.log(Qt.application.platform.os)
    //     // var uri = "https://tse3-mm.cn.bing.net/th/id/OIP-C.HjYIizKCiIsDIj-Dvm-udQAAAA?rs=1&pid=ImgDetMain";
    //     // var encodedUri = encodeURI(uri);
    //     // var encodedComponent = encodeURIComponent(uri);
    //     // console.log(encodedUri);
    //     // console.log(encodedComponent)
    //     // var decodedUri = decodeURI(encodedUri);
    //     // var decodedComponent = decodeURIComponent(encodedComponent);
    //     // console.log(decodedUri);
    //     // console.log(decodedUri)
    // }




}
