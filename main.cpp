#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "osgItem.h"

int main(int argc, char *argv[])
{
        qputenv("QSG_RENDER_LOOP", "basic");
    qmlRegisterType<OSGItem>("OSGQMLItem",1,0,"OSGItem");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
