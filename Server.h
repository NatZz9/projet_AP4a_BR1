#ifndef AP4A_SERVER_H
#define AP4A_SERVER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Sensor.h"

class Sensor;

class Server {
    private:
        std::string name;
        std::string version;
        std::vector<Sensor*> sensors;

        //For SERVER update (count)
        int tempLogs = 0;
        int humiLogs = 0;
        int soundLogs = 0;
        int lightLogs = 0;
        int motionLogs = 0;
    public:
    /* Coplien form */
    Server();
    Server(const Server& serv);
    Server& operator=(const Server& serv);
    ~Server();

    /* Other functionnalities */
    Server(std::string name, std::string version): name(name), version(version), tempLogs(0), humiLogs(0), soundLogs(0), lightLogs(0), motionLogs(0){}

    friend std::ostream& operator<<(std::ostream& os, const Server& server);

    /* Other Functions */
    std::string getName(){
        return name;
    }
    std::string getVersion(){
        return version;
    }
    void setName(std::string n){
        name = n;
    }
    void setVersion(std::string v){
        version = v;
    }

    void consoleWrite() const;

    void fileWrite(const Sensor& sensor);

    void receiveData(const Sensor* sensor);

    void update();
};


#endif //AP4A_SERVER_H
