#pragma once
#include <QObject>
#include <QTimer>

class Sensor : public QObject {
    Q_OBJECT

  public:
    explicit Sensor(QObject *parent = nullptr);
    void start();
    void stop();

  signals:
    void readingChanged(int sequence, double temperature);

  private:
    QTimer *mTimer = nullptr;
    int mSequence = 0;
};
