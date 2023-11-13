// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlProperty>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"
#include "manager.h"

int main(int argc, char *argv[])
{
    set_qt_environment();

    QGuiApplication app(argc, argv);

    // QQuickView uiLamps(QUrl::fromLocalFile("qml/content/LampColumn.qml"));
    // QObject *lamps = uiLamps.rootObject();

    // QObject::connect(lamps, SIGNAL(addNewLamp()), &manager, SLOT(addNewLamp()));
    // QObject::connect(lamps, SIGNAL(addConnected()), &manager, SLOT(addNewLamp()));

    QQmlApplicationEngine engine;

    manager *appManager = new class manager(&app);
    engine.rootContext()->setContextProperty("appManager", appManager);

    const QUrl url(u"qrc:Main/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.load(url);

    //QObject::connect(engine.rootObjects(),SIGNAL(addNewLamp(int)), appManager, SLOT(addConnected(int)));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
