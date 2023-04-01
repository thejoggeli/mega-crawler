#include "Joint.h"
#include "motors/ServosManager.h"

Joint::Joint(){
    
}

void Joint::init(){

}

void Joint::setServoByIndex(unsigned int idx){
    servo = &ServosManager::instance.servos[idx];
}

void Joint::setAngle(float angle, float seconds){
    servo->SetAngle(angle, seconds);
}