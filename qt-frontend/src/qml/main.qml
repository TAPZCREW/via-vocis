import QtQuick
import QtQuick.Controls

import MainView;

ApplicationWindow {
    title: "Via Vocis"
    visible: true

    minimumWidth: 800
    minimumHeight: 600

    Pane {
        anchors.fill: parent
        MainView {
            anchors.fill: parent
        }
    }
}
