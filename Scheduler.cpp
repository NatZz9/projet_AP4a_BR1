#include "Scheduler.h"
#include <iostream>
#include <thread>
#include <chrono>

void Scheduler::start() {
    running = true;
    std::cout << "Starting simulation " << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "." << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "." << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << ".\n\n" << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    int loopCount = 0;

    while (running) {
        loopCount++;
        std::cout << "--- Loop #" << loopCount << " ---\n";

        for (auto& sensor : sensors) {
            if (loopCount % sensor->getInterval() == 0) {
                sensor->update();
            }
        }

        std::cout << "\n" << std::endl;


        if (server != nullptr && loopCount % 10 == 0) {
            server->update();
        }


        // 1 second stop (simulation)
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (loopCount >= 20) {
            if (server != nullptr) {
                server->consoleWrite();
            }
            stop();
        }
    }
}

void Scheduler::stop() {
    running = false;
    std::cout << "\n\n !-----! Simulation Ended !-----!\n\n" << std::endl;
}

void Scheduler::addSensor(Sensor* sensor) {
    sensors.push_back(sensor);
}