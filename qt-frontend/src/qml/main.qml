import QtQuick
import QtQuick.Controls

import MainView;

ApplicationWindow {
    title: "Via Vocis"
    width: 800
    height: 600
    visible: true

    MainView {
        anchors.fill: parent
    }
}
