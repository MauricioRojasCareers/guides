#include "sensor.h"

Sensor::Sensor(QObject *parent) : QObject(parent), mTimer(new QTimer(this)) {
    mTimer->setInterval(500);
    connect(mTimer, &QTimer::timeout, this, [this] {
        ++mSequence;
        const double temperature = 20.0 + (mSequence % 20);
        emit readingChanged(mSequence, temperature);
    });
}

void Sensor::start() { mTimer->start(); }
void Sensor::stop() { mTimer->stop(); }
