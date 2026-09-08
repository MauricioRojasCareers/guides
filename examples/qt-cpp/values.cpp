#include <QDebug>
#include <QString>
#include <vector>

struct Reading {
    QString name;
    double temperature = 0.0;
};

bool isHot(const Reading &reading) {
    return reading.temperature >= 30.0;
}

int main() {
    const std::vector<Reading> readings{{"front", 24.5}, {"rear", 31.0}};
    for (const Reading &reading : readings) {
        qInfo().noquote() << reading.name << reading.temperature
                          << (isHot(reading) ? "HOT" : "OK");
    }
}
