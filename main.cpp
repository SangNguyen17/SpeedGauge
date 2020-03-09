#include "sendmessagewidget.h"
#include "qmlhandler.h"
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQuickView quickView;

    qmlRegisterType<QMLHandler>("QMLHandler", 1, 0, "QMLHandler");
    quickView.setSource(QUrl("qrc:/main.qml"));
    quickView.show();
    return app.exec();
}
