import QtQuick 2.15

Text{
    color:wrapper.ListView.isCurrentItem?"blue":"black";
    font.pixelSize: 18;
    elide:Text.ElideRight;
}
