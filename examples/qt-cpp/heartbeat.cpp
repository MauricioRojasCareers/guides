#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QTimer timer;
    int count = 0;
    QObject::connect(&timer, &QTimer::timeout, &app, [&count, &app] {
        qInfo() << "tick" << ++count;
        if (count == 5) {
            app.quit();
        }
    });
    timer.start(500);
    return app.exec();
}
