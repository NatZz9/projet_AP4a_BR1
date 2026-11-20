#include <iostream>
#include "Server.h"
#include "Sensor.h"
#include "Scheduler.h"

int main() {
    // Init Random
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Server myServer("Test_SERV", "v1.0");
    std::cout << "\n\nServer Information : " << myServer << std::endl << std::endl;


    Sensor* temp1 = new TemperatureSensor(&myServer, "Temp_Outside");
    Sensor* hum1  = new HumiditySensor(&myServer, "Humi_LivingRoom");
    Sensor* sound1 = new SoundSensor(&myServer, "Sound_OpenSpace");
    Sensor* light1 = new LightSensor(&myServer, "Light_Kitchen");
    Sensor* motion1 = new MotionSensor(&myServer, "Motion_Garage");


    Scheduler scheduler(&myServer);
    scheduler.addSensor(temp1);
    scheduler.addSensor(hum1);
    scheduler.addSensor(sound1);
    scheduler.addSensor(light1);
    scheduler.addSensor(motion1);


    std::cout << "Number of sensors added : "
              << scheduler.getSensorsCount() << "\n" <<std::endl;


    scheduler.start();

    return 0;
}
