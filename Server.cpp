#include "Server.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Sensor.h"

Server::Server(): name(""), version(""), tempLogs(0), humiLogs(0), soundLogs(0), lightLogs(0), motionLogs(0) {}

Server::Server(const Server& serv)
        : name(serv.name), version(serv.version), sensors(serv.sensors),
          tempLogs(serv.tempLogs), humiLogs(serv.humiLogs), soundLogs(serv.soundLogs),
          lightLogs(serv.lightLogs), motionLogs(serv.motionLogs) {}

Server& Server::operator=(const Server& serv){
    if (this != &serv){
        name = serv.name;
        version = serv.version;
        sensors = serv.sensors;
        tempLogs = serv.tempLogs;
        humiLogs = serv.humiLogs;
        soundLogs = serv.soundLogs;
        lightLogs = serv.lightLogs;
        motionLogs = serv.motionLogs;
    }
    return *this;
}

Server::~Server(){}

/* Reste des fonctions */
std::ostream& operator<<(std::ostream& os, const Server& server) {
    os << "Server Name: " << server.name << " - Version: " << server.version;
    return os;
}


void Server::consoleWrite() const{
    std::cout << "\n--- Actual state of server : " << name << " ---\n" << std::endl;
    std::cout << "------------------------------------------\n" << std::endl;
    std::cout << "Number of sensors connected : " << sensors.size() << "\n" << std::endl;
    std::cout << "------------------------------------------\n" << std::endl;
    for (const auto& sensor : sensors) {
        std::cout << "ID: " << sensor->getId()
                  << " - Type: " << sensor->getType()
                  << " - Name: " << sensor->getName()
                  << " - Interval: " << sensor->getInterval() << "s"
                  << " - Last Value: " << sensor->getValueAsString()
                  << " - Date: " << sensor->getDate() << std::endl;
    }
}

void Server::fileWrite(const Sensor& sensor) {
    std::string filename = sensor.getType() + "_log.csv";

    std::ofstream logFile(filename, std::ios::app);
    if (logFile.is_open()) {
        logFile << sensor.getId() << ";"
                << sensor.getType() << ";"
                << sensor.getValueAsString() << ";"
                << sensor.getDate() << "\n";
        logFile.close();
    }
}

void Server::receiveData(const Sensor* sensor) {
    if (!sensor) return;

    bool exists = false;
    for (const auto& s : sensors) {
        if (s == sensor) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        sensors.push_back(const_cast<Sensor*>(sensor));
    }

    fileWrite(*sensor);

    std::cout << "[Server " << name << "] Gets -> "
              << sensor->getType() << " (" << sensor->getName() << ") : "
              << sensor->getValueAsString() << std::endl;

    //For SERVER UPDATE (count)
    std::string type = sensor->getType();
    if (type == "Temperature"){
        tempLogs++;
    }else if (type == "Humidity"){
        humiLogs++;
    }else if (type == "Sound"){
        soundLogs++;
    }else if (type == "Light"){
        lightLogs++;
    }else if (type == "Motion"){
        motionLogs++;
    }
}


void Server::update() {
    int tempCount = 0, humiCount = 0, soundCount = 0, lightCount = 0, motionCount = 0;

    std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    std::cout << "*********************************************" << std::endl;
    std::cout << "  [SERVER STATS] - " << name << " (" << buf << ")" << std::endl;


    for (const auto& sensor : sensors) {
        std::string type = sensor->getType();
        if (type == "Temperature") tempCount++;
        else if (type == "Humidity") humiCount++;
        else if (type == "Sound") soundCount++;
        else if (type == "Light") lightCount++;
        else if (type == "Motion") motionCount++;
    }
    int totalLogs = tempLogs + humiLogs + soundLogs + lightLogs + motionLogs;

    std::cout << "\n[SERVEUR UPDATE] --- STATISTICS ---" << std::endl;
    std::cout << "Total connected sensors: " << sensors.size() << std::endl;
    std::cout << "  - Temperature : " << tempCount << std::endl;
    std::cout << "  - Humidity    : " << humiCount << std::endl;
    std::cout << "  - Sound       : " << soundCount << std::endl;
    std::cout << "  - Light       : " << lightCount << std::endl;
    std::cout << "  - Motion      : " << motionCount << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Total logs received: " << totalLogs << std::endl;
    std::cout << "  - Temperature occurrences : " << tempLogs << std::endl;
    std::cout << "  - Humidity occurrences    : " << humiLogs << std::endl;
    std::cout << "  - Sound occurrences       : " << soundLogs << std::endl;
    std::cout << "  - Light occurrences       : " << lightLogs << std::endl;
    std::cout << "  - Motion occurrences      : " << motionLogs << "\n" << std::endl;
    std::cout << "*********************************************\n\n" << std::endl;
}