#include "sensor.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("Simulated sensor — Qt + C++ lab");
    auto *layout = new QVBoxLayout(&window);
    auto *status = new QLabel("Stopped", &window);
    auto *reading = new QLabel("No readings yet", &window);
    auto *start = new QPushButton("Start", &window);
    auto *stop = new QPushButton("Stop", &window);
    layout->addWidget(status);
    layout->addWidget(reading);
    layout->addWidget(start);
    layout->addWidget(stop);
    auto *sensor = new Sensor(&window);

    QObject::connect(start, &QPushButton::clicked, sensor, &Sensor::start);
    QObject::connect(stop, &QPushButton::clicked, sensor, &Sensor::stop);
    QObject::connect(start, &QPushButton::clicked, status, [status] {
        status->setText("Running");
    });
    QObject::connect(stop, &QPushButton::clicked, status, [status] {
        status->setText("Stopped");
    });
    QObject::connect(sensor, &Sensor::readingChanged, reading,
                     [reading](int sequence, double temperature) {
        reading->setText(QString("Reading %1: %2 °C").arg(sequence).arg(temperature, 0, 'f', 1));
    });
    window.resize(360, 180);
    window.show();

    // Optional automated smoke check; ordinary launches stay interactive.
    int received = 0;
    bool valid = true;
    const bool smoke = app.arguments().contains("--smoke-test");
    if (smoke) {
        QObject::connect(sensor, &Sensor::readingChanged, &app,
                         [&received, &valid, stop](int sequence, double temperature) {
            ++received;
            valid = valid && sequence == received && temperature == 20.0 + sequence;
            if (received == 2) {
                stop->click();
            }
        });
        start->click();
        QTimer::singleShot(2200, &app, [&app, &received, &valid, status, reading] {
            app.exit(valid && received == 2 && status->text() == "Stopped"
                     && reading->text().startsWith("Reading 2:") ? 0 : 1);
        });
    }
    return app.exec();
}
