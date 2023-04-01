#include "motors/ServosManager.h"
#include <Arduino.h>

ServosManager ServosManager::instance = ServosManager();

ServosManager::ServosManager(){

}

void ServosManager::init(){
    servoSerial.begin(115200);
    pinMode(19, INPUT_PULLUP);
}

