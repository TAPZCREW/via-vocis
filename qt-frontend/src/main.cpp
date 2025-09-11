#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

import std;

auto main(int argc, char** argv) -> int {
    auto app    = QGuiApplication { argc, argv };
    auto engine = QQmlApplicationEngine {};
    QQuickStyle::setStyle("FluentWinUI3");
    engine.addImportPath("qrc:/qml");
    qDebug() << engine.importPathList();
    engine.load(QUrl { QStringLiteral("qrc:/qml/main") });
    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}
