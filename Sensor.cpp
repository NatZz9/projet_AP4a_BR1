#include "Sensor.h"
#include "Server.h"
#include <cstdlib>


//Shared variable for ID
int Sensor::nextId = 0;


void TemperatureSensor::execute() {
    value = 18.0f + static_cast<float>(rand() % 100) / 10.0f;
    date = getCurrentDate();

    if (server != nullptr) {
        server->receiveData(this);
    }
}

void TemperatureSensor::update() {
    execute();
}



void HumiditySensor::execute() {
    value = 40.0f + static_cast<float>(rand() % 400) / 10.0f;
    date = getCurrentDate();

    if (server != nullptr) {
        server->receiveData(this);
    }
}

void HumiditySensor::update() {
    execute();
}



void SoundSensor::execute() {
    value = 30 + (rand() % 60);
    date = getCurrentDate();

    if (server != nullptr) {
        server->receiveData(this);
    }
}

void SoundSensor::update() {
    execute();
}



void LightSensor::execute() {
    value = (rand() % 2 == 0);
    date = getCurrentDate();

    if (server != nullptr) {
        server->receiveData(this);
    }
}

void LightSensor::update() {
    execute();
}



void MotionSensor::execute() {
    value = (rand() % 4 == 0);
    date = getCurrentDate();

    if (server != nullptr) {
        server->receiveData(this);
    }
}

void MotionSensor::update() {
    execute();
}