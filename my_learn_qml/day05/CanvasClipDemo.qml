import QtQuick

Rectangle{
    id:control;
    width:400;
    height:400;

    property string imageUrl: "https://tse3-mm.cn.bing.net/th/id/OIP-C.HjYIizKCiIsDIj-Dvm-udQAAAA?rs=1&pid=ImgDetMain";

    Canvas{
        width:control.width;
        height:control.height;
        contextType:"2d";
        onPaint:{
            context.lineWidth =2;
            context.strokeStyle = "blue";
            context.fillStyle = Qt.rgba(0.3,0.5,0.7,0.3);

            context.save();
            context.beginPath();
            context.arc(180,150,80,0,Math.PI*2,true);
            context.moveTo(180,230);
            context.lineTo(420,280);
            context.lineTo(160,320);
            context.closePath();
            context.clip();
            context.drawImage(imageUrl,0,0,600,600);
            context.stroke();
            context.fill();

            context.rotate(Math.PI /5);
            context.font = "italic bold 32px serif";
            context.fillStyle = "red";
            context.fillText("the text will be clipped!",100,70);
            context.restore();
        }
        onImageLoaded: requestPaint();

    }


}
