#include <QDirIterator>
#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QResource>
#include <dlfcn.h>
#include <iostream>
#include <qguiapplication.h>
#include <qobject.h>
#include <string_view>

// Suppress warning about declaration
int qtExec(int argc, char *argv[]);

extern int qCleanupResources_qml();
extern int qInitResources_qml();

int qtExec(int argc, char *argv[]) {
    const QUrl url(QStringLiteral("qrc:/main.qml"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) {
                QCoreApplication::exit(-1);
            }

            if (obj) {
                std::cout << "Object created: " << obj << " url "
                          << objUrl.toString().toStdString() << std::endl;
            }
        },
        Qt::QueuedConnection);
    engine.load(url);

    int res = app.exec();

    engine.trimComponentCache();
    engine.clearComponentCache();

    return res;
}

bool shouldClose = false;

int mainfn(int argc, char *argv[]) {
    /*
     * Depends on cpprepl logic to monitor and rebuild the project
     * https://github.com/Fabio3rs/my-cpp-repl-study
     */
    int res = 0;
    auto symqCleanupResources_qml =
        (void **)dlsym(RTLD_DEFAULT, "_Z21qCleanupResources_qmlv_ptr");
    auto oldmqCleanupResources_qml =
        symqCleanupResources_qml
            ? reinterpret_cast<int (*)()>(*symqCleanupResources_qml)
            : nullptr;

    do {
        if (oldmqCleanupResources_qml) {
            oldmqCleanupResources_qml();
        }
        qInitResources_qml();

        if (symqCleanupResources_qml) {
            oldmqCleanupResources_qml =
                reinterpret_cast<int (*)()>(*symqCleanupResources_qml);
        }

        res = qtExec(argc, argv);
    } while (!shouldClose);
    return res;
}

int main(int argc, char *argv[]) { return mainfn(argc, argv); }

void reloadAllTheApp(std::string_view path) {
    std::cout << "File changed: " << path << std::endl;

    // restart the application
    bool resqt = QMetaObject::invokeMethod(
        qApp, []() { qApp->quit(); }, Qt::QueuedConnection);

    std::cout << "Quit result: " << resqt << std::endl;
}

extern "C" void onFileChange(std::string_view path) { reloadAllTheApp(path); }
