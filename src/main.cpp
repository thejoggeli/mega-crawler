#include <Arduino.h>
#include "robot/Robot.h"
#include "utils/Benchmark.h"
#include "control/GaitControl.h"
#include "control/JoystickControl.h"
#include "motors/ServosManager.h"

Robot robot;

// GaitControl gaitControl(&robot);
// JoystickControl joystickControl(&robot);

void setup() {

    Serial.begin(115200);

    ServosManager::instance.init();

    robot.init();
    // gaitControl.init();
    // gaitControl.gaitSpeed = 1.0f/5.0f;
    // joystickControl.init();
    
    robot.start();
    // gaitControl.start();
    // joystickControl.start();

    // robot.legs[0].joints[1].setAngle(-45.0f*DEG_TO_RAD, 2.0f);

    // float T = 1.0f;
    // unsigned int T_ms = (unsigned int)(T*1.0e3);
    // float f = 0.25f;
    // for(float t = 0.0f; t < 100.0f; t += T){
    //     float a = sin(t*2.0f*PI*f) * 30.0f * DEG_TO_RAD;
    //     // float a = 30.0f * DEG_TO_RAD;
    //     for(int i = 0; i < 4; i++){
    //         robot.legs[i].joints[3].setAngle(a, T);
    //     }
    //     delay(T_ms);
    // }

    // for(int i = 0; i < NUM_LEGS; i++){
    //     robot.legs[i].joints[0].setAngle(45.0f*DEG_TO_RAD, 2.0f);
    //     robot.legs[i].joints[1].setAngle(-30.0f*DEG_TO_RAD, 2.0f);
    //     robot.legs[i].joints[2].setAngle(-30.0f*DEG_TO_RAD, 2.0f);
    //     robot.legs[i].joints[3].setAngle(-30.0f*DEG_TO_RAD, 2.0f);
    // }

    Vector3 Q[4];
    float phi[4];

    Q[0] = Vector3(0.25f, 0.0f, 0.0f).rotateAroundZ(-45.0f * DEG_TO_RAD);
    Q[1] = Vector3(0.25f, 0.0f, 0.0f).rotateAroundZ(-45.0f * DEG_TO_RAD + 90.0 * DEG_TO_RAD);
    Q[2] = Vector3(0.25f, 0.0f, 0.0f).rotateAroundZ(-45.0f * DEG_TO_RAD + 180.0 * DEG_TO_RAD);
    Q[3] = Vector3(0.25f, 0.0f, 0.0f).rotateAroundZ(-45.0f * DEG_TO_RAD + 270.0 * DEG_TO_RAD);
    phi[0] = 45.0f * DEG_TO_RAD;
    phi[1] = 45.0f * DEG_TO_RAD;
    phi[2] = 45.0f * DEG_TO_RAD;
    phi[3] = 45.0f * DEG_TO_RAD;
    robot.doSimpleIK(Q, phi, 5.0f);
    delay(3500);

    // float z1 = -0.05;
    // float z2 = -0.175;
    // int N = 4;

    // for(int i = 0; i < N; i++){

    //     float t = (float)(i)/(N-1.0f);

    //     Serial.println(t*(z2-z1)+z1);
    
    //     Q[0] = Vector3(0.15f, 0.0f, t*(z2-z1)+z1).rotateAroundZ(0.0f * DEG_TO_RAD);
    //     Q[1] = Vector3(0.15f, 0.0f, t*(z2-z1)+z1).rotateAroundZ(0.0f * DEG_TO_RAD + 90.0 * DEG_TO_RAD);
    //     Q[2] = Vector3(0.15f, 0.0f, t*(z2-z1)+z1).rotateAroundZ(0.0f * DEG_TO_RAD + 180.0 * DEG_TO_RAD);
    //     Q[3] = Vector3(0.15f, 0.0f, t*(z2-z1)+z1).rotateAroundZ(0.0f * DEG_TO_RAD + 270.0 * DEG_TO_RAD);
    //     phi[0] = 0.0f * DEG_TO_RAD;
    //     phi[1] = 0.0f * DEG_TO_RAD;
    //     phi[2] = 0.0f * DEG_TO_RAD;
    //     phi[3] = 0.0f * DEG_TO_RAD;
    //     robot.doSimpleIK(Q, phi, 1.0f);
    //     delay(2500);

    // }
    

    Q[0] = Vector3(0.15f, 0.0f, -0.05).rotateAroundZ(-45.0f * DEG_TO_RAD);
    Q[1] = Vector3(0.15f, 0.0f, -0.05).rotateAroundZ(-45.0f * DEG_TO_RAD + 90.0 * DEG_TO_RAD);
    Q[2] = Vector3(0.15f, 0.0f, -0.05).rotateAroundZ(-45.0f * DEG_TO_RAD + 180.0 * DEG_TO_RAD);
    Q[3] = Vector3(0.15f, 0.0f, -0.05).rotateAroundZ(-45.0f * DEG_TO_RAD + 270.0 * DEG_TO_RAD);
    phi[0] = 0.0f * DEG_TO_RAD;
    phi[1] = 0.0f * DEG_TO_RAD;
    phi[2] = 0.0f * DEG_TO_RAD;
    phi[3] = 0.0f * DEG_TO_RAD;
    robot.doSimpleIK(Q, phi, 1.0f);
    delay(2500);

    Q[0] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD);
    Q[1] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 90.0 * DEG_TO_RAD);
    Q[2] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 180.0 * DEG_TO_RAD);
    Q[3] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 270.0 * DEG_TO_RAD);
    phi[0] = 0.0f * DEG_TO_RAD;
    phi[1] = 0.0f * DEG_TO_RAD;
    phi[2] = 0.0f * DEG_TO_RAD;
    phi[3] = 0.0f * DEG_TO_RAD;
    robot.doSimpleIK(Q, phi, 2.5f);
    delay(2500);
    
    // Q[0] = Vector3(0.18f, 0.0f, -0.085).rotateAroundZ(135.0f * DEG_TO_RAD);
    // Q[1] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 90.0 * DEG_TO_RAD);
    // Q[2] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 180.0 * DEG_TO_RAD);
    // Q[3] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 270.0 * DEG_TO_RAD);
    // phi[0] = 0.0 * DEG_TO_RAD;
    // phi[1] = 0.0f * DEG_TO_RAD;
    // phi[2] = 0.0f * DEG_TO_RAD;
    // phi[3] = 0.0f * DEG_TO_RAD;
    // robot.doSimpleIK(Q, phi, 1.0f);
    // delay(3000);

    // for(int i = 1; i < 4; i++){
    //     robot.legs[2].joints[i].setAngle(0.0f, 1.0f);
    // }

    // while(true){

    //     float phi7 = 0.0f;
    //     float xy = 0.18f;
    //     float z = -0.105;
    //     float T = 0.5f;

    //     Q[0] = Vector3(xy, 0.0f, z).rotateAroundZ(135.0f * DEG_TO_RAD);
    //     Q[1] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 90.0 * DEG_TO_RAD);
    //     Q[2] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 180.0 * DEG_TO_RAD);
    //     Q[3] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 270.0 * DEG_TO_RAD);
    //     phi[0] = phi7 * DEG_TO_RAD;
    //     phi[1] = 0.0f * DEG_TO_RAD;
    //     phi[2] = 0.0f * DEG_TO_RAD;
    //     phi[3] = 0.0f * DEG_TO_RAD;
    //     robot.doSimpleIK(Q, phi, T);
    //     delay((unsigned int)(T*1000));

    //     Q[0] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD);
    //     Q[1] = Vector3(xy, 0.0f, z).rotateAroundZ(135.0f * DEG_TO_RAD + 90.0 * DEG_TO_RAD);
    //     Q[2] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 180.0 * DEG_TO_RAD);
    //     Q[3] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 270.0 * DEG_TO_RAD);
    //     phi[0] = 0.0f * DEG_TO_RAD;
    //     phi[1] = phi7 * DEG_TO_RAD;
    //     phi[2] = 0.0f * DEG_TO_RAD;
    //     phi[3] = 0.0f * DEG_TO_RAD;
    //     robot.doSimpleIK(Q, phi, T);
    //     delay((unsigned int)(T*1000));

    //     Q[0] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD);
    //     Q[1] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 90.0 * DEG_TO_RAD);
    //     Q[2] = Vector3(xy, 0.0f, z).rotateAroundZ(135.0f * DEG_TO_RAD + 180.0 * DEG_TO_RAD);
    //     Q[3] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 270.0 * DEG_TO_RAD);
    //     phi[0] = 0.0f * DEG_TO_RAD;
    //     phi[1] = 0.0f * DEG_TO_RAD;
    //     phi[2] = phi7 * DEG_TO_RAD;
    //     phi[3] = 0.0f * DEG_TO_RAD;
    //     robot.doSimpleIK(Q, phi, T);
    //     delay((unsigned int)(T*1000));

    //     Q[0] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD);
    //     Q[1] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 90.0 * DEG_TO_RAD);
    //     Q[2] = Vector3(0.15f, 0.0f, -0.175).rotateAroundZ(135.0f * DEG_TO_RAD + 180.0 * DEG_TO_RAD);
    //     Q[3] = Vector3(xy, 0.0f, z).rotateAroundZ(135.0f * DEG_TO_RAD + 270.0 * DEG_TO_RAD);
    //     phi[0] = 0.0f * DEG_TO_RAD;
    //     phi[1] = 0.0f * DEG_TO_RAD;
    //     phi[2] = 0.0f * DEG_TO_RAD;
    //     phi[3] = phi7 * DEG_TO_RAD;
    //     robot.doSimpleIK(Q, phi, T);
    //     delay((unsigned int)(T*1000));
        
    // }

    while(true){
        delay(0xFFFF);
    }

}

