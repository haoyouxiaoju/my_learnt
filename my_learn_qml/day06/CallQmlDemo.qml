import QtQuick
import QtQuick.Controls
import QtQuick.Window

Window{
    objectName:"rootObject";
    width:360;
    height:360;
    visible:true;
    Text{
        objectName:"textLabel";
        text:"Hello World";
        anchors.centerIn:parent;
        font.pixelSize: 26;
    }
    Button{
        objectName:"quitButtom";
        anchors.right: parent.right;
        anchors.rightMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin:4;
        text:"quit";
    }
}

 // QObject* root = nullptr;
 //    QList<QObject*> rootObjects = engine.rootObjects();

 //    // rootObjects = rootObjects.at(0)->children();
 //    int count = rootObjects.size();
 //    qDebug()<<"count:"<<count;
 //    for(int i=0;i<count;++i){
 //        qDebug()<<"objectName at("<<i<<")"<<rootObjects.at(i)->objectName();
 //        if(rootObjects.at(i)->objectName() == "rootObject"){
 //            root = rootObjects.at(i);
 //            break;
 //        }
 //    }
 //    // new ChangeQmlColor(root);
 //    QObject* quitButton = root->findChild<QObject*>("quitButton");
 //    if(quitButton){
 //        QObject::connect(quitButton,SIGNAL(clicked()),&app,SLOT(quit()));
 //    }
 //    QObject* textLabel = root->findChild<QObject*>("textLabel");
 //    if(textLabel){
 //        bool bRet = QMetaObject::invokeMethod(textLabel,"setText",Q_ARG(QString,"world hello"));
 //        qDebug()<<"call setText return -"<<bRet;
 //        textLabel->setProperty("color",QColor::fromRgb(255,0,0));
 //        bRet = QMetaObject::invokeMethod(textLabel,"doLayout");
 //        qDebug()<<"call doLayout return -"<<bRet;

 //    }
