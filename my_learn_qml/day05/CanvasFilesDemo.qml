import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs


ApplicationWindow{
    visible:true;
    width:480;
    height:320;
    minimumHeight:320;
    minimumWidth:480;
    color:"black";

    onWidthChanged:mask.recals();
    onHeightChanged:mask.recalc();

    Image{
        id:source;
        anchors.fill: parent;
        fillMode:Image.PreserveAspectFit;
        visible:false;
        asynchronous: true;
        onStatusChanged:(statys)=>{
            if(status === Image.Ready){
                console.log("image loaded");
                mask.recalc();
            }
        }
    }

    FileDialog{
        id:fileDialog;
        title: "Prease choose an Imae File";
        nameFilters: {"Image Files (*.jgp *.png *.gif)"}
        onAccepted:{
            source.source = fileDialog.selectedFile;
            var imageFile = String(fileDialog.selectedFile);
            console.log(imageFile);
        }
    }

    Canvas{
        id:forSaveCanvas;
        width:128;
        height:128;
        contextType: "2d";
        visible:false;
        z:2;
        anchors.top:parent.top;
        anchors.right:parent.right;
        anchors.margins: 4;
        property var imageData: null;
        onPaint:{
            if(imageData != null){
                context.drawImage(imageData,0,0);
            }
        }
        function setImageData(data){
            imageData = data;
            requestPaint();
        }
    }

    Canvas{
        id:mask;
        anchors.fill: parent;
        z:1;
        property real w: width;
        property real h: height;
        property real dx: 0;
        property real dy: 0;
        property real dw: 0;
        property real dh: 0;
        property real frameX: 66;
        property real frameY: 66;

        function calc(){
            var sw = source.sourceSize.width;
            var sh = source.sourceSize.height;
            if(sw > 0 && sh > 0){
                if(sw <= w && sh<= h){
                    dw = sw;
                    dh = sh;
                }else{
                    var sRatio = sw /sh;
                    dw = sRatio * h;
                    if(dw > w){
                        dh = w/sRatio;
                        dw = w;
                    }else{
                        dh = h;
                    }
                }
                dx =(w-dw)/2;
                dy =(h-dh)/2;
            }
        }
        function recalc(){
            calc();
            requestPaint();
        }
        function getImageData(){
            return context.getImageData(frameX-64,frameY-64,128,128);
        }
        onPaint:{
            var ctx = getContext("2d");
            ctx.clearRect(0,0,width,height);
            if(dw <1 || dh <1){
                ctx.fillStyle = '#0000a0';
                ctx.font = "20px sans-serif";
                ctx.textAlign = "center";
                ctx.fillText("Please Choose An Image File",width/2,height/2);
                return ;
            }

            ctx.drawImage(source,dx,dy,dw,dh);
            ctx.save();
            // 创建剪切路径 - 只显示方框内部
            ctx.beginPath()
            ctx.rect(frameX-66, frameY-66, 132, 132)
            ctx.clip()

            // 重新绘制图片（只在剪切区域内可见）
            ctx.drawImage(source, dx, dy, dw, dh)

            // 恢复状态
            ctx.restore()

            // 绘制红色边框
            ctx.strokeStyle = "red"
            ctx.lineWidth = 2
            ctx.strokeRect(frameX-66, frameY-66, 132, 132)
            ctx.stroke();


        }

    }
    MultiPointTouchArea{
        anchors.fill: parent;
        minimumTouchPoints: 1;
        maximumTouchPoints: 1;
        touchPoints:[
            TouchPoint{id:point1}
        ]
        onUpdated:{
            mask.frameX = point1.x;
            mask.frameY = point1.y;
            mask.requestPaint();
        }
        onReleased:{
            forSaveCanvas.setImageData(mask.getImageData());
            actionPanel.visible = true;
        }
        onPressed:{
            actionPanel.visible = false;
        }
    }

    Row{
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 20;
        id:actionPanel;
        z:5;
        spacing:8;
        CanvasFilesDemoButton{

            text:"Open";
            onClicked:fileDialog.open();
        }
        CanvasFilesDemoButton{

            text:"Save";
            onClicked:{
                forSaveCanvas.save("save.png");
                actionPanel.visible = false;
            }
        }
        CanvasFilesDemoButton{

            text:"Cancel";
            onClicked:actionPanel.visible = false;
        }
    }


}