void ikTest(){
     
    Serial.println(String("L0: ") + String(robot.legs[0].joints[0].length, 3));
    Serial.println(String("L1: ") + String(robot.legs[0].joints[1].length, 3));
    Serial.println(String("L2: ") + String(robot.legs[0].joints[2].length, 3));
    Serial.println(String("L3: ") + String(robot.legs[0].joints[3].length, 3));

    float qx = 0.265;
    float qy = 0.0f;
    float qz = -0.033;
    Vector3 Q = Vector3(qx, qy, qz);
    float phi = 45.0f * (1.0/180.0f) * PI;

    // float qx = 0.265;
    // float qy = 0.0f;
    // float qz = -0.033 + 0.105*(1.0/1.414)*2.0;
    // Vector3 Q = Vector3(qx, qy, qz);
    // float phi = 135.0f / 180.0f * PI;
    
    float angles_out[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    Benchmark::tick();
    Leg::IKState ikState = robot.legs[0].ik(Q, phi, angles_out);
    Benchmark::tock("ik computation time");

    if(ikState == Leg::IKState::AngleLimitsError){
        Serial.println("Leg::IKState::AngleLimitsError");
        Leg::printAngles(angles_out);
    } else if(ikState == Leg::IKState::NoSolutionError){
        Serial.println("Leg::IKState::NoSolutionError");
    } else if(ikState == Leg::IKState::OK){
        Serial.println("Leg::IKState::OK");
        Leg::printAngles(angles_out);
    } else {
        Serial.println("unhandled Leg::IKState");
    }

}

void loop() {

    // ikTest();
    // delay(1000);
    
    const unsigned int fps = 30;
    const unsigned long frame_duration_us = (unsigned long)((1.0/(double)fps)*1.0e6);
    unsigned long t_start_us = micros();

    // // Benchmark::tick();
    // gaitControl.update();
    // // Benchmark::tock("gaitControl.update() duration: ");

    // // Benchmark::tick();
    // joystickControl.update();
    // // Benchmark::tock("joystickControl.update() duration: ");

    float used = ((double)(micros() - t_start_us) * 1.0e-6) / (double)(frame_duration_us * 1.0e-6) * 100.0;
    Serial.println("frame capacity used (%): " + String(used, 3));

    unsigned long t_duration_us = micros() - t_start_us;
    unsigned long t_delay_us = frame_duration_us - t_duration_us;
    if(t_delay_us > 0){
        // delayMicroseconds(t_delay_us);
        delay(t_delay_us/1000);
    }
    
}