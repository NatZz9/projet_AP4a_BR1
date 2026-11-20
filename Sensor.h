#ifndef AP4A_SENSOR_H
#define AP4A_SENSOR_H

#include <string>
#include <ctime>
#include <sstream>

class Server;

class Sensor {
    protected:
        static int nextId;
        int id;
        std::string type;
        Server* server;
        std::string name;
        std::string date;
        int interval;

        std::string getCurrentDate() const {
            std::time_t now = std::time(nullptr);
            char buf[80];
            std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
            return std::string(buf);
        }

    public:
    // Coplien form
    Sensor(std::string type, Server* server, std::string name = "", int interval = 1)
            : id(++nextId), type(type), server(server), name(name), date(getCurrentDate()), interval(interval) {}
    Sensor(const Sensor&);
    Sensor& operator= (const Sensor&);
    virtual ~Sensor() = default;

    // VIRTUAL
    virtual void execute() = 0;
    virtual void update() = 0;
    virtual std::string getValueAsString() const = 0;

    // Getters & Setters
    int getId() const { return id; }
    int getInterval() const { return interval; }
    std::string getType() const { return type; }
    std::string getName() const { return name; }
    std::string getDate() const { return date; }
};



/* SENSOR WITH NUMBER (int,float) CLASS SPECIFICATION */


template <typename T>
class NumericSensor : public Sensor {
protected:
    T value;
    std::string unit;
public:
    NumericSensor(std::string type, Server* server, std::string name, T initialVal, std::string unit, int interval = 1)
            : Sensor(type, server, name, interval), value(initialVal), unit(unit) {}

    std::string getValueAsString() const override {
        return std::to_string(value) + " " + unit;
    }
};

/* FLOAT  ----------------------------------  */

class TemperatureSensor : public NumericSensor<float> {
public:
    TemperatureSensor(Server* server, std::string name = "TempSensor", int interval = 2)
            : NumericSensor<float>("Temperature", server, name, 0.0f, "°C", interval) {}

    void execute() override;
    void update() override;
};


class HumiditySensor : public NumericSensor<float> {
public:
    HumiditySensor(Server* server, std::string name = "HumiSensor", int interval = 3)
            : NumericSensor<float>("Humidity", server, name, 0.0f, "%", interval) {}

    void execute() override;
    void update() override;
};


/* INT  ----------------------------------  */


class SoundSensor : public NumericSensor<int> {
public:
    SoundSensor(Server* server, std::string name = "SoundSensor", int interval = 1)
            : NumericSensor<int>("Sound", server, name, 0, "db", interval) {}

    void execute() override;
    void update() override;
};


/* BOOL  ----------------------------------  */


class LightSensor : public NumericSensor<bool> {
public:
    LightSensor(Server* server, std::string name = "LightSensor", int interval = 5)
            : NumericSensor<bool>("Light", server, name, false, "", interval) {}

    std::string getValueAsString() const override {
        return value ? "On" : "Off";
    }

    void execute() override;
    void update() override;
};


class MotionSensor : public NumericSensor<bool> {
public:
    MotionSensor(Server* server, std::string name = "MotionSensor", int interval = 1)
            : NumericSensor<bool>("Motion", server, name, false, "", interval) {}

    std::string getValueAsString() const override {
        return value ? "Motion detected" : "No movement";
    }

    void execute() override;
    void update() override;
};


#endif //AP4A_SENSOR_H
