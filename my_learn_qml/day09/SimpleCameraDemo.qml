import QtQuick 2.15
import QtQuick.Window
import QtMultimedia
import QtQuick.Controls


Window{

    visible:true;
    width:600;
    height: 400;
    color:"black";
    MediaDevices {
        id: mediaDevices
    }
    CaptureSession {
        camera: Camera {
            cameraDevice: mediaDevices.defaultVideoInput
        }
    }
}

