import QtQuick 2.15
import QtMultimedia

Rectangle{
    width:200;
    height:100;
    MediaPlayer{
        autoPlay: true;
        source: "wangjie_game_and_dream.mp3";
    }
}
