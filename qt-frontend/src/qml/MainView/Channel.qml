import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Pane {
    ColumnLayout {
        anchors.fill: parent
        Label {
            id: channel_name
            text: "Test"
        }

        ComboBox {
            id: output_device
            model: ["Speakers", "Screen 01 Speakers", "Screen 02 Speakers"]
        }

        Slider {
            id: volume
            orientation: Qt.Vertical

            Layout.fillHeight: true
        }
    }
}
