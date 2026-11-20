#ifndef AP4A_SCHEDULER_H
#define AP4A_SCHEDULER_H

#include <vector>
#include "Sensor.h"
#include "Server.h"

class Scheduler {
private:
    std::vector<Sensor*> sensors;
    bool running;
    Server *server;
public:
    // Coplien Form
    Scheduler(Server* s = nullptr) : running(false), server(s) {}
    Scheduler(const Sensor&) = delete;
    Scheduler& operator=(const Scheduler&) = delete;
    ~Scheduler() {
        for (auto sensor : sensors) {
            delete sensor;
        }
        sensors.clear();
    }

    //Functions
    void start();

    void stop();

    void addSensor(Sensor* sensor);

    size_t getSensorsCount() const {
        return sensors.size();
    }
};


#endif //AP4A_SCHEDULER_H
