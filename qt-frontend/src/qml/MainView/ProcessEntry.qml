import QtQuick
import QtQuick.Controls

Rectangle {
    property string process_name
    property color process_color

    height: 20
    width: 100
    
    Label {
        anchors.fill: parent
        text: parent.process_name
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        fontSizeMode: Text.Fit
        wrapMode: Text.WordWrap
    }

    color: process_color
    radius: 4
}
