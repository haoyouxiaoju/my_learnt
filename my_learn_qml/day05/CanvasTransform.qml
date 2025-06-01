import QtQuick

Canvas{
    width:480;
    height:640;
    contextType: "2d";
    property string womanUrl : "https://tse3-mm.cn.bing.net/th/id/OIP-C.HjYIizKCiIsDIj-Dvm-udQAAAA?rs=1&pid=ImgDetMain";
    onPaint: {
        context.lineWidth =2;
        context.strokeStyle = "blue";
        context.fillStyle = Qt.rgba(0.3,0.5,0.7,0.5);

        context.save();
        context.translate(width/2,height/2);
        context.drawImage(womanUrl,-68,-100,137,200);
        context.restore();

        context.save();
        context.translate(width/2,0);
        context.shear(0.6,0);
        context.drawImage(womanUrl,0,0,137,200);
        context.restore();

        context.save();
        context.translate(width/2,0);
        context.shear(-0.6,0);
        context.drawImage(womanUrl,-137,0,137,200);
        context.restore();

        context.save();
        context.translate(0,height/2);
        context.shear(0.3,0);
        context.rotate(Math.PI/3);
        context.drawImage(womanUrl,0,-100,137,200);
        context.restore();

        context.save();
        context.translate(width/2,height/2);
        // context.shear(0.3,0);
        context.rotate(Math.PI/2);
        context.drawImage(womanUrl,120,-40,137,200);
        context.restore();

        // context.save();
        // context.translate(1.2,0.5,0,0.7,width-100,height-120);
        // // context.shear(0.3,0);
        // // context.rotate(Math.PI/2);
        // context.drawImage(womanUrl,0,0,68,100);
        // context.restore();
    }
    // Component.onCompleted: loadImage()
    onImageLoaded: requestPaint();
}
