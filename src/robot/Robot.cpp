#include "Robot.h"

Robot::Robot() {

}

void Robot::init(){

    legs[0].anchor = Vector3(+0.052, +0.052, 0.0);
    legs[1].anchor = Vector3(-0.052, +0.052, 0.0);
    legs[2].anchor = Vector3(-0.052, -0.052, 0.0);
    legs[3].anchor = Vector3(+0.052, -0.052, 0.0);

    for(int i = 0; i < NUM_LEGS; i++){
        legs[i].joints[0].length = 0.068f;
        legs[i].joints[1].length = 0.068f;
        legs[i].joints[2].length = 0.068f;
        legs[i].joints[3].length = 0.105f;
    }

    legs[0].joints[0].angleOffset = 45.0f / 180.0f * PI;
    legs[1].joints[0].angleOffset = 135.0f / 180.0f * PI;
    legs[2].joints[0].angleOffset = -135.0f / 180.0f * PI;
    legs[3].joints[0].angleOffset = -45.0f / 180.0f * PI;
    
    unsigned int idx = 0;
    for(int i = 0; i < NUM_LEGS; i++){
        for(int j = 0; j < NUM_JOINTS; j++){
            legs[i].joints[j].setServoByIndex(idx++);
        }
    }
    
    for(int i = 0; i < NUM_LEGS; i++){
        legs[i].init();
    }

    for(int i = 0; i < NUM_LEGS; i++){
        for(int j = 0; j < NUM_JOINTS; j++){
            legs[i].joints[j].setAngle(0.0f, 2.0f);
        }
    }
    delay(2500);
    
}

void Robot::start(){
    
}

void Robot::update(){

}

bool Robot::doSimpleIK(Vector3 Q[NUM_LEGS], float phi[NUM_LEGS], float seconds){

    for(unsigned int i = 0; i < NUM_LEGS; i++){
        Serial.println("[Q-" + String(i) + "] " + Q[i].toString());
    }

    for(unsigned int i = 0; i < NUM_LEGS; i++){
        Serial.println("[phi-" + String(i) + "] " + String(phi[i] * RAD_TO_DEG));
    }

    float angles_out[NUM_LEGS][NUM_JOINTS];
    Leg::IKState ikStates[NUM_LEGS];
    bool ikFailed = false;

    for(int i = 0; i < NUM_LEGS; i++){
        ikStates[i] = legs[i].ik(Q[i], phi[i], angles_out[i]);
        if(ikStates[i] != Leg::IKState::OK){
            ikFailed = true;
        }
    }

    if(ikFailed){
        Serial.println("Robot::doSimpleIK() ik failed");
        for(int i = 0; i < NUM_LEGS; i++){
            Leg::printAngles(angles_out[i]);
        }
        for(int i = 0; i < NUM_LEGS; i++){
            if(ikStates[i] == Leg::IKState::AngleLimitsError){
                Serial.println("[IKState-" + String(i) + "] AngleLimitsError");
            } else if(ikStates[i] == Leg::IKState::NoSolutionError){
                Serial.println("[IKState-" + String(i) + "] NoSolutionError");
            } else { 
                Serial.println("[IKState-" + String(i) + "] unhandled state");
            }
        }
        return false;
    }
    
    for(int i = 0; i < NUM_LEGS; i++){
        for(int j = 0; j < NUM_JOINTS; j++){
            legs[i].joints[j].setAngle(angles_out[i][j], seconds);
        }
    }

    return true;
    

}