import QtQuick 2.15

Text{
    id:control;
    // text: "";
    color:wrapper.ListView.isCurrentItem?"red":"black";
    font.pixelSize: wrapper.ListView.isCurrentItem?22:18;
}
